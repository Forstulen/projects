//
// CoreSnake.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Mar 19 12:54:07 2011 chanh allaux
// Last update Sat Mar 19 17:05:36 2011 chanh allaux
//

#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

// set the snake position (niddle of the screen rightward
void			snake::Core::initSnakePosition(size_t & sx, size_t & sy)
{
  sx = (this->_grid->getSizeX() / 2) - 2;
  sy = (this->_grid->getSizeY() / 2);
}

// set the sprite of the snake
void			snake::Core::drawSnakePosition(size_t sx, size_t sy)
{
  this->_snake->getTail()->setPosition(sx, sy);
  this->_snake->getHead()->setPosition(sx + 3, sy);
  for (int i = 1; i < 3; ++i)
    this->_grid->setPoint(sx + i, sy, KeyGame::ELEM7);
  this->_grid->setPoint(sx, sy, KeyGame::ELEM15);
  this->_grid->setPoint(sx + 3, sy, KeyGame::ELEM11);
}

// check the option and do the coffee
void			snake::Core::drawWall(void)
{
  if (this->_option->getO() == true)
    this->_grid->randomWall();
  if (this->_option->getW() == false)
    this->_grid->roundWall();
}
