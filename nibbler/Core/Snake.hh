//
// Snake.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 00:41:15 2011 chanh allaux
// Last update Thu Mar 10 14:32:37 2011 chanh allaux
//

#ifndef			__SNAKE_HH_
# define		__SNAKE_HH_

#include		"Point.hh"

class			Snake
{
  Point			*_head;
  Point			*_tail;

public:
  Snake() : _head(new Point), _tail(new Point) {}
  ~Snake() { if (this->_head) delete (this->_head); if (this->_tail) delete(this->_tail); }

public:
  Point* 		getHead(void) const { return (this->_head); }
  Point*		getTail(void) const { return (this->_tail); }
};

#endif
