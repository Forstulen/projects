//
// Grid.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 01:00:36 2011 chanh allaux
// Last update Sun Mar 13 16:42:42 2011 chanh allaux
//

#include		<cstdlib>
#include		"EKey.hh"
#include		"Core.hh"
#include		"Grid.hh"

Grid::Grid(size_t sizeX, size_t sizeY)
  : _sizeX(sizeX + 2), _sizeY(sizeY + 2)
{
  this->_grid = new int*[this->_sizeY];
  for (size_t i = 0; i < this->_sizeY; ++i)
    this->_grid[i] = new int[this->_sizeX];
  this->initGrid();
}

Grid::~Grid()
{
  if (this->_grid)
    {
      for (size_t i = 0; i < this->_sizeY; ++i)
      	delete[] this->_grid[i];
      delete[] (this->_grid);
    }
}

//		Instaure un mode pour varier niveau mur initGrid(enum Mode)

void		Grid::randomWall(void)
{
  size_t	x, y;

  for (size_t i = 0; i < (this->_sizeY > this->_sizeX ? this->_sizeY : this->_sizeX); ++i)
    {
      do {
	x = rand() % this->getSizeX();
	y = rand() % this->getSizeY();
      } while (this->getPoint(x, y) != KeyGame::ELEM0
	       || y == (this->getSizeY() / 2));
      this->setPoint(x, y, KeyGame::ELEM1);
    }
}

void		Grid::initGrid()
{
  for (size_t i = 0; i < this->_sizeX; ++i)
    for (size_t j = 0; j < this->_sizeY; ++j)
      this->_grid[j][i] = KeyGame::ELEM0;
}

void		Grid::roundWall(void)
{
  for (size_t i = 0; i < this->_sizeX; ++i)
    {
      this->_grid[0][i] = KeyGame::ELEM1;
      this->_grid[this->_sizeY - 1][i] = KeyGame::ELEM1;
    }
  for (size_t j = 0; j < this->_sizeY; ++j)
    {
      this->_grid[j][0] = KeyGame::ELEM1;
      this->_grid[j][this->_sizeX - 1] = KeyGame::ELEM1;
    }
}

//----------------------------------------------------------------------------

void		Grid::setPoint(size_t x, size_t y, int value)
{
  if (x > this->_sizeX || y > this->_sizeY)
    return ;
  this->_grid[y][x] = value;
}

KeyGame::eType	Grid::getPoint(size_t x, size_t y) const
{
  if (x > this->_sizeX || y > this->_sizeY)
    return (KeyGame::ELEM0);
  return ((KeyGame::eType)this->_grid[y][x]);
}

//---------------------------------------------------------------------------

void		Grid::dump(void) const
{
  for (size_t i = 0; i < this->_sizeX; ++i)
    {
      for (size_t j = 0; j < this->_sizeY; ++j)
	{
	  if (this->_grid[j][i] == KeyGame::ELEM0)
	    std::cout << ".";
	  else if (this->_grid[j][i] == KeyGame::ELEM1)
	    std::cout << "X";
	  else if (this->_grid[j][i] == KeyGame::ELEM2)
	    std::cout << "@";
	  else if (this->_grid[j][i] == KeyGame::ELEM5
		   || this->_grid[j][i] == KeyGame::ELEM9)
	    std::cout << "^";
	  else if (this->_grid[j][i] == KeyGame::ELEM6
		   || this->_grid[j][i] == KeyGame::ELEM10)
	    std::cout << "v";
	  else if (this->_grid[j][i] == KeyGame::ELEM7
		   || this->_grid[j][i] == KeyGame::ELEM11)
	    std::cout << ">";
	  else if (this->_grid[j][i] == KeyGame::ELEM8
		   || this->_grid[j][i] == KeyGame::ELEM12)
	    std::cout << "<";
	}
      std::cout << std::endl;
    }
  std::cout << std::endl;
}
