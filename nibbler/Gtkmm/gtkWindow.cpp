//
// gtkWindow.cpp for gtkmm in /home/benram_s//Desktop/program/cpp/nibbler-2014-benram_s/Gtkmm
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Mar 12 20:37:28 2011 soufien benramdhane
// Last update Sat Mar 19 18:20:41 2011 soufien benramdhane
//

#include		<gtkmm.h>
#include		<iostream>

#include		"gtkWindow.hh"

gtkWindow::gtkWindow(libGtk::libGtkmm *lib) :
  _currentKey(KeyGame::NONE), _alive(true), _pause(true), _dead(false), _lib(lib),
  _inter(this->_lib->getCore()->getSpeed())
{
  this->c = Glib::signal_timeout().connect(mem_fun(*this, &gtkWindow::slot), this->_inter);
  signal_key_press_event().connect(mem_fun(*this, &gtkWindow::on_key_press_event));
}

KeyGame::eKeyCode		gtkWindow::getKey(GdkEventKey *event)
{
  switch (event->keyval)
    {
    case GDK_Escape:
      Gtk::Main::quit();
      return (KeyGame::NONE);
    case GDK_Up:
      return (KeyGame::UP);
    case GDK_Left:
      return (KeyGame::LEFT);
    case GDK_Right:
      return (KeyGame::RIGHT);
    case GDK_Down:
      return (KeyGame::DOWN);
    case GDK_space:
      return (KeyGame::SPACE);
    case GDK_r:
      this->_lib->getCore()->restartGame();
      this->_lib->refresh();
      this->_pause = !this->_pause;
      return (KeyGame::NONE);
    case GDK_p:
      this->_lib->setState("Press any key to carry on");
      this->_pause = !this->_pause;
      return (KeyGame::NONE);
    default:
      return (KeyGame::NONE);
    }
}

bool			gtkWindow::on_key_press_event(GdkEventKey *event)
{
  if (!this->_dead)
    this->_currentKey = this->getKey(event);
  else if (event->keyval == GDK_Escape)
    Gtk::Main::quit();
  if (!this->_dead && this->_pause && event->keyval != GDK_p)
    {
      this->_pause = false;
      this->_lib->setState("Press P to come to a halt");
    }
}

//----------------------------------------------------------------------------

void			gtkWindow::setDeadFalse()
{
  this->_dead = false;
}

void			gtkWindow::setNewInter(int newInter)
{
  this->_inter = newInter;
  this->c.disconnect();
  this->c = Glib::signal_timeout().connect(mem_fun(*this, &gtkWindow::slot), this->_inter);
}

bool			gtkWindow::slot(void)
{
  int			res;
  int			newInter;

  if (!this->_pause)
    {
      this->_lib->refresh();
      res = this->_lib->getCore()->move(this->_currentKey);
      if (res == -1)
	{
	  this->_dead = true;
	  this->_pause = true;
	  this->_lib->setState("            Game Over            ");
	  this->_lib->getCore()->restartGame();
	}
    }
  if ((newInter = this->_lib->getCore()->getSpeed()) != this->_inter)
    this->setNewInter(newInter);
  this->_currentKey = KeyGame::NONE;
  return (true);
}

//----------------------------------------------------------------------------

gtkWindow::~gtkWindow()
{
  this->_system->close();
  this->_system->release();
}
