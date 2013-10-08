//
// Stock.cpp for Stock in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/plazza
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Apr  9 15:02:39 2011 soufien benramdhane
// Last update Sun Apr 17 22:49:35 2011 romain tholimet
//

#include		<sys/types.h>
#include		<unistd.h>
#include		<cstdlib>

#include		"systemError.hh"
#include		"ScopedLock.hpp"
#include		"Kitchen.hh"
#include		"CondVar.hpp"
#include		"Thread.hh"

Kitchen::Stock::Stock(size_t repop) :
  _kindOfIngredient(0),
  _popFood(repop)
{
  size_t		count = 1;

  while (count <= Pizza::Amour)
    {
      this->_kindOfIngredient |= count;
      this->_stock[count] = 5;
      count <<= 1;
    }
}

Kitchen::Stock::~Stock()
{
}

/************************************************************/

bool				Kitchen::Stock::pickUp(Pizza::Ingredient ingredient)
{
  ScopedLock			lock(&(this->_mutex));
  size_t			cmp;

  cmp = ingredient;
  if ((this->_kindOfIngredient & cmp) != cmp)
    throw (exceptionPlazza::systemError(exceptionPlazza::BADING));
  if (this->_stock[ingredient] > 0)
    {
      this->_stock[ingredient] -= 1;
      return (true);
    }
  return (false);
}

void				Kitchen::Stock::refill(void)
{
  while (1)
    {
      this->_mutex.lock();
      for (std::map<size_t, size_t>::iterator it = this->_stock.begin(); it != this->_stock.end(); ++it)
	(*it).second += 1;
      this->_mutex.unlock();
      usleep(this->_popFood * 1000);
    }
}

/*********************************************************************/

size_t				Kitchen::Stock::getNumberOf(Pizza::Ingredient ingredient) const
{
  size_t			cmp;

  cmp = ingredient;
  if ((this->_kindOfIngredient & cmp) != cmp)
    throw (exceptionPlazza::systemError(exceptionPlazza::BADING));
  return ((*(this->_stock.find(cmp))).second);
}

void*				Kitchen::doRefill(void *arg)
{
  Stock*			stock = reinterpret_cast<Stock*>(arg);

  try
    {
      stock->refill();
    }
  catch (const exceptionPlazza::systemError & e)
    {
      std::cerr << e.getMessage() << std::endl;
      exit(EXIT_FAILURE);
    }
  return (NULL);
}

/**********************************************************************/

void				Kitchen::Stock::setNumberOf(Pizza::Ingredient ingredient, int nbr)
{
  size_t			cmp;

  cmp = ingredient;
  if ((this->_kindOfIngredient & cmp) != cmp)
    throw (exceptionPlazza::systemError(exceptionPlazza::BADING));
  (*(this->_stock.find(cmp))).second = nbr;
}
