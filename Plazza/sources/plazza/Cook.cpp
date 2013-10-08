//
// Cook.cpp for cook in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Wed Apr 13 22:26:25 2011 soufien benramdhane
// Last update Wed Apr 13 22:47:39 2011 soufien benramdhane
//

#include			"Kitchen.hh"

Kitchen::Cook::Cook(Kitchen *kitchen) :
  _kitchen(kitchen)
{
}

Kitchen::Cook::~Cook()
{
}


/*****************************************************************/

Kitchen::Kitchen		*Kitchen::Cook::getKitchen(void) const
{
  return (this->_kitchen);
}

void				Kitchen::Cook::setPizza(int serial)
{
  this->_serial = serial;
}

int				Kitchen::Cook::getPizza(void) const
{
  return (this->_serial);
}
