//
// Grid.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 00:57:23 2011 chanh allaux
// Last update Sun Mar 13 22:53:21 2011 chanh allaux
//

#ifndef			__GRID_HH_
# define		__GRID_HH_

#include		<iostream>
#include		"EKey.hh"

class			Grid
{
  size_t		_sizeX;
  size_t		_sizeY;
  int			**_grid;

public:
  Grid(size_t sizeX, size_t sizeY);
  ~Grid();

public:
  size_t		getSizeX() const { return (this->_sizeX); }
  size_t		getSizeY() const { return (this->_sizeY); }
  void			setPoint(size_t x, size_t y, int value);
  KeyGame::eType	getPoint(size_t x, size_t y) const;
  void			dump(void) const;
  void			randomWall(void);
  void			roundWall(void);

private:
  void			initGrid(void);
};

#endif
