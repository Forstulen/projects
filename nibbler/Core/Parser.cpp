//
// Parser.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Mar 12 23:12:05 2011 chanh allaux
// Last update Sun Mar 20 19:38:44 2011 romain tholimet
//

//#include		<Xlib.h>
#include		"Parser.hh"

void			Parser::isNum(std::string const & num,
				      size_t & nb)
{
  std::stringstream	ss(num);

  for (int i = 0; i < num.length(); ++i)
    {
      if (num[i] < '0' || num[i] > '9')
	throw nibblerException(num + " is not a valid number");
    }
  ss >> nb;
}

//On teste l'existence de la connetion avec le serveur X11 pour eviter le SEGFAULT
void		Parser::checkX11Server(void)
{
  //  if (!XOpenDisplay(NULL))
  //throw nibblerException("Cannot create a Window SFML !");
}

Parser::Parser(std::string const & x,
	       std::string const & y,
	       std::string const & lib)
  : _lib(lib)
{
  this->checkX11Server();
  this->isNum(x, this->_x);
  this->isNum(y, this->_y);
  if (this->_x < 7 || this->_y < 6)
    throw nibblerException("Please specify a bigger size, gameplay sucks if it's too small");
  else if (this->_x > 110 || this->_y > 65)
    throw nibblerException("I think your screen is too small, please specify a smaller size");
}
