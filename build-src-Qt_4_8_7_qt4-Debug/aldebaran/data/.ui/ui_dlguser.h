/********************************************************************************
** Form generated from reading UI file 'dlguser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGUSER_H
#define UI_DLGUSER_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
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
#include "engine.h"

QT_BEGIN_NAMESPACE

class Ui_dlgUser
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    Q3Frame *frameRights;
    QGridLayout *gridLayout1;
    Q3ListBox *listRights;
    QHBoxLayout *hboxLayout1;
    QLabel *lblName;
    QLineEdit *editName;
    QHBoxLayout *hboxLayout2;
    QLabel *lblPass;
    QLineEdit *editPass;

    void setupUi(QDialog *dlgUser)
    {
        if (dlgUser->objectName().isEmpty())
            dlgUser->setObjectName(QString::fromUtf8("dlgUser"));
        dlgUser->resize(600, 480);
        gridLayout = new QGridLayout(dlgUser);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgUser);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgUser);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout, 2, 0, 1, 2);

        frameRights = new Q3Frame(dlgUser);
        frameRights->setObjectName(QString::fromUtf8("frameRights"));
        frameRights->setFrameShape(QFrame::StyledPanel);
        frameRights->setFrameShadow(QFrame::Raised);
        gridLayout1 = new QGridLayout(frameRights);
        gridLayout1->setSpacing(1);
        gridLayout1->setContentsMargins(1, 1, 1, 1);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        listRights = new Q3ListBox(frameRights);
        listRights->setObjectName(QString::fromUtf8("listRights"));
        listRights->setCurrentItem(-1);
        listRights->setColumnMode(Q3ListBox::FixedNumber);
        listRights->setRowMode(Q3ListBox::Variable);

        gridLayout1->addWidget(listRights, 0, 0, 1, 1);


        gridLayout->addWidget(frameRights, 1, 0, 1, 2);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblName = new QLabel(dlgUser);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setWordWrap(false);

        hboxLayout1->addWidget(lblName);

        editName = new QLineEdit(dlgUser);
        editName->setObjectName(QString::fromUtf8("editName"));
        editName->setMinimumSize(QSize(200, 0));
        editName->setMaxLength(200);

        hboxLayout1->addWidget(editName);


        gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblPass = new QLabel(dlgUser);
        lblPass->setObjectName(QString::fromUtf8("lblPass"));
        lblPass->setWordWrap(false);

        hboxLayout2->addWidget(lblPass);

        editPass = new QLineEdit(dlgUser);
        editPass->setObjectName(QString::fromUtf8("editPass"));
        editPass->setMinimumSize(QSize(200, 0));
        editPass->setMaxLength(200);
        editPass->setEchoMode(QLineEdit::Password);

        hboxLayout2->addWidget(editPass);


        gridLayout->addLayout(hboxLayout2, 0, 1, 1, 1);


        retranslateUi(dlgUser);
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgUser, SLOT(reject()));
        QObject::connect(listRights, SIGNAL(doubleClicked(Q3ListBoxItem*)), dlgUser, SLOT(check(Q3ListBoxItem*)));
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgUser, SLOT(ok()));
        QObject::connect(editPass, SIGNAL(textChanged(QString)), dlgUser, SLOT(passwordChanged(QString)));

        QMetaObject::connectSlotsByName(dlgUser);
    } // setupUi

    void retranslateUi(QDialog *dlgUser)
    {
        dlgUser->setWindowTitle(QApplication::translate("dlgUser", "User", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgUser", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgUser", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        lblName->setText(QApplication::translate("dlgUser", "Name:", 0, QApplication::UnicodeUTF8));
        lblPass->setText(QApplication::translate("dlgUser", "Password:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgUser: public Ui_dlgUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGUSER_H
