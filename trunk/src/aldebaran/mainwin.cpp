#include <qdesktopwidget.h>
#include <qlayout.h>
#include <qpopupmenu.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "engine.h"
#include "mainwin.h"
#include "whall.h"
#include "orderwin.h"
#include "archivewin.h"
#include "aclock.h"
#include "dclock.h"
#include "dlgexportsales.h"
#include "dlgadvreport.h"

#define SUBSYSTEM GENERAL

alMainWindow::alMainWindow(alEngine * pEngine) :
	QMainWindow(NULL, "mainWin")
{
    fEngine = pEngine;
    if(fEngine) connect(fEngine, SIGNAL(settingsChanged()), this, SLOT(rebuild()));
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
    qDebug(tr("mainWindow rect %i, %i, %i, %i"), r.left(), r.top(), r.right(), r.bottom());
#endif
    
    serviceFrame = new QFrame(this, "service");
    serviceFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    serviceFrame->setGeometry(r.right()-165, r.top()+5, 160, r.bottom()-10);
    
    QPopupMenu * menu = new QPopupMenu(serviceFrame, "serviceMenu");
    menu->insertItem(tr("X-Report"), XReport);
    menu->insertItem(tr("Z-Report"), ZReport);
    menu->insertItem(tr("Paying"), Paying);
    menu->insertItem(tr("Payout"), Payout);
    menu->insertSeparator();    
    menu->insertItem(tr("Equipment"), Equipment);
    menu->insertSeparator();
    menu->insertItem(tr("Import goods"), Import);
    menu->insertItem(tr("Export sales"), Export);
    menu->insertSeparator();    
    menu->insertItem(tr("Settings"), Settings);
    menu->insertSeparator();
    menu->insertItem(tr("Archive"), Archive);
    menu->insertItem(tr("Advanced report"), AdvancedReport);
    
    connect(menu, SIGNAL(activated(int)), this, SLOT(service(int)));
    
    QGridLayout * grid = new QGridLayout(serviceFrame, 1, 1, 11, 6, "serviceLayout");
    QPushButton * btn = new QPushButton(serviceFrame, "btnService");
    btn->setText(tr("Service"));
    btn->setIconSet(QPixmap::fromMimeSource("settings.png"));
    btn->setPopup(menu);
    grid->addWidget(btn, 0, 0);
    
    btn = new QPushButton(serviceFrame, "btnLock");
    btn->setText(tr("Lock"));
    btn->setIconSet(QPixmap::fromMimeSource("lock.png"));
    connect(btn, SIGNAL(clicked()), fEngine, SLOT(loginLock()));
    grid->addWidget(btn, 1, 0);
    
//    QFrame * frameClock = new QFrame(serviceFrame, "frameClock");
//    grid->addWidget(frameClock, 2, 0);
//    QGridLayout * lytClock = new QGridLayout(frameClock, 1, 3);
//    
//    QLCDNumber * number = new QLCDNumber(frameClock)
    AnalogClock * aclocks = new AnalogClock(serviceFrame, "aclocks");
    grid->addWidget(aclocks, 2, 0);
    DigitalClock * dclocks = new DigitalClock(serviceFrame, "dclocks");
    grid->addWidget(dclocks, 3, 0);    
    
    btn = new QPushButton(serviceFrame, "btnExit");
    btn->setText(tr("Exit"));
    btn->setAccel(ALT+Key_X);
    btn->setIconSet(QPixmap::fromMimeSource("exit.png"));    
    grid->addWidget(btn, 10, 0);
    connect(btn, SIGNAL(clicked()), this, SLOT(close()));
    serviceFrame->show();    
    rebuild();
    ((QPushButton*)serviceFrame->child("btnExit"))->setEnabled(TRUE);
    ((QPushButton*)serviceFrame->child("btnService"))->setEnabled(TRUE);    
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
    QPopupMenu * menu = ((QPushButton*)(serviceFrame->child("btnService")))->popup();
    //TODO more automated ??
    menu->setItemEnabled(ZReport, user->right(rZReport));
    menu->setItemEnabled(XReport, user->right(rXReport));     
    menu->setItemEnabled(Paying, user->right(rPaying));
    menu->setItemEnabled(Payout, user->right(rPayout));
    menu->setItemEnabled(Equipment, user->right(rEquipment));
    menu->setItemEnabled(Import, user->right(rImport));    
    menu->setItemEnabled(Export, user->right(rExport));        
    menu->setItemEnabled(Archive, user->right(rArchive));        
    menu->setItemEnabled(Settings, user->right(rSettings));
    menu->setItemEnabled(AdvancedReport, user->right(rAdvancedReport));    
}

void alMainWindow::service(int action)
{
    QDialog * dlg;
    switch(action)
    {
    case ZReport:
	if(QMessageBox::question(this, "aldebaran", tr("Process Z-report??"), YES, NO) == YES)  fEngine->zReport();
	break;
    case XReport:
	if(QMessageBox::question(this, "aldebaran", tr("Process X-report??"), YES, NO) == YES)  fEngine->xReport();
	break;
    case Paying:
	fEngine->payin();
	break;
    case Payout: //ECR actions
	fEngine->payout();
	break;
    case Equipment: // Equipment actions
	fEngine->eqDialog();
	break;
    case Settings: // Settings
	fEngine->settingsDialog();
	break;
    case Import:
	fEngine->startImport();
	break;
    case Export:
	dlg = new dlgExportSales(this);
	dlg->setCaption(tr("Export sales"));	
	if(dlg->exec()) fEngine->exportSales(((dlgExportSales*)dlg)->period(), ((dlgExportSales*)dlg)->begin(), ((dlgExportSales*)dlg)->end());
	delete dlg;
	break;
    case Archive:
	openArchive();
	break;
    case AdvancedReport:
	dlg = new dlgAdvReport(this);
	dlg->setCaption(tr("Advanced report"));
	if(dlg->exec()) fEngine->advancedReport(((dlgAdvReport* )dlg)->period(), ((dlgAdvReport* )dlg)->type(), ((dlgAdvReport*)dlg)->begin(), ((dlgAdvReport*)dlg)->end());
	delete dlg;
	break;
    default:
	QMessageBox::information(this, "TODO", QString(tr("unknown menu action %1")).arg(action));	
	break;
    }
}

void alMainWindow::rebuild()
{
    orderWin = NULL;
    if(currentWin) delete currentWin;
    bool useshema = fEngine->parameter(SUBSYSTEM, USESHEMA).toString().toInt();
    if(!useshema) hall = new alWHall(fEngine, this, tr("Hall"), fEngine->parameter(SUBSYSTEM, TABLENUM).toString().toInt());
    else
    {
	QPixmap px = bytearray2pixmap(fEngine->parameter(SUBSYSTEM, SHEMA).toByteArray());
	hall = new alWHall(fEngine, this, "hall", 0, px);
    }
    setWidgetGeometry(hall);
    hall->show();    
    checkWidgets();
}

void alMainWindow::openOrder(Q_ULLONG orderId, int tableNum)
{
    if(hall) hall->hide();
    orderWin = new alOrderWindow(fEngine, this, "order window", orderId);
    connect(orderWin, SIGNAL(exit()), this, SLOT(rebuild()));    
    orderWin->init();
    orderWin->setTable(tableNum); 
    setWidgetGeometry(orderWin);
    orderWin->show();
    connect(orderWin, SIGNAL(orderUpdated(alOrderRecord*)), fEngine, SLOT(exportOrder(alOrderRecord*)));    
    checkWidgets();
}

void alMainWindow::openArchive()
{
    if(hall) hall->hide();
    arcWin = new alArchiveWindow(fEngine, this, "archive window");
    connect(arcWin, SIGNAL(exit()), this, SLOT(rebuild()));
    arcWin->init();
    setWidgetGeometry(arcWin);
    arcWin->show();
    checkWidgets();
}

void alMainWindow::checkWidgets()
{
    bool enabled = FALSE;
    if(hall) enabled = hall->isVisible();
    ((QPushButton*)serviceFrame->child("btnExit"))->setEnabled(enabled);
    ((QPushButton*)serviceFrame->child("btnService"))->setEnabled(enabled);
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
