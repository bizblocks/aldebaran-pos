/********************************************************************************
** Form generated from reading UI file 'dlgecrsettings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGECRSETTINGS_H
#define UI_DLGECRSETTINGS_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
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
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "fr.h"

QT_BEGIN_NAMESPACE

class Ui_dlgECRSettings
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    Q3GroupBox *groupBox2;
    QGridLayout *gridLayout1;
    QSpacerItem *spacer5;
    QHBoxLayout *hboxLayout1;
    QLabel *lblAccessPassword;
    QLineEdit *editAccessPassword;
    QHBoxLayout *hboxLayout2;
    QLabel *lblOperatorPassword;
    QLineEdit *editOperatorPassword;
    QHBoxLayout *hboxLayout3;
    QLabel *lblAdminPassword;
    QLineEdit *editAdminPassword;
    QHBoxLayout *hboxLayout4;
    QLabel *lblCodepage;
    QComboBox *comboCP;
    QHBoxLayout *hboxLayout5;
    QLabel *lblPrintWidth;
    QSpinBox *spinPrintWidth;
    Q3GroupBox *groupBox1;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout6;
    QLabel *lblDataBits;
    QComboBox *comboDataBits;
    QHBoxLayout *hboxLayout7;
    QLabel *lblStopBits;
    QComboBox *comboStopBits;
    QHBoxLayout *hboxLayout8;
    QLabel *lblDevice;
    QLineEdit *editDevice;
    QHBoxLayout *hboxLayout9;
    QLabel *lblFlowControl;
    QComboBox *comboFlowControl;
    QHBoxLayout *hboxLayout10;
    QLabel *lblParity;
    QComboBox *comboParity;
    QHBoxLayout *hboxLayout11;
    QLabel *lblBaudRate;
    QComboBox *comboBaudRate;
    QHBoxLayout *hboxLayout12;
    QLabel *driver;
    QComboBox *comboDriver;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    Q3TextEdit *editHeader;
    QVBoxLayout *vboxLayout1;
    QLabel *textLabel1_2;
    Q3TextEdit *editFooter;

    void setupUi(QDialog *dlgECRSettings)
    {
        if (dlgECRSettings->objectName().isEmpty())
            dlgECRSettings->setObjectName(QString::fromUtf8("dlgECRSettings"));
        dlgECRSettings->resize(524, 467);
        dlgECRSettings->setSizeGripEnabled(false);
        dlgECRSettings->setModal(true);
        gridLayout = new QGridLayout(dlgECRSettings);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgECRSettings);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgECRSettings);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 2);

        groupBox2 = new Q3GroupBox(dlgECRSettings);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setMaximumSize(QSize(32767, 32767));
        groupBox2->setColumnLayout(0, Qt::Vertical);
        groupBox2->layout()->setSpacing(6);
        groupBox2->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox2->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        spacer5 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacer5, 3, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblAccessPassword = new QLabel(groupBox2);
        lblAccessPassword->setObjectName(QString::fromUtf8("lblAccessPassword"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblAccessPassword->sizePolicy().hasHeightForWidth());
        lblAccessPassword->setSizePolicy(sizePolicy);
        lblAccessPassword->setWordWrap(false);

        hboxLayout1->addWidget(lblAccessPassword);

        editAccessPassword = new QLineEdit(groupBox2);
        editAccessPassword->setObjectName(QString::fromUtf8("editAccessPassword"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(editAccessPassword->sizePolicy().hasHeightForWidth());
        editAccessPassword->setSizePolicy(sizePolicy1);
        editAccessPassword->setMaximumSize(QSize(40, 32767));
        editAccessPassword->setMaxLength(2);

        hboxLayout1->addWidget(editAccessPassword);


        gridLayout1->addLayout(hboxLayout1, 0, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblOperatorPassword = new QLabel(groupBox2);
        lblOperatorPassword->setObjectName(QString::fromUtf8("lblOperatorPassword"));
        lblOperatorPassword->setWordWrap(false);

        hboxLayout2->addWidget(lblOperatorPassword);

        editOperatorPassword = new QLineEdit(groupBox2);
        editOperatorPassword->setObjectName(QString::fromUtf8("editOperatorPassword"));
        sizePolicy1.setHeightForWidth(editOperatorPassword->sizePolicy().hasHeightForWidth());
        editOperatorPassword->setSizePolicy(sizePolicy1);
        editOperatorPassword->setMaximumSize(QSize(80, 32767));
        editOperatorPassword->setMaxLength(4);

        hboxLayout2->addWidget(editOperatorPassword);


        gridLayout1->addLayout(hboxLayout2, 1, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblAdminPassword = new QLabel(groupBox2);
        lblAdminPassword->setObjectName(QString::fromUtf8("lblAdminPassword"));
        lblAdminPassword->setWordWrap(false);

        hboxLayout3->addWidget(lblAdminPassword);

        editAdminPassword = new QLineEdit(groupBox2);
        editAdminPassword->setObjectName(QString::fromUtf8("editAdminPassword"));
        sizePolicy1.setHeightForWidth(editAdminPassword->sizePolicy().hasHeightForWidth());
        editAdminPassword->setSizePolicy(sizePolicy1);
        editAdminPassword->setMaximumSize(QSize(80, 32767));
        editAdminPassword->setMaxLength(4);

        hboxLayout3->addWidget(editAdminPassword);


        gridLayout1->addLayout(hboxLayout3, 2, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        lblCodepage = new QLabel(groupBox2);
        lblCodepage->setObjectName(QString::fromUtf8("lblCodepage"));
        lblCodepage->setWordWrap(false);

        hboxLayout4->addWidget(lblCodepage);

        comboCP = new QComboBox(groupBox2);
        comboCP->setObjectName(QString::fromUtf8("comboCP"));

        hboxLayout4->addWidget(comboCP);


        gridLayout1->addLayout(hboxLayout4, 4, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblPrintWidth = new QLabel(groupBox2);
        lblPrintWidth->setObjectName(QString::fromUtf8("lblPrintWidth"));
        lblPrintWidth->setWordWrap(false);

        hboxLayout5->addWidget(lblPrintWidth);

        spinPrintWidth = new QSpinBox(groupBox2);
        spinPrintWidth->setObjectName(QString::fromUtf8("spinPrintWidth"));

        hboxLayout5->addWidget(spinPrintWidth);


        gridLayout1->addLayout(hboxLayout5, 5, 0, 1, 1);


        gridLayout->addWidget(groupBox2, 0, 1, 1, 1);

        groupBox1 = new Q3GroupBox(dlgECRSettings);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout2 = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout2);
        gridLayout2->setAlignment(Qt::AlignTop);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblDataBits = new QLabel(groupBox1);
        lblDataBits->setObjectName(QString::fromUtf8("lblDataBits"));
        lblDataBits->setWordWrap(false);

        hboxLayout6->addWidget(lblDataBits);

        comboDataBits = new QComboBox(groupBox1);
        comboDataBits->setObjectName(QString::fromUtf8("comboDataBits"));

        hboxLayout6->addWidget(comboDataBits);


        gridLayout2->addLayout(hboxLayout6, 3, 0, 1, 1);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        lblStopBits = new QLabel(groupBox1);
        lblStopBits->setObjectName(QString::fromUtf8("lblStopBits"));
        lblStopBits->setWordWrap(false);

        hboxLayout7->addWidget(lblStopBits);

        comboStopBits = new QComboBox(groupBox1);
        comboStopBits->setObjectName(QString::fromUtf8("comboStopBits"));

        hboxLayout7->addWidget(comboStopBits);


        gridLayout2->addLayout(hboxLayout7, 5, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        lblDevice = new QLabel(groupBox1);
        lblDevice->setObjectName(QString::fromUtf8("lblDevice"));
        lblDevice->setWordWrap(false);

        hboxLayout8->addWidget(lblDevice);

        editDevice = new QLineEdit(groupBox1);
        editDevice->setObjectName(QString::fromUtf8("editDevice"));

        hboxLayout8->addWidget(editDevice);


        gridLayout2->addLayout(hboxLayout8, 1, 0, 1, 1);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        lblFlowControl = new QLabel(groupBox1);
        lblFlowControl->setObjectName(QString::fromUtf8("lblFlowControl"));
        lblFlowControl->setWordWrap(false);

        hboxLayout9->addWidget(lblFlowControl);

        comboFlowControl = new QComboBox(groupBox1);
        comboFlowControl->setObjectName(QString::fromUtf8("comboFlowControl"));

        hboxLayout9->addWidget(comboFlowControl);


        gridLayout2->addLayout(hboxLayout9, 6, 0, 1, 1);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        lblParity = new QLabel(groupBox1);
        lblParity->setObjectName(QString::fromUtf8("lblParity"));
        lblParity->setWordWrap(false);

        hboxLayout10->addWidget(lblParity);

        comboParity = new QComboBox(groupBox1);
        comboParity->setObjectName(QString::fromUtf8("comboParity"));

        hboxLayout10->addWidget(comboParity);


        gridLayout2->addLayout(hboxLayout10, 4, 0, 1, 1);

        hboxLayout11 = new QHBoxLayout();
        hboxLayout11->setSpacing(6);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        lblBaudRate = new QLabel(groupBox1);
        lblBaudRate->setObjectName(QString::fromUtf8("lblBaudRate"));
        lblBaudRate->setWordWrap(false);

        hboxLayout11->addWidget(lblBaudRate);

        comboBaudRate = new QComboBox(groupBox1);
        comboBaudRate->setObjectName(QString::fromUtf8("comboBaudRate"));

        hboxLayout11->addWidget(comboBaudRate);


        gridLayout2->addLayout(hboxLayout11, 2, 0, 1, 1);

        hboxLayout12 = new QHBoxLayout();
        hboxLayout12->setSpacing(6);
        hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
        driver = new QLabel(groupBox1);
        driver->setObjectName(QString::fromUtf8("driver"));
        driver->setWordWrap(false);

        hboxLayout12->addWidget(driver);

        comboDriver = new QComboBox(groupBox1);
        comboDriver->setObjectName(QString::fromUtf8("comboDriver"));

        hboxLayout12->addWidget(comboDriver);


        gridLayout2->addLayout(hboxLayout12, 0, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textLabel1 = new QLabel(groupBox1);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout->addWidget(textLabel1);

        editHeader = new Q3TextEdit(groupBox1);
        editHeader->setObjectName(QString::fromUtf8("editHeader"));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        editHeader->setFont(font);

        vboxLayout->addWidget(editHeader);


        gridLayout2->addLayout(vboxLayout, 7, 0, 1, 1);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        textLabel1_2 = new QLabel(groupBox1);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        vboxLayout1->addWidget(textLabel1_2);

        editFooter = new Q3TextEdit(groupBox1);
        editFooter->setObjectName(QString::fromUtf8("editFooter"));
        editFooter->setFont(font);

        vboxLayout1->addWidget(editFooter);


        gridLayout2->addLayout(vboxLayout1, 8, 0, 1, 1);


        gridLayout->addWidget(groupBox1, 0, 0, 1, 1);


        retranslateUi(dlgECRSettings);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgECRSettings, SLOT(apply()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgECRSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlgECRSettings);
    } // setupUi

    void retranslateUi(QDialog *dlgECRSettings)
    {
        dlgECRSettings->setWindowTitle(QApplication::translate("dlgECRSettings", "ECR", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgECRSettings", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgECRSettings", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        groupBox2->setTitle(QApplication::translate("dlgECRSettings", "passwords", 0, QApplication::UnicodeUTF8));
        lblAccessPassword->setText(QApplication::translate("dlgECRSettings", "access", 0, QApplication::UnicodeUTF8));
        lblOperatorPassword->setText(QApplication::translate("dlgECRSettings", "operator", 0, QApplication::UnicodeUTF8));
        lblAdminPassword->setText(QApplication::translate("dlgECRSettings", "administrator", 0, QApplication::UnicodeUTF8));
        lblCodepage->setText(QApplication::translate("dlgECRSettings", "codepage", 0, QApplication::UnicodeUTF8));
        lblPrintWidth->setText(QApplication::translate("dlgECRSettings", "print width", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("dlgECRSettings", "device settings", 0, QApplication::UnicodeUTF8));
        lblDataBits->setText(QApplication::translate("dlgECRSettings", "databits", 0, QApplication::UnicodeUTF8));
        lblStopBits->setText(QApplication::translate("dlgECRSettings", "stopbits", 0, QApplication::UnicodeUTF8));
        lblDevice->setText(QApplication::translate("dlgECRSettings", "device", 0, QApplication::UnicodeUTF8));
        lblFlowControl->setText(QApplication::translate("dlgECRSettings", "flow control", 0, QApplication::UnicodeUTF8));
        lblParity->setText(QApplication::translate("dlgECRSettings", "parity", 0, QApplication::UnicodeUTF8));
        lblBaudRate->setText(QApplication::translate("dlgECRSettings", "baudrate", 0, QApplication::UnicodeUTF8));
        driver->setText(QApplication::translate("dlgECRSettings", "driver", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("dlgECRSettings", "Check header", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("dlgECRSettings", "Check footer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgECRSettings: public Ui_dlgECRSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGECRSETTINGS_H
