//
// main.cpp for machine in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Thu Feb 17 14:08:34 2011 soufien benramdhane
// Last update Sun Feb 20 17:39:31 2011 soufien benramdhane
//

#include		<fstream>
#include		<iostream>
#include		"Machine.hh"
#include		"systemError.hh"

int			main(int ac, char **av)
{
  std::fstream		file;
  Machine		mach(ac == 2);

  try
    {
      if (ac > 2)
	throw systemError(USAGE);
      else if (ac == 2)
	{
	  std::string	name_file(av[1]);
	  if (name_file.find_last_of('.') != std::string::npos)
	    {
	      if ((name_file.substr(name_file.find_last_of('.'), std::string::npos)) != ".avm")
	  	throw systemError(WEXT);
	    }
	  else
	    throw systemError(WEXT);
	  file.open(name_file.c_str());
	  if (file.is_open() == false)
	    throw systemError(WFILE);
	  mach.run(file);
	}
      else
	mach.run(std::cin);
    }
  catch(systemError e)
    {
      std::cerr << "Abstract VM: Fatal Error: ";
      if ((e.getType() == WFILE) || (e.getType() == WEXT) || (e.getType() == USAGE));
      else if ((e.getType() == UNDOVER) || (e.getType() == DIV0) ||
	       (e.getType() == WMOD))
	std::cerr << "Line " << mach.getInstructionMap().front()->getLine() << ": ";
      else
	std::cerr << "Line " << mach.getLine() << ": ";
      std::cerr << e.what() <<  std::endl;
      mach.cleanUp();
    }
  return (0);
}
