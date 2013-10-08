#ifndef MAPITEM_H
#define MAPITEM_H

#include <QLabel>

class MapItem : public QLabel
{
    Q_OBJECT

public:

  explicit        MapItem(unsigned int &value, QPixmap const &, QWidget *parent = 0);
  void            mousePressEvent(QMouseEvent *);
  unsigned int    getValue() const ;

signals:

    void    onClick();

public slots:


    void    click();
    void    setMap(unsigned int const value, QString const & str);

private:

    unsigned int      &select_;
    unsigned int      value;
};

#endif // MAPITEM_H
