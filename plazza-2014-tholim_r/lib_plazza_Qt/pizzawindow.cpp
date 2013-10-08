#include <QInputDialog>
#include "Reception.hh"
#include "pizzawindow.hh"

extern Reception *gl_reception;

PizzaWindow::PizzaWindow(QWidget *parent)
    : QWidget(parent)
{
}

PizzaWindow::~PizzaWindow()
{

}

void        PizzaWindow::KeyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();
}

void        PizzaWindow::slot(void)
{
    this->_str = QInputDialog::getText(this, "Order", "Enter your order").toStdString();
    gl_reception->do_un_truc(this->_str);
}
