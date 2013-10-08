#ifndef LIB_HH
#define LIB_HH

#include <QApplication>
#include <QPixmap>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMap>
#include <QStatusBar>
#include <QTimer>
#include "ACore.hh"
#include "ALibrary.hh"
#include "nibblerwidget.hh"

class NibblerWidget;

class			libQt : public ALibrary
{
  QApplication*		_app;
  NibblerWidget*	_win;
  QGridLayout*		_grid;
  QMap<int, QPixmap *>	_map;
  QStatusBar*		_status;
  QStatusBar*		_bestStatus;
  QLabel*		_score;
  QLabel*		_best;
  QTimer*		_timer;
  QLabel**		_pix;
  int**			_pixVerif;

public:
  libQt();
  virtual ~libQt() {}
  virtual int		init(ACore * const, int, char **);
  virtual int		run(void);
  virtual void		destroy(void);
  virtual void		refresh(void);
  virtual void		initGrid(void);
  ACore*		getCore(void) const { return (this->_core); }
  QTimer*		getTimer(void) const { return (this->_timer); }
  QLabel*		getScore(void) const { return (this->_score); }
  void			updateScore(void);
  void			loadPixmap(void);
};

#endif // LIB_HH
