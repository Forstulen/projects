//
// main.cpp for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/lib_plazza_Qt
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Apr  7 18:15:22 2011 chanh allaux
// Last update Thu Apr  7 18:30:33 2011 chanh allaux
//

#include		<iostream>
#include		<dlfcn.h>
#include		"ILibrary.hh"
#include		"DLLoader.hpp"
#include		"Reception.hh"

int			main(int argc, char **argv)
{
  Reception		reception;
  DLLoader<ILibrary>	dll("./lib_plazza_Qt.so");
  ILibrary*		lib = NULL;

  lib = dll.getLib();
  lib->init(argc, argv);
  lib->run(reception);
  return (0);
}
