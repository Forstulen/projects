#include <sstream>
#include <iostream>
#include "plazzawindow.hh"
#include "ui_plazzawindow.h"
#include "kitcheninspector.hh"

PlazzaWindow::PlazzaWindow(IReception *reception, QWidget *parent) :
    QMainWindow(parent),  ui(new Ui::PlazzaWindow), _reception(reception)
{
    ui->setupUi(this);
    this->connectSignalSlot();
    this->updateCommand();
}

PlazzaWindow::~PlazzaWindow()
{
    delete ui;
}

void PlazzaWindow::connectSignalSlot(void)
{
    this->ui->orderButton->connect(this->ui->orderButton, SIGNAL(clicked()), this, SLOT(sendCommand()));
    this->ui->pizza1->connect(this->ui->pizza1, SIGNAL(clicked()), this, SLOT(commandMargarita()));
    this->ui->pizza2->connect(this->ui->pizza2, SIGNAL(clicked()), this, SLOT(commandRegina()));
    this->ui->pizza3->connect(this->ui->pizza3, SIGNAL(clicked()), this, SLOT(commandAmericaine()));
    this->ui->pizza4->connect(this->ui->pizza4, SIGNAL(clicked()), this, SLOT(commandFantasia()));
    this->ui->pizzaSize->connect(this->ui->pizzaSize, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCommand()));
    this->ui->pizzaSize->connect(this->ui->pizzaNumber, SIGNAL(valueChanged(int)), this, SLOT(updateCommand()));
    this->ui->inspector->connect(this->ui->inspector, SIGNAL(clicked()), this, SLOT(openInspector()));
}

void PlazzaWindow::openInspector(void)
{
       KitchenInspector *inspector = new KitchenInspector(this->_reception);

       inspector->setModal(true);
       inspector->show();
}

void PlazzaWindow::sendCommand(void)
{
    this->_reception->receiveCommand(this->ui->orderLine->text().toStdString());
    this->ui->orderLine->clear();
}

void PlazzaWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();
}

void PlazzaWindow::updateCommand(void)
{
    std::stringstream ss;

    ss << this->ui->pizzaSize->currentText().toStdString();
    ss << " x";
    ss << this->ui->pizzaNumber->value();
    ss << "; ";
    this->_command = ss.str();
}

void PlazzaWindow::assemblyCommand(const std::string & pizza)
{
    std::string s;
    s = this->ui->orderLine->text().toStdString();
    s = s + pizza + " " + this->_command;
    this->ui->orderLine->setText(s.c_str());
}

void PlazzaWindow::commandMargarita(void)
{
    this->assemblyCommand("Margarita");
}

void PlazzaWindow::commandRegina(void)
{
    this->assemblyCommand("Regina");
}

void PlazzaWindow::commandAmericaine(void)
{
    this->assemblyCommand("Americaine");
}

void PlazzaWindow::commandFantasia(void)
{
    this->assemblyCommand("Fantasia");
}
