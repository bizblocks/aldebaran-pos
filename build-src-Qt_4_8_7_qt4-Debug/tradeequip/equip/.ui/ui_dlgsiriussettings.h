/********************************************************************************
** Form generated from reading UI file 'dlgsiriussettings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSIRIUSSETTINGS_H
#define UI_DLGSIRIUSSETTINGS_H

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
#include "driver.h"

QT_BEGIN_NAMESPACE

class Ui_dlgSiriusSettings
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *lblDevice;
    QLineEdit *editHost;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QHBoxLayout *hboxLayout2;
    QLabel *lblPrintWidth;
    QSpinBox *spinPort;
    QHBoxLayout *hboxLayout3;
    QLabel *lblTable;
    QSpinBox *spinTable;

    void setupUi(QDialog *dlgSiriusSettings)
    {
        if (dlgSiriusSettings->objectName().isEmpty())
            dlgSiriusSettings->setObjectName(QString::fromUtf8("dlgSiriusSettings"));
        dlgSiriusSettings->resize(208, 115);
        gridLayout = new QGridLayout(dlgSiriusSettings);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblDevice = new QLabel(dlgSiriusSettings);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setWordWrap(false);

        hboxLayout->addWidget(lblDevice);

        editHost = new QLineEdit(dlgSiriusSettings);
        editHost->setObjectName(QString::fromUtf8("editHost"));

        hboxLayout->addWidget(editHost);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgSiriusSettings);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout1->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgSiriusSettings);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout1->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout1, 3, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblPrintWidth = new QLabel(dlgSiriusSettings);
        lblPrintWidth->setObjectName(QString::fromUtf8("lblPrintWidth"));
        lblPrintWidth->setWordWrap(false);

        hboxLayout2->addWidget(lblPrintWidth);

        spinPort = new QSpinBox(dlgSiriusSettings);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setMaximum(65535);
        spinPort->setValue(1018);

        hboxLayout2->addWidget(spinPort);


        gridLayout->addLayout(hboxLayout2, 1, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblTable = new QLabel(dlgSiriusSettings);
        lblTable->setObjectName(QString::fromUtf8("lblTable"));
        lblTable->setWordWrap(false);

        hboxLayout3->addWidget(lblTable);

        spinTable = new QSpinBox(dlgSiriusSettings);
        spinTable->setObjectName(QString::fromUtf8("spinTable"));
        spinTable->setMaximum(100);
        spinTable->setValue(1);

        hboxLayout3->addWidget(spinTable);


        gridLayout->addLayout(hboxLayout3, 2, 0, 1, 1);


        retranslateUi(dlgSiriusSettings);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgSiriusSettings, SLOT(apply()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgSiriusSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlgSiriusSettings);
    } // setupUi

    void retranslateUi(QDialog *dlgSiriusSettings)
    {
        dlgSiriusSettings->setWindowTitle(QApplication::translate("dlgSiriusSettings", "Sirius", 0, QApplication::UnicodeUTF8));
        lblDevice->setText(QApplication::translate("dlgSiriusSettings", "host", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgSiriusSettings", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgSiriusSettings", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        lblPrintWidth->setText(QApplication::translate("dlgSiriusSettings", "port", 0, QApplication::UnicodeUTF8));
        lblTable->setText(QApplication::translate("dlgSiriusSettings", "table", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgSiriusSettings: public Ui_dlgSiriusSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSIRIUSSETTINGS_H
