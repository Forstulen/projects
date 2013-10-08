//
// ILibrary.hh for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Apr  7 17:51:47 2011 chanh allaux
// Last update Sun Apr 17 15:13:12 2011 romain tholimet
//

#ifndef			__ILIBRARY_HH_
#define			__ILIBRARY_HH_

#include		<fstream>
#include		"IReception.hh"

class			ILibrary
{
public:
  virtual ~ILibrary() {}
  virtual int		run(void) = 0;
  virtual void		init(int, char**, IReception*) = 0;
  virtual void		destroy(void) = 0;
  virtual void		log(std::string const &, std::fstream &) = 0;
  virtual void		_close() = 0;
};

#endif
