//
// Option.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Mar 13 15:14:20 2011 chanh allaux
// Last update Sat Mar 19 17:13:06 2011 chanh allaux
//

#include		<iostream>
#include		<getopt.h>
#include		"NibblerException.hpp"
#include		"Option.hh"

void			Option::usage(void) const
{
  std::cout << "usage: ./nibbler width height lib_nibbler_XXX.so [-w] [-o] [-m] [-h] [-v]" << std::endl;
}

void			Option::printDescription(std::string const & description)
{
  std::cout << description << std::endl;
}

Option::Option(int argc, char **argv)
  : _o(false), _w(false), _m(false), _h(false), _v(false)
{
  int			opt;

  while ((opt = getopt(argc, argv, "owmhv")) != -1)
    {
      switch (opt)
	{
	case 'o':
	  this->_o = true;
	  break ;
	case 'h':
	  this->_h = true;
	  break ;
	case 'w':
	  this->_w = true;
	  break ;
	case 'm':
	  this->_m = true;
	  break ;
	case 'v':
	  this->_v = true;
	  break ;
	default:
	  this->usage();
	  throw nibblerException("invalid option");
	}
    }
}
