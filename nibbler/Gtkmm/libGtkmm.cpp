//
// libGtkmm.cpp for gtkmm in /home/benram_s//Desktop/program/cpp/nibbler-2014-benram_s/Gtkmm
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Mar 12 18:25:36 2011 soufien benramdhane
// Last update Sun Mar 20 19:49:52 2011 romain tholimet
//

#include	<iostream>
#include	<sstream>

#include	"gtkWindow.hh"
#include	"libGtkmm.hh"

int			libGtk::libGtkmm::init(ACore * const core, int argc, char **argv)
{
  this->_kit = new Gtk::Main(argc, argv);
  this->_core = core;
  this->_win = new gtkWindow(this);
  this->initMap();
  this->fillGrid();
  this->_win->set_title(this->_core->getTitle());
  this->_win->set_position(Gtk::WIN_POS_CENTER);
  this->_win->resize(this->_core->getGrid()->getSizeX() * 15,
		     this->_core->getGrid()->getSizeY() * 15);
  this->_box = new Gtk::HBox;
  this->fillVBox();
  this->_restart->signal_clicked().connect(sigc::mem_fun(*this->_core, &ACore::restartGame));
  this->_restart->signal_clicked().connect(sigc::mem_fun(*this, &libGtk::libGtkmm::refresh));
}

void			libGtk::libGtkmm::initMap()
{
  std::stringstream	*ss;

  for (int i = 0; i <= 20; ++i)
    {
      ss = new std::stringstream;
      *ss << "./resources/" << this->getName() << "/" << this->getCore()->getName() << "images/elem" << i << ".png";
      this->_map[i] = ss->str().c_str();
      delete ss;
    }
}

void			libGtk::libGtkmm::fillDetailScreen()
{
  this->_detail = new Gtk::VBox;
  this->_restart = new Gtk::Button("Restart");
  this->_score = new Gtk::Label("Score : 0");
  this->_bestScore = new Gtk::Label("Best Score : ");
  this->setBestScore();
  this->_descr = new Gtk::ScrolledWindow;
  this->_state = new Gtk::Label("State :\n   Press any key to start   ");
  this->_text = new Gtk::Label(this->_core->getDescription());
}

void			libGtk::libGtkmm::fillVBox()
{
  this->fillDetailScreen();
  this->_descr->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  this->_descr->add(*this->_text);
  this->_state->set_justify(Gtk::JUSTIFY_CENTER);
  this->_detail->pack_start(*this->_descr);
  this->_detail->pack_start(*this->_score);
  this->_detail->pack_start(*this->_bestScore);
  this->_detail->pack_start(*this->_state);
  this->_detail->pack_start(*this->_restart);
  this->_box->pack_start(*(this->_grid));
  this->_box->pack_start(*(this->_detail));
  this->_win->add(*(this->_box));
  this->_win->show_all();
}

void			libGtk::libGtkmm::allocateGrid(int x, int y)
{
  this->_grid = new Gtk::Table(x / 15, y / 15);
  this->_img = new Gtk::Image *[y / 15];
  this->_type = new int *[y / 15];
  for (int j = 0; j < y; j = j + 15)
    {
      this->_img[j / 15] = new Gtk::Image[x / 15];
      this->_type[j / 15] = new int[x / 15];
    }
}

void			libGtk::libGtkmm::fillGrid()
{
  int			x = this->_core->getGrid()->getSizeX() * 15;
  int			y = this->_core->getGrid()->getSizeY() * 15;

  this->allocateGrid(x, y);
  for (int i = 0; i < x; i = i + 15)
    {
      for (int j = 0; j < y; j = j + 15)
	{
	  this->_img[j / 15][i / 15].set(this->_map[this->_core->getGrid()->getPoint(i / 15, j / 15)]);
	  this->_grid->attach(this->_img[j / 15][i / 15], i, i + 14, j, j + 14, Gtk::FILL, Gtk::FILL);
	  this->_type[j / 15][i / 15] = this->_core->getGrid()->getPoint(i / 15, j / 15);
	}
    }
}

//----------------------------------------------------------------------------

int			libGtk::libGtkmm::run()
{
  this->refresh();
  this->_grid->show_all();
  Gtk::Main::run(*(this->_win));
  return (0);
}

void			libGtk::libGtkmm::refresh()
{
  int			x = this->_core->getGrid()->getSizeX();
  int			y = this->_core->getGrid()->getSizeY();

  for (int i = 0; i < x; ++i)
    for (int j = 0; j < y; ++j)
      if (this->_type[j][i] != this->_core->getGrid()->getPoint(i, j))
	{
	  this->_img[j][i].set(this->_map[this->_core->getGrid()->getPoint(i, j)]);
	  this->_type[j][i] = this->_core->getGrid()->getPoint(i, j);
	}
  this->setScore();
  this->setBestScore();
  this->_win->setDeadFalse();
  this->_grid->show_all();
}

//----------------------------------------------------------------------------

void			libGtk::libGtkmm::destroy()
{
  int			y = this->_core->getGrid()->getSizeY();

  if (this->_kit)
    delete this->_kit;
  if (this->_grid)
    delete this->_grid;
  if (this->_win)
    delete this->_win;
  for (int i = 0; i < y; ++i)
    {
      delete[] this->_img[i];
      delete[] this->_type[i];
    }
  delete[] this->_img;
  delete[] this->_type;
  this->destroyDetail();
}

void			libGtk::libGtkmm::destroyDetail()
{
  delete this->_bestScore;
  delete this->_score;
  delete this->_state;
  delete this->_descr;
  delete this->_restart;
  delete this->_detail;
  delete this->_box;
  delete this->_text;
}

//---------------------------------------------------------------------------

Gtk::Table  & 		libGtk::libGtkmm::getGrid() const
{
  return (*this->_grid);
}

ACore			*libGtk::libGtkmm::getCore(void) const
{
  return (this->_core);
}

Gtk::Button 		*libGtk::libGtkmm::getButton() const
{
  return (this->_restart);
}

//----------------------------------------------------------------------------

void			libGtk::libGtkmm::setState(std::string const & str)
{
  this->_state->set_text("State :\n" + str);
}

void			libGtk::libGtkmm::setScore()
{
  std::stringstream	*ss = new std::stringstream;

  *ss << "Score : " << this->_core->getScore();
  this->_score->set_text(ss->str().c_str());
  delete ss;
}

void			libGtk::libGtkmm::setBestScore()
{
  std::stringstream	*ss = new std::stringstream;

  *ss << "Best Score : " << this->_core->getBestScore();
  this->_bestScore->set_text(ss->str().c_str());
  delete ss;
}

//----------------------------------------------------------------------------

extern "C"	ALibrary*	entry(void)
{
  return (new libGtk::libGtkmm);
}
