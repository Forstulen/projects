//
// ACore.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 00:39:47 2011 chanh allaux
// Last update Sat Mar 19 18:45:54 2011 romain tholimet
//

#ifndef			__ACORE_HH_
# define		__ACORE_HH_

#include		<fstream>
#include		<string>
#include		"Grid.hh"
#include		"EKey.hh"
#include		"Option.hh"

class ALibrary;

class			ACore
{
protected:
  ALibrary		*_lib;
  Grid			*_grid;
  Option		*_option;
  int			_score;
  int			_bestScore;
  std::string		_name;
  std::string		_title;
  std::string		_description;
  int			_msec;
  std::fstream		_file;

public:
  virtual ~ACore() { if (this->_grid) delete (this->_grid); }
  virtual int		move(KeyGame::eKeyCode) = 0;
  virtual void		restartGame(void) = 0;

public:
  ALibrary*		getLib(void) const { return (this->_lib); }
  Grid*			getGrid(void) const { return (this->_grid); }
  Option*		getOption(void) const { return (this->_option); }
  std::string const &	getName(void) const { return (this->_name); }
  std::string const &	getTitle() const { return (this->_title); }
  std::string const &	getDescription() const { return (this->_description); }
  int			getScore(void) const { return (this->_score); }
  int			getBestScore(void) const { return (this->_bestScore); }
  int			getSpeed(void) const { return (this->_msec); }

protected:
  void			updateBest(void);
  void			openBest(void);

public:
  void			initDescription(void);
};

#endif
