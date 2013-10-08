#include	<iostream>

#include	"mainwindow.h"
#include	"Database.hpp"
#include	"Exception.hpp"

int		main(int argc, char *argv[])
{
  try
    {

      if (!RTDB::Database::getInstance().fillFromFile("../../resource/bdd.rtdb"))
	{
	  std::cerr << "Error : Cannot load database !" << std::endl;
	  return 1;
	}

      QApplication	a(argc, argv);
      MainWindow	w;

      w.show();
      return a.exec();
    }
  catch (Exception const &ex) { std::cerr << ex; }
  return (1);
}
