/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MainWindow>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3ProgressBar>
#include <Qt3Support/Q3Table>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
//#include "felix-rk.h"

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget2;
    QWidget *tab;
    QGridLayout *gridLayout1;
    QSplitter *splitter1;
    Q3TextEdit *te_Log;
    Q3GroupBox *groupBox1;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout;
    QLabel *lblParam1;
    QSpinBox *param1;
    QLabel *lblParam2;
    QSpinBox *param2;
    Q3Table *table1;
    QPushButton *pb_ReadState;
    QPushButton *pbReadOptions;
    QSpacerItem *spacer2_2;
    QPushButton *pb_MoneyRegs;
    QPushButton *pb_OperRegs;
    QPushButton *pushButton5;
    QHBoxLayout *hboxLayout1;
    QPushButton *pb_Open;
    QPushButton *pb_Close;
    QPushButton *op_Command;
    QPushButton *pushButton6;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel2;
    QComboBox *cb_BaudRate;
    QSpacerItem *spacer2;
    QLineEdit *le_Command;
    QWidget *tab1;
    QHBoxLayout *hboxLayout3;
    QSplitter *splitter3;
    QWidget *layout11;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout4;
    QVBoxLayout *vboxLayout1;
    QPushButton *pb_ReadTableList;
    QPushButton *pb_CommitTable;
    QSpacerItem *spacer3;
    Q3ListBox *lb_Tables;
    Q3Table *table2;
    QWidget *TabPage;
    QGridLayout *gridLayout3;
    QSpacerItem *spacer4;
    QHBoxLayout *hboxLayout5;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout6;
    QLabel *textLabel1;
    QComboBox *cb_Port;
    QPushButton *pb_SetCommConfig;
    Q3GroupBox *grpPasswords;
    QGridLayout *gridLayout4;
    QHBoxLayout *hboxLayout7;
    QLabel *textLabel2_3;
    QSpacerItem *spacer7;
    QLineEdit *editAccessPass;
    QHBoxLayout *hboxLayout8;
    QLabel *lblOperPass;
    QSpacerItem *spacer8;
    QLineEdit *editOperPass;
    QHBoxLayout *hboxLayout9;
    QLabel *lblAdminPass;
    QSpacerItem *spacer9;
    QLineEdit *editAdminPass;
    QHBoxLayout *hboxLayout10;
    QLabel *lblFiscalPass;
    QSpacerItem *spacer10;
    QLineEdit *editFiscalPass;
    QSpacerItem *spacer5;
    Q3GroupBox *groupBox3;
    QHBoxLayout *hboxLayout11;
    Q3ListBox *lb_Ops;
    QVBoxLayout *vboxLayout3;
    QPushButton *pb_commit;
    QLabel *textLabel1_3;
    QLineEdit *le_ItName;
    QLabel *textLabel2_2;
    QLineEdit *le_Sum;
    Q3GroupBox *groupBox2;
    QGridLayout *gridLayout5;
    QLabel *textLabel1_2;
    QLineEdit *le_devNumber;
    QPushButton *pushButton9;
    Q3ProgressBar *pb_Load;

    void setupUi(Q3MainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(779, 572);
        widget = new QWidget(MainForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 779, 572));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget2 = new QTabWidget(widget);
        tabWidget2->setObjectName(QString::fromUtf8("tabWidget2"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout1 = new QGridLayout(tab);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        splitter1 = new QSplitter(tab);
        splitter1->setObjectName(QString::fromUtf8("splitter1"));
        splitter1->setOrientation(Qt::Horizontal);
        te_Log = new Q3TextEdit(splitter1);
        te_Log->setObjectName(QString::fromUtf8("te_Log"));
        te_Log->setTextFormat(Qt::LogText);
        splitter1->addWidget(te_Log);
        groupBox1 = new Q3GroupBox(splitter1);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout2 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout2);
        gridLayout2->setAlignment(Qt::AlignTop);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lblParam1 = new QLabel(groupBox1);
        lblParam1->setObjectName(QString::fromUtf8("lblParam1"));
        lblParam1->setWordWrap(false);

        hboxLayout->addWidget(lblParam1);

        param1 = new QSpinBox(groupBox1);
        param1->setObjectName(QString::fromUtf8("param1"));
        param1->setMaximum(255);

        hboxLayout->addWidget(param1);

        lblParam2 = new QLabel(groupBox1);
        lblParam2->setObjectName(QString::fromUtf8("lblParam2"));
        lblParam2->setWordWrap(false);

        hboxLayout->addWidget(lblParam2);

        param2 = new QSpinBox(groupBox1);
        param2->setObjectName(QString::fromUtf8("param2"));
        param2->setMaximum(255);

        hboxLayout->addWidget(param2);


        gridLayout2->addLayout(hboxLayout, 1, 0, 1, 5);

        table1 = new Q3Table(groupBox1);
        table1->setObjectName(QString::fromUtf8("table1"));
        table1->setFrameShadow(QFrame::Sunken);
        table1->setLineWidth(1);
        table1->setMidLineWidth(0);
        table1->setResizePolicy(Q3ScrollView::AutoOneFit);
        table1->setNumRows(0);
        table1->setNumCols(2);
        table1->setShowGrid(true);
        table1->setReadOnly(true);
        table1->setSelectionMode(Q3Table::SingleRow);

        gridLayout2->addWidget(table1, 0, 0, 1, 5);

        pb_ReadState = new QPushButton(groupBox1);
        pb_ReadState->setObjectName(QString::fromUtf8("pb_ReadState"));

        gridLayout2->addWidget(pb_ReadState, 2, 1, 1, 1);

        pbReadOptions = new QPushButton(groupBox1);
        pbReadOptions->setObjectName(QString::fromUtf8("pbReadOptions"));

        gridLayout2->addWidget(pbReadOptions, 2, 0, 1, 1);

        spacer2_2 = new QSpacerItem(20, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacer2_2, 2, 5, 1, 1);

        pb_MoneyRegs = new QPushButton(groupBox1);
        pb_MoneyRegs->setObjectName(QString::fromUtf8("pb_MoneyRegs"));

        gridLayout2->addWidget(pb_MoneyRegs, 2, 4, 1, 1);

        pb_OperRegs = new QPushButton(groupBox1);
        pb_OperRegs->setObjectName(QString::fromUtf8("pb_OperRegs"));

        gridLayout2->addWidget(pb_OperRegs, 2, 3, 1, 1);

        pushButton5 = new QPushButton(groupBox1);
        pushButton5->setObjectName(QString::fromUtf8("pushButton5"));

        gridLayout2->addWidget(pushButton5, 2, 2, 1, 1);

        splitter1->addWidget(groupBox1);

        gridLayout1->addWidget(splitter1, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        pb_Open = new QPushButton(tab);
        pb_Open->setObjectName(QString::fromUtf8("pb_Open"));

        hboxLayout1->addWidget(pb_Open);

        pb_Close = new QPushButton(tab);
        pb_Close->setObjectName(QString::fromUtf8("pb_Close"));

        hboxLayout1->addWidget(pb_Close);

        op_Command = new QPushButton(tab);
        op_Command->setObjectName(QString::fromUtf8("op_Command"));
        op_Command->setDefault(true);

        hboxLayout1->addWidget(op_Command);

        pushButton6 = new QPushButton(tab);
        pushButton6->setObjectName(QString::fromUtf8("pushButton6"));

        hboxLayout1->addWidget(pushButton6);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        textLabel2 = new QLabel(tab);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        hboxLayout2->addWidget(textLabel2);

        cb_BaudRate = new QComboBox(tab);
        cb_BaudRate->setObjectName(QString::fromUtf8("cb_BaudRate"));

        hboxLayout2->addWidget(cb_BaudRate);


        hboxLayout1->addLayout(hboxLayout2);

        spacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer2);


        gridLayout1->addLayout(hboxLayout1, 1, 0, 1, 1);

        le_Command = new QLineEdit(tab);
        le_Command->setObjectName(QString::fromUtf8("le_Command"));

        gridLayout1->addWidget(le_Command, 2, 0, 1, 1);

        tabWidget2->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        hboxLayout3 = new QHBoxLayout(tab1);
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(11, 11, 11, 11);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        splitter3 = new QSplitter(tab1);
        splitter3->setObjectName(QString::fromUtf8("splitter3"));
        splitter3->setOrientation(Qt::Horizontal);
        layout11 = new QWidget(splitter3);
        layout11->setObjectName(QString::fromUtf8("layout11"));
        vboxLayout = new QVBoxLayout(layout11);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        pb_ReadTableList = new QPushButton(layout11);
        pb_ReadTableList->setObjectName(QString::fromUtf8("pb_ReadTableList"));

        vboxLayout1->addWidget(pb_ReadTableList);

        pb_CommitTable = new QPushButton(layout11);
        pb_CommitTable->setObjectName(QString::fromUtf8("pb_CommitTable"));

        vboxLayout1->addWidget(pb_CommitTable);


        hboxLayout4->addLayout(vboxLayout1);

        spacer3 = new QSpacerItem(52, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacer3);


        vboxLayout->addLayout(hboxLayout4);

        lb_Tables = new Q3ListBox(layout11);
        lb_Tables->setObjectName(QString::fromUtf8("lb_Tables"));

        vboxLayout->addWidget(lb_Tables);

        splitter3->addWidget(layout11);
        table2 = new Q3Table(splitter3);
        table2->setObjectName(QString::fromUtf8("table2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        table2->setFont(font);
        table2->setNumRows(0);
        table2->setNumCols(0);
        table2->setReadOnly(false);
        table2->setSelectionMode(Q3Table::Single);
        splitter3->addWidget(table2);

        hboxLayout3->addWidget(splitter3);

        tabWidget2->addTab(tab1, QString());
        TabPage = new QWidget();
        TabPage->setObjectName(QString::fromUtf8("TabPage"));
        gridLayout3 = new QGridLayout(TabPage);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        spacer4 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacer4, 3, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        textLabel1 = new QLabel(TabPage);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        hboxLayout6->addWidget(textLabel1);

        cb_Port = new QComboBox(TabPage);
        cb_Port->setObjectName(QString::fromUtf8("cb_Port"));

        hboxLayout6->addWidget(cb_Port);


        vboxLayout2->addLayout(hboxLayout6);

        pb_SetCommConfig = new QPushButton(TabPage);
        pb_SetCommConfig->setObjectName(QString::fromUtf8("pb_SetCommConfig"));

        vboxLayout2->addWidget(pb_SetCommConfig);


        hboxLayout5->addLayout(vboxLayout2);

        grpPasswords = new Q3GroupBox(TabPage);
        grpPasswords->setObjectName(QString::fromUtf8("grpPasswords"));
        grpPasswords->setColumnLayout(0, Qt::Vertical);
        grpPasswords->layout()->setSpacing(6);
        grpPasswords->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout4 = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(grpPasswords->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout4);
        gridLayout4->setAlignment(Qt::AlignTop);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        textLabel2_3 = new QLabel(grpPasswords);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setWordWrap(false);

        hboxLayout7->addWidget(textLabel2_3);

        spacer7 = new QSpacerItem(21, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(spacer7);

        editAccessPass = new QLineEdit(grpPasswords);
        editAccessPass->setObjectName(QString::fromUtf8("editAccessPass"));
        editAccessPass->setMinimumSize(QSize(50, 0));
        editAccessPass->setMaximumSize(QSize(50, 32767));
        editAccessPass->setMaxLength(4);

        hboxLayout7->addWidget(editAccessPass);


        gridLayout4->addLayout(hboxLayout7, 0, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        lblOperPass = new QLabel(grpPasswords);
        lblOperPass->setObjectName(QString::fromUtf8("lblOperPass"));
        lblOperPass->setWordWrap(false);

        hboxLayout8->addWidget(lblOperPass);

        spacer8 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacer8);

        editOperPass = new QLineEdit(grpPasswords);
        editOperPass->setObjectName(QString::fromUtf8("editOperPass"));
        editOperPass->setMinimumSize(QSize(100, 0));
        editOperPass->setMaximumSize(QSize(100, 32767));
        editOperPass->setMaxLength(8);

        hboxLayout8->addWidget(editOperPass);


        gridLayout4->addLayout(hboxLayout8, 1, 0, 1, 2);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        lblAdminPass = new QLabel(grpPasswords);
        lblAdminPass->setObjectName(QString::fromUtf8("lblAdminPass"));
        lblAdminPass->setWordWrap(false);

        hboxLayout9->addWidget(lblAdminPass);

        spacer9 = new QSpacerItem(41, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout9->addItem(spacer9);

        editAdminPass = new QLineEdit(grpPasswords);
        editAdminPass->setObjectName(QString::fromUtf8("editAdminPass"));
        editAdminPass->setMinimumSize(QSize(100, 0));
        editAdminPass->setMaximumSize(QSize(100, 32767));
        editAdminPass->setMaxLength(8);

        hboxLayout9->addWidget(editAdminPass);


        gridLayout4->addLayout(hboxLayout9, 0, 1, 1, 2);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        lblFiscalPass = new QLabel(grpPasswords);
        lblFiscalPass->setObjectName(QString::fromUtf8("lblFiscalPass"));
        lblFiscalPass->setWordWrap(false);

        hboxLayout10->addWidget(lblFiscalPass);

        spacer10 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout10->addItem(spacer10);

        editFiscalPass = new QLineEdit(grpPasswords);
        editFiscalPass->setObjectName(QString::fromUtf8("editFiscalPass"));
        editFiscalPass->setMinimumSize(QSize(100, 0));
        editFiscalPass->setMaximumSize(QSize(100, 32767));
        editFiscalPass->setMaxLength(8);

        hboxLayout10->addWidget(editFiscalPass);


        gridLayout4->addLayout(hboxLayout10, 1, 2, 1, 1);


        hboxLayout5->addWidget(grpPasswords);

        spacer5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacer5);


        gridLayout3->addLayout(hboxLayout5, 0, 0, 1, 1);

        groupBox3 = new Q3GroupBox(TabPage);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        groupBox3->setColumnLayout(0, Qt::Vertical);
        groupBox3->layout()->setSpacing(6);
        groupBox3->layout()->setContentsMargins(11, 11, 11, 11);
        hboxLayout11 = new QHBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(groupBox3->layout());
        if (boxlayout2)
            boxlayout2->addLayout(hboxLayout11);
        hboxLayout11->setAlignment(Qt::AlignTop);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        lb_Ops = new Q3ListBox(groupBox3);
        lb_Ops->setObjectName(QString::fromUtf8("lb_Ops"));

        hboxLayout11->addWidget(lb_Ops);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        pb_commit = new QPushButton(groupBox3);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));

        vboxLayout3->addWidget(pb_commit);

        textLabel1_3 = new QLabel(groupBox3);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setWordWrap(false);

        vboxLayout3->addWidget(textLabel1_3);

        le_ItName = new QLineEdit(groupBox3);
        le_ItName->setObjectName(QString::fromUtf8("le_ItName"));

        vboxLayout3->addWidget(le_ItName);

        textLabel2_2 = new QLabel(groupBox3);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        vboxLayout3->addWidget(textLabel2_2);

        le_Sum = new QLineEdit(groupBox3);
        le_Sum->setObjectName(QString::fromUtf8("le_Sum"));

        vboxLayout3->addWidget(le_Sum);


        hboxLayout11->addLayout(vboxLayout3);


        gridLayout3->addWidget(groupBox3, 2, 0, 1, 1);

        groupBox2 = new Q3GroupBox(TabPage);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setColumnLayout(0, Qt::Vertical);
        groupBox2->layout()->setSpacing(6);
        groupBox2->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout5 = new QGridLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(groupBox2->layout());
        if (boxlayout3)
            boxlayout3->addLayout(gridLayout5);
        gridLayout5->setAlignment(Qt::AlignTop);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        textLabel1_2 = new QLabel(groupBox2);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        gridLayout5->addWidget(textLabel1_2, 0, 0, 1, 1);

        le_devNumber = new QLineEdit(groupBox2);
        le_devNumber->setObjectName(QString::fromUtf8("le_devNumber"));

        gridLayout5->addWidget(le_devNumber, 0, 1, 1, 2);

        pushButton9 = new QPushButton(groupBox2);
        pushButton9->setObjectName(QString::fromUtf8("pushButton9"));

        gridLayout5->addWidget(pushButton9, 1, 0, 1, 2);

        pb_Load = new Q3ProgressBar(groupBox2);
        pb_Load->setObjectName(QString::fromUtf8("pb_Load"));

        gridLayout5->addWidget(pb_Load, 1, 2, 1, 1);


        gridLayout3->addWidget(groupBox2, 1, 0, 1, 1);

        tabWidget2->addTab(TabPage, QString());

        gridLayout->addWidget(tabWidget2, 0, 0, 1, 1);

        MainForm->setCentralWidget(widget);

        retranslateUi(MainForm);
        QObject::connect(pb_Open, SIGNAL(clicked()), MainForm, SLOT(open()));
        QObject::connect(pb_Close, SIGNAL(clicked()), MainForm, SLOT(close()));
        QObject::connect(op_Command, SIGNAL(clicked()), MainForm, SLOT(issueCommand()));
        QObject::connect(pbReadOptions, SIGNAL(clicked()), MainForm, SLOT(readOptions()));
        QObject::connect(pushButton5, SIGNAL(clicked()), MainForm, SLOT(burstRead()));
        QObject::connect(pushButton6, SIGNAL(clicked()), MainForm, SLOT(printString()));
        QObject::connect(pb_ReadTableList, SIGNAL(clicked()), MainForm, SLOT(readTableList()));
        QObject::connect(lb_Tables, SIGNAL(highlighted(int)), MainForm, SLOT(tableSelected(int)));
        QObject::connect(pb_SetCommConfig, SIGNAL(clicked()), MainForm, SLOT(setPortConfig()));
        QObject::connect(pushButton9, SIGNAL(clicked()), MainForm, SLOT(saveDump()));
        QObject::connect(pb_commit, SIGNAL(clicked()), MainForm, SLOT(commitAction()));
        QObject::connect(pb_CommitTable, SIGNAL(clicked()), MainForm, SLOT(commitTableChanges()));
        QObject::connect(pb_OperRegs, SIGNAL(clicked()), MainForm, SLOT(onOperRegs()));
        QObject::connect(pb_MoneyRegs, SIGNAL(clicked()), MainForm, SLOT(onMoneyRegs()));
        QObject::connect(pb_ReadState, SIGNAL(clicked()), MainForm, SLOT(readState()));

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(Q3MainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Felix driver test", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("MainForm", "FR state", 0, QApplication::UnicodeUTF8));
        lblParam1->setText(QApplication::translate("MainForm", "parameter 1", 0, QApplication::UnicodeUTF8));
        lblParam2->setText(QApplication::translate("MainForm", "parameter 2", 0, QApplication::UnicodeUTF8));
        table1->horizontalHeader()->setLabel(0, QApplication::translate("MainForm", "Name", 0, QApplication::UnicodeUTF8));
        table1->horizontalHeader()->setLabel(1, QApplication::translate("MainForm", "Value", 0, QApplication::UnicodeUTF8));
        pb_ReadState->setText(QApplication::translate("MainForm", "Read State", 0, QApplication::UnicodeUTF8));
        pbReadOptions->setText(QApplication::translate("MainForm", "Read", 0, QApplication::UnicodeUTF8));
        pb_MoneyRegs->setText(QApplication::translate("MainForm", "MoneyRegs", 0, QApplication::UnicodeUTF8));
        pb_OperRegs->setText(QApplication::translate("MainForm", "OperRegs", 0, QApplication::UnicodeUTF8));
        pushButton5->setText(QApplication::translate("MainForm", "Burst read", 0, QApplication::UnicodeUTF8));
        pb_Open->setText(QApplication::translate("MainForm", "Open", 0, QApplication::UnicodeUTF8));
        pb_Close->setText(QApplication::translate("MainForm", "Close", 0, QApplication::UnicodeUTF8));
        op_Command->setText(QApplication::translate("MainForm", "Issue command", 0, QApplication::UnicodeUTF8));
        pushButton6->setText(QApplication::translate("MainForm", "Print string", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("MainForm", "Port baud rate", 0, QApplication::UnicodeUTF8));
        cb_BaudRate->clear();
        cb_BaudRate->insertItems(0, QStringList()
         << QApplication::translate("MainForm", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "115200", 0, QApplication::UnicodeUTF8)
        );
        tabWidget2->setTabText(tabWidget2->indexOf(tab), QApplication::translate("MainForm", "Low level/state functions", 0, QApplication::UnicodeUTF8));
        pb_ReadTableList->setText(QApplication::translate("MainForm", "Read table list", 0, QApplication::UnicodeUTF8));
        pb_CommitTable->setText(QApplication::translate("MainForm", "Commit changes", 0, QApplication::UnicodeUTF8));
        tabWidget2->setTabText(tabWidget2->indexOf(tab1), QApplication::translate("MainForm", "Table functions", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("MainForm", "Com-port number", 0, QApplication::UnicodeUTF8));
        cb_Port->clear();
        cb_Port->insertItems(0, QStringList()
         << QApplication::translate("MainForm", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainForm", "4", 0, QApplication::UnicodeUTF8)
        );
        pb_SetCommConfig->setText(QApplication::translate("MainForm", "Set port config", 0, QApplication::UnicodeUTF8));
        grpPasswords->setTitle(QApplication::translate("MainForm", "Passwords", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("MainForm", "access", 0, QApplication::UnicodeUTF8));
        editAccessPass->setText(QApplication::translate("MainForm", "0", 0, QApplication::UnicodeUTF8));
        lblOperPass->setText(QApplication::translate("MainForm", "operator", 0, QApplication::UnicodeUTF8));
        editOperPass->setText(QApplication::translate("MainForm", "30", 0, QApplication::UnicodeUTF8));
        lblAdminPass->setText(QApplication::translate("MainForm", "administrator", 0, QApplication::UnicodeUTF8));
        editAdminPass->setText(QApplication::translate("MainForm", "30", 0, QApplication::UnicodeUTF8));
        lblFiscalPass->setText(QApplication::translate("MainForm", "fiscal", 0, QApplication::UnicodeUTF8));
        editFiscalPass->setText(QString());
        groupBox3->setTitle(QApplication::translate("MainForm", "Check Ops", 0, QApplication::UnicodeUTF8));
        lb_Ops->clear();
        lb_Ops->insertItem(QApplication::translate("MainForm", "Open check for sell", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "Open check for sell return", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "Add sell operation", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "Add sell return operation", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "Close check", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "Cancel check", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "New mode check", 0, QApplication::UnicodeUTF8));
        lb_Ops->insertItem(QApplication::translate("MainForm", "\320\241\321\203\321\202\320\276\321\207\320\275\321\213\320\271 \320\276\321\202\321\207\320\265\321\202 \321\201 \320\263\320\260\321\210\320\265\320\275\320\270\320\265\320\274", 0, QApplication::UnicodeUTF8));
        pb_commit->setText(QApplication::translate("MainForm", "Commit operation", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("MainForm", "Item name", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("MainForm", "Sum", 0, QApplication::UnicodeUTF8));
        groupBox2->setTitle(QApplication::translate("MainForm", "Dump functions", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("MainForm", "Device number", 0, QApplication::UnicodeUTF8));
        pushButton9->setText(QApplication::translate("MainForm", "Save dump", 0, QApplication::UnicodeUTF8));
        tabWidget2->setTabText(tabWidget2->indexOf(TabPage), QApplication::translate("MainForm", "Other", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
