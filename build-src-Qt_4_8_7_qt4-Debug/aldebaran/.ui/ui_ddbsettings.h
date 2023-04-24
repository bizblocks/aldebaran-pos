/********************************************************************************
** Form generated from reading UI file 'ddbsettings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DDBSETTINGS_H
#define UI_DDBSETTINGS_H

#include <Qt3Support/Q3Frame>
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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ddbsettings
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *btnTest;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    Q3Frame *frame3;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *lblDBName;
    QLineEdit *editDBName;
    QHBoxLayout *hboxLayout2;
    QLabel *lblAdress;
    QSpacerItem *spacer2;
    QLineEdit *editAdress;
    QHBoxLayout *hboxLayout3;
    QLabel *lblUser;
    QSpacerItem *spacer4;
    QLineEdit *editUser;
    QHBoxLayout *hboxLayout4;
    QLabel *lblPort;
    QSpacerItem *spacer3;
    QLineEdit *editPort;
    QHBoxLayout *hboxLayout5;
    QLabel *lblPassword;
    QSpacerItem *spacer6;
    QLineEdit *editPassword;
    QHBoxLayout *hboxLayout6;
    QLabel *lblDBType;
    QComboBox *cmbDBType;

    void setupUi(QDialog *ddbsettings)
    {
        if (ddbsettings->objectName().isEmpty())
            ddbsettings->setObjectName(QString::fromUtf8("ddbsettings"));
        ddbsettings->resize(428, 298);
        ddbsettings->setSizeGripEnabled(false);
        ddbsettings->setModal(true);
        gridLayout = new QGridLayout(ddbsettings);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        btnTest = new QPushButton(ddbsettings);
        btnTest->setObjectName(QString::fromUtf8("btnTest"));

        hboxLayout->addWidget(btnTest);

        Horizontal_Spacing2 = new QSpacerItem(130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        btnOk = new QPushButton(ddbsettings);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon);
        btnOk->setAutoDefault(true);
        btnOk->setDefault(true);

        hboxLayout->addWidget(btnOk);

        btnCancel = new QPushButton(ddbsettings);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon1);
        btnCancel->setAutoDefault(true);

        hboxLayout->addWidget(btnCancel);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        frame3 = new Q3Frame(ddbsettings);
        frame3->setObjectName(QString::fromUtf8("frame3"));
        frame3->setMinimumSize(QSize(100, 0));
        frame3->setFrameShape(QFrame::StyledPanel);
        frame3->setFrameShadow(QFrame::Raised);
        gridLayout1 = new QGridLayout(frame3);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblDBName = new QLabel(frame3);
        lblDBName->setObjectName(QString::fromUtf8("lblDBName"));
        lblDBName->setWordWrap(false);

        hboxLayout1->addWidget(lblDBName);

        editDBName = new QLineEdit(frame3);
        editDBName->setObjectName(QString::fromUtf8("editDBName"));

        hboxLayout1->addWidget(editDBName);


        gridLayout1->addLayout(hboxLayout1, 1, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        lblAdress = new QLabel(frame3);
        lblAdress->setObjectName(QString::fromUtf8("lblAdress"));
        lblAdress->setWordWrap(false);

        hboxLayout2->addWidget(lblAdress);

        spacer2 = new QSpacerItem(21, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer2);

        editAdress = new QLineEdit(frame3);
        editAdress->setObjectName(QString::fromUtf8("editAdress"));

        hboxLayout2->addWidget(editAdress);


        gridLayout1->addLayout(hboxLayout2, 2, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        lblUser = new QLabel(frame3);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));
        lblUser->setWordWrap(false);

        hboxLayout3->addWidget(lblUser);

        spacer4 = new QSpacerItem(51, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer4);

        editUser = new QLineEdit(frame3);
        editUser->setObjectName(QString::fromUtf8("editUser"));

        hboxLayout3->addWidget(editUser);


        gridLayout1->addLayout(hboxLayout3, 4, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        lblPort = new QLabel(frame3);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        lblPort->setMinimumSize(QSize(0, 0));
        lblPort->setWordWrap(false);

        hboxLayout4->addWidget(lblPort);

        spacer3 = new QSpacerItem(260, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacer3);

        editPort = new QLineEdit(frame3);
        editPort->setObjectName(QString::fromUtf8("editPort"));
        editPort->setMinimumSize(QSize(60, 0));
        editPort->setMaximumSize(QSize(60, 32767));

        hboxLayout4->addWidget(editPort);


        gridLayout1->addLayout(hboxLayout4, 3, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblPassword = new QLabel(frame3);
        lblPassword->setObjectName(QString::fromUtf8("lblPassword"));
        lblPassword->setWordWrap(false);

        hboxLayout5->addWidget(lblPassword);

        spacer6 = new QSpacerItem(121, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacer6);

        editPassword = new QLineEdit(frame3);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setEchoMode(QLineEdit::Password);

        hboxLayout5->addWidget(editPassword);


        gridLayout1->addLayout(hboxLayout5, 5, 0, 1, 1);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblDBType = new QLabel(frame3);
        lblDBType->setObjectName(QString::fromUtf8("lblDBType"));
        lblDBType->setWordWrap(false);

        hboxLayout6->addWidget(lblDBType);

        cmbDBType = new QComboBox(frame3);
        cmbDBType->setObjectName(QString::fromUtf8("cmbDBType"));

        hboxLayout6->addWidget(cmbDBType);


        gridLayout1->addLayout(hboxLayout6, 0, 0, 1, 1);


        gridLayout->addWidget(frame3, 0, 0, 1, 1);

        QWidget::setTabOrder(cmbDBType, editDBName);
        QWidget::setTabOrder(editDBName, editAdress);
        QWidget::setTabOrder(editAdress, editPort);
        QWidget::setTabOrder(editPort, editUser);
        QWidget::setTabOrder(editUser, editPassword);
        QWidget::setTabOrder(editPassword, btnTest);
        QWidget::setTabOrder(btnTest, btnOk);
        QWidget::setTabOrder(btnOk, btnCancel);

        retranslateUi(ddbsettings);
        QObject::connect(btnOk, SIGNAL(clicked()), ddbsettings, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), ddbsettings, SLOT(reject()));
        QObject::connect(btnTest, SIGNAL(clicked()), ddbsettings, SLOT(testConnection()));

        QMetaObject::connectSlotsByName(ddbsettings);
    } // setupUi

    void retranslateUi(QDialog *ddbsettings)
    {
        ddbsettings->setWindowTitle(QApplication::translate("ddbsettings", "Database connection settings", 0, QApplication::UnicodeUTF8));
        btnTest->setText(QApplication::translate("ddbsettings", "Test", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("ddbsettings", "&OK", 0, QApplication::UnicodeUTF8));
        btnOk->setShortcut(QApplication::translate("ddbsettings", "Ctrl+Return", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("ddbsettings", "&Cancel", 0, QApplication::UnicodeUTF8));
        btnCancel->setShortcut(QApplication::translate("ddbsettings", "Esc", 0, QApplication::UnicodeUTF8));
        lblDBName->setText(QApplication::translate("ddbsettings", "DB Name", 0, QApplication::UnicodeUTF8));
        lblAdress->setText(QApplication::translate("ddbsettings", "Adress", 0, QApplication::UnicodeUTF8));
        editAdress->setText(QString());
        lblUser->setText(QApplication::translate("ddbsettings", "User", 0, QApplication::UnicodeUTF8));
        lblPort->setText(QApplication::translate("ddbsettings", "Port", 0, QApplication::UnicodeUTF8));
        lblPassword->setText(QApplication::translate("ddbsettings", "Password", 0, QApplication::UnicodeUTF8));
        lblDBType->setText(QApplication::translate("ddbsettings", "DB Type", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ddbsettings: public Ui_ddbsettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDBSETTINGS_H
