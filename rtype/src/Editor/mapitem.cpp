#include	<iostream>

#include	"mapitem.h"
#include	"Table.hpp"
#include	"mainwindow.h"
#include	"Database.hpp"
#include	"Conversions.hpp"


MapItem::MapItem(unsigned int &value, QPixmap const &pixmap, QWidget *parent) :
  QLabel(parent),
  select_(value),
  value(value)
{
  connect(this, SIGNAL(onClick()), this, SLOT(click()));
  this->setPixmap(pixmap);
}

void    MapItem::mousePressEvent(QMouseEvent *)
{
  emit	onClick();
}

unsigned int MapItem::getValue() const
{
  return this->value;
}

void			MapItem::click()
{
  if (this->value != this->select_)
    {
      this->setPixmap(QPixmap(Tools::Singleton<MainWindow>::getInstance().getItem(this->select_).c_str()));
      this->value = this->select_;
    }
}

void    MapItem::setMap(unsigned int const value, QString const & str)
{
  this->value = value;
  this->setPixmap(QPixmap(str));
}
