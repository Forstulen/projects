#ifndef		MAINWINDOW_H
#define		MAINWINDOW_H

#include	<map>
#include	<string>
#include	<QLabel>
#include	<QMainWindow>
#include	<QtGui/QApplication>

#include	"mapitem.h"
#include	"Singleton.hpp"

namespace	Ui
{
    class	MainWindow;
}

class		MainWindow : public QMainWindow
{
    Q_OBJECT


 public:

  friend class Tools::Singleton<MainWindow>;
  typedef std::map<unsigned int, std::string> map;

  explicit MainWindow(QWidget *parent = 0);

 public:

    ~MainWindow();

    std::string		getItem(unsigned int const) const;

private:

    Ui::MainWindow			*ui;
    unsigned int			select_;
    map					map_;
    MapItem*				labels[5200];

    void				reset();

private slots:

    void		on_toolButton_4_clicked();
    void		on_toolButton_3_clicked();

};

#endif // MAINWINDOW_H
