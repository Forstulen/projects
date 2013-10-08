//
// Parser.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Mar 12 23:11:27 2011 chanh allaux
// Last update Sun Mar 20 15:59:56 2011 romain tholimet
//

#ifndef			__PARSER_HH_
#define			__PARSER_HH_

#include		<sstream>
#include		<iostream>
#include		"NibblerException.hpp"

class			Parser
{
  size_t		_x;
  size_t		_y;
  std::string		_lib;

public:
  Parser(std::string const & y,
	 std::string const & x,
	 std::string const & lib);
  void			checkX11Server(void);
  void			isNum(std::string const &, size_t &);
  size_t		getX(void) const { return (this->_x); }
  size_t		getY(void) const { return (this->_y); }
  std::string const &	getLib(void) const { return (this->_lib); }
};

#endif
