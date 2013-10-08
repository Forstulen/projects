//
// lib.cpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Fri Mar 18 11:03:11 2011 chanh allaux
// Last update Sun Mar 20 20:06:53 2011 romain tholimet
//

#include <sstream>
#include <iostream>
#include <QRect>
#include <QTimer>
#include <QString>
#include "lib.hh"

libQt::libQt()
{
    this->_name = "QT";
}

void			libQt::initGrid(void)
{
  this->_pix = new QLabel*[this->_core->getGrid()->getSizeY()];
  for (size_t i = 0; i < this->_core->getGrid()->getSizeY(); ++i)
    this->_pix[i] = new QLabel[this->_core->getGrid()->getSizeX()];
  this->_pixVerif = new int*[this->_core->getGrid()->getSizeY()];
  for (size_t i = 0; i < this->_core->getGrid()->getSizeY(); ++i)
    this->_pixVerif[i] = new int[this->_core->getGrid()->getSizeX()];

  for (size_t i = 0; i < this->_core->getGrid()->getSizeX(); ++i)
    {
      for (size_t j = 0; j < this->_core->getGrid()->getSizeY(); ++j)
        {
	  this->_pix[j][i].setPixmap(*this->_map[this->_core->getGrid()->getPoint(i, j)]);
	  this->_grid->addWidget(&this->_pix[j][i], j, i);
	  this->_pixVerif[j][i] = this->_core->getGrid()->getPoint(i, j);
        }
    }
}

void			libQt::refresh(void)
{
  if (this->_win->getDead() == false)
    {
      for (size_t i = 0; i < this->_core->getGrid()->getSizeX(); ++i)
        {
	  for (size_t j = 0; j < this->_core->getGrid()->getSizeY(); ++j)
            {
	      if (this->_pixVerif[j][i] != this->_core->getGrid()->getPoint(i, j)
		  && (this->_core->getGrid()->getPoint(i, j) >= 0 && this->_core->getGrid()->getPoint(i, j) <= 20))
                {
		  this->_pix[j][i].setPixmap(*this->_map[this->_core->getGrid()->getPoint(i, j)]);
		  this->_pixVerif[j][i] = this->_core->getGrid()->getPoint(i, j);
                }
            }
        }
    }
  this->updateScore();
}

void			libQt::updateScore(void)
{
  if (this->_win->getDead() == false)
    {
      std::stringstream *ss = new std::stringstream;
      *ss << "Score:";
      *ss << this->_core->getScore();
      this->_score->setText(ss->str().c_str());
      delete (ss);
      ss = new std::stringstream;
      *ss << "Best : " << this->_core->getBestScore();
      this->_best->setText(ss->str().c_str());
      delete(ss);
    }
  else
    {
      std::stringstream *ss = new std::stringstream;
      *ss << "Game Over:";
      *ss << this->_core->getScore();
      this->_score->setText(ss->str().c_str());
      delete (ss);
    }
}

int			libQt::init(ACore * const core, int argc, char **argv)
{
    std::stringstream   ss;

    this->_core = core;
    this->_app = new QApplication(argc, argv);
    this->_app->setApplicationName(this->_core->getTitle().c_str());
    this->_win = new NibblerWidget(this);
    this->_win->setWindowTitle(this->_core->getTitle().c_str());
    this->_grid = new QGridLayout(this->_win);
    this->_status = new QStatusBar;
    this->_bestStatus = new QStatusBar;
    this->_win->setLayout(this->_grid);
    this->_grid->setSpacing(0);
    this->_score = new QLabel("Score:0");
    ss << "Best : " << this->_core->getBestScore();
    this->_best = new QLabel(ss.str().c_str());
    this->_grid->addWidget(this->_status, this->_core->getGrid()->getSizeY(), 0, 30, 0);
    this->_grid->addWidget(this->_bestStatus, this->_core->getGrid()->getSizeY() + 30, 0, 30, 0);
    this->_bestStatus->addWidget(this->_best);
    this->_status->addWidget(this->_score);
    this->_timer = new QTimer(this->_win);
    this->_timer->connect(this->_timer, SIGNAL(timeout()), this->_win, SLOT(slot()));
    this->loadPixmap();
    return (0);
}

void			libQt::loadPixmap(void)
{
  std::stringstream   *ss;
  QString             s;

  // load the images, if images are invalid, Qt can handle it, it won't crash
  for (int i = 0; i <= 21; ++i)
    {
      ss = new std::stringstream;
      *ss << "./resources/";
      *ss << this->getName() << "/";
      *ss << this->_core->getName();
      *ss << "images/elem";
      *ss << i;
      *ss << ".png";
      s = ss->str().c_str();
      this->_map[i] = new QPixmap(s);
      delete (ss);
    }
}

int			libQt::run(void)
{
  this->initGrid();
  this->refresh();
  this->_win->show();
  this->_timer->start(this->_core->getSpeed());
  return (this->_app->exec());
}

void			libQt::destroy(void)
{
  if (this->_app)
    delete(this->_app);
  for (size_t i = 0; i <= 20; ++i)
    delete(this->_map[i]);
  if (this->_pix)
    {
      for (size_t i = 0; i < this->_core->getGrid()->getSizeY(); ++i)
	{
	  if (this->_pix[i])
	    delete[] (this->_pix[i]);
	  if (this->_pixVerif[i])
	    delete[] (this->_pixVerif[i]);
	}
      delete[] (this->_pix);
      delete[] (this->_pixVerif);
    }
  if (this->_score)
    delete(this->_score);
  if (this->_status)
    delete(this->_status);
  if (this->_best)
    delete(this->_best);
  if (this->_bestStatus)
    delete(this->_bestStatus);
  if (this->_grid)
    delete(this->_grid);
  if (this->_timer)
    delete(this->_timer);
}

extern "C" ALibrary*	entry(void)
{
  return (new libQt);
}
