//
// CoreSpecialMove.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 16:11:03 2011 chanh allaux
// Last update Sun Mar 20 17:27:36 2011 chanh allaux
//

#include		"Core.hh"
#include		"ACore.hh"
#include		"ALibrary.hh"

void			snake::Core::poison(KeyGame::eKeyCode & keyCode, size_t x, size_t y)
{
  if (this->_reverse > 0)
    {
      switch (keyCode)
	{
	case KeyGame::RIGHT:
	  keyCode = KeyGame::LEFT;
	  break ;
	case KeyGame::LEFT:
	  keyCode = KeyGame::RIGHT;
	  break ;
	case KeyGame::UP:
	  keyCode = KeyGame::DOWN;
	  break ;
	case KeyGame::DOWN:
	  keyCode = KeyGame::UP;
	  break ;
	}
      --this->_reverse;
    }
}

// check if youre going backward, avoid to die stupidly
void			snake::Core::reverseDirection(KeyGame::eKeyCode & keyCode,
						      Point* head)
{
  if (keyCode == KeyGame::RIGHT
      && this->_grid->getPoint(head->getX(), head->getY()) == KeyGame::ELEM12)
    keyCode = KeyGame::LEFT;
  else if (keyCode == KeyGame::LEFT
	   && this->_grid->getPoint(head->getX(), head->getY()) == KeyGame::ELEM11)
    keyCode = KeyGame::RIGHT;
  else if (keyCode == KeyGame::UP
	   && this->_grid->getPoint(head->getX(), head->getY()) == KeyGame::ELEM10)
    keyCode = KeyGame::DOWN;
  else if (keyCode == KeyGame::DOWN
	   && this->_grid->getPoint(head->getX(), head->getY()) == KeyGame::ELEM9)
    keyCode = KeyGame::UP;
}

// check if youre going off the wall
void			snake::Core::noWallMove(int & newX, int & newY)
{
  if (newX > this->_grid->getSizeX() - 1 || newX < 0 || newY > this->_grid->getSizeY() - 1 || newY < 0)
    {
      if (newX < 0)
	newX = this->_grid->getSizeX() - 1;
      else if (newY < 0)
	newY = this->_grid->getSizeY() - 1;
      else if (newX > this->_grid->getSizeX() - 1)
	newX = 0;
      else if (newY > this->_grid->getSizeY() - 1)
	newY = 0;
    }
}

void			snake::Core::reverseKeyCode(KeyGame::eKeyCode & keyCode,
						    int x, int y)
{
  // Change the key if is NONE or the reverse of the head
  if (keyCode == KeyGame::NONE || keyCode == KeyGame::SPACE)
    keyCode = this->_none[(KeyGame::eType)this->_grid->getPoint(x, y)];
  else
    this->reverseDirection(keyCode, this->_snake->getHead());
}

int			snake::Core::die(int newX, int newY)
{
  // test if you hit a wall or yourself
  if (this->_grid->getPoint(newX, newY) == KeyGame::ELEM1

      || (this->_grid->getPoint(newX, newY) >= KeyGame::ELEM5
	  && this->_grid->getPoint(newX, newY) <= KeyGame::ELEM16))
    {
      this->playSound(-1);
      this->updateBest();
      return (-1);
    }
  return (0);
}

// update the counter for growing and boost
void			snake::Core::updateGrowBoost(void)
{
  if (this->_grow > 0)
    --this->_grow;
  if (this->_boost > 0)
    --this->_boost;
}
