//
// CoreSound.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 15:43:45 2011 chanh allaux
// Last update Sat Mar 19 15:24:15 2011 chanh allaux
//

#include		<sstream>
#include		"ALibrary.hh"
#include		"Core.hh"

void			snake::Core::initSound(void)
{
  std::stringstream	ss1;
  std::stringstream	ss2;
  std::stringstream	ss3;
  std::stringstream	ss4;
  std::stringstream	ss5;

  ss1 << "./resources/" << this->_lib->getName() << "/" << this->_name << "sounds/sound1.ogg";
  ss2 << "./resources/" << this->_lib->getName() << "/" << this->_name << "sounds/sound2.ogg";
  ss3 << "./resources/" << this->_lib->getName() << "/" << this->_name << "sounds/sound3.ogg";
  ss4 << "./resources/" << this->_lib->getName() << "/" << this->_name << "sounds/sound-1.ogg";
  ss5 << "./resources/" << this->_lib->getName() << "/" << this->_name << "sounds/music.ogg";

  FMOD::System_Create(&(this->_system));

  this->_system->init(4, FMOD_INIT_NORMAL, NULL);

  this->_system->createSound(ss1.str().c_str(), FMOD_CREATESAMPLE, 0, &this->_apple);
  this->_system->createSound(ss2.str().c_str(), FMOD_CREATESAMPLE, 0, &this->_mickey);
  this->_system->createSound(ss3.str().c_str(), FMOD_CREATESAMPLE, 0, &this->_caca);
  this->_system->createSound(ss4.str().c_str(), FMOD_CREATESAMPLE, 0, &this->_dying);

  this->_system->createSound(ss5.str().c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &this->_ambiance);

  FMOD::Channel *channel = NULL;
  this->_system->playSound(this->_ambiance, NULL, false, &channel);
}

void			snake::Core::playSound(int ret)
{

  FMOD::Channel *channel = NULL;
  switch (ret)
    {
    case -1:
      this->_system->playSound(this->_dying, NULL, false, &channel);
      break ;
    case 1:
      this->_system->playSound(this->_apple, NULL, false, &channel);
      break ;
    case 2:
      this->_system->playSound(this->_mickey, NULL, false, &channel);
      break ;
    case 3:
      this->_system->playSound(this->_caca, NULL, false, &channel);
      break ;
    }
}
