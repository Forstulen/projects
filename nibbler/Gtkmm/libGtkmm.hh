//
// libGtkmm.hh for gtkmm in /home/benram_s//Desktop/program/cpp/nibbler-2014-benram_s/Gtkmm
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Mar 12 18:23:11 2011 soufien benramdhane
// Last update Sun Mar 20 19:49:44 2011 romain tholimet
//

#ifndef			__LIBGTKMM_HH__
# define		__LIBGTKMM_HH__

# include		<gtkmm.h>
# include		<string>
# include		<map>

# include		"ALibrary.hh"
# include		"ACore.hh"

class			gtkWindow;

namespace		libGtk
{
  class			libGtkmm : public ALibrary
  {
    Gtk::Main		*_kit;
    Gtk::Table		*_grid;
    gtkWindow		*_win;
    Gtk::Image		**_img;
    Gtk::VBox		*_detail;
    Gtk::Label		*_score;
    Gtk::Label		*_bestScore;
    Gtk::Label		*_state;
    Gtk::Label		*_text;
    Gtk::ScrolledWindow	*_descr;
    Gtk::HBox		*_box;
    Gtk::Button		*_restart;
    int			**_type;
    std::map<int, std::string>		_map;

  public:
    libGtkmm() { this->_name = "GTK"; }
    virtual ~libGtkmm() {}

  public:
    virtual int			init(ACore * const core, int, char **);
    virtual void		destroy(void);
    virtual int			run(void);
    virtual void		refresh(void);

  private:
    void			allocateGrid(int x, int y);
    void			fillGrid();
    void			fillVBox();
    void			fillDetailScreen();
    void			initMap();

  public:
    ACore			*getCore(void) const;
    Gtk::Table &		getGrid() const;
    Gtk::Button 		*getButton() const;

  public:
    void			setScore();
    void			setBestScore();
    void			setState(std::string const & str);

  public:
    void			destroyDetail();
  };
}

#endif
