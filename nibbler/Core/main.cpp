//
// main.cpp for  in /home/allaux_c//rendu/cpp/nibbler
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Mon Mar  7 19:08:20 2011 chanh allaux
// Last update Sun Mar 20 16:04:09 2011 romain tholimet
//

#include		<cstdlib>
#include		<string>
#include		<iostream>
#include		<dlfcn.h>
#include		"ALibrary.hh"
#include		"DLLoader.hpp"
#include		"NibblerException.hpp"
#include		"Snake.hh"
#include		"Point.hh"
#include		"ACore.hh"
#include		"Core.hh"
#include		"MinesweeperCore.hh"
#include		"Parser.hh"
#include		"Option.hh"

int			main(int argc, char **argv)
{
  if (argc < 4)
    throw nibblerException("usage: ./nibbler width height lib_nibbler_XXX.so [-o] [-w] [-m] [-h] [-v]");

  Parser		parser(argv[1], argv[2], argv[3]);

  DLLoader<ALibrary>	dll(parser.getLib());
  ALibrary*		lib = NULL;
  Option		*option = new Option(argc, argv);
  ACore			*core;

  srand(time(NULL));
  lib = dll.getLib();

  if (option->getM())
    core = new minesweeper::Core(parser.getX(), parser.getY(), option, lib);
  else
    core = new snake::Core(parser.getX(), parser.getY(), option, lib);

  try
    {
      lib->init(core, argc, argv);
    }
  catch (nibblerException e)
    {
      std::cout << e.getMessage() << std::endl;
      delete(option);
      delete(core);
      return (1);
    }

  if (option->getV())
    option->printDescription(core->getDescription());

  lib->run();
  lib->destroy();

  delete (option);
  delete (core);
  return (0);
}
