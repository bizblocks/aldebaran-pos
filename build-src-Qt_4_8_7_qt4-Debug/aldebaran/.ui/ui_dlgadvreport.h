/********************************************************************************
** Form generated from reading UI file 'dlgadvreport.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGADVREPORT_H
#define UI_DLGADVREPORT_H

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

class Ui_dlgAdvReport
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
    QHBoxLayout *hboxLayout2;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QLabel *textLabel2;
    QComboBox *cmbType;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel1;
    QComboBox *cmbReport;

    void setupUi(QDialog *dlgAdvReport)
    {
        if (dlgAdvReport->objectName().isEmpty())
            dlgAdvReport->setObjectName(QString::fromUtf8("dlgAdvReport"));
        dlgAdvReport->resize(262, 168);
        gridLayout = new QGridLayout(dlgAdvReport);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblBegin = new QLabel(dlgAdvReport);
        lblBegin->setObjectName(QString::fromUtf8("lblBegin"));
        lblBegin->setWordWrap(false);

        hboxLayout->addWidget(lblBegin);

        dteBegin = new Q3DateTimeEdit(dlgAdvReport);
        dteBegin->setObjectName(QString::fromUtf8("dteBegin"));

        hboxLayout->addWidget(dteBegin);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblEnd = new QLabel(dlgAdvReport);
        lblEnd->setObjectName(QString::fromUtf8("lblEnd"));
        lblEnd->setWordWrap(false);

        hboxLayout1->addWidget(lblEnd);

        dteEnd = new Q3DateTimeEdit(dlgAdvReport);
        dteEnd->setObjectName(QString::fromUtf8("dteEnd"));

        hboxLayout1->addWidget(dteEnd);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout->addLayout(vboxLayout, 3, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(dlgAdvReport);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOk->setIcon(icon);
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout2->addWidget(buttonOk);

        buttonCancel = new QPushButton(dlgAdvReport);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon1);
        buttonCancel->setAutoDefault(true);

        hboxLayout2->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout2, 4, 0, 1, 1);

        textLabel2 = new QLabel(dlgAdvReport);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 2, 0, 1, 1);

        cmbType = new QComboBox(dlgAdvReport);
        cmbType->setObjectName(QString::fromUtf8("cmbType"));

        gridLayout->addWidget(cmbType, 1, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        textLabel1 = new QLabel(dlgAdvReport);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        hboxLayout3->addWidget(textLabel1);

        cmbReport = new QComboBox(dlgAdvReport);
        cmbReport->setObjectName(QString::fromUtf8("cmbReport"));

        hboxLayout3->addWidget(cmbReport);


        gridLayout->addLayout(hboxLayout3, 0, 0, 1, 1);


        retranslateUi(dlgAdvReport);
        QObject::connect(buttonOk, SIGNAL(clicked()), dlgAdvReport, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), dlgAdvReport, SLOT(reject()));
        QObject::connect(cmbType, SIGNAL(activated(int)), dlgAdvReport, SLOT(refresh(int)));

        QMetaObject::connectSlotsByName(dlgAdvReport);
    } // setupUi

    void retranslateUi(QDialog *dlgAdvReport)
    {
        dlgAdvReport->setWindowTitle(QApplication::translate("dlgAdvReport", "dlgAdvReport", 0, QApplication::UnicodeUTF8));
        lblBegin->setText(QApplication::translate("dlgAdvReport", "begin", 0, QApplication::UnicodeUTF8));
        lblEnd->setText(QApplication::translate("dlgAdvReport", "end", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("dlgAdvReport", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("dlgAdvReport", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        textLabel2->setText(QApplication::translate("dlgAdvReport", "Period", 0, QApplication::UnicodeUTF8));
        cmbType->clear();
        cmbType->insertItems(0, QStringList()
         << QApplication::translate("dlgAdvReport", "Current", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgAdvReport", "Period", 0, QApplication::UnicodeUTF8)
        );
        textLabel1->setText(QApplication::translate("dlgAdvReport", "Report type", 0, QApplication::UnicodeUTF8));
        cmbReport->clear();
        cmbReport->insertItems(0, QStringList()
         << QApplication::translate("dlgAdvReport", "Goods", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgAdvReport", "Hourly", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgAdvReport", "Checks", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgAdvReport", "Discounts", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class dlgAdvReport: public Ui_dlgAdvReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGADVREPORT_H
