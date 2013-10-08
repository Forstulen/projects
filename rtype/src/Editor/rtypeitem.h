#ifndef RTYPEITEM_H
#define RTYPEITEM_H

#include <QLabel>

class RtypeItem : public QLabel
{
    Q_OBJECT
public:

    explicit RtypeItem(unsigned int const value, unsigned int &select, QWidget *parent = 0);

    void    mousePressEvent(QMouseEvent *);

signals:

    void    onClick();

public slots:


    void    click();

private:

   unsigned int      value_;
   unsigned int      &select_;

};

#endif // RTYPEITEM_H
