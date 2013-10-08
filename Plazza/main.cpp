//
// main.cpp for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 11:53:24 2011 soufien benramdhane
// Last update Sun Apr 17 16:54:18 2011 romain tholimet
//

#include			<cstdlib>
#include			<iostream>
#include			<sstream>
#include			<string>
#include			"ILibrary.hh"
#include			"IReception.hh"
#include			"Reception.hh"
#include			"DLLoader.hpp"
#include			"systemError.hh"

int				checkArgument(char *str)
{
  const std::string		arg(str);
  std::stringstream		ss;
  int				ret;

  for (std::string::const_iterator it = arg.begin(); it != arg.end(); ++it)
    if (*it < '0' || *it > '9')
      throw exceptionPlazza::systemError(exceptionPlazza::BADARG);
  ss << str;
  ss >> ret;
  if (ret <= 0)
    throw exceptionPlazza::systemError(exceptionPlazza::BADARG);
  return (ret);
}

int				main(int argc, char **argv)
{
  if (argc != 4)
    {
      std::cerr << "Error: Usage: ./plazza [Mult Cooking] [Number Cook] [Pop Ingredients]" << std::endl;
      return (EXIT_FAILURE);
    }
  IReception*			reception = NULL;
  ILibrary*			lib = NULL;
  DLLoader<ILibrary>		*dll = NULL;
  bool				isinit = false;
  
  try
    {
      dll = new DLLoader<ILibrary>("./lib_plazza_Qt.so");
      lib = dll->getLib();
      reception = new Reception::Reception(checkArgument(argv[1]),
					   checkArgument(argv[2]),
					   checkArgument(argv[3]),
					   lib);
      lib->init(argc, argv, reception);
      isinit = !isinit;
      lib->run();
      lib->destroy();
    }
  catch (...)
    {
      if (reception)
        delete (reception);
      if (lib && isinit)
      	lib->_close();
      if (dll)
      	delete (dll);
      return (EXIT_FAILURE);
    }
  delete (reception);
  return (EXIT_SUCCESS);
}
