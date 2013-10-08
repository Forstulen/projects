//
// CoreTail.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 16:09:28 2011 chanh allaux
// Last update Fri Mar 18 16:09:50 2011 chanh allaux
//

#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

// get the tail direction
void			snake::Core::getTailDirection(Point* tail, size_t & x, size_t & y)
{
  switch (this->_grid->getPoint(tail->getX(), tail->getY()))
    {
    case KeyGame::ELEM13:
      tail->setY(y - 1);
      break ;
    case KeyGame::ELEM14:
      tail->setY(y + 1);
      break ;
    case KeyGame::ELEM15:
      tail->setX(x + 1);
      break ;
    case KeyGame::ELEM16:
      tail->setX(x - 1);
      break ;
    }
}

// get the new tail image
void			snake::Core::getTailPixmap(Point* tail, KeyGame::eType & tailPix)
{
  switch (this->_grid->getPoint(tail->getX(), tail->getY()))
    {
    case KeyGame::ELEM5:
      tailPix = KeyGame::ELEM13;
      break ;
    case KeyGame::ELEM6:
      tailPix = KeyGame::ELEM14;
      break ;
    case KeyGame::ELEM7:
      tailPix = KeyGame::ELEM15;
      break ;
    case KeyGame::ELEM8:
      tailPix = KeyGame::ELEM16;
      break ;
    }
}

// move the tail position and erase the last element
void			snake::Core::moveTail(Point* tail)
{
  size_t		x, y;
  KeyGame::eType	tailPix;

  x = tail->getX();
  y = tail->getY();

  this->getTailDirection(tail, x, y);

  // check if youre going off the wall
  if ((int)tail->getX() < 0)
    tail->setX(this->_grid->getSizeX() - 1);
  else if ((int)tail->getY() < 0)
    tail->setY(this->_grid->getSizeY() - 1);
  else if (tail->getX() > this->_grid->getSizeX() - 1)
    tail->setX(0);
  else if (tail->getY() > this->_grid->getSizeY() - 1)
    tail->setY(0);

  this->getTailPixmap(tail, tailPix);

  this->_grid->setPoint(x, y, KeyGame::ELEM0);
  this->_grid->setPoint(tail->getX(), tail->getY(), tailPix);
}
