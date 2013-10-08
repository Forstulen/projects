#include "rtypeitem.h"
#include <iostream>

RtypeItem::RtypeItem(unsigned int const value, unsigned int &select, QWidget *parent) :
  QLabel(parent),
  value_(value),
  select_(select)
{
  connect(this, SIGNAL(onClick()), this, SLOT(click()));
}

void    RtypeItem::mousePressEvent(QMouseEvent *)
{
    emit onClick();
}

void    RtypeItem::click()
{
  this->select_ = this->value_;
}

