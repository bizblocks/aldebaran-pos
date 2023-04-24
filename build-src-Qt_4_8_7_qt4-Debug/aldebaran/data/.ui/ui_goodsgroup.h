/********************************************************************************
** Form generated from reading UI file 'goodsgroup.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOODSGROUP_H
#define UI_GOODSGROUP_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "data/datagoods.h"

QT_BEGIN_NAMESPACE

class Ui_GoodsGroup
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *lblName;
    QLineEdit *editName;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QLabel *labelPicture;
    QHBoxLayout *hboxLayout2;
    QHBoxLayout *hboxLayout3;
    QLabel *lblPicture;
    QPushButton *btnSelectPicture;
    QPushButton *btnClearPicture;
    QCheckBox *chkEqExport;
    QSpacerItem *spacer8;

    void setupUi(QDialog *GoodsGroup)
    {
        if (GoodsGroup->objectName().isEmpty())
            GoodsGroup->setObjectName(QString::fromUtf8("GoodsGroup"));
        GoodsGroup->resize(459, 413);
        GoodsGroup->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(GoodsGroup);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblName = new QLabel(GoodsGroup);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setWordWrap(false);

        hboxLayout->addWidget(lblName);

        editName = new QLineEdit(GoodsGroup);
        editName->setObjectName(QString::fromUtf8("editName"));
        editName->setMinimumSize(QSize(400, 0));
        editName->setMaxLength(200);

        hboxLayout->addWidget(editName);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(GoodsGroup);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout1->addWidget(buttonOk);

        buttonCancel = new QPushButton(GoodsGroup);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout1->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout1, 3, 0, 1, 1);

        labelPicture = new QLabel(GoodsGroup);
        labelPicture->setObjectName(QString::fromUtf8("labelPicture"));
        labelPicture->setMinimumSize(QSize(300, 300));
        labelPicture->setMaximumSize(QSize(300, 300));
        labelPicture->setScaledContents(true);
        labelPicture->setWordWrap(false);

        gridLayout->addWidget(labelPicture, 2, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblPicture = new QLabel(GoodsGroup);
        lblPicture->setObjectName(QString::fromUtf8("lblPicture"));
        lblPicture->setWordWrap(false);

        hboxLayout3->addWidget(lblPicture);

        btnSelectPicture = new QPushButton(GoodsGroup);
        btnSelectPicture->setObjectName(QString::fromUtf8("btnSelectPicture"));

        hboxLayout3->addWidget(btnSelectPicture);

        btnClearPicture = new QPushButton(GoodsGroup);
        btnClearPicture->setObjectName(QString::fromUtf8("btnClearPicture"));

        hboxLayout3->addWidget(btnClearPicture);


        hboxLayout2->addLayout(hboxLayout3);

        chkEqExport = new QCheckBox(GoodsGroup);
        chkEqExport->setObjectName(QString::fromUtf8("chkEqExport"));

        hboxLayout2->addWidget(chkEqExport);

        spacer8 = new QSpacerItem(80, 41, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer8);


        gridLayout->addLayout(hboxLayout2, 1, 0, 1, 1);


        retranslateUi(GoodsGroup);
        QObject::connect(buttonOk, SIGNAL(clicked()), GoodsGroup, SLOT(ok()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), GoodsGroup, SLOT(reject()));
        QObject::connect(btnSelectPicture, SIGNAL(clicked()), GoodsGroup, SLOT(selectPicture()));
        QObject::connect(btnClearPicture, SIGNAL(clicked()), GoodsGroup, SLOT(clearPicture()));

        QMetaObject::connectSlotsByName(GoodsGroup);
    } // setupUi

    void retranslateUi(QDialog *GoodsGroup)
    {
        GoodsGroup->setWindowTitle(QApplication::translate("GoodsGroup", "Group", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("GoodsGroup", "Name:", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("GoodsGroup", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("GoodsGroup", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        lblPicture->setText(QApplication::translate("GoodsGroup", "Picture", 0, QApplication::UnicodeUTF8));
        btnSelectPicture->setText(QString());
        btnClearPicture->setText(QString());
        chkEqExport->setText(QApplication::translate("GoodsGroup", "Export to equipment", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GoodsGroup: public Ui_GoodsGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOODSGROUP_H
