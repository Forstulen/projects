//
// Point.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 00:42:51 2011 chanh allaux
// Last update Sun Mar 13 22:52:58 2011 chanh allaux
//

#ifndef			__POINT_HH_
# define		__POINT_HH_

#include		<iostream>

class			Point
{
  size_t		_x;
  size_t		_y;

public:
  Point() {}
  ~Point() {}

public:
  size_t		getX(void) const { return (this->_x); }
  size_t		getY(void) const { return (this->_y); }
  void			setX(size_t x) { this->_x = x; }
  void			setY(size_t y) { this->_y = y; }
  void			setPosition(size_t x, size_t y) { this->_x = x; this->_y = y; }
};

#endif
