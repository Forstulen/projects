#ifndef NIBBLERWIDGET_HH
#define NIBBLERWIDGET_HH

#include <iostream>
#include <QWidget>
#include <QKeyEvent>
#include "EKey.hh"
#include "lib.hh"

class libQt;

class NibblerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NibblerWidget(libQt* lib, QWidget *parent = 0);
    ~NibblerWidget();
    void keyPressEvent(QKeyEvent *);
    void pause(void);
    bool getDead(void) const { return (this->_dead); }

public slots:
    void slot();

private:
    KeyGame::eKeyCode   _currentKey;
    libQt*              _lib;
    bool                _pause;
    bool                _dead;
};

#endif // NIBBLERWIDGET_HH
