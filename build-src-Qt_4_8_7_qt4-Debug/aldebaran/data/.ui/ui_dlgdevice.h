/********************************************************************************
** Form generated from reading UI file 'dlgdevice.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDEVICE_H
#define UI_DLGDEVICE_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "dataeq.h"
#include "driver.h"
#include "engine.h"

QT_BEGIN_NAMESPACE

class Ui_dlgDevice
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *lblName;
    QLineEdit *editName;
    QHBoxLayout *hboxLayout2;
    QLabel *lblType;
    QComboBox *comboType;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnSettings;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QCheckBox *chkEnabled;

    void setupUi(QDialog *dlgDevice)
    {
        if (dlgDevice->objectName().isEmpty())
            dlgDevice->setObjectName(QString::fromUtf8("dlgDevice"));
        dlgDevice->resize(353, 92);
        dlgDevice->setSizeGripEnabled(false);
        dlgDevice->setModal(true);
        gridLayout = new QGridLayout(dlgDevice);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblName = new QLabel(dlgDevice);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblName->sizePolicy().hasHeightForWidth());
        lblName->setSizePolicy(sizePolicy);
        lblName->setWordWrap(false);

        hboxLayout1->addWidget(lblName);

        editName = new QLineEdit(dlgDevice);
        editName->setObjectName(QString::fromUtf8("editName"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(editName->sizePolicy().hasHeightForWidth());
        editName->setSizePolicy(sizePolicy1);
        editName->setMaximumSize(QSize(300, 32767));

        hboxLayout1->addWidget(editName);


        hboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblType = new QLabel(dlgDevice);
        lblType->setObjectName(QString::fromUtf8("lblType"));
        lblType->setWordWrap(false);

        hboxLayout2->addWidget(lblType);

        comboType = new QComboBox(dlgDevice);
        comboType->setObjectName(QString::fromUtf8("comboType"));

        hboxLayout2->addWidget(comboType);


        hboxLayout->addLayout(hboxLayout2);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        btnSettings = new QPushButton(dlgDevice);
        btnSettings->setObjectName(QString::fromUtf8("btnSettings"));

        hboxLayout3->addWidget(btnSettings);

        Horizontal_Spacing2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgDevice);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout3->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgDevice);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout3->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout3, 2, 0, 1, 1);

        chkEnabled = new QCheckBox(dlgDevice);
        chkEnabled->setObjectName(QString::fromUtf8("chkEnabled"));

        gridLayout->addWidget(chkEnabled, 1, 0, 1, 1);


        retranslateUi(dlgDevice);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgDevice, SLOT(apply()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgDevice, SLOT(reject()));
        QObject::connect(comboType, SIGNAL(activated(QString)), dlgDevice, SLOT(driverSelected(QString)));
        QObject::connect(btnSettings, SIGNAL(clicked()), dlgDevice, SLOT(settingsDialog()));

        QMetaObject::connectSlotsByName(dlgDevice);
    } // setupUi

    void retranslateUi(QDialog *dlgDevice)
    {
        dlgDevice->setWindowTitle(QApplication::translate("dlgDevice", "Device", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("dlgDevice", "name:", 0, QApplication::UnicodeUTF8));
        lblType->setText(QApplication::translate("dlgDevice", "type:", 0, QApplication::UnicodeUTF8));
        btnSettings->setText(QApplication::translate("dlgDevice", "Settings", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgDevice", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgDevice", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        chkEnabled->setText(QApplication::translate("dlgDevice", "Enabled", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgDevice: public Ui_dlgDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGDEVICE_H
