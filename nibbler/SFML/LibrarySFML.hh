//
// LibrarySFML.hh for nibbler in /home/tholim_r//nibbler-2014-benram_s/SFML
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Sat Mar 12 14:56:32 2011 romain tholimet
// Last update Sun Mar 20 19:51:11 2011 romain tholimet
//

#ifndef			__LIBRARYSFML_HH__
#define			__LIBRARYSFML_HH__

#include		<map>
#include		<vector>
#include		<iostream>
#include		<algorithm>
#include		<sstream>
#include		<cstdlib>
#include		<SFML/Window.hpp>
#include		<SFML/Graphics.hpp>
#include		<SFML/Audio.hpp>
#include		"ACore.hh"
#include		"ALibrary.hh"
#include		"NibblerException.hpp"

typedef std::map<unsigned int, sf::Image>	Elements;
typedef std::map<unsigned int, sf::Music>	Sounds;
typedef std::vector<sf::Sprite>			Sprites;
typedef std::vector<unsigned int>		Values;

class			LibrarySFML : public ALibrary
{
  sf::RenderWindow	*_window;

  Elements		_images;
  Sprites		_sprites;
  Values		_values;
  Sounds		_sounds;

  bool			_pause;
  bool			_gameOver;

  size_t		_width;
  size_t		_height;

  float			_imageWidth;
  float			_imageHeight;

  float			_frameRate;

  float			_paddingTop;
  float			_paddingLeft;

  sf::Image		_imageScore;

public:
  LibrarySFML();
  ~LibrarySFML();
  int			init(ACore * const, int, char **);
  void			destroy();
  int			run();
  void			refresh();

private:
  void			initImages();
  void			initSprites();
  void			initWindow();
  void			refreshSprite();
  void			gameOver();
  void			restartScreen();
  void			setScreenSize(const Grid * const);
  void			setDescription();
  void			setScore(bool, size_t, sf::String &);
  void			setGameBoySprite(sf::Sprite &);
  KeyGame::eKeyCode	getKey(sf::Key::Code);
};

#endif
