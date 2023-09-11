/********************************************************************************
** Form generated from reading UI file 'winserver.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSERVER_H
#define UI_WINSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinServer
{
public:

    void setupUi(QWidget *WinServer)
    {
        if (WinServer->objectName().isEmpty())
            WinServer->setObjectName("WinServer");
        WinServer->resize(400, 300);

        retranslateUi(WinServer);

        QMetaObject::connectSlotsByName(WinServer);
    } // setupUi

    void retranslateUi(QWidget *WinServer)
    {
        WinServer->setWindowTitle(QCoreApplication::translate("WinServer", "WinServer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinServer: public Ui_WinServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSERVER_H
