#include <QDebug>
#include <qdesktopwidget.h>
#include <qlayout.h>
#include <QMenu>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <QCloseEvent>
#include "engine.h"
#include "mainwin.h"
#include "whall.h"
#include "orderwin.h"
#include "archivewin.h"
#include "aclock.h"
#include "dclock.h"
#include "ui_dlgexportsales.h"
#include "ui_dlgadvreport.h"

#define SUBSYSTEM GENERAL

alMainWindow::alMainWindow(alEngine * pEngine) :
    QMainWindow(NULL)
{
    setObjectName("mainWin");
    fEngine = pEngine;
    if(fEngine)
        connect(fEngine, SIGNAL(settingsChanged()), this, SLOT(rebuild()));
    currentWin = NULL;    
    hall = NULL;
    orderWin = NULL;
    arcWin = NULL;
    init();    
    showFullScreen();
}

void alMainWindow::init()
{
    createWidgets();	
}

alMainWindow::~alMainWindow()
{

}

void alMainWindow::createWidgets()
{
    QDesktopWidget desktop;
    QRect r = desktop.screenGeometry();
#ifdef DEBUG
    qDebug() << tr("mainWindow rect %i, %i, %i, %i"), r.left(), r.top(), r.right(), r.bottom();
#endif
    
    serviceFrame = new QFrame(this);
    serviceFrame->setObjectName("service");
    serviceFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    serviceFrame->setGeometry(r.right()-165, r.top()+5, 160, r.bottom()-10);
    
    QMenu * menu = new QMenu(serviceFrame);
    menu->setObjectName("serviceMenu");
    connect(menu->addAction(tr("X-Report")), &QAction::triggered, this, [this](){qDebug() << "X-Report";} );
    connect(menu->addAction(tr("Z-Report")), &QAction::triggered, this, [this](){qDebug() << "Z-Report";} );
    connect(menu->addAction(tr("Paying")), &QAction::triggered, this, [this](){qDebug() << "Paying";} );
    connect(menu->addAction(tr("Payout")), &QAction::triggered, this, [this](){qDebug() << "Payout";} );
    menu->addSeparator();
    connect(menu->addAction(tr("Equipment")), &QAction::triggered, this, [this](){qDebug() << "Equipment";} );
    menu->addSeparator();
    connect(menu->addAction(tr("Import goods")), &QAction::triggered, this, [this](){qDebug() << "Import goods";} );
    connect(menu->addAction(tr("Export sales")), &QAction::triggered, this, [this](){qDebug() << "Export sales";} );
    menu->addSeparator();
    connect(menu->addAction(tr("Settings")), &QAction::triggered, this, [this](){this->fEngine->settingsDialog();} );
    menu->addSeparator();
    connect(menu->addAction(tr("Archive")), &QAction::triggered, this, [this](){qDebug() << "Archive";} );
    connect(menu->addAction(tr("Advanced report")), &QAction::triggered, this, [this](){qDebug() << "Advanced report";} );
        
    QGridLayout * grid = new QGridLayout(serviceFrame);
    grid->setObjectName("serviceLayout");//, 1, 1, 11, 6, );
    QPushButton * btn = new QPushButton(serviceFrame);
    btn->setObjectName("btnService");
    btn->setText(tr("Service"));
    btn->setIcon(QIcon(":/images/settings.png"));
    btn->setMenu(menu);
    grid->addWidget(btn, 0, 0);
    
    btn = new QPushButton(serviceFrame);
    btn->setObjectName("btnLock");
    btn->setText(tr("Lock"));
    btn->setIcon(QIcon(":/images/lock.png"));
    connect(btn, SIGNAL(clicked()), fEngine, SLOT(loginLock()));
    grid->addWidget(btn, 1, 0);
    
//    AnalogClock * aclocks = new AnalogClock(serviceFrame, "aclocks");
//    grid->addWidget(aclocks, 2, 0);
    DigitalClock * dclocks = new DigitalClock(serviceFrame, "dclocks");
    grid->addWidget(dclocks, 3, 0);
    grid->setRowMinimumHeight(3, 60);
    
    grid->addItem(new QSpacerItem(0, 0,QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 0);

    btn = new QPushButton(serviceFrame);
    btn->setObjectName("btnExit");
    btn->setText(tr("Exit"));
    btn->setShortcut(Qt::ALT+Qt::Key_X);
    btn->setIcon(QIcon(":/images/exit.png"));
    grid->addWidget(btn, 5, 0);

    connect(btn, SIGNAL(clicked()), this, SLOT(close()));
    serviceFrame->show();    
    rebuild();
    //((QPushButton*)serviceFrame->findChild("btnExit"))->setEnabled(TRUE);
    //((QPushButton*)serviceFrame->findChild("btnService"))->setEnabled(TRUE);
}

/*
Обработчик закрытия окна, испускает сигнал closed()
*/
void alMainWindow::closeEvent(QCloseEvent * e)
{
	e->accept();
	emit(closed());
}

void alMainWindow::showEvent(QShowEvent * e)
{
    Q_UNUSED(e);
    alUserRecord * user = fEngine->currentUser();    
    //QMenu * menu = ((QPushButton*)(serviceFrame->findChild("btnService")))->popup();
    //TODO more automated ??
//    menu->setItemEnabled(ZReport, user->right(rZReport));
//    menu->setItemEnabled(XReport, user->right(rXReport));
//    menu->setItemEnabled(Paying, user->right(rPaying));
//    menu->setItemEnabled(Payout, user->right(rPayout));
//    menu->setItemEnabled(Equipment, user->right(rEquipment));
//    menu->setItemEnabled(Import, user->right(rImport));
//    menu->setItemEnabled(Export, user->right(rExport));
//    menu->setItemEnabled(Archive, user->right(rArchive));
//    menu->setItemEnabled(Settings, user->right(rSettings));
//    menu->setItemEnabled(AdvancedReport, user->right(rAdvancedReport));
}

void alMainWindow::settings()
{
    fEngine->settingsDialog();
//    QDialog * dlg;
//    switch(action)
//    {
//    case ZReport:
//        if(QMessageBox::question(this, "aldebaran", tr("Process Z-report??"), YES, NO) == YES)  fEngine->zReport();
//        break;
//    case XReport:
//        if(QMessageBox::question(this, "aldebaran", tr("Process X-report??"), YES, NO) == YES)  fEngine->xReport();
//        break;
//    case Paying:
//        fEngine->payin();
//        break;
//    case Payout: //ECR actions
//        fEngine->payout();
//        break;
//    case Equipment: // Equipment actions
//        fEngine->eqDialog();
//        break;
//    case Settings: // Settings
//    case Import:
//        fEngine->startImport();
//        break;
//    case Export:
////        dlg = new dlgExportSales(this);
////        dlg->setCaption(tr("Export sales"));
////        if(dlg->exec()) fEngine->exportSales(((dlgExportSales*)dlg)->period(), ((dlgExportSales*)dlg)->begin(), ((dlgExportSales*)dlg)->end());
////        delete dlg;
//        break;
//    case Archive:
//        openArchive();
//        break;
//    case AdvancedReport:
////        dlg = new dlgAdvReport(this);
////        dlg->setCaption(tr("Advanced report"));
////        if(dlg->exec()) fEngine->advancedReport(((dlgAdvReport* )dlg)->period(), ((dlgAdvReport* )dlg)->type(), ((dlgAdvReport*)dlg)->begin(), ((dlgAdvReport*)dlg)->end());
////        delete dlg;
//        break;
//    default:
//        QMessageBox::information(this, "TODO", QString(tr("unknown menu action %1")).arg(action));
//        break;
//    }
}

void alMainWindow::rebuild()
{
    orderWin = NULL;
    if(currentWin)
        delete currentWin;
    bool useshema = fEngine->parameter(SUBSYSTEM, USESHEMA).toString().toInt();
    if(!useshema)
        hall = new alWHall(fEngine, this, tr("Hall"), fEngine->parameter(SUBSYSTEM, TABLENUM).toString().toInt());
    else
    {
        QPixmap px = bytearray2pixmap(fEngine->parameter(SUBSYSTEM, SHEMA).toByteArray());
        hall = new alWHall(fEngine, this, "hall", 0, px);
    }
    setWidgetGeometry(hall);
    hall->show();    
    checkWidgets();
}

//TODO uncomment
void alMainWindow::openOrder(ULLID orderId, int tableNum)
{
//    if(hall) hall->hide();
//    orderWin = new alOrderWindow(fEngine, this, "order window", orderId);
//    connect(orderWin, SIGNAL(exit()), this, SLOT(rebuild()));
//    orderWin->init();
//    orderWin->setTable(tableNum);
//    setWidgetGeometry(orderWin);
//    orderWin->show();
//    connect(orderWin, SIGNAL(orderUpdated(alOrderRecord*)), fEngine, SLOT(exportOrder(alOrderRecord*)));
//    checkWidgets();
}

//TODO uncomment
void alMainWindow::openArchive()
{
//    if(hall) hall->hide();
//    arcWin = new alArchiveWindow(fEngine, this, "archive window");
//    connect(arcWin, SIGNAL(exit()), this, SLOT(rebuild()));
//    arcWin->init();
//    setWidgetGeometry(arcWin);
//    arcWin->show();
//    checkWidgets();
}

void alMainWindow::checkWidgets()
{
    bool enabled = FALSE;
    if(hall) enabled = hall->isVisible();
//    ((QPushButton*)serviceFrame->findChild("btnExit"))->setEnabled(enabled);
//    ((QPushButton*)serviceFrame->findChild("btnService"))->setEnabled(enabled);
}

void alMainWindow::setWidgetGeometry(QWidget * w)
{
    QDesktopWidget desktop;    
    QRect r = desktop.screenGeometry();    
    w->setGeometry(r.left()+5, r.top()+5, r.right()-170, r.bottom()-10);
    currentWin = w;
}

alOrderRecord * alMainWindow::currentOrder()
{
    if(orderWin) return orderWin->order();
    return NULL;
}
