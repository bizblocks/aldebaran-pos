/********************************************************************************
** Form generated from reading UI file 'dlgdiscount.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDISCOUNT_H
#define UI_DLGDISCOUNT_H

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
#include <QtGui/QSpinBox>
#include "engine.h"

QT_BEGIN_NAMESPACE

class Ui_dlgDiscount
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
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QHBoxLayout *hboxLayout4;
    QHBoxLayout *hboxLayout5;
    QLabel *lblValue;
    QSpinBox *spinValue;
    QCheckBox *chkProtect;
    QHBoxLayout *hboxLayout6;
    QLabel *lblName_2;
    QLineEdit *editCode;

    void setupUi(QDialog *dlgDiscount)
    {
        if (dlgDiscount->objectName().isEmpty())
            dlgDiscount->setObjectName(QString::fromUtf8("dlgDiscount"));
        dlgDiscount->resize(317, 127);
        gridLayout = new QGridLayout(dlgDiscount);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblName = new QLabel(dlgDiscount);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblName->sizePolicy().hasHeightForWidth());
        lblName->setSizePolicy(sizePolicy);
        lblName->setWordWrap(false);

        hboxLayout1->addWidget(lblName);

        editName = new QLineEdit(dlgDiscount);
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
        lblType = new QLabel(dlgDiscount);
        lblType->setObjectName(QString::fromUtf8("lblType"));
        lblType->setWordWrap(false);

        hboxLayout2->addWidget(lblType);

        comboType = new QComboBox(dlgDiscount);
        comboType->setObjectName(QString::fromUtf8("comboType"));

        hboxLayout2->addWidget(comboType);


        hboxLayout->addLayout(hboxLayout2);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        Horizontal_Spacing2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgDiscount);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout3->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgDiscount);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout3->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout3, 3, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblValue = new QLabel(dlgDiscount);
        lblValue->setObjectName(QString::fromUtf8("lblValue"));
        lblValue->setWordWrap(false);

        hboxLayout5->addWidget(lblValue);

        spinValue = new QSpinBox(dlgDiscount);
        spinValue->setObjectName(QString::fromUtf8("spinValue"));

        hboxLayout5->addWidget(spinValue);


        hboxLayout4->addLayout(hboxLayout5);

        chkProtect = new QCheckBox(dlgDiscount);
        chkProtect->setObjectName(QString::fromUtf8("chkProtect"));

        hboxLayout4->addWidget(chkProtect);


        gridLayout->addLayout(hboxLayout4, 1, 0, 1, 1);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblName_2 = new QLabel(dlgDiscount);
        lblName_2->setObjectName(QString::fromUtf8("lblName_2"));
        sizePolicy.setHeightForWidth(lblName_2->sizePolicy().hasHeightForWidth());
        lblName_2->setSizePolicy(sizePolicy);
        lblName_2->setWordWrap(false);

        hboxLayout6->addWidget(lblName_2);

        editCode = new QLineEdit(dlgDiscount);
        editCode->setObjectName(QString::fromUtf8("editCode"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(editCode->sizePolicy().hasHeightForWidth());
        editCode->setSizePolicy(sizePolicy2);
        editCode->setMaximumSize(QSize(32767, 32767));

        hboxLayout6->addWidget(editCode);


        gridLayout->addLayout(hboxLayout6, 2, 0, 1, 1);


        retranslateUi(dlgDiscount);
        QObject::connect(comboType, SIGNAL(activated(int)), dlgDiscount, SLOT(typeSelected(int)));
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgDiscount, SLOT(apply()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgDiscount, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlgDiscount);
    } // setupUi

    void retranslateUi(QDialog *dlgDiscount)
    {
        dlgDiscount->setWindowTitle(QApplication::translate("dlgDiscount", "discount", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("dlgDiscount", "name:", 0, QApplication::UnicodeUTF8));
        lblType->setText(QApplication::translate("dlgDiscount", "type:", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgDiscount", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgDiscount", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        lblValue->setText(QApplication::translate("dlgDiscount", "value", 0, QApplication::UnicodeUTF8));
        chkProtect->setText(QApplication::translate("dlgDiscount", "protect", 0, QApplication::UnicodeUTF8));
        lblName_2->setText(QApplication::translate("dlgDiscount", "code:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgDiscount: public Ui_dlgDiscount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGDISCOUNT_H
