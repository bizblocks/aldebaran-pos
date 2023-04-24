/********************************************************************************
** Form generated from reading UI file 'dlglogin.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOGIN_H
#define UI_DLGLOGIN_H

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
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMessageBox>
#include "engine.h"
#include "userstable.h"

QT_BEGIN_NAMESPACE

class Ui_dlgLogin
{
public:
    QGridLayout *gridLayout;
    QLabel *lblPassword;
    QLineEdit *editPassword;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QHBoxLayout *hboxLayout1;
    Q3Frame *frmSelect;
    QVBoxLayout *vboxLayout;
    QSpacerItem *spacer2;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QSpacerItem *spacer3;

    void setupUi(QDialog *dlgLogin)
    {
        if (dlgLogin->objectName().isEmpty())
            dlgLogin->setObjectName(QString::fromUtf8("dlgLogin"));
        dlgLogin->resize(376, 232);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dlgLogin->sizePolicy().hasHeightForWidth());
        dlgLogin->setSizePolicy(sizePolicy);
        dlgLogin->setFocusPolicy(Qt::StrongFocus);
        dlgLogin->setSizeGripEnabled(false);
        dlgLogin->setModal(true);
        gridLayout = new QGridLayout(dlgLogin);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblPassword = new QLabel(dlgLogin);
        lblPassword->setObjectName(QString::fromUtf8("lblPassword"));
        lblPassword->setWordWrap(false);

        gridLayout->addWidget(lblPassword, 1, 0, 1, 1);

        editPassword = new QLineEdit(dlgLogin);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setFocusPolicy(Qt::StrongFocus);
        editPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editPassword, 1, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgLogin);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgLogin);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout, 2, 0, 1, 2);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        frmSelect = new Q3Frame(dlgLogin);
        frmSelect->setObjectName(QString::fromUtf8("frmSelect"));
        sizePolicy.setHeightForWidth(frmSelect->sizePolicy().hasHeightForWidth());
        frmSelect->setSizePolicy(sizePolicy);
        frmSelect->setMinimumSize(QSize(320, 170));
        frmSelect->setFrameShape(QFrame::StyledPanel);
        frmSelect->setFrameShadow(QFrame::Raised);

        hboxLayout1->addWidget(frmSelect);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        spacer2 = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer2);

        btnUp = new QPushButton(dlgLogin);
        btnUp->setObjectName(QString::fromUtf8("btnUp"));
        btnUp->setFocusPolicy(Qt::StrongFocus);
        btnUp->setChecked(false);
        btnUp->setFlat(false);

        vboxLayout->addWidget(btnUp);

        btnDown = new QPushButton(dlgLogin);
        btnDown->setObjectName(QString::fromUtf8("btnDown"));
        btnDown->setFocusPolicy(Qt::StrongFocus);
        btnDown->setChecked(false);

        vboxLayout->addWidget(btnDown);

        spacer3 = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer3);


        hboxLayout1->addLayout(vboxLayout);


        gridLayout->addLayout(hboxLayout1, 0, 0, 1, 2);


        retranslateUi(dlgLogin);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgLogin, SLOT(login()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgLogin, SLOT(reject()));
        QObject::connect(btnUp, SIGNAL(clicked()), dlgLogin, SLOT(up()));
        QObject::connect(btnDown, SIGNAL(clicked()), dlgLogin, SLOT(down()));

        QMetaObject::connectSlotsByName(dlgLogin);
    } // setupUi

    void retranslateUi(QDialog *dlgLogin)
    {
        dlgLogin->setWindowTitle(QApplication::translate("dlgLogin", "Authorization", 0, QApplication::UnicodeUTF8));
        lblPassword->setText(QApplication::translate("dlgLogin", "Password", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgLogin", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("dlgLogin", "Return", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("dlgLogin", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QApplication::translate("dlgLogin", "Esc", 0, QApplication::UnicodeUTF8));
        btnUp->setText(QString());
        btnUp->setShortcut(QApplication::translate("dlgLogin", "Up", 0, QApplication::UnicodeUTF8));
        btnDown->setText(QString());
        btnDown->setShortcut(QApplication::translate("dlgLogin", "Down", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgLogin: public Ui_dlgLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOGIN_H
