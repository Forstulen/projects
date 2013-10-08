//
// Core.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 13:55:19 2011 chanh allaux
// Last update Sun Mar 20 17:26:48 2011 chanh allaux
//

#include		<sstream>
#include		<string>
#include		<cstdlib>
#include		<iostream>
#include		"ALibrary.hh"
#include		"Point.hh"
#include		"Core.hh"
#include		"EKey.hh"

snake::Core::Core(size_t x, size_t y, Option* opt, ALibrary* lib)
  : _snake(new Snake),
    _bonus(new Point), _malus(new Point),
    _cptBonus(71), _cptMalus(71),
    _grow(0), _hasBeenUpdate(true),
    _boost(0), _reverse(0)
{
  // map to check if youre not going backward
  this->_none[KeyGame::ELEM9] = KeyGame::UP;
  this->_none[KeyGame::ELEM10] = KeyGame::DOWN;
  this->_none[KeyGame::ELEM11] = KeyGame::RIGHT;
  this->_none[KeyGame::ELEM12] = KeyGame::LEFT;

  this->initAttributes(x, y, opt, lib);

  // init data and ... sound
  this->initDescription();
  this->initData();
  this->initSound();
  this->openBest();
}

snake::Core::~Core()
{
  if (this->_snake)
    delete (this->_snake);
  if (this->_bonus)
    delete (this->_bonus);
  if (this->_malus)
    delete (this->_malus);
}

// set the inherited attributes
void			snake::Core::initAttributes(size_t x, size_t y, Option* opt, ALibrary* lib)
{
  this->_realmsec = this->_msec = 200;
  this->_name = "snake/";
  this->_score = 0;
  this->_bestScore = 0;
  this->_title = "Nibbler";
  this->_grid = new Grid(x, y);
  this->_option = opt;
  this->_lib = lib;
  if (this->_option->getH())
    this->_realmsec = this->_msec = 50;
}

void			snake::Core::initData(void)
{
  size_t		sx, sy;

  this->initSnakePosition(sx, sy);
  this->drawSnakePosition(sx, sy);
  this->drawWall();
  this->popFood(KeyGame::ELEM2, NULL);
}

void			snake::Core::restartGame(void)
{
  int			sizeX = this->_grid->getSizeX();
  int			sizeY = this->_grid->getSizeY();

  this->_cptMalus = 71;
  this->_cptBonus = 71;
  this->_grow = 0;
  this->_hasBeenUpdate = true;
  this->_score = 0;
  this->_boost = 0;
  this->_realmsec = this->_msec = 200;
  delete this->_grid;
  delete this->_snake;
  this->_grid = new Grid(sizeX - 2, sizeY - 2);
  this->_snake = new Snake;
  this->initData();
  this->openBest();
  if (this->_option->getH())
    this->_realmsec = this->_msec = 50;
}

int			snake::Core::move(KeyGame::eKeyCode keyCode)
{
  size_t		x, y;
  int			newX, newY;
  KeyGame::eType	headPix, beforePix;
  int			ret = 0;

  newX = x = this->_snake->getHead()->getX();
  newY = y = this->_snake->getHead()->getY();

  this->poison(keyCode, x, y);
  this->updateBoost(keyCode);
  this->reverseKeyCode(keyCode, x, y);
  this->getDirection(newX, newY, headPix, beforePix, keyCode);
  this->noWallMove(newX, newY);

  if (this->die(newX, newY) == -1)
    return (-1);

  this->updateSpeed();
  this->playSound((ret = this->grow(newX, newY, x, y, this->_snake->getHead(), this->_snake->getTail())));

  this->updateSprite(x, y, headPix, beforePix);
  this->resetFood();
  this->updateGrowBoost();

  return (ret);
}
