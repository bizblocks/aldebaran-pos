/********************************************************************************
** Form generated from reading UI file 'dlgmscreader.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMSCREADER_H
#define UI_DLGMSCREADER_H

#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "driver.h"

QT_BEGIN_NAMESPACE

class Ui_dlgMSCReader
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    Q3GroupBox *groupBox1;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *lblDataBits;
    QComboBox *comboDataBits;
    QHBoxLayout *hboxLayout2;
    QLabel *lblBaudRate;
    QComboBox *comboBaudRate;
    QHBoxLayout *hboxLayout3;
    QLabel *lblStopBits;
    QComboBox *comboStopBits;
    QHBoxLayout *hboxLayout4;
    QLabel *lblDevice;
    QLineEdit *editDevice;
    QHBoxLayout *hboxLayout5;
    QLabel *lblFlowControl;
    QComboBox *comboFlowControl;
    QHBoxLayout *hboxLayout6;
    QLabel *lblParity;
    QComboBox *comboParity;
    QHBoxLayout *hboxLayout7;
    QLabel *lblFlowControl_2;
    QLineEdit *editHeader;
    QHBoxLayout *hboxLayout8;
    QLabel *lblFlowControl_2_2;
    QLineEdit *editTrailer;

    void setupUi(QDialog *dlgMSCReader)
    {
        if (dlgMSCReader->objectName().isEmpty())
            dlgMSCReader->setObjectName(QString::fromUtf8("dlgMSCReader"));
        dlgMSCReader->resize(224, 355);
        gridLayout = new QGridLayout(dlgMSCReader);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgMSCReader);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgMSCReader);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        groupBox1 = new Q3GroupBox(dlgMSCReader);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblDataBits = new QLabel(groupBox1);
        lblDataBits->setObjectName(QString::fromUtf8("lblDataBits"));
        lblDataBits->setWordWrap(false);

        hboxLayout1->addWidget(lblDataBits);

        comboDataBits = new QComboBox(groupBox1);
        comboDataBits->setObjectName(QString::fromUtf8("comboDataBits"));

        hboxLayout1->addWidget(comboDataBits);


        gridLayout1->addLayout(hboxLayout1, 2, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblBaudRate = new QLabel(groupBox1);
        lblBaudRate->setObjectName(QString::fromUtf8("lblBaudRate"));
        lblBaudRate->setWordWrap(false);

        hboxLayout2->addWidget(lblBaudRate);

        comboBaudRate = new QComboBox(groupBox1);
        comboBaudRate->setObjectName(QString::fromUtf8("comboBaudRate"));

        hboxLayout2->addWidget(comboBaudRate);


        gridLayout1->addLayout(hboxLayout2, 1, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblStopBits = new QLabel(groupBox1);
        lblStopBits->setObjectName(QString::fromUtf8("lblStopBits"));
        lblStopBits->setWordWrap(false);

        hboxLayout3->addWidget(lblStopBits);

        comboStopBits = new QComboBox(groupBox1);
        comboStopBits->setObjectName(QString::fromUtf8("comboStopBits"));

        hboxLayout3->addWidget(comboStopBits);


        gridLayout1->addLayout(hboxLayout3, 4, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        lblDevice = new QLabel(groupBox1);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setWordWrap(false);

        hboxLayout4->addWidget(lblDevice);

        editDevice = new QLineEdit(groupBox1);
        editDevice->setObjectName(QString::fromUtf8("editDevice"));

        hboxLayout4->addWidget(editDevice);


        gridLayout1->addLayout(hboxLayout4, 0, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblFlowControl = new QLabel(groupBox1);
        lblFlowControl->setObjectName(QString::fromUtf8("lblFlowControl"));
        lblFlowControl->setWordWrap(false);

        hboxLayout5->addWidget(lblFlowControl);

        comboFlowControl = new QComboBox(groupBox1);
        comboFlowControl->setObjectName(QString::fromUtf8("comboFlowControl"));

        hboxLayout5->addWidget(comboFlowControl);


        gridLayout1->addLayout(hboxLayout5, 5, 0, 1, 1);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblParity = new QLabel(groupBox1);
        lblParity->setObjectName(QString::fromUtf8("lblParity"));
        lblParity->setWordWrap(false);

        hboxLayout6->addWidget(lblParity);

        comboParity = new QComboBox(groupBox1);
        comboParity->setObjectName(QString::fromUtf8("comboParity"));

        hboxLayout6->addWidget(comboParity);


        gridLayout1->addLayout(hboxLayout6, 3, 0, 1, 1);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        lblFlowControl_2 = new QLabel(groupBox1);
        lblFlowControl_2->setObjectName(QString::fromUtf8("lblFlowControl_2"));
        lblFlowControl_2->setWordWrap(false);

        hboxLayout7->addWidget(lblFlowControl_2);

        editHeader = new QLineEdit(groupBox1);
        editHeader->setObjectName(QString::fromUtf8("editHeader"));
        editHeader->setMaxLength(1);

        hboxLayout7->addWidget(editHeader);


        gridLayout1->addLayout(hboxLayout7, 6, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        lblFlowControl_2_2 = new QLabel(groupBox1);
        lblFlowControl_2_2->setObjectName(QString::fromUtf8("lblFlowControl_2_2"));
        lblFlowControl_2_2->setWordWrap(false);

        hboxLayout8->addWidget(lblFlowControl_2_2);

        editTrailer = new QLineEdit(groupBox1);
        editTrailer->setObjectName(QString::fromUtf8("editTrailer"));
        editTrailer->setMaxLength(1);

        hboxLayout8->addWidget(editTrailer);


        gridLayout1->addLayout(hboxLayout8, 7, 0, 1, 1);


        gridLayout->addWidget(groupBox1, 0, 0, 1, 1);


        retranslateUi(dlgMSCReader);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgMSCReader, SLOT(apply()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgMSCReader, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlgMSCReader);
    } // setupUi

    void retranslateUi(QDialog *dlgMSCReader)
    {
        dlgMSCReader->setWindowTitle(QApplication::translate("dlgMSCReader", "MSC Redaer", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgMSCReader", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgMSCReader", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        groupBox1->setTitle(QApplication::translate("dlgMSCReader", "device settings", 0, QApplication::UnicodeUTF8));
        lblDataBits->setText(QApplication::translate("dlgMSCReader", "databits", 0, QApplication::UnicodeUTF8));
        lblBaudRate->setText(QApplication::translate("dlgMSCReader", "baudrate", 0, QApplication::UnicodeUTF8));
        lblStopBits->setText(QApplication::translate("dlgMSCReader", "stopbits", 0, QApplication::UnicodeUTF8));
        lblDevice->setText(QApplication::translate("dlgMSCReader", "device", 0, QApplication::UnicodeUTF8));
        lblFlowControl->setText(QApplication::translate("dlgMSCReader", "flow control", 0, QApplication::UnicodeUTF8));
        lblParity->setText(QApplication::translate("dlgMSCReader", "parity", 0, QApplication::UnicodeUTF8));
        lblFlowControl_2->setText(QApplication::translate("dlgMSCReader", "header", 0, QApplication::UnicodeUTF8));
        lblFlowControl_2_2->setText(QApplication::translate("dlgMSCReader", "trailer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgMSCReader: public Ui_dlgMSCReader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGMSCREADER_H
