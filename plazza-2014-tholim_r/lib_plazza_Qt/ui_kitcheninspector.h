/********************************************************************************
** Form generated from reading UI file 'kitcheninspector.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KITCHENINSPECTOR_H
#define UI_KITCHENINSPECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KitchenInspector
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *KitchenInspector)
    {
        if (KitchenInspector->objectName().isEmpty())
            KitchenInspector->setObjectName(QString::fromUtf8("KitchenInspector"));
        KitchenInspector->resize(1072, 350);
        listWidget = new QListWidget(KitchenInspector);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(4, 4, 1061, 341));

        retranslateUi(KitchenInspector);

        QMetaObject::connectSlotsByName(KitchenInspector);
    } // setupUi

    void retranslateUi(QWidget *KitchenInspector)
    {
        KitchenInspector->setWindowTitle(QApplication::translate("KitchenInspector", "Kitchen Inspector", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KitchenInspector: public Ui_KitchenInspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KITCHENINSPECTOR_H
