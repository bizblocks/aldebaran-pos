/********************************************************************************
** Form generated from reading UI file 'dlgexportsales.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXPORTSALES_H
#define UI_DLGEXPORTSALES_H

#include <Qt3Support/Q3DateTimeEdit>
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
#include <QtGui/QVBoxLayout>
#include <QtCore/QDateTime>

QT_BEGIN_NAMESPACE

class Ui_dlgExportSales
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *lblBegin;
    Q3DateTimeEdit *dteBegin;
    QHBoxLayout *hboxLayout1;
    QLabel *lblEnd;
    Q3DateTimeEdit *dteEnd;
    QLabel *textLabel2;
    QComboBox *cmbType;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *dlgExportSales)
    {
        if (dlgExportSales->objectName().isEmpty())
            dlgExportSales->setObjectName(QString::fromUtf8("dlgExportSales"));
        dlgExportSales->resize(258, 146);
        gridLayout = new QGridLayout(dlgExportSales);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblBegin = new QLabel(dlgExportSales);
        lblBegin->setObjectName(QString::fromUtf8("lblBegin"));
        lblBegin->setWordWrap(false);

        hboxLayout->addWidget(lblBegin);

        dteBegin = new Q3DateTimeEdit(dlgExportSales);
        dteBegin->setObjectName(QString::fromUtf8("dteBegin"));

        hboxLayout->addWidget(dteBegin);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblEnd = new QLabel(dlgExportSales);
        lblEnd->setObjectName(QString::fromUtf8("lblEnd"));
        lblEnd->setWordWrap(false);

        hboxLayout1->addWidget(lblEnd);

        dteEnd = new Q3DateTimeEdit(dlgExportSales);
        dteEnd->setObjectName(QString::fromUtf8("dteEnd"));

        hboxLayout1->addWidget(dteEnd);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout->addLayout(vboxLayout, 2, 0, 1, 1);

        textLabel2 = new QLabel(dlgExportSales);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 1, 0, 1, 1);

        cmbType = new QComboBox(dlgExportSales);
        cmbType->setObjectName(QString::fromUtf8("cmbType"));

        gridLayout->addWidget(cmbType, 0, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgExportSales);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout2->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgExportSales);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout2->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout2, 3, 0, 1, 1);


        retranslateUi(dlgExportSales);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgExportSales, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgExportSales, SLOT(reject()));
        QObject::connect(cmbType, SIGNAL(activated(int)), dlgExportSales, SLOT(refresh(int)));

        QMetaObject::connectSlotsByName(dlgExportSales);
    } // setupUi

    void retranslateUi(QDialog *dlgExportSales)
    {
        dlgExportSales->setWindowTitle(QApplication::translate("dlgExportSales", "Export sales", 0, QApplication::UnicodeUTF8));
        lblBegin->setText(QApplication::translate("dlgExportSales", "begin", 0, QApplication::UnicodeUTF8));
        lblEnd->setText(QApplication::translate("dlgExportSales", "end", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("dlgExportSales", "Period", 0, QApplication::UnicodeUTF8));
        cmbType->clear();
        cmbType->insertItems(0, QStringList()
         << QApplication::translate("dlgExportSales", "Current", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgExportSales", "Period", 0, QApplication::UnicodeUTF8)
        );
        buttonOk->setText(QApplication::translate("dlgExportSales", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgExportSales", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class dlgExportSales: public Ui_dlgExportSales {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGEXPORTSALES_H
