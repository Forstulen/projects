//
// CoreSpeed.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 16:07:57 2011 chanh allaux
// Last update Sat Mar 19 12:45:15 2011 chanh allaux
//

#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

// update speed ...
void			snake::Core::updateSpeed(void)
{
  if (this->_realmsec > 20 && this->_score && this->_score % 20 == 0
      && this->_hasBeenUpdate == false)
    {
      this->_realmsec = this->_realmsec - (this->_realmsec / 10);
      this->_hasBeenUpdate = true;
    }
}

// check if you request a boost
void			snake::Core::boost(KeyGame::eKeyCode keyCode)
{
  if (keyCode == KeyGame::SPACE && this->_boost == 0)
    {
      this->_realmsec = this->_msec;
      this->_msec /= 2;
      this->_boost = 10;
    }
}

// count the number of movement to stop you limited boost
void			snake::Core::updateBoost(KeyGame::eKeyCode keyCode)
{
  if (this->_boost == 0)
    this->_msec = this->_realmsec;
  this->boost(keyCode);
}
