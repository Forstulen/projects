#include <sstream>
#include "nibblerwidget.hh"

NibblerWidget::NibblerWidget(libQt* lib, QWidget *parent)
  : QWidget(parent), _currentKey(KeyGame::NONE), _lib(lib), _pause(true), _dead(false)
{
}

NibblerWidget::~NibblerWidget()
{
}

void        NibblerWidget::pause(void)
{
  if (this->_pause == false || this->_dead == true)
    this->_lib->getTimer()->stop();
  else
    this->_lib->getTimer()->start();
}

void        NibblerWidget::keyPressEvent(QKeyEvent* event)
{
  switch (event->key())
    {
    case Qt::Key_Escape:
      this->close();
      break ;
    case Qt::Key_Up:
      this->_currentKey = KeyGame::UP;
      break ;
    case Qt::Key_Down:
      this->_currentKey = KeyGame::DOWN;
      break ;
    case Qt::Key_Right:
      this->_currentKey = KeyGame::RIGHT;
      break ;
    case Qt::Key_Left:
      this->_currentKey = KeyGame::LEFT;
      break ;
    case Qt::Key_Space:
      this->_currentKey = KeyGame::SPACE;
      break ;
    case Qt::Key_P:
      this->_pause = !this->_pause;
      this->pause();
      break ;
    case Qt::Key_R:
      this->_lib->getCore()->restartGame();
      this->_dead = false;
      return ;
    default:
      this->_currentKey = KeyGame::NONE;
    }
}

void        NibblerWidget::slot(void)
{
  int     ret;

  if (this->_dead == false)
    {
      ret = this->_lib->getCore()->move(this->_currentKey);
      if (ret == -1)
        {
	  this->_dead = true;
	  this->_lib->getTimer()->stop();
        }
    }
  this->_lib->refresh();
  this->_currentKey = KeyGame::NONE;
  this->_lib->getTimer()->start(this->_lib->getCore()->getSpeed());
}
