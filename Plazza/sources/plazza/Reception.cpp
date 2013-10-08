//
// Reception.cpp for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/sources
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Mon Apr 11 16:11:01 2011 chanh allaux
// Last update Sun Apr 17 22:59:42 2011 chanh allaux
//

#include		<fstream>
#include		<cstdlib>
#include		<iomanip>
#include		<unistd.h>
#include		<sys/types.h>
#include		<algorithm>
#include		"Pizza.hh"
#include		"Serializer.hh"
#include		"Waiter.hh"
#include		"Reception.hh"
#include		"Kitchen.hh"
#include		"Serializer.hh"
#include		"Fork.hh"
#include		"ScopedLock.hpp"
#include		"ILibrary.hh"

Reception::Reception::Reception(size_t coefCook, size_t nbrCook, size_t timePopFood, ILibrary* lib)
  : _coefCook(coefCook), _nbrCook(nbrCook), _timePopFood(timePopFood), _pipeInput(NULL), _flag(true), _lib(lib), _updPizza(NULL)
{
  try
    {
      this->_updPizza = new CondVar(&this->_update);
      this->_pipeInput = new NamedPipe("Reception");
      this->_threadForPizza.Create(&receivePizza, this);
      this->_logFile.open("plazza.log", std::fstream::in | std::fstream::out | std::fstream::app);
      if (!this->_logFile.is_open())
	std::cerr << "Error: Log : Can't create log file." << std::endl;
    }
  catch (const exceptionPlazza::systemError& e)
    {
      std::cerr << e.getMessage() << std::endl;
      throw ;
    }
}

Reception::Reception::~Reception()
{
  if (this->_pipeInput)
    delete (this->_pipeInput);
  if (this->_updPizza)
    delete (this->_updPizza);
  for (std::vector<Kitchen::Kitchen *>::iterator it = this->_kitchens.begin();
       it != this->_kitchens.end(); ++it)
    delete (*it);
  if (this->_logFile.is_open())
    this->_logFile.close();
}

void			Reception::Reception::sendPizzaToKitchen(Kitchen::Kitchen* kitchen, const Pizza::Pizza *pizza)
{
  NamedPipe		*pipeToKitchen;

  pipeToKitchen = kitchen->getNamedPipe();
  pipeToKitchen->send(Serializer::pack(*pizza));
}

void			Reception::Reception::openKitchen(const Pizza::Pizza* pizza)
{
  std::ostringstream	oss;
  static size_t		i = 0;
  Kitchen::Kitchen	*kitchen = new Kitchen::Kitchen(i++, this->_coefCook, this->_nbrCook, this->_timePopFood, this->_pipeInput);
  int			pid;

  try
    {
      pid = Fork::_fork();
      if (pid == 0)
	{
	  if (kitchen)
	    kitchen->startCooking();
	  exit(EXIT_SUCCESS);
	}
      oss << "KITCHEN NUMBER " << i - 1 << " OPENED";
      this->log(oss.str());
      this->_kitchens.push_back(kitchen);
      this->sendPizzaToKitchen(kitchen, pizza);
    }
  catch (const exceptionPlazza::systemError& e)
    {
      std::cerr << e.getMessage() << std::endl;
      throw;
    }
}

void			Reception::Reception::updateNbPizza(const Kitchen::Kitchen* kitchen)
{
  int			serial;

  serial = REFRESH;
  serial <<= 24;
  if (kitchen)
    (kitchen->getNamedPipe())->send(serial);
}

void			Reception::Reception::repartPizza(const Pizza::Pizza* pizza)
{
  std::vector<Kitchen::Kitchen *>::iterator	kitchen_less_full;
  std::vector<Kitchen::Kitchen *>::iterator	it = this->_kitchens.begin();
  size_t					nbPizza = std::string::npos;
  size_t					nbTmp;

  for (; it != this->_kitchens.end(); ++it)
    {
      this->updateNbPizza(*it);
      usleep(100);
      if ((*it) && (((nbTmp = (*it)->getNbPizza()) < nbPizza || nbPizza == std::string::npos)
	   && nbTmp < this->_nbrCook * 2))
	{
	  nbPizza = nbTmp;
	  kitchen_less_full = it;
	}
    }
  if (nbPizza != std::string::npos)
    this->sendPizzaToKitchen(*kitchen_less_full, pizza);
  else
    this->openKitchen(pizza);
}

void			Reception::Reception::log(std::string const & str)
{
  this->_lib->log(str, this->_logFile);
}

void			Reception::Reception::log(const Pizza::Pizza* pizza, std::string const & str)
{
  std::ostringstream	ss;
  std::map<const std::string, Pizza::TypePizza>::iterator	it_type;
  std::map<const std::string, Pizza::TaillePizza>::iterator	it_taille;

  it_type = Waiter::pizzaType.begin();
  for (; it_type != Waiter::pizzaType.end(); ++it_type)
    {
      if ((*it_type).second == pizza->getType())
	{
	  ss << (*it_type).first;
	  break ;
	}
    }
  ss << " ";
  it_taille = Waiter::pizzaSize.begin();
  for (; it_taille != Waiter::pizzaSize.end(); ++it_taille)
    {
      if ((*it_taille).second == pizza->getSize())
	{
	  ss << (*it_taille).first;
	  break ;
	}
    }
  ss << " " << str;
  this->_lib->log(ss.str(), this->_logFile);
}

void			Reception::Reception::repartPizzaList(std::vector<const Pizza::Pizza*> *pizzaList)
{
  std::vector<const Pizza::Pizza*>::const_iterator	it = pizzaList->begin();

  for (; it != pizzaList->end(); ++it)
    {
      this->log(*it, "ORDERED");
	this->repartPizza(*it);
    }
}

void			Reception::Reception::receiveCommand(std::string const & str)
{
  std::vector<const Pizza::Pizza*>	*pizzaList;

  pizzaList = Waiter::takeCommand(str);
  this->repartPizzaList(pizzaList);
  if (pizzaList)
    {
      for (std::vector<const Pizza::Pizza*>::iterator it = pizzaList->begin(); it != pizzaList->end(); ++it)
	delete *it;
      delete (pizzaList);
    }
}

/**********************************************************************/

bool			Reception::Reception::getFlag(void) const
{
  return (this->_flag);
}

NamedPipe		*Reception::Reception::getPipe(void) const
{
  return (this->_pipeInput);
}

std::vector<Kitchen::Kitchen *> const &	Reception::Reception::getKitchenList(void)
{
  ScopedLock		lock(&this->_mutex);

  return (this->_kitchens);
}

/**********************************************************************/

void*			Reception::receivePizza(void* arg)
{
  Reception*		reception = reinterpret_cast<Reception*>(arg);
  int			serial;
  Pizza::Pizza*		pizza;

  while (reception->getFlag() == true)
    {
      try
	{
	  serial = reception->getPipe()->receive();
	  if (reception->checkInformations(serial) == 1)
	    {
	      pizza = Serializer::unpack(serial);
	      reception->log(pizza, "READY");
	      if (pizza)
		delete (pizza);
	    }
	}
      catch (const exceptionPlazza::systemError& e)
	{
	  std::cerr << e.getMessage() << std::endl;
	  throw;
	}
    }
  return (NULL);
}

int			Reception::Reception::updateKitchen(int serial)
{
  Kitchen::u_infoSerial	data;
  Kitchen::Kitchen*	kitchen = NULL;
  unsigned int		numKitchen;
  int			type = 1;
  int			count = 2;
  int			number;

  numKitchen = serial & 0x00FFFFFF;
  for (std::vector<Kitchen::Kitchen *>::iterator it = this->_kitchens.begin();
       it != this->_kitchens.end(); ++it)
    if ((*it)->getPid() == numKitchen)
      {
	kitchen = *it;
	break ;
      }
  if (kitchen)
    {
      try
	{
	  this->_pipeInput->receive(data);
	}
      catch (const exceptionPlazza::systemError& e)
	{
	  std::cerr << e.getMessage() << std::endl;
	  throw ;
	}
	  kitchen->setCookSleeping(data.info[1]);
      while (type != Kitchen::MAX)
	{
	  ++count;
	  number = data.info[count++];
	  kitchen->setNumberOf(static_cast<Pizza::Ingredient>(1 << (type - 1)), number);
	  ++type;
	}
      ++count;
      kitchen->setNbPizza(data.info[count++]);
    }
  this->_updPizza->broadcast();
  return (0);
}

void			Reception::Reception::workFinished()
{
  if (!this->_kitchens.size())
    this->log("MY WORK IS FINISHED, I'M GONNA WAIT");
}

int			Reception::Reception::killKitchen(int serial)
{
  std::ostringstream	oss;
  unsigned int		numKitchen;

  numKitchen = serial & 0x00FFFFFF;
  oss << "KITCHEN NUMBER " << numKitchen << " CLOSED";
  this->log(oss.str());
  for (std::vector<Kitchen::Kitchen *>::iterator it = this->_kitchens.begin();
       it != this->_kitchens.end();)
    if ((*it)->getPid() == numKitchen)
      {
	delete (*it);
	*it = NULL;
	it = this->_kitchens.erase(it);
      }
    else
      ++it;
  this->workFinished();
  return (0);
}

void			Reception::Reception::killReception(int serial)
{
  int			option = serial >> 24;

  try
    {
      if ((option & THROW) == THROW)
	throw exceptionPlazza::systemError(exceptionPlazza::KITCHERR);
    }
  catch (const exceptionPlazza::systemError& e)
    {
      std::cerr << e.getMessage() << std::endl;
      throw;
    }
}

int			Reception::Reception::checkInformations(int serial)
{
  int			value = 1;
  int			option = serial >> 24;

  this->killReception(serial);
  if ((option & REFRESH) == REFRESH)
    value = this->updateKitchen(serial);
  else if ((option & DEAD) == DEAD)
    value = killKitchen(serial);
  return (value);
}
