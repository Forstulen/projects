/********************************************************************************
** Form generated from reading UI file 'plazzawindow.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAZZAWINDOW_H
#define UI_PLAZZAWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlazzaWindow
{
public:
    QAction *actionQuit;
    QAction *actionAbout_Plazza;
    QAction *actionAbout_Qt;
    QAction *actionCommand_pizza;
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pizza1;
    QPushButton *pizza2;
    QPushButton *pizza3;
    QPushButton *pizza4;
    QLineEdit *orderLine;
    QPushButton *orderButton;
    QListWidget *logList;
    QSpinBox *pizzaNumber;
    QComboBox *pizzaSize;
    QPushButton *inspector;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlazzaWindow)
    {
        if (PlazzaWindow->objectName().isEmpty())
            PlazzaWindow->setObjectName(QString::fromUtf8("PlazzaWindow"));
        PlazzaWindow->resize(763, 583);
        actionQuit = new QAction(PlazzaWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout_Plazza = new QAction(PlazzaWindow);
        actionAbout_Plazza->setObjectName(QString::fromUtf8("actionAbout_Plazza"));
        actionAbout_Qt = new QAction(PlazzaWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionCommand_pizza = new QAction(PlazzaWindow);
        actionCommand_pizza->setObjectName(QString::fromUtf8("actionCommand_pizza"));
        centralwidget = new QWidget(PlazzaWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(5, 4, 651, 251));
        label->setPixmap(QPixmap(QString::fromUtf8("resources/plazza-reception-tmp.jpg")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        pizza1 = new QPushButton(centralwidget);
        pizza1->setObjectName(QString::fromUtf8("pizza1"));
        pizza1->setGeometry(QRect(660, 4, 100, 100));
        pizza1->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/pizza1-tmp.png"), QSize(), QIcon::Normal, QIcon::Off);
        pizza1->setIcon(icon);
        pizza1->setIconSize(QSize(95, 95));
        pizza2 = new QPushButton(centralwidget);
        pizza2->setObjectName(QString::fromUtf8("pizza2"));
        pizza2->setGeometry(QRect(660, 111, 100, 100));
        pizza2->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("resources/pizza2-tmp.png"), QSize(), QIcon::Normal, QIcon::Off);
        pizza2->setIcon(icon1);
        pizza2->setIconSize(QSize(90, 90));
        pizza3 = new QPushButton(centralwidget);
        pizza3->setObjectName(QString::fromUtf8("pizza3"));
        pizza3->setGeometry(QRect(660, 218, 100, 100));
        pizza3->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("resources/pizza3-tmp.png"), QSize(), QIcon::Normal, QIcon::Off);
        pizza3->setIcon(icon2);
        pizza3->setIconSize(QSize(90, 90));
        pizza4 = new QPushButton(centralwidget);
        pizza4->setObjectName(QString::fromUtf8("pizza4"));
        pizza4->setGeometry(QRect(660, 326, 100, 100));
        pizza4->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("resources/pizza4-tmp.png"), QSize(), QIcon::Normal, QIcon::Off);
        pizza4->setIcon(icon3);
        pizza4->setIconSize(QSize(100, 100));
        orderLine = new QLineEdit(centralwidget);
        orderLine->setObjectName(QString::fromUtf8("orderLine"));
        orderLine->setGeometry(QRect(4, 259, 551, 27));
        orderButton = new QPushButton(centralwidget);
        orderButton->setObjectName(QString::fromUtf8("orderButton"));
        orderButton->setGeometry(QRect(556, 259, 101, 27));
        orderButton->setDefault(true);
        logList = new QListWidget(centralwidget);
        logList->setObjectName(QString::fromUtf8("logList"));
        logList->setGeometry(QRect(5, 288, 651, 241));
        pizzaNumber = new QSpinBox(centralwidget);
        pizzaNumber->setObjectName(QString::fromUtf8("pizzaNumber"));
        pizzaNumber->setGeometry(QRect(660, 468, 100, 27));
        pizzaNumber->setMinimum(1);
        pizzaNumber->setMaximum(100);
        pizzaSize = new QComboBox(centralwidget);
        pizzaSize->setObjectName(QString::fromUtf8("pizzaSize"));
        pizzaSize->setGeometry(QRect(660, 433, 100, 27));
        inspector = new QPushButton(centralwidget);
        inspector->setObjectName(QString::fromUtf8("inspector"));
        inspector->setGeometry(QRect(660, 503, 98, 27));
        PlazzaWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlazzaWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 763, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        PlazzaWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlazzaWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlazzaWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout_Plazza);
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(PlazzaWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), PlazzaWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(PlazzaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlazzaWindow)
    {
        PlazzaWindow->setWindowTitle(QApplication::translate("PlazzaWindow", "Plazza", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("PlazzaWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionAbout_Plazza->setText(QApplication::translate("PlazzaWindow", "About Plazza", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("PlazzaWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionCommand_pizza->setText(QApplication::translate("PlazzaWindow", "Command pizza", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        pizza1->setText(QString());
        pizza2->setText(QString());
        pizza3->setText(QString());
        pizza4->setText(QString());
        orderLine->setText(QString());
        orderButton->setText(QApplication::translate("PlazzaWindow", "Order", 0, QApplication::UnicodeUTF8));
        pizzaSize->clear();
        pizzaSize->insertItems(0, QStringList()
         << QApplication::translate("PlazzaWindow", "S", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlazzaWindow", "M", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlazzaWindow", "L", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlazzaWindow", "XL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PlazzaWindow", "XXL", 0, QApplication::UnicodeUTF8)
        );
        inspector->setText(QApplication::translate("PlazzaWindow", "Inspector", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("PlazzaWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("PlazzaWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlazzaWindow: public Ui_PlazzaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAZZAWINDOW_H
