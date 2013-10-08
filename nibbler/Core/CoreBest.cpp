//
// CoreBest.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 17:11:08 2011 chanh allaux
// Last update Sat Mar 19 18:43:01 2011 romain tholimet
//

#include		<fstream>
#include		<sstream>
#include		<iostream>
#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

void			ACore::initDescription()
{
  std::fstream		_filetmp;
  std::streambuf	*str;
  std::streamsize	size;
  std::stringstream	ss;
  std::string		name = ".about" + this->getTitle();

  _filetmp.open(name.c_str());
  if (_filetmp.is_open())
    {
      str = _filetmp.rdbuf();
      size = str->in_avail();
      if (size)
	ss << str;
      this->_description = ss.str().c_str();
      _filetmp.close();
    }
}
