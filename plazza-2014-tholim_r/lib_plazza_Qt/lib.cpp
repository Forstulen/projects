//
// lib.cpp for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/lib_plazza_Qt
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Apr  7 17:57:13 2011 chanh allaux
// Last update Sun Apr 17 22:31:28 2011 romain tholimet
//

#include		<iostream>
#include                <sstream>
#include                <time.h>
#include		"systemError.hh"
#include		"lib.hh"
#include                "plazzawindow.hh"
#include                "ui_plazzawindow.h"

Lib::Lib()
{
}

int			Lib::run()
{
  this->_window->show();
  return (this->_app->exec());
}

void			Lib::init(int argc, char **argv, IReception *reception)
{
  this->_app = new QApplication(argc, argv);
  this->_window = new PlazzaWindow(reception);
  this->ui = this->_window->getUi();
  this->ui->actionAbout_Qt->connect(this->ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
  this->_window->setFixedSize(this->_window->width(), this->_window->height());
}

void                    Lib::log(std::string const & str, std::fstream & log)
{
    std::ostringstream  oss;
    time_t              rawtime;
    char                ftime[32];
    struct tm*          timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(ftime, 32, "%H:%M:%S -- ", timeinfo);
    oss << ftime << " " << str;
    if (log.is_open())
      log << oss.str() << std::endl;
    this->ui->logList->addItem(oss.str().c_str());
    std::cout << oss.str() << std::endl;
}

void			Lib::destroy(void)
{
  delete (this->_window);
  delete (this->_app);
}

void			Lib::_close(void)
{
  this->_window->close();
}

extern "C" ILibrary*	entry(void)
{
  return (new Lib);
}
