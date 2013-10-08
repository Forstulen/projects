//
// Kitchen.cpp for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/plazza
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Fri Apr  8 17:46:42 2011 soufien benramdhane
// Last update Sun Apr 17 22:06:55 2011 romain tholimet
//

#include		<cstdlib>
#include		<sstream>
#include		<errno.h>

#include		"Pizza.hh"
#include		"Reception.hh"
#include		"Serializer.hh"
#include		"Kitchen.hh"

Kitchen::Kitchen::Kitchen(size_t pid, size_t coefTime, size_t nbrCook, size_t popFood, NamedPipe *pipe) :
  _nbPizza(0), _coefTime(coefTime), _nbrCook(nbrCook), _popFood(popFood), _pipeOutput(pipe), _stock(popFood)
{
  size_t		count = 0;
  std::string		name;
  std::stringstream	ss;

  while (count < nbrCook)
    {
      this->_cook.push_back(new Cook(this));
      ++count;
    }
  this->_pid = pid;
  ss << "Cuisine_" << pid;
  ss >> name;
  this->_pipeInput = new NamedPipe(name);
  this->_name = name;
}

Kitchen::Kitchen::~Kitchen()
{
  size_t		count = 0;

  while (count < this->_nbrCook)
    {
      (this->_cook[count])->Cancel();
      delete this->_cook[count];
      ++count;
    }
  delete (this->_pipeInput);
}

/*****************************************************************/

void			Kitchen::Kitchen::startCooking(void)
{
  Thread::Thread	kitchen;
  Thread::Thread	delivery;

  try
    {
      kitchen.Create(&dispatchPizza, this);
      delivery.Create(&doRefill, &this->_stock);
      this->executeOrder();
    }
  catch (const exceptionPlazza::systemError & e)
    {
      std::cerr << e.getMessage() << std::endl;
      this->youAreDead();
      exit(EXIT_FAILURE);
    }
}

int			Kitchen::Kitchen::typeCommand(int serial) const
{
  return (serial >> 24);
}

void			Kitchen::Kitchen::sendInfo(void) const
{
  u_infoSerial		serial;
  int			type = 1;
  int			count = 2;

  serial.info[0] = 0;
  serial.info[1] = this->getCookSleeping();
  while (type != MAX)
    {
      serial.info[count++] = type;
      serial.info[count++] = this->_stock.getNumberOf(static_cast<Pizza::Ingredient>(1 << (type - 1)));
      ++type;
    }
  serial.info[count++] = PIZZAS;
  serial.info[count++] = this->_nbPizza;
  type = Reception::REFRESH;
  type <<= 24;
  type |= this->_pid;
  this->_pipeOutput->send(type, serial);
}

void			Kitchen::Kitchen::typeManagement(int serial)
{
  int			type;

  type = this->typeCommand(serial);
  if (type == Reception::PIZZA)
    {
      this->_nbPizza += 1;
      this->_queuePizza.push(serial);
      this->_condKitchen.signal();
    }
  else if (type == Reception::REFRESH)
    this->sendInfo();
}

void			Kitchen::Kitchen::receiveCommand(void)
{
  int			serial;

  while (!this->_queuePizza.isFinished())
    {
      serial = this->_pipeInput->receive();
      this->typeManagement(serial);
    }
}

void			Kitchen::Kitchen::iAmDead(void)
{
  int			serial;

  serial = Reception::DEAD;
  this->_pipeOutput->send((serial << 24) | this->_pid);
}

void			Kitchen::Kitchen::executeOrder(void)
{
  Cook			*cook;

  while (!this->_queuePizza.isFinished() || this->_nbPizza)
    {
      if (!this->_queuePizza.isFinished() && !this->_queuePizza.empty())
	{
	  cook = this->getCook();
	  cook->setPizza(this->_queuePizza.pop());
	  cook->Create(&doPizza, cook);
	}
      else if (!this->_queuePizza.isFinished() && !this->_nbPizza
	       && (this->_condKitchen.timedwait(5000) == ETIMEDOUT))
	break ;
    }
  this->iAmDead();
}

void			Kitchen::Kitchen::packPizza(int serial)
{
  Pizza::Pizza		*pizza = Serializer::unpack(serial);
  size_t		ingredient = pizza->getIngredient();
  size_t		packIngredient = 0;
  size_t		ingredientChoosen = 1;

  while (ingredient != packIngredient)
    {
      if ((ingredient & ingredientChoosen) == ingredientChoosen)
	{
	  if (this->_stock.pickUp(static_cast<Pizza::Ingredient>(ingredientChoosen)))
	    {
	      packIngredient |= ingredientChoosen;
	      ingredientChoosen <<= 1;
	    }
	  else
	    usleep(this->_popFood);
	}
      else
	ingredientChoosen <<= 1;
    }
  usleep(pizza->getTimeCooking() * this->_coefTime);
  delete pizza;
  this->_pipeOutput->send(serial);
  this->decremPizza();
  this->_condCook.signal();
}

/*****************************************************************/

void			Kitchen::Kitchen::decremPizza(void)
{
  this->_mutex.lock();
  this->_nbPizza -= 1;
  this->_mutex.unlock();
}

/******************************************************************/

Kitchen::Stock const &	       Kitchen::Kitchen::getStock(void) const
{
  return (this->_stock);
}

Kitchen::Cook			*Kitchen::Kitchen::getCook()
{
  Cook				*cook;

  cook = this->getFreeCook();
  if (!cook)
    {
      this->_condCook.wait();
      return (this->getCook());
    }
  return (cook);
}

Kitchen::Cook			*Kitchen::Kitchen::getFreeCook(void) const
{
  size_t			count = 0;

  while (count < this->_nbrCook)
    {
      if (this->_cook[count]->getStatus() == Thread::SLEEPING)
	  return (this->_cook[count]);
      ++count;
    }
  return (NULL);
}

/*****************************************************************/

size_t			Kitchen::Kitchen::getPid() const
{
  return (this->_pid);
}

size_t			Kitchen::Kitchen::getNbPizza(void) const
{
  return (this->_nbPizza);
}

NamedPipe		*Kitchen::Kitchen::getNamedPipe(void) const
{
  return (this->_pipeInput);
}

size_t			Kitchen::Kitchen::getIngredient(Pizza::Ingredient ingredient) const
{
  size_t		ret;

  ret = this->_stock.getNumberOf(ingredient);
  return (ret);
}

size_t			Kitchen::Kitchen::getCookSleeping() const
{
  std::vector<Cook*>::const_iterator	it = this->_cook.begin();
  size_t		nbr = 0;

  for(; it != this->_cook.end(); ++it)
    if ((*it)->getStatus() == Thread::SLEEPING)
      ++nbr;
  return (nbr);
}

size_t			Kitchen::Kitchen::getSleeping() const
{
  return (this->_sleepingCook);
}

std::string const	&Kitchen::Kitchen::getName() const
{
  return (this->_name);
}

size_t			Kitchen::Kitchen::getTotalCook() const
{
  return (this->_nbrCook);
}

/*****************************************************************/

void			Kitchen::Kitchen::setNumberOf(Pizza::Ingredient ingredient, int nbr)
{
  this->_stock.setNumberOf(ingredient, nbr);
}

void			Kitchen::Kitchen::setCookSleeping(int nbr)
{
  this->_sleepingCook = nbr;
}

void			Kitchen::Kitchen::setNbPizza(int nbr)
{
  this->_nbPizza = nbr;
}

/*****************************************************************/

void			*Kitchen::doPizza(void *arg)
{
  Cook			*cook = reinterpret_cast<Cook *>(arg);

  cook->setStatus(Thread::RUNNING);
  cook->getKitchen()->packPizza(cook->getPizza());
  cook->setStatus(Thread::SLEEPING);
  return (NULL);
}

void			Kitchen::Kitchen::youAreDead(void)
{ 
  int			serial;

  serial = Reception::THROW;
  this->_pipeOutput->send((serial << 24) | this->_pid);
}

void			*Kitchen::dispatchPizza(void *arg)
{
  Kitchen::Kitchen	*kitchen = reinterpret_cast<Kitchen::Kitchen *>(arg);

  try
    {
      kitchen->receiveCommand();
    }
  catch (const exceptionPlazza::systemError & e)
    {
      std::cerr << e.getMessage() << std::endl;
      kitchen->youAreDead();
      exit(EXIT_FAILURE);
    }
  return (NULL);
}
