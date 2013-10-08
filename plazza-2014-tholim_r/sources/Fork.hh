//
// Fork.hh for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/sources
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Mon Apr 11 16:12:14 2011 chanh allaux
// Last update Wed Apr 13 14:11:03 2011 chanh allaux
//

#ifndef			__FORK_HH_
#define			__FORK_HH_

#include		<unistd.h>

class			Fork
{
private:
  Fork();
  ~Fork();

public:
  static int		_fork();
};

#endif
