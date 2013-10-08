//
// lib.hh for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/lib_plazza_Qt
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Apr  7 17:57:45 2011 chanh allaux
// Last update Sun Apr 17 15:13:24 2011 romain tholimet
//

#ifndef			__LIB_HH_
#define			__LIB_HH_

#include                <fstream>
#include                <QLineEdit>
#include		<QApplication>
#include                <QPushButton>
#include                <QGridLayout>
#include		"ILibrary.hh"
#include		"plazzawindow.hh"
#include                "ui_plazzawindow.h"

class			Lib : public ILibrary
{
  QApplication*		_app;
  PlazzaWindow*         _window;
  Ui::PlazzaWindow      *ui;

public:
  Lib();
  virtual ~Lib() {}
  virtual int		run(void);
  virtual void		init(int, char**, IReception*);
  virtual void		destroy(void);
  virtual void          log(std::string const &, std::fstream &);
  virtual void		_close();
};

#endif
