/********************************************************************************
** Form generated from reading UI file 'dlgselectdiscount.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSELECTDISCOUNT_H
#define UI_DLGSELECTDISCOUNT_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "discounttable.h"
#include "engine.h"

QT_BEGIN_NAMESPACE

class Ui_dlgSelectDiscount
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    Q3Frame *frameDiscount;

    void setupUi(QDialog *dlgSelectDiscount)
    {
        if (dlgSelectDiscount->objectName().isEmpty())
            dlgSelectDiscount->setObjectName(QString::fromUtf8("dlgSelectDiscount"));
        dlgSelectDiscount->resize(367, 277);
        gridLayout = new QGridLayout(dlgSelectDiscount);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgSelectDiscount);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgSelectDiscount);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        frameDiscount = new Q3Frame(dlgSelectDiscount);
        frameDiscount->setObjectName(QString::fromUtf8("frameDiscount"));
        frameDiscount->setFrameShape(QFrame::StyledPanel);
        frameDiscount->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameDiscount, 0, 0, 1, 1);


        retranslateUi(dlgSelectDiscount);
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgSelectDiscount, SLOT(reject()));
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgSelectDiscount, SLOT(selected()));

        QMetaObject::connectSlotsByName(dlgSelectDiscount);
    } // setupUi

    void retranslateUi(QDialog *dlgSelectDiscount)
    {
        dlgSelectDiscount->setWindowTitle(QApplication::translate("dlgSelectDiscount", "Choose discount", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgSelectDiscount", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgSelectDiscount", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class dlgSelectDiscount: public Ui_dlgSelectDiscount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSELECTDISCOUNT_H
