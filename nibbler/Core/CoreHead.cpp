//
// CoreHead.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 16:12:09 2011 chanh allaux
// Last update Sun Mar 20 17:19:15 2011 chanh allaux
//

#include		<cstdlib>
#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

// Permit to get the direction in x and y, and get the enum for the new sprites
void			snake::Core::getDirection(int & newX, int & newY,
						  KeyGame::eType & headPix,
						  KeyGame::eType & beforePix,
						  KeyGame::eKeyCode keyCode)
{
  switch (keyCode)
    {
    case KeyGame::UP:
      newY -= 1;
      headPix = KeyGame::ELEM9;
      beforePix = KeyGame::ELEM5;
      break ;
    case KeyGame::DOWN:
      newY += 1;
      headPix = KeyGame::ELEM10;
      beforePix = KeyGame::ELEM6;
      break ;
    case KeyGame::RIGHT:
      newX += 1;
      headPix = KeyGame::ELEM11;
      beforePix = KeyGame::ELEM7;
      break ;
    case KeyGame::LEFT:
      newX -= 1;
      headPix = KeyGame::ELEM12;
      beforePix = KeyGame::ELEM8;
      break ;
    }
}

// grow youre snake if you eat an apple, update score, set the new head position
int			snake::Core::grow(int newX, int newY,
					  size_t x, size_t y,
					  Point* head, Point* tail)
{
  int			ret = 0;

  if (this->_grid->getPoint(newX, newY) == KeyGame::ELEM2)
    {
      this->_score += 10;
      if (this->popFood(KeyGame::ELEM2, NULL) == -1)
	return (-1);
      ret = 1;
      this->_grow += (rand() % 3) + 1;
      this->otherFood();
    }
  else if (this->_grid->getPoint(newX, newY) == KeyGame::ELEM3)
    {
      this->_score += 20;
      this->_cptBonus = 71;
      this->_grow += (rand() % 4) + 2;
      ret = 2;
    }
  else if (this->_grid->getPoint(newX, newY) == KeyGame::ELEM4)
    {
      this->_score -= 50;
      this->_cptMalus = 71;
      this->_grow += (rand() % 5) + 5;
      this->_reverse = 71;
      ret = 3;
    }
  if (this->_grid->getPoint(newX, newY) == KeyGame::ELEM0 && this->_grow == 0)
    this->moveTail(tail);
  if (ret == 1)
    this->_hasBeenUpdate = false;
  head->setPosition(newX, newY);
  return (ret);
}
