/********************************************************************************
** Form generated from reading UI file 'dlgvmsettings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGVMSETTINGS_H
#define UI_DLGVMSETTINGS_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "driver.h"

QT_BEGIN_NAMESPACE

class Ui_dlgVMSettings
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *lblPrintWidth;
    QSpinBox *spinPort;
    QHBoxLayout *hboxLayout1;
    QLabel *lblDevice;
    QLineEdit *editHost;
    QHBoxLayout *hboxLayout2;
    QLabel *lblDevice_2;
    QLineEdit *editDb;
    QHBoxLayout *hboxLayout3;
    QLabel *lblTable;
    QSpinBox *spinTable;
    QHBoxLayout *hboxLayout4;
    QLabel *lblDevice_2_2_2;
    QLineEdit *editPrefix;
    QHBoxLayout *hboxLayout5;
    QLabel *lblDevice_2_2;
    QLineEdit *editLogin;
    QHBoxLayout *hboxLayout6;
    QLabel *lblDevice_2_2_3;
    QLineEdit *editPassword;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout7;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QPushButton *btnTestConnect;

    void setupUi(QDialog *dlgVMSettings)
    {
        if (dlgVMSettings->objectName().isEmpty())
            dlgVMSettings->setObjectName(QString::fromUtf8("dlgVMSettings"));
        dlgVMSettings->resize(230, 322);
        gridLayout = new QGridLayout(dlgVMSettings);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblPrintWidth = new QLabel(dlgVMSettings);
        lblPrintWidth->setObjectName(QString::fromUtf8("lblPrintWidth"));
        lblPrintWidth->setWordWrap(false);

        hboxLayout->addWidget(lblPrintWidth);

        spinPort = new QSpinBox(dlgVMSettings);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setMaximum(65535);
        spinPort->setValue(1018);

        hboxLayout->addWidget(spinPort);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblDevice = new QLabel(dlgVMSettings);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setWordWrap(false);

        hboxLayout1->addWidget(lblDevice);

        editHost = new QLineEdit(dlgVMSettings);
        editHost->setObjectName(QString::fromUtf8("editHost"));

        hboxLayout1->addWidget(editHost);


        gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblDevice_2 = new QLabel(dlgVMSettings);
        lblDevice_2->setObjectName(QString::fromUtf8("lblDevice_2"));
        lblDevice_2->setWordWrap(false);

        hboxLayout2->addWidget(lblDevice_2);

        editDb = new QLineEdit(dlgVMSettings);
        editDb->setObjectName(QString::fromUtf8("editDb"));

        hboxLayout2->addWidget(editDb);


        gridLayout->addLayout(hboxLayout2, 2, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblTable = new QLabel(dlgVMSettings);
        lblTable->setObjectName(QString::fromUtf8("lblTable"));
        lblTable->setWordWrap(false);

        hboxLayout3->addWidget(lblTable);

        spinTable = new QSpinBox(dlgVMSettings);
        spinTable->setObjectName(QString::fromUtf8("spinTable"));
        spinTable->setMaximum(100);
        spinTable->setValue(1);

        hboxLayout3->addWidget(spinTable);


        gridLayout->addLayout(hboxLayout3, 6, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        lblDevice_2_2_2 = new QLabel(dlgVMSettings);
        lblDevice_2_2_2->setObjectName(QString::fromUtf8("lblDevice_2_2_2"));
        lblDevice_2_2_2->setWordWrap(false);

        hboxLayout4->addWidget(lblDevice_2_2_2);

        editPrefix = new QLineEdit(dlgVMSettings);
        editPrefix->setObjectName(QString::fromUtf8("editPrefix"));

        hboxLayout4->addWidget(editPrefix);


        gridLayout->addLayout(hboxLayout4, 5, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblDevice_2_2 = new QLabel(dlgVMSettings);
        lblDevice_2_2->setObjectName(QString::fromUtf8("lblDevice_2_2"));
        lblDevice_2_2->setWordWrap(false);

        hboxLayout5->addWidget(lblDevice_2_2);

        editLogin = new QLineEdit(dlgVMSettings);
        editLogin->setObjectName(QString::fromUtf8("editLogin"));

        hboxLayout5->addWidget(editLogin);


        gridLayout->addLayout(hboxLayout5, 3, 0, 1, 1);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblDevice_2_2_3 = new QLabel(dlgVMSettings);
        lblDevice_2_2_3->setObjectName(QString::fromUtf8("lblDevice_2_2_3"));
        lblDevice_2_2_3->setWordWrap(false);

        hboxLayout6->addWidget(lblDevice_2_2_3);

        editPassword = new QLineEdit(dlgVMSettings);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setEchoMode(QLineEdit::Password);

        hboxLayout6->addWidget(editPassword);


        gridLayout->addLayout(hboxLayout6, 4, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgVMSettings);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout7->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgVMSettings);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout7->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout7);

        btnTestConnect = new QPushButton(dlgVMSettings);
        btnTestConnect->setObjectName(QString::fromUtf8("btnTestConnect"));

        vboxLayout->addWidget(btnTestConnect);


        gridLayout->addLayout(vboxLayout, 7, 0, 1, 1);

        QWidget::setTabOrder(editHost, spinPort);
        QWidget::setTabOrder(spinPort, editDb);
        QWidget::setTabOrder(editDb, editLogin);
        QWidget::setTabOrder(editLogin, editPassword);
        QWidget::setTabOrder(editPassword, editPrefix);
        QWidget::setTabOrder(editPrefix, spinTable);
        QWidget::setTabOrder(spinTable, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);
        QWidget::setTabOrder(buttonCancel, btnTestConnect);

        retranslateUi(dlgVMSettings);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgVMSettings, SLOT(apply()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgVMSettings, SLOT(reject()));
        QObject::connect(editPassword, SIGNAL(textChanged(QString)), dlgVMSettings, SLOT(passwordChanged(QString)));
        QObject::connect(btnTestConnect, SIGNAL(clicked()), dlgVMSettings, SLOT(testConnection()));

        QMetaObject::connectSlotsByName(dlgVMSettings);
    } // setupUi

    void retranslateUi(QDialog *dlgVMSettings)
    {
        dlgVMSettings->setWindowTitle(QApplication::translate("dlgVMSettings", "VirtualMart", 0, QApplication::UnicodeUTF8));
        lblPrintWidth->setText(QApplication::translate("dlgVMSettings", "port", 0, QApplication::UnicodeUTF8));
        lblDevice->setText(QApplication::translate("dlgVMSettings", "host", 0, QApplication::UnicodeUTF8));
        lblDevice_2->setText(QApplication::translate("dlgVMSettings", "database", 0, QApplication::UnicodeUTF8));
        lblTable->setText(QApplication::translate("dlgVMSettings", "table", 0, QApplication::UnicodeUTF8));
        lblDevice_2_2_2->setText(QApplication::translate("dlgVMSettings", "prefix", 0, QApplication::UnicodeUTF8));
        lblDevice_2_2->setText(QApplication::translate("dlgVMSettings", "login", 0, QApplication::UnicodeUTF8));
        lblDevice_2_2_3->setText(QApplication::translate("dlgVMSettings", "password", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgVMSettings", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgVMSettings", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        btnTestConnect->setText(QApplication::translate("dlgVMSettings", "Test connection", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgVMSettings: public Ui_dlgVMSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGVMSETTINGS_H
