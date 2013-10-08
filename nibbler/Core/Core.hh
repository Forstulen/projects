//
// Core.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 00:38:33 2011 chanh allaux
// Last update Sun Mar 20 17:26:53 2011 chanh allaux
//

#ifndef			__CORE_HH_
# define		__CORE_HH_

#include		<fstream>
#include		<iostream>
#include		<map>
#include		<fmodex/fmod.hpp>
#include		"ACore.hh"
#include		"Snake.hh"
#include		"Grid.hh"

namespace		snake
{
  class			Core : public ACore
  {
    FMOD::System	*_system;
    FMOD::Sound		*_dying;
    FMOD::Sound		*_apple;
    FMOD::Sound		*_mickey;
    FMOD::Sound		*_caca;
    FMOD::Sound		*_ambiance;

    Snake		*_snake;
    Point		*_bonus;
    Point		*_malus;
    size_t		_cptBonus;
    size_t		_cptMalus;
    size_t		_grow;
    bool		_hasBeenUpdate;
    size_t		_boost;
    size_t		_realmsec;
    size_t		_reverse;

    std::map<KeyGame::eType, KeyGame::eKeyCode> _none;

  public:
    virtual ~Core();
    virtual int		move(KeyGame::eKeyCode);
    virtual void	restartGame();

  public:
    Core(size_t, size_t, Option*, ALibrary *);

  private:
    void		reverseDirection(KeyGame::eKeyCode & keyCode,
					 Point *head);
    void		getDirection(int & newX, int & newY,
				     KeyGame::eType & headPix,
				     KeyGame::eType & beforePix,
				     KeyGame::eKeyCode keyCode);

  private:
    void		getTailDirection(Point* tail, size_t &, size_t &);
    void		getTailPixmap(Point* tail, KeyGame::eType & tailPix);
    void		moveTail(Point *tail);

  private:
    int			grow(int newX, int newY,
			     size_t x, size_t y,
			     Point* head, Point* tail);
    int			popFood(KeyGame::eType, Point* set);
    void		otherFood(void);
    void		resetFood(void);

  private:
    void		initSound(void);
    void		playSound(int ret);

  private:
    void		updateSpeed(void);
    void		boost(KeyGame::eKeyCode keyCode);
    void		updateBoost(KeyGame::eKeyCode keyCode);

  private:
    void		initAttributes(size_t x, size_t y, Option* opt, ALibrary* lib);
    void		initData(void);
    void		initSnakePosition(size_t & sx, size_t & sy);

  private:
    void		drawSnakePosition(size_t sx, size_t sy);
    void		drawWall(void);

  private:
    int			die(int newX, int newY);
    void		noWallMove(int & newX, int & newY);
    void		reverseKeyCode(KeyGame::eKeyCode & keyCode, int x, int y);
    void		poison(KeyGame::eKeyCode & keyCode, size_t x, size_t y);

  private:
    void		updateGrowBoost(void);
    void		updateSprite(size_t x, size_t y,
				     KeyGame::eType headpix,
				     KeyGame::eType beforePix);
  };
}

#endif
