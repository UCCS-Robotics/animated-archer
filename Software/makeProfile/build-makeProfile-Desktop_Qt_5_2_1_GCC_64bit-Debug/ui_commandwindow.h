/********************************************************************************
** Form generated from reading UI file 'commandwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDWINDOW_H
#define UI_COMMANDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_commandwindow
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *commandwindow)
    {
        if (commandwindow->objectName().isEmpty())
            commandwindow->setObjectName(QStringLiteral("commandwindow"));
        commandwindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(commandwindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(commandwindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), commandwindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), commandwindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(commandwindow);
    } // setupUi

    void retranslateUi(QDialog *commandwindow)
    {
        commandwindow->setWindowTitle(QApplication::translate("commandwindow", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class commandwindow: public Ui_commandwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDWINDOW_H
