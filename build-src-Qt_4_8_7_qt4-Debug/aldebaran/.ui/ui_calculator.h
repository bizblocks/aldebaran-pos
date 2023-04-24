/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_alCalculator
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn3;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btn0;
    QPushButton *btn_;
    QPushButton *btnEq;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QPushButton *btnMul;
    QPushButton *btnDiv;
    QPushButton *btnPlusMinus;
    QPushButton *btnBackspace;
    QPushButton *btnCE;
    QPushButton *btnC;
    QLCDNumber *lcdNumber;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *alCalculator)
    {
        if (alCalculator->objectName().isEmpty())
            alCalculator->setObjectName(QString::fromUtf8("alCalculator"));
        alCalculator->resize(251, 206);
        gridLayout = new QGridLayout(alCalculator);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn3 = new QPushButton(alCalculator);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setMinimumSize(QSize(40, 40));
        btn3->setMaximumSize(QSize(40, 40));
        QFont font;
        font.setPointSize(14);
        btn3->setFont(font);

        gridLayout->addWidget(btn3, 3, 2, 1, 1);

        btn1 = new QPushButton(alCalculator);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setMinimumSize(QSize(40, 40));
        btn1->setMaximumSize(QSize(40, 40));
        btn1->setFont(font);

        gridLayout->addWidget(btn1, 3, 0, 1, 1);

        btn2 = new QPushButton(alCalculator);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setMinimumSize(QSize(40, 40));
        btn2->setMaximumSize(QSize(40, 40));
        btn2->setFont(font);

        gridLayout->addWidget(btn2, 3, 1, 1, 1);

        btn4 = new QPushButton(alCalculator);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setMinimumSize(QSize(40, 40));
        btn4->setMaximumSize(QSize(40, 40));
        btn4->setFont(font);

        gridLayout->addWidget(btn4, 2, 0, 1, 1);

        btn5 = new QPushButton(alCalculator);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        btn5->setMinimumSize(QSize(40, 40));
        btn5->setMaximumSize(QSize(40, 40));
        btn5->setFont(font);

        gridLayout->addWidget(btn5, 2, 1, 1, 1);

        btn6 = new QPushButton(alCalculator);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        btn6->setMinimumSize(QSize(40, 40));
        btn6->setMaximumSize(QSize(40, 40));
        btn6->setFont(font);

        gridLayout->addWidget(btn6, 2, 2, 1, 1);

        btn7 = new QPushButton(alCalculator);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        btn7->setMinimumSize(QSize(40, 40));
        btn7->setMaximumSize(QSize(40, 40));
        btn7->setFont(font);

        gridLayout->addWidget(btn7, 1, 0, 1, 1);

        btn8 = new QPushButton(alCalculator);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        btn8->setMinimumSize(QSize(40, 40));
        btn8->setMaximumSize(QSize(40, 40));
        btn8->setFont(font);

        gridLayout->addWidget(btn8, 1, 1, 1, 1);

        btn9 = new QPushButton(alCalculator);
        btn9->setObjectName(QString::fromUtf8("btn9"));
        btn9->setMinimumSize(QSize(40, 40));
        btn9->setMaximumSize(QSize(40, 40));
        btn9->setFont(font);

        gridLayout->addWidget(btn9, 1, 2, 1, 1);

        btn0 = new QPushButton(alCalculator);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setMinimumSize(QSize(40, 40));
        btn0->setMaximumSize(QSize(40, 40));
        btn0->setFont(font);

        gridLayout->addWidget(btn0, 4, 0, 1, 1);

        btn_ = new QPushButton(alCalculator);
        btn_->setObjectName(QString::fromUtf8("btn_"));
        btn_->setMinimumSize(QSize(40, 40));
        btn_->setMaximumSize(QSize(40, 40));
        btn_->setFont(font);

        gridLayout->addWidget(btn_, 4, 1, 1, 1);

        btnEq = new QPushButton(alCalculator);
        btnEq->setObjectName(QString::fromUtf8("btnEq"));
        btnEq->setMinimumSize(QSize(40, 40));
        btnEq->setMaximumSize(QSize(40, 40));
        btnEq->setFont(font);

        gridLayout->addWidget(btnEq, 4, 2, 1, 1);

        btnPlus = new QPushButton(alCalculator);
        btnPlus->setObjectName(QString::fromUtf8("btnPlus"));
        btnPlus->setMinimumSize(QSize(40, 40));
        btnPlus->setMaximumSize(QSize(40, 40));
        btnPlus->setFont(font);

        gridLayout->addWidget(btnPlus, 1, 3, 1, 1);

        btnMinus = new QPushButton(alCalculator);
        btnMinus->setObjectName(QString::fromUtf8("btnMinus"));
        btnMinus->setMinimumSize(QSize(40, 40));
        btnMinus->setMaximumSize(QSize(40, 40));
        btnMinus->setFont(font);

        gridLayout->addWidget(btnMinus, 2, 3, 1, 1);

        btnMul = new QPushButton(alCalculator);
        btnMul->setObjectName(QString::fromUtf8("btnMul"));
        btnMul->setMinimumSize(QSize(40, 40));
        btnMul->setMaximumSize(QSize(40, 40));
        btnMul->setFont(font);

        gridLayout->addWidget(btnMul, 3, 3, 1, 1);

        btnDiv = new QPushButton(alCalculator);
        btnDiv->setObjectName(QString::fromUtf8("btnDiv"));
        btnDiv->setMinimumSize(QSize(40, 40));
        btnDiv->setMaximumSize(QSize(40, 40));
        btnDiv->setFont(font);

        gridLayout->addWidget(btnDiv, 4, 3, 1, 1);

        btnPlusMinus = new QPushButton(alCalculator);
        btnPlusMinus->setObjectName(QString::fromUtf8("btnPlusMinus"));
        btnPlusMinus->setMinimumSize(QSize(40, 40));
        btnPlusMinus->setMaximumSize(QSize(40, 40));
        btnPlusMinus->setFont(font);

        gridLayout->addWidget(btnPlusMinus, 2, 4, 1, 1);

        btnBackspace = new QPushButton(alCalculator);
        btnBackspace->setObjectName(QString::fromUtf8("btnBackspace"));
        btnBackspace->setMinimumSize(QSize(40, 40));
        btnBackspace->setMaximumSize(QSize(40, 40));
        btnBackspace->setFont(font);

        gridLayout->addWidget(btnBackspace, 2, 5, 1, 1);

        btnCE = new QPushButton(alCalculator);
        btnCE->setObjectName(QString::fromUtf8("btnCE"));
        btnCE->setMinimumSize(QSize(40, 40));
        btnCE->setMaximumSize(QSize(40, 40));
        btnCE->setFont(font);

        gridLayout->addWidget(btnCE, 1, 4, 1, 1);

        btnC = new QPushButton(alCalculator);
        btnC->setObjectName(QString::fromUtf8("btnC"));
        btnC->setMinimumSize(QSize(40, 40));
        btnC->setMaximumSize(QSize(40, 40));
        btnC->setFont(font);

        gridLayout->addWidget(btnC, 1, 5, 1, 1);

        lcdNumber = new QLCDNumber(alCalculator);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(0, 40));
        lcdNumber->setMaximumSize(QSize(32767, 40));
        lcdNumber->setNumDigits(12);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(123.444));

        gridLayout->addWidget(lcdNumber, 0, 0, 1, 6);

        btnOK = new QPushButton(alCalculator);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 40));
        btnOK->setFont(font);
        btnOK->setDefault(true);

        gridLayout->addWidget(btnOK, 4, 4, 1, 2);

        btnCancel = new QPushButton(alCalculator);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(0, 40));
        btnCancel->setFont(font);

        gridLayout->addWidget(btnCancel, 3, 4, 1, 2);


        retranslateUi(alCalculator);
        QObject::connect(btnOK, SIGNAL(clicked()), alCalculator, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), alCalculator, SLOT(reject()));
        QObject::connect(btn0, SIGNAL(clicked()), alCalculator, SLOT(on0()));
        QObject::connect(btn1, SIGNAL(clicked()), alCalculator, SLOT(on1()));
        QObject::connect(btn2, SIGNAL(clicked()), alCalculator, SLOT(on2()));
        QObject::connect(btn3, SIGNAL(clicked()), alCalculator, SLOT(on3()));
        QObject::connect(btn4, SIGNAL(clicked()), alCalculator, SLOT(on4()));
        QObject::connect(btn5, SIGNAL(clicked()), alCalculator, SLOT(on5()));
        QObject::connect(btn6, SIGNAL(clicked()), alCalculator, SLOT(on6()));
        QObject::connect(btn7, SIGNAL(clicked()), alCalculator, SLOT(on7()));
        QObject::connect(btn8, SIGNAL(clicked()), alCalculator, SLOT(on8()));
        QObject::connect(btn9, SIGNAL(clicked()), alCalculator, SLOT(on9()));
        QObject::connect(btnEq, SIGNAL(clicked()), alCalculator, SLOT(onEq()));
        QObject::connect(btnMul, SIGNAL(clicked()), alCalculator, SLOT(onMul()));
        QObject::connect(btnPlus, SIGNAL(clicked()), alCalculator, SLOT(onPlus()));
        QObject::connect(btnDiv, SIGNAL(clicked()), alCalculator, SLOT(onDiv()));
        QObject::connect(btn_, SIGNAL(clicked()), alCalculator, SLOT(on_()));
        QObject::connect(btnBackspace, SIGNAL(clicked()), alCalculator, SLOT(onBackspace()));
        QObject::connect(btnC, SIGNAL(clicked()), alCalculator, SLOT(onC()));
        QObject::connect(btnCE, SIGNAL(clicked()), alCalculator, SLOT(onCE()));
        QObject::connect(btnMinus, SIGNAL(clicked()), alCalculator, SLOT(onMinus()));
        QObject::connect(btnPlusMinus, SIGNAL(clicked()), alCalculator, SLOT(onPlusMinus()));

        QMetaObject::connectSlotsByName(alCalculator);
    } // setupUi

    void retranslateUi(QDialog *alCalculator)
    {
        alCalculator->setWindowTitle(QApplication::translate("alCalculator", "Calculator", 0, QApplication::UnicodeUTF8));
        btn3->setText(QApplication::translate("alCalculator", "3", 0, QApplication::UnicodeUTF8));
        btn3->setShortcut(QApplication::translate("alCalculator", "3", 0, QApplication::UnicodeUTF8));
        btn1->setText(QApplication::translate("alCalculator", "1", 0, QApplication::UnicodeUTF8));
        btn1->setShortcut(QApplication::translate("alCalculator", "1", 0, QApplication::UnicodeUTF8));
        btn2->setText(QApplication::translate("alCalculator", "2", 0, QApplication::UnicodeUTF8));
        btn2->setShortcut(QApplication::translate("alCalculator", "2", 0, QApplication::UnicodeUTF8));
        btn4->setText(QApplication::translate("alCalculator", "4", 0, QApplication::UnicodeUTF8));
        btn4->setShortcut(QApplication::translate("alCalculator", "4", 0, QApplication::UnicodeUTF8));
        btn5->setText(QApplication::translate("alCalculator", "5", 0, QApplication::UnicodeUTF8));
        btn5->setShortcut(QApplication::translate("alCalculator", "5", 0, QApplication::UnicodeUTF8));
        btn6->setText(QApplication::translate("alCalculator", "6", 0, QApplication::UnicodeUTF8));
        btn6->setShortcut(QApplication::translate("alCalculator", "6", 0, QApplication::UnicodeUTF8));
        btn7->setText(QApplication::translate("alCalculator", "7", 0, QApplication::UnicodeUTF8));
        btn7->setShortcut(QApplication::translate("alCalculator", "7", 0, QApplication::UnicodeUTF8));
        btn8->setText(QApplication::translate("alCalculator", "8", 0, QApplication::UnicodeUTF8));
        btn8->setShortcut(QApplication::translate("alCalculator", "8", 0, QApplication::UnicodeUTF8));
        btn9->setText(QApplication::translate("alCalculator", "9", 0, QApplication::UnicodeUTF8));
        btn9->setShortcut(QApplication::translate("alCalculator", "9", 0, QApplication::UnicodeUTF8));
        btn0->setText(QApplication::translate("alCalculator", "0", 0, QApplication::UnicodeUTF8));
        btn0->setShortcut(QApplication::translate("alCalculator", "0", 0, QApplication::UnicodeUTF8));
        btn_->setText(QApplication::translate("alCalculator", ".", 0, QApplication::UnicodeUTF8));
        btn_->setShortcut(QApplication::translate("alCalculator", ".", 0, QApplication::UnicodeUTF8));
        btnEq->setText(QApplication::translate("alCalculator", "=", 0, QApplication::UnicodeUTF8));
        btnEq->setShortcut(QApplication::translate("alCalculator", "=", 0, QApplication::UnicodeUTF8));
        btnPlus->setText(QApplication::translate("alCalculator", "+", 0, QApplication::UnicodeUTF8));
        btnPlus->setShortcut(QApplication::translate("alCalculator", "Shift++", 0, QApplication::UnicodeUTF8));
        btnMinus->setText(QApplication::translate("alCalculator", "-", 0, QApplication::UnicodeUTF8));
        btnMinus->setShortcut(QApplication::translate("alCalculator", "-", 0, QApplication::UnicodeUTF8));
        btnMul->setText(QApplication::translate("alCalculator", "*", 0, QApplication::UnicodeUTF8));
        btnMul->setShortcut(QApplication::translate("alCalculator", "Shift+*", 0, QApplication::UnicodeUTF8));
        btnDiv->setText(QApplication::translate("alCalculator", "\303\267", 0, QApplication::UnicodeUTF8));
        btnDiv->setShortcut(QApplication::translate("alCalculator", "/", 0, QApplication::UnicodeUTF8));
        btnPlusMinus->setText(QApplication::translate("alCalculator", "\302\261", 0, QApplication::UnicodeUTF8));
        btnPlusMinus->setShortcut(QString());
        btnBackspace->setText(QApplication::translate("alCalculator", "BS", 0, QApplication::UnicodeUTF8));
        btnBackspace->setShortcut(QApplication::translate("alCalculator", "Backspace", 0, QApplication::UnicodeUTF8));
        btnCE->setText(QApplication::translate("alCalculator", "CE", 0, QApplication::UnicodeUTF8));
        btnCE->setShortcut(QApplication::translate("alCalculator", "Del", 0, QApplication::UnicodeUTF8));
        btnC->setText(QApplication::translate("alCalculator", "C", 0, QApplication::UnicodeUTF8));
        btnC->setShortcut(QApplication::translate("alCalculator", "Ctrl+Del", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("alCalculator", "&OK", 0, QApplication::UnicodeUTF8));
        btnOK->setShortcut(QApplication::translate("alCalculator", "Alt+O", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("alCalculator", "&Cancel", 0, QApplication::UnicodeUTF8));
        btnCancel->setShortcut(QApplication::translate("alCalculator", "Alt+C, Esc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class alCalculator: public Ui_alCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
