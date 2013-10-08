//
// CoreFood.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 16:05:59 2011 chanh allaux
// Last update Sun Mar 20 18:24:06 2011 soufien benramdhane
//

#include		<cstdlib>
#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

// delete the extra food if it's time for
void			snake::Core::resetFood(void)
{
  ++this->_cptBonus;
  if (this->_cptBonus == 70)
    this->_grid->setPoint(this->_bonus->getX(), this->_bonus->getY(), KeyGame::ELEM0);
  ++this->_cptMalus;
  if (this->_cptMalus == 70)
    this->_grid->setPoint(this->_malus->getX(), this->_malus->getY(), KeyGame::ELEM0);
}

// check if it's time for bonus/malus food
void			snake::Core::otherFood(void)
{
  if (this->_score % 100 == 0)
    {
      this->_cptBonus = 0;
      this->popFood(KeyGame::ELEM3, this->_bonus);
    }
  if (this->_score % 150 == 0)
    {
      this->_cptMalus = 0;
      this->popFood(KeyGame::ELEM4, this->_malus);
    }
}

// generate a random apple on the map
int			snake::Core::popFood(KeyGame::eType key, Point* set)
{
  int			i = 0;
  size_t		x;
  size_t		y;

  do {
    if (i++ > 500000)
      return (-1);
    x = rand() % this->_grid->getSizeX();
    y = rand() % this->_grid->getSizeY();
  } while (this->_grid->getPoint(x, y) != KeyGame::ELEM0);
  this->_grid->setPoint(x, y, key);
  if (set)
    set->setPosition(x, y);
  return (0);
}
