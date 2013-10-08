//
// ALibrary.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Tue Mar  8 11:55:20 2011 chanh allaux
// Last update Sun Mar 20 19:48:45 2011 romain tholimet
//

#ifndef			__ALIBRARY_HH_
# define		__AILIBRARY_HH_

#include		<string>

class ACore;

class			ALibrary
{
protected:
  ACore*		_core;
  std::string		_name;

public:
  virtual		~ALibrary() {}
  virtual int		init(ACore * const core, int argc, char **argv) = 0;
  virtual void		destroy(void) = 0;
  virtual int		run(void) = 0;
  virtual void		refresh(void) = 0;
  std::string const &	getName(void) const { return (this->_name); }
};

#endif
