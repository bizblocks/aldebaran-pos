/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QPixmap>
#include "engine.h"

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QTabWidget *tabDiscounts;
    QWidget *tabGeneral;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout1;
    Q3ButtonGroup *buttonGroup1;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout2;
    QRadioButton *rbNumber;
    QSpinBox *spinTables;
    QHBoxLayout *hboxLayout3;
    QRadioButton *rbShema;
    QPushButton *btnPictureSelect;
    QLabel *labelPreview;
    Q3GroupBox *grpPrnForms;
    QGridLayout *gridLayout3;
    QHBoxLayout *hboxLayout4;
    QLabel *lblOrder;
    QLineEdit *editOrder;
    QPushButton *btnOrderSelect;
    QHBoxLayout *hboxLayout5;
    QLabel *lblBill;
    QLineEdit *editBill;
    QPushButton *btnBillSelect;
    Q3GroupBox *grpImpExp;
    QGridLayout *gridLayout4;
    QToolBox *boxExchange;
    QWidget *itemLocal;
    QGridLayout *gridLayout5;
    QHBoxLayout *hboxLayout6;
    QLabel *lblCP;
    QComboBox *comboCP;
    QHBoxLayout *hboxLayout7;
    QLabel *lblPath;
    QLineEdit *editPath;
    QPushButton *btnImportSelect;
    QHBoxLayout *hboxLayout8;
    QHBoxLayout *hboxLayout9;
    QLabel *lblImport;
    QLineEdit *editImport;
    QHBoxLayout *hboxLayout10;
    QLabel *lblExport;
    QLineEdit *editExport;
    QHBoxLayout *hboxLayout11;
    QLabel *lblFilename;
    QSpacerItem *spacer8;
    QLabel *lblFormat;
    QComboBox *comboFormat;
    QWidget *page2;
    QGridLayout *gridLayout6;
    QHBoxLayout *hboxLayout12;
    QHBoxLayout *hboxLayout13;
    QLabel *lblLogin;
    QLineEdit *editLogin;
    QHBoxLayout *hboxLayout14;
    QLabel *lblLogin_2;
    QLineEdit *editPassword;
    QHBoxLayout *hboxLayout15;
    QCheckBox *cbUseFtp;
    QHBoxLayout *hboxLayout16;
    QLabel *lblHost;
    QLineEdit *editHost;
    QHBoxLayout *hboxLayout17;
    QLabel *lblPort;
    QSpinBox *spinPort;
    QHBoxLayout *hboxLayout18;
    QLabel *lblHost_2;
    QLineEdit *editRDir;
    QWidget *TabPage;
    QGridLayout *gridLayout7;
    Q3Frame *frame4_2;
    QGridLayout *gridLayout8;
    QPushButton *btnUsersEdit;
    QSpacerItem *spacer3_2;
    QPushButton *btnUsersNew;
    QPushButton *btnUsersDelete;
    Q3Frame *frameUsers;
    QWidget *tabEquipment;
    QGridLayout *gridLayout9;
    Q3Frame *frameBtnsEq;
    QGridLayout *gridLayout10;
    QPushButton *btnDeviceEdit;
    QSpacerItem *spacer3_2_2;
    QPushButton *btnDeviceNew;
    QPushButton *btnDeviceDelete;
    Q3Frame *frameEq;
    Q3Frame *frame18;
    QGridLayout *gridLayout11;
    QVBoxLayout *vboxLayout;
    QLabel *lblDefPrinter;
    QLineEdit *editDefPrinter;
    QVBoxLayout *vboxLayout1;
    QLabel *lblDefECR;
    QLineEdit *editDefECR;
    QSpacerItem *spacer13;
    QWidget *tabGoods;
    QGridLayout *gridLayout12;
    Q3Frame *frameGoods;
    Q3Frame *frame4;
    QGridLayout *gridLayout13;
    QFrame *line1;
    QPushButton *btnLevelUp;
    QPushButton *btnHome;
    QPushButton *btnNewGroup;
    QPushButton *btnNew;
    QPushButton *btnDelete;
    QPushButton *btnEdit;
    QSpacerItem *spacer3;
    QWidget *tabDiscounts1;
    QGridLayout *gridLayout14;
    Q3Frame *frameBtnsDiscount;
    QGridLayout *gridLayout15;
    QPushButton *btnDiscountEdit;
    QSpacerItem *spacer3_2_2_2;
    QPushButton *btnDiscountNew;
    QPushButton *btnDiscountDelete;
    Q3Frame *frameDiscount;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName(QString::fromUtf8("settingsDialog"));
        settingsDialog->resize(765, 457);
        settingsDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(settingsDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        btnOk = new QPushButton(settingsDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon);
        btnOk->setAutoDefault(true);
        btnOk->setDefault(true);

        hboxLayout->addWidget(btnOk);

        btnCancel = new QPushButton(settingsDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("stop_cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon1);
        btnCancel->setAutoDefault(true);

        hboxLayout->addWidget(btnCancel);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        tabDiscounts = new QTabWidget(settingsDialog);
        tabDiscounts->setObjectName(QString::fromUtf8("tabDiscounts"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
        gridLayout1 = new QGridLayout(tabGeneral);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        buttonGroup1 = new Q3ButtonGroup(tabGeneral);
        buttonGroup1->setObjectName(QString::fromUtf8("buttonGroup1"));
        buttonGroup1->setColumnLayout(0, Qt::Vertical);
        buttonGroup1->layout()->setSpacing(6);
        buttonGroup1->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout2 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup1->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout2);
        gridLayout2->setAlignment(Qt::AlignTop);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        rbNumber = new QRadioButton(buttonGroup1);
        rbNumber->setObjectName(QString::fromUtf8("rbNumber"));

        hboxLayout2->addWidget(rbNumber);

        spinTables = new QSpinBox(buttonGroup1);
        spinTables->setObjectName(QString::fromUtf8("spinTables"));
        spinTables->setWrapping(true);
        spinTables->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinTables->setMaximum(300);
        spinTables->setValue(0);

        hboxLayout2->addWidget(spinTables);


        gridLayout2->addLayout(hboxLayout2, 0, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        rbShema = new QRadioButton(buttonGroup1);
        rbShema->setObjectName(QString::fromUtf8("rbShema"));

        hboxLayout3->addWidget(rbShema);

        btnPictureSelect = new QPushButton(buttonGroup1);
        btnPictureSelect->setObjectName(QString::fromUtf8("btnPictureSelect"));
        btnPictureSelect->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("select-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPictureSelect->setIcon(icon2);

        hboxLayout3->addWidget(btnPictureSelect);


        gridLayout2->addLayout(hboxLayout3, 1, 0, 1, 1);


        hboxLayout1->addWidget(buttonGroup1);

        labelPreview = new QLabel(tabGeneral);
        labelPreview->setObjectName(QString::fromUtf8("labelPreview"));
        labelPreview->setMinimumSize(QSize(100, 100));
        labelPreview->setMaximumSize(QSize(100, 100));
        labelPreview->setScaledContents(true);
        labelPreview->setWordWrap(false);

        hboxLayout1->addWidget(labelPreview);


        gridLayout1->addLayout(hboxLayout1, 0, 0, 1, 2);

        grpPrnForms = new Q3GroupBox(tabGeneral);
        grpPrnForms->setObjectName(QString::fromUtf8("grpPrnForms"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(grpPrnForms->sizePolicy().hasHeightForWidth());
        grpPrnForms->setSizePolicy(sizePolicy);
        grpPrnForms->setColumnLayout(0, Qt::Vertical);
        grpPrnForms->layout()->setSpacing(6);
        grpPrnForms->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout3 = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(grpPrnForms->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout3);
        gridLayout3->setAlignment(Qt::AlignTop);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        lblOrder = new QLabel(grpPrnForms);
        lblOrder->setObjectName(QString::fromUtf8("lblOrder"));
        lblOrder->setWordWrap(false);

        hboxLayout4->addWidget(lblOrder);

        editOrder = new QLineEdit(grpPrnForms);
        editOrder->setObjectName(QString::fromUtf8("editOrder"));

        hboxLayout4->addWidget(editOrder);

        btnOrderSelect = new QPushButton(grpPrnForms);
        btnOrderSelect->setObjectName(QString::fromUtf8("btnOrderSelect"));
        btnOrderSelect->setMaximumSize(QSize(32, 32));
        btnOrderSelect->setIcon(icon2);

        hboxLayout4->addWidget(btnOrderSelect);


        gridLayout3->addLayout(hboxLayout4, 0, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        lblBill = new QLabel(grpPrnForms);
        lblBill->setObjectName(QString::fromUtf8("lblBill"));
        lblBill->setWordWrap(false);

        hboxLayout5->addWidget(lblBill);

        editBill = new QLineEdit(grpPrnForms);
        editBill->setObjectName(QString::fromUtf8("editBill"));

        hboxLayout5->addWidget(editBill);

        btnBillSelect = new QPushButton(grpPrnForms);
        btnBillSelect->setObjectName(QString::fromUtf8("btnBillSelect"));
        btnBillSelect->setMaximumSize(QSize(32, 32));
        btnBillSelect->setIcon(icon2);

        hboxLayout5->addWidget(btnBillSelect);


        gridLayout3->addLayout(hboxLayout5, 1, 0, 1, 1);


        gridLayout1->addWidget(grpPrnForms, 1, 0, 1, 1);

        grpImpExp = new Q3GroupBox(tabGeneral);
        grpImpExp->setObjectName(QString::fromUtf8("grpImpExp"));
        grpImpExp->setColumnLayout(0, Qt::Vertical);
        grpImpExp->layout()->setSpacing(6);
        grpImpExp->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout4 = new QGridLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(grpImpExp->layout());
        if (boxlayout2)
            boxlayout2->addLayout(gridLayout4);
        gridLayout4->setAlignment(Qt::AlignTop);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        boxExchange = new QToolBox(grpImpExp);
        boxExchange->setObjectName(QString::fromUtf8("boxExchange"));
        itemLocal = new QWidget();
        itemLocal->setObjectName(QString::fromUtf8("itemLocal"));
        itemLocal->setGeometry(QRect(0, 0, 424, 152));
        gridLayout5 = new QGridLayout(itemLocal);
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(11, 11, 11, 11);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        lblCP = new QLabel(itemLocal);
        lblCP->setObjectName(QString::fromUtf8("lblCP"));
        lblCP->setWordWrap(false);

        hboxLayout6->addWidget(lblCP);

        comboCP = new QComboBox(itemLocal);
        comboCP->setObjectName(QString::fromUtf8("comboCP"));

        hboxLayout6->addWidget(comboCP);


        gridLayout5->addLayout(hboxLayout6, 3, 0, 1, 1);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        lblPath = new QLabel(itemLocal);
        lblPath->setObjectName(QString::fromUtf8("lblPath"));
        lblPath->setWordWrap(false);

        hboxLayout7->addWidget(lblPath);

        editPath = new QLineEdit(itemLocal);
        editPath->setObjectName(QString::fromUtf8("editPath"));

        hboxLayout7->addWidget(editPath);

        btnImportSelect = new QPushButton(itemLocal);
        btnImportSelect->setObjectName(QString::fromUtf8("btnImportSelect"));
        btnImportSelect->setMaximumSize(QSize(32, 32));
        btnImportSelect->setIcon(icon2);

        hboxLayout7->addWidget(btnImportSelect);


        gridLayout5->addLayout(hboxLayout7, 0, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        lblImport = new QLabel(itemLocal);
        lblImport->setObjectName(QString::fromUtf8("lblImport"));
        lblImport->setWordWrap(false);

        hboxLayout9->addWidget(lblImport);

        editImport = new QLineEdit(itemLocal);
        editImport->setObjectName(QString::fromUtf8("editImport"));

        hboxLayout9->addWidget(editImport);


        hboxLayout8->addLayout(hboxLayout9);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        lblExport = new QLabel(itemLocal);
        lblExport->setObjectName(QString::fromUtf8("lblExport"));
        lblExport->setAcceptDrops(false);
        lblExport->setWordWrap(false);

        hboxLayout10->addWidget(lblExport);

        editExport = new QLineEdit(itemLocal);
        editExport->setObjectName(QString::fromUtf8("editExport"));

        hboxLayout10->addWidget(editExport);


        hboxLayout8->addLayout(hboxLayout10);


        gridLayout5->addLayout(hboxLayout8, 2, 0, 1, 1);

        hboxLayout11 = new QHBoxLayout();
        hboxLayout11->setSpacing(6);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        lblFilename = new QLabel(itemLocal);
        lblFilename->setObjectName(QString::fromUtf8("lblFilename"));
        lblFilename->setWordWrap(false);

        hboxLayout11->addWidget(lblFilename);

        spacer8 = new QSpacerItem(134, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout11->addItem(spacer8);

        lblFormat = new QLabel(itemLocal);
        lblFormat->setObjectName(QString::fromUtf8("lblFormat"));
        lblFormat->setWordWrap(false);

        hboxLayout11->addWidget(lblFormat);

        comboFormat = new QComboBox(itemLocal);
        comboFormat->setObjectName(QString::fromUtf8("comboFormat"));

        hboxLayout11->addWidget(comboFormat);


        gridLayout5->addLayout(hboxLayout11, 1, 0, 1, 1);

        boxExchange->addItem(itemLocal, QString::fromUtf8("Local"));
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        page2->setGeometry(QRect(0, 0, 273, 109));
        gridLayout6 = new QGridLayout(page2);
        gridLayout6->setSpacing(6);
        gridLayout6->setContentsMargins(11, 11, 11, 11);
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        hboxLayout12 = new QHBoxLayout();
        hboxLayout12->setSpacing(6);
        hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
        hboxLayout13 = new QHBoxLayout();
        hboxLayout13->setSpacing(6);
        hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
        lblLogin = new QLabel(page2);
        lblLogin->setObjectName(QString::fromUtf8("lblLogin"));
        lblLogin->setWordWrap(false);

        hboxLayout13->addWidget(lblLogin);

        editLogin = new QLineEdit(page2);
        editLogin->setObjectName(QString::fromUtf8("editLogin"));

        hboxLayout13->addWidget(editLogin);


        hboxLayout12->addLayout(hboxLayout13);

        hboxLayout14 = new QHBoxLayout();
        hboxLayout14->setSpacing(6);
        hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
        lblLogin_2 = new QLabel(page2);
        lblLogin_2->setObjectName(QString::fromUtf8("lblLogin_2"));
        lblLogin_2->setWordWrap(false);

        hboxLayout14->addWidget(lblLogin_2);

        editPassword = new QLineEdit(page2);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setAcceptDrops(false);
        editPassword->setEchoMode(QLineEdit::Password);

        hboxLayout14->addWidget(editPassword);


        hboxLayout12->addLayout(hboxLayout14);


        gridLayout6->addLayout(hboxLayout12, 1, 0, 1, 1);

        hboxLayout15 = new QHBoxLayout();
        hboxLayout15->setSpacing(6);
        hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
        cbUseFtp = new QCheckBox(page2);
        cbUseFtp->setObjectName(QString::fromUtf8("cbUseFtp"));

        hboxLayout15->addWidget(cbUseFtp);

        hboxLayout16 = new QHBoxLayout();
        hboxLayout16->setSpacing(6);
        hboxLayout16->setObjectName(QString::fromUtf8("hboxLayout16"));
        lblHost = new QLabel(page2);
        lblHost->setObjectName(QString::fromUtf8("lblHost"));
        lblHost->setWordWrap(false);

        hboxLayout16->addWidget(lblHost);

        editHost = new QLineEdit(page2);
        editHost->setObjectName(QString::fromUtf8("editHost"));

        hboxLayout16->addWidget(editHost);


        hboxLayout15->addLayout(hboxLayout16);

        hboxLayout17 = new QHBoxLayout();
        hboxLayout17->setSpacing(6);
        hboxLayout17->setObjectName(QString::fromUtf8("hboxLayout17"));
        lblPort = new QLabel(page2);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        lblPort->setWordWrap(false);

        hboxLayout17->addWidget(lblPort);

        spinPort = new QSpinBox(page2);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinPort->setMaximum(65535);

        hboxLayout17->addWidget(spinPort);


        hboxLayout15->addLayout(hboxLayout17);


        gridLayout6->addLayout(hboxLayout15, 0, 0, 1, 1);

        hboxLayout18 = new QHBoxLayout();
        hboxLayout18->setSpacing(6);
        hboxLayout18->setObjectName(QString::fromUtf8("hboxLayout18"));
        lblHost_2 = new QLabel(page2);
        lblHost_2->setObjectName(QString::fromUtf8("lblHost_2"));
        lblHost_2->setWordWrap(false);

        hboxLayout18->addWidget(lblHost_2);

        editRDir = new QLineEdit(page2);
        editRDir->setObjectName(QString::fromUtf8("editRDir"));

        hboxLayout18->addWidget(editRDir);


        gridLayout6->addLayout(hboxLayout18, 2, 0, 1, 1);

        boxExchange->addItem(page2, QString::fromUtf8("FTP"));

        gridLayout4->addWidget(boxExchange, 0, 0, 1, 1);


        gridLayout1->addWidget(grpImpExp, 1, 1, 1, 1);

        tabDiscounts->addTab(tabGeneral, QString());
        TabPage = new QWidget();
        TabPage->setObjectName(QString::fromUtf8("TabPage"));
        gridLayout7 = new QGridLayout(TabPage);
        gridLayout7->setSpacing(1);
        gridLayout7->setContentsMargins(1, 1, 1, 1);
        gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
        frame4_2 = new Q3Frame(TabPage);
        frame4_2->setObjectName(QString::fromUtf8("frame4_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame4_2->sizePolicy().hasHeightForWidth());
        frame4_2->setSizePolicy(sizePolicy1);
        frame4_2->setFrameShape(QFrame::StyledPanel);
        frame4_2->setFrameShadow(QFrame::Raised);
        frame4_2->setMargin(1);
        gridLayout8 = new QGridLayout(frame4_2);
        gridLayout8->setSpacing(0);
        gridLayout8->setContentsMargins(1, 1, 1, 1);
        gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
        btnUsersEdit = new QPushButton(frame4_2);
        btnUsersEdit->setObjectName(QString::fromUtf8("btnUsersEdit"));
        btnUsersEdit->setMinimumSize(QSize(42, 42));
        btnUsersEdit->setMaximumSize(QSize(42, 42));

        gridLayout8->addWidget(btnUsersEdit, 0, 1, 1, 1);

        spacer3_2 = new QSpacerItem(574, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout8->addItem(spacer3_2, 0, 3, 1, 1);

        btnUsersNew = new QPushButton(frame4_2);
        btnUsersNew->setObjectName(QString::fromUtf8("btnUsersNew"));
        btnUsersNew->setMinimumSize(QSize(42, 42));
        btnUsersNew->setMaximumSize(QSize(42, 42));

        gridLayout8->addWidget(btnUsersNew, 0, 0, 1, 1);

        btnUsersDelete = new QPushButton(frame4_2);
        btnUsersDelete->setObjectName(QString::fromUtf8("btnUsersDelete"));
        btnUsersDelete->setMinimumSize(QSize(42, 42));
        btnUsersDelete->setMaximumSize(QSize(42, 42));

        gridLayout8->addWidget(btnUsersDelete, 0, 2, 1, 1);


        gridLayout7->addWidget(frame4_2, 0, 0, 1, 1);

        frameUsers = new Q3Frame(TabPage);
        frameUsers->setObjectName(QString::fromUtf8("frameUsers"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frameUsers->sizePolicy().hasHeightForWidth());
        frameUsers->setSizePolicy(sizePolicy2);
        frameUsers->setFrameShape(QFrame::StyledPanel);
        frameUsers->setFrameShadow(QFrame::Raised);

        gridLayout7->addWidget(frameUsers, 1, 0, 1, 1);

        tabDiscounts->addTab(TabPage, QString());
        tabEquipment = new QWidget();
        tabEquipment->setObjectName(QString::fromUtf8("tabEquipment"));
        gridLayout9 = new QGridLayout(tabEquipment);
        gridLayout9->setSpacing(6);
        gridLayout9->setContentsMargins(11, 11, 11, 11);
        gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
        frameBtnsEq = new Q3Frame(tabEquipment);
        frameBtnsEq->setObjectName(QString::fromUtf8("frameBtnsEq"));
        sizePolicy1.setHeightForWidth(frameBtnsEq->sizePolicy().hasHeightForWidth());
        frameBtnsEq->setSizePolicy(sizePolicy1);
        frameBtnsEq->setFrameShape(QFrame::StyledPanel);
        frameBtnsEq->setFrameShadow(QFrame::Raised);
        frameBtnsEq->setMargin(1);
        gridLayout10 = new QGridLayout(frameBtnsEq);
        gridLayout10->setSpacing(0);
        gridLayout10->setContentsMargins(1, 1, 1, 1);
        gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
        btnDeviceEdit = new QPushButton(frameBtnsEq);
        btnDeviceEdit->setObjectName(QString::fromUtf8("btnDeviceEdit"));
        btnDeviceEdit->setMinimumSize(QSize(42, 42));
        btnDeviceEdit->setMaximumSize(QSize(42, 42));

        gridLayout10->addWidget(btnDeviceEdit, 0, 1, 1, 1);

        spacer3_2_2 = new QSpacerItem(574, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout10->addItem(spacer3_2_2, 0, 3, 1, 1);

        btnDeviceNew = new QPushButton(frameBtnsEq);
        btnDeviceNew->setObjectName(QString::fromUtf8("btnDeviceNew"));
        btnDeviceNew->setMinimumSize(QSize(42, 42));
        btnDeviceNew->setMaximumSize(QSize(42, 42));

        gridLayout10->addWidget(btnDeviceNew, 0, 0, 1, 1);

        btnDeviceDelete = new QPushButton(frameBtnsEq);
        btnDeviceDelete->setObjectName(QString::fromUtf8("btnDeviceDelete"));
        btnDeviceDelete->setMinimumSize(QSize(42, 42));
        btnDeviceDelete->setMaximumSize(QSize(42, 42));

        gridLayout10->addWidget(btnDeviceDelete, 0, 2, 1, 1);


        gridLayout9->addWidget(frameBtnsEq, 0, 0, 1, 2);

        frameEq = new Q3Frame(tabEquipment);
        frameEq->setObjectName(QString::fromUtf8("frameEq"));
        sizePolicy2.setHeightForWidth(frameEq->sizePolicy().hasHeightForWidth());
        frameEq->setSizePolicy(sizePolicy2);
        frameEq->setFrameShape(QFrame::StyledPanel);
        frameEq->setFrameShadow(QFrame::Raised);

        gridLayout9->addWidget(frameEq, 1, 0, 1, 1);

        frame18 = new Q3Frame(tabEquipment);
        frame18->setObjectName(QString::fromUtf8("frame18"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame18->sizePolicy().hasHeightForWidth());
        frame18->setSizePolicy(sizePolicy3);
        frame18->setFrameShape(QFrame::StyledPanel);
        frame18->setFrameShadow(QFrame::Raised);
        gridLayout11 = new QGridLayout(frame18);
        gridLayout11->setSpacing(6);
        gridLayout11->setContentsMargins(11, 11, 11, 11);
        gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        lblDefPrinter = new QLabel(frame18);
        lblDefPrinter->setObjectName(QString::fromUtf8("lblDefPrinter"));
        lblDefPrinter->setWordWrap(false);

        vboxLayout->addWidget(lblDefPrinter);

        editDefPrinter = new QLineEdit(frame18);
        editDefPrinter->setObjectName(QString::fromUtf8("editDefPrinter"));

        vboxLayout->addWidget(editDefPrinter);


        gridLayout11->addLayout(vboxLayout, 0, 0, 1, 1);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        lblDefECR = new QLabel(frame18);
        lblDefECR->setObjectName(QString::fromUtf8("lblDefECR"));
        lblDefECR->setWordWrap(false);

        vboxLayout1->addWidget(lblDefECR);

        editDefECR = new QLineEdit(frame18);
        editDefECR->setObjectName(QString::fromUtf8("editDefECR"));

        vboxLayout1->addWidget(editDefECR);


        gridLayout11->addLayout(vboxLayout1, 1, 0, 1, 1);

        spacer13 = new QSpacerItem(51, 161, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout11->addItem(spacer13, 2, 0, 1, 1);


        gridLayout9->addWidget(frame18, 1, 1, 1, 1);

        tabDiscounts->addTab(tabEquipment, QString());
        tabGoods = new QWidget();
        tabGoods->setObjectName(QString::fromUtf8("tabGoods"));
        gridLayout12 = new QGridLayout(tabGoods);
        gridLayout12->setSpacing(1);
        gridLayout12->setContentsMargins(1, 1, 1, 1);
        gridLayout12->setObjectName(QString::fromUtf8("gridLayout12"));
        frameGoods = new Q3Frame(tabGoods);
        frameGoods->setObjectName(QString::fromUtf8("frameGoods"));
        sizePolicy2.setHeightForWidth(frameGoods->sizePolicy().hasHeightForWidth());
        frameGoods->setSizePolicy(sizePolicy2);
        frameGoods->setFrameShape(QFrame::StyledPanel);
        frameGoods->setFrameShadow(QFrame::Raised);
        frameGoods->setMargin(1);

        gridLayout12->addWidget(frameGoods, 1, 0, 1, 1);

        frame4 = new Q3Frame(tabGoods);
        frame4->setObjectName(QString::fromUtf8("frame4"));
        sizePolicy1.setHeightForWidth(frame4->sizePolicy().hasHeightForWidth());
        frame4->setSizePolicy(sizePolicy1);
        frame4->setFrameShape(QFrame::StyledPanel);
        frame4->setFrameShadow(QFrame::Raised);
        frame4->setMargin(1);
        gridLayout13 = new QGridLayout(frame4);
        gridLayout13->setSpacing(0);
        gridLayout13->setContentsMargins(1, 1, 1, 1);
        gridLayout13->setObjectName(QString::fromUtf8("gridLayout13"));
        line1 = new QFrame(frame4);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::VLine);
        line1->setFrameShadow(QFrame::Sunken);

        gridLayout13->addWidget(line1, 0, 4, 1, 1);

        btnLevelUp = new QPushButton(frame4);
        btnLevelUp->setObjectName(QString::fromUtf8("btnLevelUp"));
        btnLevelUp->setMinimumSize(QSize(42, 42));
        btnLevelUp->setMaximumSize(QSize(42, 42));

        gridLayout13->addWidget(btnLevelUp, 0, 5, 1, 1);

        btnHome = new QPushButton(frame4);
        btnHome->setObjectName(QString::fromUtf8("btnHome"));
        btnHome->setMinimumSize(QSize(42, 42));
        btnHome->setMaximumSize(QSize(42, 42));

        gridLayout13->addWidget(btnHome, 0, 6, 1, 1);

        btnNewGroup = new QPushButton(frame4);
        btnNewGroup->setObjectName(QString::fromUtf8("btnNewGroup"));
        btnNewGroup->setMinimumSize(QSize(42, 42));
        btnNewGroup->setMaximumSize(QSize(42, 42));

        gridLayout13->addWidget(btnNewGroup, 0, 1, 1, 1);

        btnNew = new QPushButton(frame4);
        btnNew->setObjectName(QString::fromUtf8("btnNew"));
        btnNew->setMinimumSize(QSize(42, 42));
        btnNew->setMaximumSize(QSize(42, 42));

        gridLayout13->addWidget(btnNew, 0, 0, 1, 1);

        btnDelete = new QPushButton(frame4);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        btnDelete->setMinimumSize(QSize(42, 42));
        btnDelete->setMaximumSize(QSize(42, 42));

        gridLayout13->addWidget(btnDelete, 0, 3, 1, 1);

        btnEdit = new QPushButton(frame4);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
        btnEdit->setMinimumSize(QSize(42, 42));
        btnEdit->setMaximumSize(QSize(42, 42));

        gridLayout13->addWidget(btnEdit, 0, 2, 1, 1);

        spacer3 = new QSpacerItem(31, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout13->addItem(spacer3, 0, 7, 1, 1);


        gridLayout12->addWidget(frame4, 0, 0, 1, 1);

        tabDiscounts->addTab(tabGoods, QString());
        tabDiscounts1 = new QWidget();
        tabDiscounts1->setObjectName(QString::fromUtf8("tabDiscounts1"));
        gridLayout14 = new QGridLayout(tabDiscounts1);
        gridLayout14->setSpacing(1);
        gridLayout14->setContentsMargins(1, 1, 1, 1);
        gridLayout14->setObjectName(QString::fromUtf8("gridLayout14"));
        frameBtnsDiscount = new Q3Frame(tabDiscounts1);
        frameBtnsDiscount->setObjectName(QString::fromUtf8("frameBtnsDiscount"));
        sizePolicy1.setHeightForWidth(frameBtnsDiscount->sizePolicy().hasHeightForWidth());
        frameBtnsDiscount->setSizePolicy(sizePolicy1);
        frameBtnsDiscount->setFrameShape(QFrame::StyledPanel);
        frameBtnsDiscount->setFrameShadow(QFrame::Raised);
        frameBtnsDiscount->setMargin(1);
        gridLayout15 = new QGridLayout(frameBtnsDiscount);
        gridLayout15->setSpacing(0);
        gridLayout15->setContentsMargins(1, 1, 1, 1);
        gridLayout15->setObjectName(QString::fromUtf8("gridLayout15"));
        btnDiscountEdit = new QPushButton(frameBtnsDiscount);
        btnDiscountEdit->setObjectName(QString::fromUtf8("btnDiscountEdit"));
        btnDiscountEdit->setMinimumSize(QSize(42, 42));
        btnDiscountEdit->setMaximumSize(QSize(42, 42));

        gridLayout15->addWidget(btnDiscountEdit, 0, 1, 1, 1);

        spacer3_2_2_2 = new QSpacerItem(574, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout15->addItem(spacer3_2_2_2, 0, 3, 1, 1);

        btnDiscountNew = new QPushButton(frameBtnsDiscount);
        btnDiscountNew->setObjectName(QString::fromUtf8("btnDiscountNew"));
        btnDiscountNew->setMinimumSize(QSize(42, 42));
        btnDiscountNew->setMaximumSize(QSize(42, 42));

        gridLayout15->addWidget(btnDiscountNew, 0, 0, 1, 1);

        btnDiscountDelete = new QPushButton(frameBtnsDiscount);
        btnDiscountDelete->setObjectName(QString::fromUtf8("btnDiscountDelete"));
        btnDiscountDelete->setMinimumSize(QSize(42, 42));
        btnDiscountDelete->setMaximumSize(QSize(42, 42));

        gridLayout15->addWidget(btnDiscountDelete, 0, 2, 1, 1);


        gridLayout14->addWidget(frameBtnsDiscount, 0, 0, 1, 1);

        frameDiscount = new Q3Frame(tabDiscounts1);
        frameDiscount->setObjectName(QString::fromUtf8("frameDiscount"));
        sizePolicy2.setHeightForWidth(frameDiscount->sizePolicy().hasHeightForWidth());
        frameDiscount->setSizePolicy(sizePolicy2);
        frameDiscount->setFrameShape(QFrame::StyledPanel);
        frameDiscount->setFrameShadow(QFrame::Raised);

        gridLayout14->addWidget(frameDiscount, 1, 0, 1, 1);

        tabDiscounts->addTab(tabDiscounts1, QString());

        gridLayout->addWidget(tabDiscounts, 0, 0, 1, 1);


        retranslateUi(settingsDialog);
        QObject::connect(btnOk, SIGNAL(clicked()), settingsDialog, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), settingsDialog, SLOT(reject()));
        QObject::connect(btnPictureSelect, SIGNAL(clicked()), settingsDialog, SLOT(selectPicture()));
        QObject::connect(rbNumber, SIGNAL(stateChanged(int)), settingsDialog, SLOT(disableEnable()));
        QObject::connect(rbShema, SIGNAL(stateChanged(int)), settingsDialog, SLOT(disableEnable()));
        QObject::connect(btnImportSelect, SIGNAL(clicked()), settingsDialog, SLOT(selectImpExpDir()));
        QObject::connect(btnBillSelect, SIGNAL(clicked()), settingsDialog, SLOT(selectBill()));
        QObject::connect(btnOrderSelect, SIGNAL(clicked()), settingsDialog, SLOT(selectOrder()));

        boxExchange->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QApplication::translate("settingsDialog", "Settings", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("settingsDialog", "&OK", 0, QApplication::UnicodeUTF8));
        btnOk->setShortcut(QApplication::translate("settingsDialog", "Alt+O", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("settingsDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        btnCancel->setShortcut(QString());
        buttonGroup1->setTitle(QApplication::translate("settingsDialog", "Tables", 0, QApplication::UnicodeUTF8));
        rbNumber->setText(QApplication::translate("settingsDialog", "number of tables", 0, QApplication::UnicodeUTF8));
        rbShema->setText(QApplication::translate("settingsDialog", "use graphical shema", 0, QApplication::UnicodeUTF8));
        btnPictureSelect->setText(QString());
        grpPrnForms->setTitle(QApplication::translate("settingsDialog", "Print forms", 0, QApplication::UnicodeUTF8));
        lblOrder->setText(QApplication::translate("settingsDialog", "order template", 0, QApplication::UnicodeUTF8));
        btnOrderSelect->setText(QString());
        lblBill->setText(QApplication::translate("settingsDialog", "bill template", 0, QApplication::UnicodeUTF8));
        btnBillSelect->setText(QString());
        grpImpExp->setTitle(QApplication::translate("settingsDialog", "Import/Export", 0, QApplication::UnicodeUTF8));
        lblCP->setText(QApplication::translate("settingsDialog", "codepage", 0, QApplication::UnicodeUTF8));
        lblPath->setText(QApplication::translate("settingsDialog", "path", 0, QApplication::UnicodeUTF8));
        btnImportSelect->setText(QString());
        lblImport->setText(QApplication::translate("settingsDialog", "import", 0, QApplication::UnicodeUTF8));
        lblExport->setText(QApplication::translate("settingsDialog", "export", 0, QApplication::UnicodeUTF8));
        lblFilename->setText(QApplication::translate("settingsDialog", "filenames", 0, QApplication::UnicodeUTF8));
        lblFormat->setText(QApplication::translate("settingsDialog", "format", 0, QApplication::UnicodeUTF8));
        boxExchange->setItemText(boxExchange->indexOf(itemLocal), QApplication::translate("settingsDialog", "Local", 0, QApplication::UnicodeUTF8));
        lblLogin->setText(QApplication::translate("settingsDialog", "login:", 0, QApplication::UnicodeUTF8));
        lblLogin_2->setText(QApplication::translate("settingsDialog", "password:", 0, QApplication::UnicodeUTF8));
        cbUseFtp->setText(QApplication::translate("settingsDialog", "use FTP", 0, QApplication::UnicodeUTF8));
        lblHost->setText(QApplication::translate("settingsDialog", "host:", 0, QApplication::UnicodeUTF8));
        lblPort->setText(QApplication::translate("settingsDialog", "port:", 0, QApplication::UnicodeUTF8));
        lblHost_2->setText(QApplication::translate("settingsDialog", "remote dir:", 0, QApplication::UnicodeUTF8));
        boxExchange->setItemText(boxExchange->indexOf(page2), QApplication::translate("settingsDialog", "FTP", 0, QApplication::UnicodeUTF8));
        tabDiscounts->setTabText(tabDiscounts->indexOf(tabGeneral), QApplication::translate("settingsDialog", "General", 0, QApplication::UnicodeUTF8));
        btnUsersEdit->setText(QString());
        btnUsersNew->setText(QString());
        btnUsersDelete->setText(QString());
        tabDiscounts->setTabText(tabDiscounts->indexOf(TabPage), QApplication::translate("settingsDialog", "Users", 0, QApplication::UnicodeUTF8));
        btnDeviceEdit->setText(QString());
        btnDeviceNew->setText(QString());
        btnDeviceDelete->setText(QString());
        lblDefPrinter->setText(QApplication::translate("settingsDialog", "Default printer name", 0, QApplication::UnicodeUTF8));
        lblDefECR->setText(QApplication::translate("settingsDialog", "Default ECR name", 0, QApplication::UnicodeUTF8));
        tabDiscounts->setTabText(tabDiscounts->indexOf(tabEquipment), QApplication::translate("settingsDialog", "Equipment", 0, QApplication::UnicodeUTF8));
        btnLevelUp->setText(QString());
        btnHome->setText(QString());
        btnNewGroup->setText(QString());
        btnNew->setText(QString());
        btnDelete->setText(QString());
        btnEdit->setText(QString());
        tabDiscounts->setTabText(tabDiscounts->indexOf(tabGoods), QApplication::translate("settingsDialog", "Goods", 0, QApplication::UnicodeUTF8));
        btnDiscountEdit->setText(QString());
        btnDiscountNew->setText(QString());
        btnDiscountDelete->setText(QString());
        tabDiscounts->setTabText(tabDiscounts->indexOf(tabDiscounts1), QApplication::translate("settingsDialog", "Discounts", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
