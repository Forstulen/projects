//
// MinesweeperCore.cpp for MineSweeper in /home/tholim_r//nibbler-2014-benram_s
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Wed Mar 16 20:38:37 2011 romain tholimet
// Last update Sun Mar 20 17:09:11 2011 romain tholimet
//

#include		<cstdlib>
#include		<iostream>
#include		"MinesweeperCore.hh"

minesweeper::Core::Core(size_t x, size_t y, Option * option, ALibrary * lib)
  :_data(new Grid(x - 2, y - 2)),
   _cursorX((x - 2) / 2),
   _cursorY((y - 2) / 2),
   _gameover(false),
   _difficulty((x * y) / 10)
{
  // set the inherited attributes
  this->_msec = 10;
  this->_lib = lib;
  this->_name = "minesweeper/";
  this->_bestScore = 0;
  this->_score = 0;
  this->_title = "MineSweeper";
  this->_grid = new Grid(x - 2, y - 2);
  this->_option = option;
  if (this->_option->getH())
    this->_difficulty = (x * y) / 5;
  this->_grid->setPoint(this->_cursorX, this->_cursorY, this->_grid->getPoint(this->_cursorX, this->_cursorY) + 10);

  //Init game
  this->openBest();
  this->fillGrid(x, y);
  this->initDescription();
}

minesweeper::Core::~Core()
{
  if (this->_data)
    delete this->_data;
}

void		minesweeper::Core::showGrid(int x, int y)
{
  size_t	maxX = this->_data->getSizeX();
  size_t	maxY = this->_data->getSizeY();

  this->_grid->setPoint(x, y, this->_data->getPoint(x, y));
  if (this->_data->getPoint(x, y) == KeyGame::ELEM0)
    {
      this->_grid->setPoint(x, y, KeyGame::ELEM9);
      this->_data->setPoint(x, y, KeyGame::ELEM9);
      if (y - 1 >= 0 && x - 1 >= 0)
	this->showGrid(x - 1, y - 1);
      if (y - 1 >= 0)
        this->showGrid(x, y - 1);
      if (x + 1 < maxX && y - 1 >= 0)
        this->showGrid(x + 1, y - 1);
      if (x + 1 < maxX)
        this->showGrid(x + 1, y);
      if (x + 1 < maxX && y + 1 < maxY)
        this->showGrid(x + 1, y + 1);
      if (y + 1 < maxY)
        this->showGrid(x, y + 1);
      if (y + 1 < maxY && x - 1 >= 0)
        this->showGrid(x - 1, y + 1);
      if (x - 1 >= 0)
        this->showGrid(x - 1, y);
    }
}

void		minesweeper::Core::copyGrid()
{
  int		x = this->_grid->getSizeX();
  int		y = this->_grid->getSizeY();

  for (size_t lines = 0; lines < y; ++lines)
    for (size_t cols = 0; cols < x; ++cols)
      {
	if (this->_data->getPoint(cols, lines) == KeyGame::ELEM0)
	  this->_grid->setPoint(cols, lines, KeyGame::ELEM9);
	else
	  this->_grid->setPoint(cols, lines, this->_data->getPoint(cols, lines));
      }
}

size_t		minesweeper::Core::onlyMinesLeft()
{
  int		x = this->_grid->getSizeX();
  int		y = this->_grid->getSizeY();
  int		countMines = 0;

  for (size_t lines = 0; lines < y; ++lines)
    for (size_t cols = 0; cols < x; ++cols)
      {
	if (this->_grid->getPoint(cols, lines) == KeyGame::ELEM0)
	  ++countMines;
      }
  if (countMines == this->_difficulty)
    return (1);
  return (0);
}

int		minesweeper::Core::move(KeyGame::eKeyCode key)
{
  int		returnValue = 0;

  this->_grid->setPoint(this->_cursorX, this->_cursorY, this->_grid->getPoint(this->_cursorX, this->_cursorY) - 10);
  if (this->_gameover)
    returnValue = -1;
  else
    {
      switch (key)
	{
	case KeyGame::UP :
	  if (this->_cursorY > 0)
	    --this->_cursorY;
	  break;
	case KeyGame::DOWN :
	  if (this->_cursorY < this->_data->getSizeY() - 1)
	    ++this->_cursorY;
	  break;
	case KeyGame::LEFT :
	  if (this->_cursorX > 0)
	    --this->_cursorX;
	  break;
	case KeyGame::RIGHT :
	  if (this->_cursorX < this->_data->getSizeX() - 1)
	    ++this->_cursorX;
	  break;
	case KeyGame::SPACE :
	  if (this->_data->getPoint(this->_cursorX, this->_cursorY) == KeyGame::ELEM20)
	    {
	      this->copyGrid();
	      this->_gameover = true;
	    }
	  else
	    this->showGrid(this->_cursorX, this->_cursorY);
	  break;
	}
      if (this->onlyMinesLeft())
      	{
      	  this->_score += this->_difficulty * 10;
      	  this->copyGrid();
      	}
      if (this->_gameover == false)
	this->_grid->setPoint(this->_cursorX, this->_cursorY, this->_grid->getPoint(this->_cursorX, this->_cursorY) + 10);
    }
  return (returnValue);
}

void		minesweeper::Core::restartGame()
{
  this->updateBest();
  if (this->_data)
    delete this->_data;
  if (this->_gameover)
    this->_score = 0;
  this->_gameover = false;
  this->_data = new Grid(this->_grid->getSizeX() - 2, this->_grid->getSizeY() - 2);
  this->fillGrid(this->_data->getSizeX(), this->_data->getSizeY());
  if (this->_grid)
    delete this->_grid;
  this->_grid = new Grid(this->_data->getSizeX() - 2, this->_data->getSizeY() - 2);
  this->_grid->setPoint(this->_cursorX, this->_cursorY, this->_grid->getPoint(this->_cursorX, this->_cursorY) + 10);
}

size_t		minesweeper::Core::getNumberMines(int cols, int lines)
{
  size_t	minesAround = 0;
  size_t	maxX = this->_data->getSizeX();
  size_t	maxY = this->_data->getSizeY();

  if (lines - 1 >= 0 && cols - 1 >= 0 && this->_data->getPoint(cols - 1, lines - 1) == KeyGame::ELEM20)
    ++minesAround;
  if (lines - 1 >= 0 && this->_data->getPoint(cols, lines - 1) == KeyGame::ELEM20)
    ++minesAround;
  if (cols + 1 < maxX && lines - 1 >= 0 && this->_data->getPoint(cols + 1, lines - 1) == KeyGame::ELEM20)
    ++minesAround;
  if (cols + 1 < maxX && this->_data->getPoint(cols + 1, lines) == KeyGame::ELEM20)
    ++minesAround;
  if (cols + 1 < maxX && lines + 1 < maxY && this->_data->getPoint(cols + 1, lines + 1) == KeyGame::ELEM20)
    ++minesAround;
  if (lines + 1 < maxY && this->_data->getPoint(cols, lines + 1) == KeyGame::ELEM20)
    ++minesAround;
  if (lines + 1 < maxY && cols - 1 >= 0 && this->_data->getPoint(cols - 1, lines + 1) == KeyGame::ELEM20)
    ++minesAround;
  if (cols - 1 >= 0 && this->_data->getPoint(cols - 1, lines) == KeyGame::ELEM20)
    ++minesAround;
  return minesAround;
}

void		minesweeper::Core::putNumber(size_t cols, size_t lines)
{
  size_t	nbMineProx = this->getNumberMines(cols, lines);

  if (this->_data->getPoint(cols, lines) != KeyGame::ELEM20)
    this->_data->setPoint(cols, lines, nbMineProx);
}

void		minesweeper::Core::putMines(size_t nbMines, size_t x, size_t y)
{
  size_t	lines = 0;
  size_t	cols = 0;

  for (size_t countMines = 0; countMines < nbMines; ++countMines)
    {
      cols = rand() % x;
      lines = rand() % y;
      if (this->_data->getPoint(cols, lines) != KeyGame::ELEM20)
	this->_data->setPoint(cols, lines, KeyGame::ELEM20);
    }
}

void		minesweeper::Core::fillGrid(size_t x, size_t y)
{
  this->putMines(this->_difficulty, x, y);
  for (size_t lines = 0; lines < x; ++lines)
    for (size_t cols = 0; cols < y; ++cols)
      this->putNumber(lines, cols);
}
