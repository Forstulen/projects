//
// gtkWindow.hh for gtkmm in /home/benram_s//Desktop/program/cpp/nibbler-2014-benram_s/Gtkmm
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Mar 12 20:37:21 2011 soufien benramdhane
// Last update Fri Mar 18 14:51:06 2011 chanh allaux
//

#ifndef			__GTKWINDOW_HH__
# define		__GTKWINDOW_HH__

# include		<fmodex/fmod.hpp>

# include		"EKey.hh"
# include		"libGtkmm.hh"

class			gtkWindow : public Gtk::Window
{
  KeyGame::eKeyCode	_currentKey;
  bool			_alive;
  bool			_pause;
  bool			_dead;
  libGtk::libGtkmm*	_lib;
  int			_inter;
  sigc::connection	c;

  FMOD::System		*_system;
  FMOD::Sound		*_dying;
  FMOD::Sound		*_apple;
  FMOD::Sound		*_mickey;
  FMOD::Sound		*_caca;
  FMOD::Sound		*_ambiance;

public:
  gtkWindow(libGtk::libGtkmm *lib);
  ~gtkWindow();

private:
  bool			on_key_press_event(GdkEventKey *event);
  bool			slot(void);

private:
  void			setNewInter(int newInter);
  KeyGame::eKeyCode	getKey(GdkEventKey *event);
  void			setSound();
  void			playSound(int ret);

public:
  void			setDeadFalse();
};

#endif
