//
// CoreSprite.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Mar 19 12:46:26 2011 chanh allaux
// Last update Sat Mar 19 12:48:57 2011 chanh allaux
//

#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

void			snake::Core::updateSprite(size_t x, size_t y,
						  KeyGame::eType headPix,
						  KeyGame::eType beforePix)
{
  this->_grid->setPoint(this->_snake->getHead()->getX(), this->_snake->getHead()->getY(), headPix);
  this->_grid->setPoint(x, y, beforePix);
}
