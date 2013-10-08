//
// MinesweeperCore.hh for MineSweeper in /home/tholim_r//nibbler-2014-benram_s
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Wed Mar 16 20:38:03 2011 romain tholimet
// Last update Sat Mar 19 16:57:31 2011 romain tholimet
//

#ifndef			__MINESWEEPERCORE_HH__
#define			__MINESWEEPERCORE_HH__

#include		<iostream>
#include		"ACore.hh"
#include		"Grid.hh"
#include		"EKey.hh"

class ALibrary;

namespace		minesweeper
{
  class			Core : public ACore
  {
    Grid		*_data;
    size_t		_cursorX;
    size_t		_cursorY;
    bool		_gameover;
    size_t		_difficulty;

  public:
    Core(size_t, size_t, Option*, ALibrary*);
    virtual		~Core();
    int			move(KeyGame::eKeyCode);
    void		restartGame();

  private:
    void		fillGrid(size_t, size_t);
    void		putMines(size_t, size_t, size_t);
    size_t		getNumberMines(int, int);
    size_t		onlyMinesLeft();
    void		putNumber(size_t, size_t);
    void		copyGrid();
    void		showGrid(int, int);
  };
}

#endif		/*	__MINESWEEPERCORE_HH__	*/
