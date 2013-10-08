//
// Fork.cpp for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/sources
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Mon Apr 11 16:15:22 2011 chanh allaux
// Last update Sun Apr 17 18:44:55 2011 romain tholimet
//

#include		<iostream>
#include		"systemError.hh"
#include		"Fork.hh"

int			Fork::_fork()
{
  int			pid;

  pid = fork();
  if (pid < 0)
    throw exceptionPlazza::systemError(exceptionPlazza::FORK);
  return (pid);
}
