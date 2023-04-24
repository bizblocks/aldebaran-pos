/*
Equipment actions dialog.
*/

/********************************************************************************
** Form generated from reading UI file 'equipmentdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUIPMENTDIALOG_H
#define UI_EQUIPMENTDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
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
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolBox>
#include <QtGui/QWidget>
#include "engine.h"

QT_BEGIN_NAMESPACE

class Ui_equipmentDialog
{
public:
    QGridLayout *gridLayout;
    QToolBox *toolbox;
    QWidget *page2;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *lblAction;
    QComboBox *cbActions;
    Q3ListBox *listDevices;
    QHBoxLayout *hboxLayout1;
    QPushButton *btnCheckAll;
    QPushButton *btnUnCheckAll;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *equipmentDialog)
    {
        if (equipmentDialog->objectName().isEmpty())
            equipmentDialog->setObjectName(QString::fromUtf8("equipmentDialog"));
        equipmentDialog->resize(531, 345);
        gridLayout = new QGridLayout(equipmentDialog);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolbox = new QToolBox(equipmentDialog);
        toolbox->setObjectName(QString::fromUtf8("toolbox"));
        toolbox->setFrameShape(QFrame::NoFrame);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        page2->setGeometry(QRect(0, 0, 513, 296));
        gridLayout1 = new QGridLayout(page2);
        gridLayout1->setSpacing(0);
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblAction = new QLabel(page2);
        lblAction->setObjectName(QString::fromUtf8("lblAction"));
        lblAction->setWordWrap(false);

        hboxLayout->addWidget(lblAction);

        cbActions = new QComboBox(page2);
        cbActions->setObjectName(QString::fromUtf8("cbActions"));

        hboxLayout->addWidget(cbActions);


        gridLayout1->addLayout(hboxLayout, 0, 0, 1, 1);

        listDevices = new Q3ListBox(page2);
        listDevices->setObjectName(QString::fromUtf8("listDevices"));

        gridLayout1->addWidget(listDevices, 1, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        btnCheckAll = new QPushButton(page2);
        btnCheckAll->setObjectName(QString::fromUtf8("btnCheckAll"));

        hboxLayout1->addWidget(btnCheckAll);

        btnUnCheckAll = new QPushButton(page2);
        btnUnCheckAll->setObjectName(QString::fromUtf8("btnUnCheckAll"));

        hboxLayout1->addWidget(btnUnCheckAll);

        Horizontal_Spacing2 = new QSpacerItem(180, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(page2);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("right.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout1->addWidget(buttonOk);

        buttonCancel = new QPushButton(page2);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout1->addWidget(buttonCancel);


        gridLayout1->addLayout(hboxLayout1, 2, 0, 1, 1);

        toolbox->addItem(page2, QString::fromUtf8("Sirius"));

        gridLayout->addWidget(toolbox, 0, 0, 1, 1);


        retranslateUi(equipmentDialog);
        QObject::connect(toolbox, SIGNAL(currentChanged(int)), equipmentDialog, SLOT(fill(int)));
        QObject::connect(buttonOk, SIGNAL(clicked()), equipmentDialog, SLOT(execute()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), equipmentDialog, SLOT(checkClose()));
        QObject::connect(listDevices, SIGNAL(clicked(Q3ListBoxItem*)), equipmentDialog, SLOT(check(Q3ListBoxItem*)));
        QObject::connect(btnCheckAll, SIGNAL(clicked()), equipmentDialog, SLOT(checkAll()));
        QObject::connect(btnUnCheckAll, SIGNAL(clicked()), equipmentDialog, SLOT(unCheckAll()));

        toolbox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(equipmentDialog);
    } // setupUi

    void retranslateUi(QDialog *equipmentDialog)
    {
        equipmentDialog->setWindowTitle(QApplication::translate("equipmentDialog", "Equipment", 0, QApplication::UnicodeUTF8));
        lblAction->setText(QApplication::translate("equipmentDialog", "action:", 0, QApplication::UnicodeUTF8));
        btnCheckAll->setText(QString());
        btnUnCheckAll->setText(QString());
        buttonOk->setText(QApplication::translate("equipmentDialog", "&Execute", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("equipmentDialog", "Alt+E", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("equipmentDialog", "&Close", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("equipmentDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        toolbox->setItemText(toolbox->indexOf(page2), QApplication::translate("equipmentDialog", "Sirius", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class equipmentDialog: public Ui_equipmentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUIPMENTDIALOG_H
