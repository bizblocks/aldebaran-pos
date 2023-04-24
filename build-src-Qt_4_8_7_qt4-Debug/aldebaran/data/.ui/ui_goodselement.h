/********************************************************************************
** Form generated from reading UI file 'goodselement.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOODSELEMENT_H
#define UI_GOODSELEMENT_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
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
#include <QtGui/QVBoxLayout>
#include <Qt3Support/Q3TextEdit>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include "data/datagoods.h"

QT_BEGIN_NAMESPACE

class Ui_GoodsElement
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *lblName;
    QLineEdit *editName;
    QHBoxLayout *hboxLayout3;
    QLabel *lblBarCode;
    QSpacerItem *spacer17_2;
    QLineEdit *editBarcode;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout4;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout5;
    QLabel *lblExtCode;
    QSpacerItem *spacer17;
    QLineEdit *editExternalCode;
    QHBoxLayout *hboxLayout6;
    QLabel *lblFat_2;
    QSpacerItem *spacer15;
    QLineEdit *editProtein;
    QHBoxLayout *hboxLayout7;
    QLabel *lblHydroCarbonat;
    QSpacerItem *spacer16;
    QLineEdit *editHydroCarbonat;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout8;
    QLabel *lblFat_2_2;
    QSpacerItem *spacer13;
    QLineEdit *editCalories;
    QHBoxLayout *hboxLayout9;
    QLabel *lblFat;
    QSpacerItem *spacer14;
    QLineEdit *editFat;
    QHBoxLayout *hboxLayout10;
    QLabel *lblPrice;
    QSpacerItem *spacer12;
    QLineEdit *editPrice;
    QHBoxLayout *hboxLayout11;
    QCheckBox *chkOutOfStore;
    QCheckBox *chkEqExport;
    QSpacerItem *spacer10;
    QLabel *lblMaxDiscount;
    QLineEdit *editMaxDiscount;
    Q3Frame *editor;
    QGridLayout *gridLayout1;
    Q3TextEdit *editDescription;
    Q3Frame *toolbarParent;
    Q3Frame *frame17;
    QGridLayout *gridLayout2;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout12;
    QLabel *lblPicture;
    QPushButton *btnSelectPicture;
    QPushButton *btnClearPicture;
    QLabel *labelPicture;

    void setupUi(QDialog *GoodsElement)
    {
        if (GoodsElement->objectName().isEmpty())
            GoodsElement->setObjectName(QString::fromUtf8("GoodsElement"));
        GoodsElement->resize(849, 425);
        GoodsElement->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(GoodsElement);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(GoodsElement);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(GoodsElement);
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
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblName = new QLabel(GoodsElement);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setWordWrap(false);

        hboxLayout2->addWidget(lblName);

        editName = new QLineEdit(GoodsElement);
        editName->setObjectName(QString::fromUtf8("editName"));
        editName->setMinimumSize(QSize(400, 0));
        editName->setMaxLength(200);

        hboxLayout2->addWidget(editName);


        hboxLayout1->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblBarCode = new QLabel(GoodsElement);
        lblBarCode->setObjectName(QString::fromUtf8("lblBarCode"));
        lblBarCode->setWordWrap(false);

        hboxLayout3->addWidget(lblBarCode);

        spacer17_2 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer17_2);

        editBarcode = new QLineEdit(GoodsElement);
        editBarcode->setObjectName(QString::fromUtf8("editBarcode"));
        editBarcode->setMinimumSize(QSize(100, 0));
        editBarcode->setMaxLength(13);

        hboxLayout3->addWidget(editBarcode);


        hboxLayout1->addLayout(hboxLayout3);


        gridLayout->addLayout(hboxLayout1, 0, 0, 1, 2);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(1);
        hboxLayout4->setContentsMargins(1, 1, 1, 1);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(1);
        vboxLayout1->setContentsMargins(1, 1, 1, 1);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblExtCode = new QLabel(GoodsElement);
        lblExtCode->setObjectName(QString::fromUtf8("lblExtCode"));
        lblExtCode->setWordWrap(false);

        hboxLayout5->addWidget(lblExtCode);

        spacer17 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacer17);

        editExternalCode = new QLineEdit(GoodsElement);
        editExternalCode->setObjectName(QString::fromUtf8("editExternalCode"));
        editExternalCode->setMinimumSize(QSize(70, 0));
        editExternalCode->setMaxLength(15);

        hboxLayout5->addWidget(editExternalCode);


        vboxLayout1->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblFat_2 = new QLabel(GoodsElement);
        lblFat_2->setObjectName(QString::fromUtf8("lblFat_2"));
        lblFat_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblFat_2->setWordWrap(false);

        hboxLayout6->addWidget(lblFat_2);

        spacer15 = new QSpacerItem(21, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout6->addItem(spacer15);

        editProtein = new QLineEdit(GoodsElement);
        editProtein->setObjectName(QString::fromUtf8("editProtein"));
        editProtein->setMinimumSize(QSize(100, 0));
        editProtein->setMaximumSize(QSize(100, 32767));
        editProtein->setAlignment(Qt::AlignRight);

        hboxLayout6->addWidget(editProtein);


        vboxLayout1->addLayout(hboxLayout6);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        lblHydroCarbonat = new QLabel(GoodsElement);
        lblHydroCarbonat->setObjectName(QString::fromUtf8("lblHydroCarbonat"));
        lblHydroCarbonat->setWordWrap(false);

        hboxLayout7->addWidget(lblHydroCarbonat);

        spacer16 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(spacer16);

        editHydroCarbonat = new QLineEdit(GoodsElement);
        editHydroCarbonat->setObjectName(QString::fromUtf8("editHydroCarbonat"));
        editHydroCarbonat->setMinimumSize(QSize(100, 0));
        editHydroCarbonat->setMaximumSize(QSize(100, 32767));
        editHydroCarbonat->setAlignment(Qt::AlignRight);

        hboxLayout7->addWidget(editHydroCarbonat);


        vboxLayout1->addLayout(hboxLayout7);


        hboxLayout4->addLayout(vboxLayout1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(1);
        vboxLayout2->setContentsMargins(1, 1, 1, 1);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        lblFat_2_2 = new QLabel(GoodsElement);
        lblFat_2_2->setObjectName(QString::fromUtf8("lblFat_2_2"));
        lblFat_2_2->setWordWrap(false);

        hboxLayout8->addWidget(lblFat_2_2);

        spacer13 = new QSpacerItem(21, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacer13);

        editCalories = new QLineEdit(GoodsElement);
        editCalories->setObjectName(QString::fromUtf8("editCalories"));
        editCalories->setMinimumSize(QSize(100, 0));
        editCalories->setMaximumSize(QSize(100, 32767));
        editCalories->setAlignment(Qt::AlignRight);

        hboxLayout8->addWidget(editCalories);


        vboxLayout2->addLayout(hboxLayout8);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        lblFat = new QLabel(GoodsElement);
        lblFat->setObjectName(QString::fromUtf8("lblFat"));
        lblFat->setWordWrap(false);

        hboxLayout9->addWidget(lblFat);

        spacer14 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout9->addItem(spacer14);

        editFat = new QLineEdit(GoodsElement);
        editFat->setObjectName(QString::fromUtf8("editFat"));
        editFat->setMinimumSize(QSize(100, 0));
        editFat->setMaximumSize(QSize(100, 32767));
        editFat->setAlignment(Qt::AlignRight);

        hboxLayout9->addWidget(editFat);


        vboxLayout2->addLayout(hboxLayout9);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        lblPrice = new QLabel(GoodsElement);
        lblPrice->setObjectName(QString::fromUtf8("lblPrice"));
        lblPrice->setWordWrap(false);

        hboxLayout10->addWidget(lblPrice);

        spacer12 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout10->addItem(spacer12);

        editPrice = new QLineEdit(GoodsElement);
        editPrice->setObjectName(QString::fromUtf8("editPrice"));
        editPrice->setMinimumSize(QSize(100, 0));
        editPrice->setMaximumSize(QSize(100, 32767));
        editPrice->setAlignment(Qt::AlignRight);

        hboxLayout10->addWidget(editPrice);


        vboxLayout2->addLayout(hboxLayout10);


        hboxLayout4->addLayout(vboxLayout2);


        vboxLayout->addLayout(hboxLayout4);

        hboxLayout11 = new QHBoxLayout();
        hboxLayout11->setSpacing(6);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        chkOutOfStore = new QCheckBox(GoodsElement);
        chkOutOfStore->setObjectName(QString::fromUtf8("chkOutOfStore"));

        hboxLayout11->addWidget(chkOutOfStore);

        chkEqExport = new QCheckBox(GoodsElement);
        chkEqExport->setObjectName(QString::fromUtf8("chkEqExport"));

        hboxLayout11->addWidget(chkEqExport);

        spacer10 = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout11->addItem(spacer10);

        lblMaxDiscount = new QLabel(GoodsElement);
        lblMaxDiscount->setObjectName(QString::fromUtf8("lblMaxDiscount"));
        lblMaxDiscount->setWordWrap(false);

        hboxLayout11->addWidget(lblMaxDiscount);

        editMaxDiscount = new QLineEdit(GoodsElement);
        editMaxDiscount->setObjectName(QString::fromUtf8("editMaxDiscount"));
        editMaxDiscount->setMinimumSize(QSize(100, 0));
        editMaxDiscount->setMaximumSize(QSize(100, 32767));
        editMaxDiscount->setAlignment(Qt::AlignRight);

        hboxLayout11->addWidget(editMaxDiscount);


        vboxLayout->addLayout(hboxLayout11);

        editor = new Q3Frame(GoodsElement);
        editor->setObjectName(QString::fromUtf8("editor"));
        editor->setMinimumSize(QSize(0, 100));
        editor->setFrameShape(QFrame::StyledPanel);
        editor->setFrameShadow(QFrame::Raised);
        editor->setMargin(1);
        gridLayout1 = new QGridLayout(editor);
        gridLayout1->setSpacing(0);
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        editDescription = new Q3TextEdit(editor);
        editDescription->setObjectName(QString::fromUtf8("editDescription"));

        gridLayout1->addWidget(editDescription, 1, 0, 1, 1);

        toolbarParent = new Q3Frame(editor);
        toolbarParent->setObjectName(QString::fromUtf8("toolbarParent"));
        toolbarParent->setMinimumSize(QSize(0, 1));
        toolbarParent->setFrameShape(QFrame::StyledPanel);
        toolbarParent->setFrameShadow(QFrame::Raised);

        gridLayout1->addWidget(toolbarParent, 0, 0, 1, 1);


        vboxLayout->addWidget(editor);


        gridLayout->addLayout(vboxLayout, 1, 0, 1, 1);

        frame17 = new Q3Frame(GoodsElement);
        frame17->setObjectName(QString::fromUtf8("frame17"));
        frame17->setFrameShape(QFrame::StyledPanel);
        frame17->setFrameShadow(QFrame::Raised);
        gridLayout2 = new QGridLayout(frame17);
        gridLayout2->setSpacing(1);
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        hboxLayout12 = new QHBoxLayout();
        hboxLayout12->setSpacing(6);
        hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
        lblPicture = new QLabel(frame17);
        lblPicture->setObjectName(QString::fromUtf8("lblPicture"));
        lblPicture->setWordWrap(false);

        hboxLayout12->addWidget(lblPicture);

        btnSelectPicture = new QPushButton(frame17);
        btnSelectPicture->setObjectName(QString::fromUtf8("btnSelectPicture"));
        btnSelectPicture->setMaximumSize(QSize(40, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("select-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSelectPicture->setIcon(icon2);

        hboxLayout12->addWidget(btnSelectPicture);

        btnClearPicture = new QPushButton(frame17);
        btnClearPicture->setObjectName(QString::fromUtf8("btnClearPicture"));
        btnClearPicture->setMaximumSize(QSize(40, 40));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearPicture->setIcon(icon3);

        hboxLayout12->addWidget(btnClearPicture);


        vboxLayout3->addLayout(hboxLayout12);

        labelPicture = new QLabel(frame17);
        labelPicture->setObjectName(QString::fromUtf8("labelPicture"));
        labelPicture->setMinimumSize(QSize(300, 300));
        labelPicture->setMaximumSize(QSize(300, 300));
        labelPicture->setScaledContents(true);
        labelPicture->setWordWrap(false);

        vboxLayout3->addWidget(labelPicture);


        gridLayout2->addLayout(vboxLayout3, 0, 0, 1, 1);


        gridLayout->addWidget(frame17, 1, 1, 1, 1);

        QWidget::setTabOrder(editName, editExternalCode);
        QWidget::setTabOrder(editExternalCode, editPrice);
        QWidget::setTabOrder(editPrice, editHydroCarbonat);
        QWidget::setTabOrder(editHydroCarbonat, editFat);
        QWidget::setTabOrder(editFat, editCalories);
        QWidget::setTabOrder(editCalories, editProtein);
        QWidget::setTabOrder(editProtein, editDescription);
        QWidget::setTabOrder(editDescription, btnSelectPicture);
        QWidget::setTabOrder(btnSelectPicture, btnClearPicture);
        QWidget::setTabOrder(btnClearPicture, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);

        retranslateUi(GoodsElement);
        QObject::connect(buttonOk, SIGNAL(clicked()), GoodsElement, SLOT(ok()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), GoodsElement, SLOT(reject()));
        QObject::connect(btnSelectPicture, SIGNAL(clicked()), GoodsElement, SLOT(selectPicture()));
        QObject::connect(btnClearPicture, SIGNAL(clicked()), GoodsElement, SLOT(clearPicture()));

        QMetaObject::connectSlotsByName(GoodsElement);
    } // setupUi

    void retranslateUi(QDialog *GoodsElement)
    {
        GoodsElement->setWindowTitle(QApplication::translate("GoodsElement", "Element", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("GoodsElement", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("GoodsElement", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        lblName->setText(QApplication::translate("GoodsElement", "Name:", 0, QApplication::UnicodeUTF8));
        lblBarCode->setText(QApplication::translate("GoodsElement", "Barcode:", 0, QApplication::UnicodeUTF8));
        editBarcode->setInputMask(QString());
        editBarcode->setText(QApplication::translate("GoodsElement", "1234567890123", 0, QApplication::UnicodeUTF8));
        lblExtCode->setText(QApplication::translate("GoodsElement", "Ext.code:", 0, QApplication::UnicodeUTF8));
        editExternalCode->setInputMask(QString());
        editExternalCode->setText(QString());
        lblFat_2->setText(QApplication::translate("GoodsElement", "Proteins:", 0, QApplication::UnicodeUTF8));
        editProtein->setInputMask(QString());
        editProtein->setText(QString());
        lblHydroCarbonat->setText(QApplication::translate("GoodsElement", "Hydrocarbonates:", 0, QApplication::UnicodeUTF8));
        editHydroCarbonat->setInputMask(QString());
        editHydroCarbonat->setText(QString());
        lblFat_2_2->setText(QApplication::translate("GoodsElement", "Calories:", 0, QApplication::UnicodeUTF8));
        editCalories->setInputMask(QString());
        editCalories->setText(QString());
        lblFat->setText(QApplication::translate("GoodsElement", "Fat:", 0, QApplication::UnicodeUTF8));
        editFat->setInputMask(QString());
        editFat->setText(QString());
        lblPrice->setText(QApplication::translate("GoodsElement", "Price:", 0, QApplication::UnicodeUTF8));
        editPrice->setInputMask(QString());
        editPrice->setText(QString());
        chkOutOfStore->setText(QApplication::translate("GoodsElement", "Out of store", 0, QApplication::UnicodeUTF8));
        chkEqExport->setText(QApplication::translate("GoodsElement", "Export to equipment", 0, QApplication::UnicodeUTF8));
        lblMaxDiscount->setText(QApplication::translate("GoodsElement", "Max discount:", 0, QApplication::UnicodeUTF8));
        editMaxDiscount->setInputMask(QString());
        editMaxDiscount->setText(QString());
        lblPicture->setText(QApplication::translate("GoodsElement", "Picture", 0, QApplication::UnicodeUTF8));
        btnSelectPicture->setText(QString());
        btnClearPicture->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GoodsElement: public Ui_GoodsElement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOODSELEMENT_H
