
#include	<iostream>
#include	<sstream>
#include	<QIconSet>
#include	<QPushButton>
#include	<QMessageBox>
#include	<QGridLayout>
#include	<QFileDialog>
#include	<QStandardItemModel>

#include	"rtypeitem.h"
#include	"mainwindow.h"
#include	"ui_mainwindow.h"

#include	"Table.hpp"
#include	"Database.hpp"
#include	"Exception.hpp"
#include	"Conversions.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  select_(0)
{
  RTDB::Table			*table = RTDB::Database::getInstance()["Images"];
  RTDB::Table			*table2 = RTDB::Database::getInstance()["Map"];

  if (!table || !table2)
    throw Exception("RTDB::Table", "Cannot find Image Table");

  RTDB::Table::Rows const	&rows = table->getRows();
  RTDB::Table::Rows const	&rows2 = table2->getRows();

  this->ui->setupUi(this);
  for (int i = 0; i < 5200; ++i)
    labels[i] = NULL;

  RtypeItem			*emptyItem = new RtypeItem(0, this->select_, this);

  emptyItem->setPixmap(QPixmap(""));
  emptyItem->setFixedHeight(16);
  emptyItem->setFixedWidth(64);
  this->ui->verticalLayout->addWidget(emptyItem);
  this->map_[0] = "";

  for (RTDB::Table::Rows::const_iterator it = rows.begin(); it != rows.end(); ++it)
    if (it->second.size() >= 2 && !it->second[0].compare(0, 5, "block"))
      {
	for (RTDB::Table::Rows::const_iterator it2 = rows2.begin(); it2 != rows2.end(); ++it2)
	  if (it2->second[1].compare(it->second[1]) == 0)
	    this->map_[ Conversions::convertString<unsigned int>(it2->second[0])]
	      = std::string("../../resource/sprites/" + it->second[0] + ".png");
      }

  for (map::iterator i = this->map_.begin() ; i != this->map_.end(); ++i)
    {
      RtypeItem		*label = new RtypeItem(i->first, this->select_, this);

      label->setPixmap(QPixmap(QString(i->second.c_str())));
      label->setFixedHeight(16);
      label->setFixedWidth(64);
      this->ui->verticalLayout->addWidget(label);
    }

  int const nb = 26;

  this->ui->gridLayout_3->setSpacing(0);
  for (int row = 0; row < nb; ++row)
    for (int col = 0; col < 200; ++col)
      {
	labels[row + col * nb] = new MapItem(this->select_, QPixmap(""));
	labels[row + col * nb]->setFixedHeight(16);
	labels[row + col * nb]->setFixedWidth(64);
	this->ui->gridLayout_3->addWidget(labels[row + col * nb] , row, col);
      }

  QWidget *a = new QWidget();
  a->setLayout(this->ui->gridLayout_3);
  this->ui->scrollArea->setWidget(a);
  QWidget *b = new QWidget();
  b->setLayout(this->ui->verticalLayout);
  this->ui->scrollArea_2->setWidget(b);
}

std::string				MainWindow::getItem(unsigned int const value) const
{
  MainWindow::map::const_iterator	it = this->map_.find(value);

  return (it == this->map_.end()) ? "" :  it->second ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::reset()
{
  for (int row = 0; row < 26; ++row)
    for (int col = 0; col < 200; ++col)
      this->labels[row + col * 26]->setMap(0, QString(""));
}

void				MainWindow::on_toolButton_3_clicked()
{
  RTDB::Table			*table = RTDB::Database::getInstance()["Map"];
  RTDB::Table::Rows const	&rows = table->getRows();
  QString			fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
									"", tr("R-Type Map (*.rtmap)"));
  QFile				file(fileName);
  bool				end = false;

  file.open(QIODevice::ReadOnly);
  if (file.isOpen())
  {
    this->reset();

    for (int row = 0; row < 26 && !end; ++row)
    {
        QByteArray		line = file.readLine();
        QList<QByteArray>	elements = line.split(';');

        for (int col = 0; col <  200 && col < elements.size() && !end; ++col)
        {
            std::istringstream     iss(elements.at(col).constData());
            unsigned int           elem = 0;

            iss >> elem;
            if (elem >= this->map_.size())
	      elem = 0;
	    this->labels[row + col * 26]->setMap(elem, QString(this->map_[elem].c_str()));
       }
	if (!line.size())
	  end = true;
    }
    file.close();
  }
  else
    QMessageBox::warning(this, "Error", file.errorString(), QMessageBox::Close);
}

void MainWindow::on_toolButton_4_clicked()
{
  QString	fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("R-Type Map (*.rtmap)"));
  QFile		file(fileName);

  file.open(QIODevice::Truncate | QIODevice::WriteOnly);
  std::ostringstream     oss;

  if (file.isOpen())
    {
      for (int row = 0; row < 26; ++row)
	{
	  (row) ? oss << std::endl : oss << "" ;
	  for (int col = 0; col < 200; ++col)
	    (col) ? oss << ";" << this->labels[row + col * 26]->getValue() :
	      oss << this->labels[row + col * 26]->getValue();
	}
      oss << "!" << std::endl;
      file.write(oss.str().c_str());
      file.close();
    }
  else
    QMessageBox::warning(this, "Error", file.errorString(), QMessageBox::Close);
}
