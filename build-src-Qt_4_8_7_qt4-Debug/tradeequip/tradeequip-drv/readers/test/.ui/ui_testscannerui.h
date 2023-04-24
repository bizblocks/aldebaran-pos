/********************************************************************************
** Form generated from reading UI file 'testscannerui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTSCANNERUI_H
#define UI_TESTSCANNERUI_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <tereaderbase.h>

QT_BEGIN_NAMESPACE

class Ui_Form1
{
public:
    QVBoxLayout *vboxLayout;
    Q3TextEdit *textEdit1;

    void setupUi(QDialog *Form1)
    {
        if (Form1->objectName().isEmpty())
            Form1->setObjectName(QString::fromUtf8("Form1"));
        Form1->resize(379, 194);
        vboxLayout = new QVBoxLayout(Form1);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textEdit1 = new Q3TextEdit(Form1);
        textEdit1->setObjectName(QString::fromUtf8("textEdit1"));
        textEdit1->setTextFormat(Qt::LogText);
        textEdit1->setAutoFormatting(Q3TextEdit::AutoAll);

        vboxLayout->addWidget(textEdit1);


        retranslateUi(Form1);

        QMetaObject::connectSlotsByName(Form1);
    } // setupUi

    void retranslateUi(QDialog *Form1)
    {
        Form1->setWindowTitle(QApplication::translate("Form1", "Scanner Test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTSCANNERUI_H
