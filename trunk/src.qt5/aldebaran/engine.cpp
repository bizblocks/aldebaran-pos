#include <qapplication.h>
#include <QtSql/QSqlDatabase>
#include <qpixmap.h>
#include <qbuffer.h>
#include <qfile.h>
#include <QTranslator>
#include <QMessageBox>
//TODO reimplement
//#include <qftp.h>
#include "engine.h"
#include "mainwin.h"
#include "whall.h"
#include "wtable.h"
#include "settings.h"
#include "worker.h"
#include "driver.h"
#include "mscreader.h"
#include "barcodereader.h"
#include "siriusterminal.h"
#include "virtualmart.h"
#include "ieshtrih.h"
#include "sirius/iesirius.h"

#include "ui_calculator.h"
#include "ui_dlglogin.h"
#include "ui_equipmentdialog.h"

//ui
#include "dlglogin.ui.h"

alEngine::alEngine(int argc, char ** argv) :
    QObject(),
    mainWindow(NULL),
    settings(NULL),
    dbInited(FALSE),
    fCurrentUser(NULL),
    fWorker(NULL),
    server(NULL),
    dlgLogin(new Ui::dlgLogin)
{
    app = new QApplication( argc, argv );        
    init();
}

alEngine::~alEngine()
{
    delete app;
} 

/* 
Инициализация объекта
*	- Загрузка переводов
*	- Чтение настроек
*	- Открытие БД
*/
void alEngine::init()
{    
    QTranslator * translator = new QTranslator(0);
   
    translator->load("aldebaran-ru", "/usr/share/aldebaran");
    qApp->installTranslator(translator);
    translator = new QTranslator(0);    
    translator->load("aldebaran-data-ru", "/usr/share/aldebaran");
    qApp->installTranslator(translator);        
    translator = new QTranslator(0);    
    translator->load("impexp-ru", "/usr/share/aldebaran");
    qApp->installTranslator(translator);    
    translator = new QTranslator(0);    
    translator->load("equip-ru", "/usr/share/aldebaran");
    qApp->installTranslator(translator);
    translator = new QTranslator(0);    
    translator->load("qt_ru", "/usr/share/aldebaran");
    qApp->installTranslator(translator);            
    settings = new alSettings(this);
}

QSqlDatabase alEngine::db()
{
    return fDB;
}

void alEngine::setCurrentUser(alUserRecord * u)
{
    if(!u)
    {
       exitApp();
        return;
    }
    alDataUsers * users = new alDataUsers(this);
    fCurrentUser = users->select(u->id());
    delete users;
}

void alEngine::initUsers()
{
    alDataUsers * users = new alDataUsers(this);
    users->checkUsers();
    delete users;
}

void alEngine::initEquipment()
{
    //fWorker = eqWorker::worker();
    //TODO reimplement with refactoring
//    alDataEq * eq = new alDataEq(this);
//    connect(fWorker, SIGNAL(deviceError(int)), this, SLOT(onError(int)));
//    fWorker->initEquipment(eq);
    
//    int err;
//    eqJob * job = createPrinterJob("", "print");
//    if(job)
//    {
//        job->setData(QString("%1 ready\n\n\n\n\n").arg(job->device()->name()));
//        job->process();
//        if((err=job->error()))
//            error(tr("default printer error: %1").arg(err));
//        delete job;
//        job = createPrinterJob("", "cut");
//        job->process();
//        delete job;
//    }

//    job = createECRJob("", "beep");
//    if(!job) error(tr("ERROR: default ECR not connected"));
//    else
//    {
//        job->process();
//        if((err=job->error()))
//            error(tr("default ECR error: %1").arg(err));
//        delete job;
//    }
    
//    eq->select("type='MSC Reader'");
//    if(eq->first()) do
//    {
//        alEqRecord * device = (alEqRecord*)eq->current();
//        if(!device->enabled())
//            continue;
//        eqMSCReader * reader = (eqMSCReader*)fWorker->getDevice(device->name());
//        connect(reader, SIGNAL(data(int, QString)), this, SLOT(readerData(int, QString)));
//    }while (eq->next());

//    eq->select("type='Barcode Reader'");
//    if(eq->first()) do
//    {
//        alEqRecord * device = (alEqRecord*)eq->current();
//        if(!device->enabled())
//            continue;
//        eqBarcodeReader * reader = (eqBarcodeReader*)fWorker->getDevice(device->name());
//        connect(reader, SIGNAL(data(QString)), this, SLOT(barcodeReaderData(QString)));
//    }while (eq->next());

//    eq->select("type='Sirius'");
//    if(eq->first()) do
//    {
//        alEqRecord * device = (alEqRecord*)eq->current();
//        if(!device->enabled())
//            continue;
//        eqSirius * sirius = (eqSirius*)fWorker->getDevice(device->name());
//        connect(sirius, SIGNAL(data(importer*)), this, SLOT(importData(importer*)));
//    }while (eq->next());

//    eq->select("type='Virtual Mart'");
//    if(eq->first()) do
//    {
//        alEqRecord * device = (alEqRecord*)eq->current();
//        if(!device->enabled()) continue;
//        eqVirtualMart * vMart = (eqVirtualMart*)fWorker->getDevice(device->name());
//        connect(vMart, SIGNAL(data(importer*)), this, SLOT(importData(importer*)));
//    }while (eq->next());

//    server = new sServer(this);
//    connect(server, SIGNAL(hasData(importer*)), this, SLOT(importData(importer*)));
//    server->start();
}

//TODO uncomment
//void alEngine::importData(importer * imp)
//{
////    if(QString(imp->name())==QString("Sirius"))
//    {
//	alDataOrder * orders;
//	alOrderRecord * order;
//	switch(((impSirius*)imp)->cmd())
//	{
//		case 'O':
//		    orders = new alDataOrder(this);
//		    order = orders->import(imp);
//		    exportOrder(order);
////TODO how many time print order?? in settings
//		    order->printOrder();
//		    order->printOrder();
//		    if(!mainWindow->currentOrder()) mainWindow->rebuild();
//		    delete orders;
//		    break;
//		case 'W':
//		    imp->seek(0);
//		    QMessageBox::information(0, "aldebaran", QString(tr("Call from table #%1")).arg(imp->value("table").toInt()));
//		    break;
//		default:
//		    break;
//	}
//    }
//}

bool alEngine::loginLock()
{
    if(mainWindow)
        mainWindow->hide();
    QDialog dlg;
    Ui::dlgLogin uidlg;
    uidlg.setupUi(&dlg);
//    dlg.init(this);
    int res = dlg.exec();
    if(res==QDialog::Accepted)
    {
        if(mainWindow) mainWindow->showFullScreen();
        return TRUE;
    }
    if(mainWindow)
        return loginLock(); //WARNING recursion
    return FALSE;
}

/*
Запуск приложения
	- Открытие базы данных
	- Логин
	- Инициализация оборудования, очередь задач
	- Основное окно
*/
//TODO uncomment
int alEngine::start()
{	
    QStringList dbParams;
    do
    {
        dbParams = settings->dbSettings();
        fDB = QSqlDatabase::addDatabase(dbParams[0], dbParams[1]);
        fDB.setDatabaseName(dbParams[1]);
        fDB.setHostName(dbParams[2]);
        fDB.setPort(dbParams[3].toInt());
        if(!fDB.open(dbParams[4], dbParams[5]))
        {
            if(!settings->dbDialog())
            {
                exitApp();
                return 0;
            }
        }
        else
        {
            break;
        }
    }while(true);
    Queries::setDialect(dbParams[0]);
    dbInited = TRUE;
    emit(initialized());
    initUsers();
//    initEquipment();
    if(!loginLock())
      return -1;

//    initTables();

//    mainWindow = new alMainWindow(this);
//    connect(mainWindow, SIGNAL(closed()), this, SLOT(exitApp()));
//    qApp->setActiveWindow(mainWindow);

////    alDataGoods * goods = new alDataGoods(this);
////    goods->exportpictures();

    return qApp->exec();
}

alValueList  alEngine::settingsFor(QString subSystem)
{
    return settings->subSystemSettings(subSystem);
}

QVariant alEngine::parameter(QString sub, QString key)
{
    return settings->parameter(sub, key);
}

//TODO uncomment
void alEngine::settingsDialog()
{
//    if(settings->dialog())
//        emit(settingsChanged());
}

void alEngine::eqDialog()
{
//TODO reimplement
//    equipmentDialog * dlg = new equipmentDialog();
//    dlg->init(this);
//    dlg->exec();
//    delete dlg;
}

bool alEngine::startTransaction()
{
    if(fDB.isOpen())
        return fDB.transaction();
    return false;
}

bool alEngine::commitTransaction()
{
    if(fDB.isOpen())
        return fDB.commit();
    return false;
}

bool alEngine::rollbackTransaction()
{
    if(fDB.isOpen())
        return fDB.rollback();
    return false;
}

//TODO uncomment
void alEngine::openOrder(int num)
{    
//    alOrderRecord * order = tableOrder(num);
//    if(!order) mainWindow->openOrder(-1, num);
//    else mainWindow->openOrder(order->id(), num);
}

//TODO uncomment
alOrderRecord * alEngine::tableOrder(int num)
{
//    fOrders->select(QString("tablenum=%1 AND status<2").arg(num));
//    if(fOrders->first()) return (alOrderRecord*)fOrders->current();
    return NULL;
}

void alEngine::initTables()
{
//    fOrders = new alDataOrder(this);
}

//TODO uncomment
QStringList alEngine::driverList()
{
//    if(!fWorker)
//        return QStringList();
//    return fWorker->driverList();
}

//TODO uncomment

eqJob * alEngine::createPrinterJob(QString device, QString action)
{
//    if(device=="")
//        device = parameter(EQUIPMENT, PRINTER).toString();
//    return fWorker->createJob(device, action);
}

//TODO uncomment
eqJob * alEngine::createECRJob(QString device, QString action)
{
//    if(device=="")
//        device = parameter(EQUIPMENT, ECR).toString();
//    return fWorker->createJob(device, action);
}

//TODO uncomment
void alEngine::exportOrder(alOrderRecord * order)
{
//    QString device = "_NO_DEVICE_";
//    alDataEq * eq = new alDataEq(this);
//    eq->select("type='Sirius' OR type='Virtual Mart'");
//    if(eq->first()) do
//    {
//	alEqRecord * dev = (alEqRecord*)eq->current();
//    qDebug() << QString("device name is %1, table %2").arg(dev->name()).arg(dev->option("table").toInt());
//	if(dev->option("table").toInt()==order->table())
//	{
//	    device = dev->name();
//	    break;
//	}
//    } while (eq->next());
//    delete eq;
//    if(device=="_NO_DEVICE_") return;
    
//    if(!connectDevice(device)) return;
//    map m;
//    m["1"] = (uint)order->id();
//    m["2"] = order->externalCode().toUInt();
//    m["3"] = (uint)order->status();
//    m["4"] = date2int(order->date());
//    m["5"] = time2int(order->timeOpen());
////TODO export client
////    m["6"] = order->client();
//    m["6"] = 0;
//    eqJob * job = fWorker->createJob(device, "orderStart");
//    job->setData(QVariant(m));
//    job->process();
//    alDataOrderTable * table = order->getDocumentTable();
//    table->select();
//    for(int row=0;row<table->count();row++)
//    {
//	alOrderLine * line = table->getLine(row);
//	if(!line->item()) continue;
//	m["1"] = line->lineNum();
//	m["2"] = (uint)line->item()->id();
//	m["3"] = QString("%1").arg(line->amount(), 5, 'F', 2);
//	m["4"] = QString("%1").arg(line->price(), 5, 'F', 2);
//	m["5"] = QString("%1").arg(line->summ(), 6, 'F', 2);
//	job = fWorker->createJob(device, "line");
//	job->setData(QVariant(m));
//	job->process();
//    }
//    job = fWorker->createJob(device, "orderEnd");
//    job->process();
}

//TODO uncomment
bool alEngine::prepareGoods(QString deviceType)
{
//    eqDriver * drv = fWorker->createDevice(deviceType, "prepareGoods", false);
//    if(!drv) return FALSE;
//    drv->setOption("path", parameter(GENERAL, IMPEXPPATH).toString());
//    drv->init();
//    eqJob * job = drv->createJob("goodsStart");
//    if(!job) return FALSE;
//    job->process();
//    delete job;
//    alDataGoods * goods = new alDataGoods(this);
//    goods->select("eqexport=true");
//    if(goods->first()) do
//    {
//        map m;
//        alGoodsRecord * rec = (alGoodsRecord *)goods->current();
//        m["01"] = (uint)rec->id();
//        if((uint)rec->parent()) m["02"] =  (uint)rec->parent()->id();
//        else m["02"] = 0;
//        m["03"] = rec->isGroup();
//        m["04"] = rec->name();
//        m["05"] = rec->description();
//        m["06"] = pixmap2bytearray(rec->picture());
//        m["07"] = QString("%1").arg(rec->price(), 5, 'F', 2);
//        m["08"] = QString("%1").arg(rec->hydroCarbonat(), 6, 'F', 3);
//        m["09"] = QString("%1").arg(rec->fat(), 6, 'F', 3);
//        m["10"] = QString("%1").arg(rec->protein(), 6, 'F', 3);
//        m["11"] = QString("%1").arg(rec->calories(), 7, 'F', 3);
//        m["12"] = rec->outOfStore();

//        job = drv->createJob("line");
//        job->setData(QVariant(m));
//        job->process();
//        delete job;
//        if(app->hasPendingEvents())
//            app->processEvents(QEventLoop::AllEvents, 1000);
//    }while(goods->next());
//    job = drv->createJob("goodsEnd");
//    job->process();
//    delete job;
//    delete drv;
    return TRUE;    
}

//TODO uncomment
bool alEngine::exportGoods(QString device)
{
//    eqJob * job = fWorker->createJob(device, "goodsStart");
//    if(!job) return FALSE;
//    job->process();
//    delete job;
//    job = fWorker->createJob(device, "goodsEnd");
//    job->process();
//    delete job;
    return TRUE;        
}

//TODO uncomment
void alEngine::sendElement(alGoodsRecord * rec)
{
//    qDebug("sending element");
//    alDataEq * eq = new alDataEq(this);
//    eq->select("type='Sirius'");
//    if(eq->first()) do
//    {
//	alEqRecord * dev = (alEqRecord*)eq->current();
//    qDebug() << QString("device name is %1, table %2").arg(dev->name()).arg(dev->option(tr("table")).toInt());
//	QString device = dev->name();
//	if(!connectDevice(device)) return;
//	eqJob * job = fWorker->createJob(device, "elementStart");
//	if(!job) return;
//	job->process();
//	delete job;
//	map m;
//	m["01"] = (uint)rec->id();
//	if((uint)rec->parent()) m["02"] =  (uint)rec->parent()->id();
//	else m["02"] = 0;
//	m["03"] = rec->isGroup();
//	m["04"] = rec->name();
//	m["05"] = rec->description();
//	m["06"] = pixmap2bytearray(rec->picture());
//	m["07"] = QString("%1").arg(rec->price(), 5, 'F', 2);
//	m["08"] = QString("%1").arg(rec->hydroCarbonat(), 6, 'F', 3);
//	m["09"] = QString("%1").arg(rec->fat(), 6, 'F', 3);
//	m["10"] = QString("%1").arg(rec->protein(), 6, 'F', 3);
//	m["11"] = QString("%1").arg(rec->calories(), 7, 'F', 3);
//	m["12"] = rec->outOfStore();
	
//	job = fWorker->createJob(device, "line");
//	job->setData(QVariant(m));
//	job->process();
//	delete job;
//	job = fWorker->createJob(device, "elementEnd");
//	job->process();
//	delete job;
//    } while (eq->next());
//    delete eq;
}

//TODO uncomment
bool alEngine::resetDevice(QString device)
{
//    if(!connectDevice(device)) return FALSE;
//    eqJob * job = fWorker->createJob(device, "resetDevice");
//    job->process();
//    delete job;
    return TRUE;
}

//TODO uncomment
bool alEngine::shutdownDevice(QString device)
{
//    if(!connectDevice(device)) return FALSE;
//    eqJob * job = fWorker->createJob(device, "haltDevice");
//    job->process();
//    delete job;
    return TRUE;    
}

//TODO uncomment
bool alEngine::updateDevice(QString device)
{
//    if(!connectDevice(device)) return FALSE;
//    eqJob * job = fWorker->createJob(device, "updateDevice");
//    job->process();
//    delete job;
    return TRUE;
}

//TODO uncomment
bool alEngine::connectDevice(QString device)
{
//    eqJob * job = fWorker->createJob(device, "connect");
//    if(!job) return FALSE;
//    job->process();
//    delete job;
    return TRUE;    
}

int alEngine::printWidth()
{
    return fWorker->option(parameter(EQUIPMENT, PRINTER).toString(), "print width").toInt(); 
}

QString alEngine::centerString(QString str, int iWidth)
{
    if(!iWidth)
        return str;
    str = str.rightJustified((iWidth-str.length())/2-1+str.length());
    return str;
}

QString alEngine::alignStrings(QStringList lst, QList<int> tabs, int iWidth)
{
    QString sRes, sRes2, tmp;
    if(!lst.count()) return QString("");
    int tabWidth = iWidth / lst.count();
    for(int i=lst.count()-1;i>0;i--)
    {
        tmp = lst[i];
        if((int)tmp.length()>tabWidth)
        {
            sRes = " " + tmp.left(tabWidth-1) + sRes;
            sRes2 = " " + tmp.mid(tabWidth-1, tabWidth).rightJustified(tabWidth-1) + sRes2;
        }
        else
        {
            sRes = " " + tmp.rightJustified(tabs[i] ? tabs[i] : tmp.length()+2) + sRes;
        }
    }
    tmp = lst[0];
    tabWidth = iWidth - sRes.length();
    sRes = tmp.leftJustified(tabWidth-1, ' ', TRUE) + sRes;
    if((int)tmp.length()>tabWidth) sRes2 = tmp.mid(tabWidth-1, tabWidth) + sRes2;
    if(!sRes2.isEmpty()) sRes = sRes + "\n" + sRes2;
    return sRes;
}

void alEngine::startImport()
{
//TDOD fixit
    //    QString path = QString(settings->parameter(GENERAL, IMPEXPPATH).toString());
//    if(path.right(1)!="/") path += "/";
//    QString fileName =  path + QString(settings->parameter(GENERAL, IMPEXPIMPORT).toString());
//    if(settings->parameter(GENERAL, IMPEXPFTP).toInt())
//    {
//	QFile * file = new QFile(fileName);
//    file->open(QIODevice::WriteOnly);
//	QString remotePath = settings->parameter(GENERAL, IMPEXPFTPRDIR).toString();
//	if(remotePath.right(1)!="/") remotePath += "/";
//	QFtp * ftp = ftpget(settings->parameter(GENERAL, IMPEXPFTPHOST).toString(),
//			settings->parameter(GENERAL, IMPEXPFTPPORT).toInt(),
//			settings->parameter(GENERAL, IMPEXPFTPLOGIN).toString(),
//			settings->parameter(GENERAL, IMPEXPFTPPASSWORD).toString(),
//			remotePath + QString(settings->parameter(GENERAL, IMPEXPIMPORT).toString()),
//			*file);
////	connect(ftp, SIGNAL(done(bool)), SLOT(import(bool)));
//    }
//    else import();
}

//TODO uncomment
void alEngine::import(bool stop)
{
//    if(stop) return;
//    QString path = QString(settings->parameter(GENERAL, IMPEXPPATH).toString());
//    if(path.right(1)!="/") path += "/";
//    QString fileName =  path + QString(settings->parameter(GENERAL, IMPEXPIMPORT).toString());
//    QString fmt = QString::fromUtf8(settings->parameter(GENERAL, IMPEXPFMT).toByteArray());
//    importer * imp = importer::createImporter(fmt);
//    imp->setCodepage(settings->parameter(GENERAL, IMPEXPCP).toString());
////    if(!imp->open(fileName)) qDebug("NOFILE");
//    imp->open(fileName);
////    qDebug(QString("start time %1").arg(QTime::currentTime().toString()));
//    alDataGoods * goods = new alDataGoods(this);
//    goods->import(imp);
//    alDataDiscount * disc = new alDataDiscount(this);
//    disc->import(imp);
////    qDebug(QString("end time %1").arg(QTime::currentTime().toString()));
}

    //TODO uncomment
void alEngine::exportSales(int type, QDateTime begin, QDateTime end)
{
//    QString fileName = QString(settings->parameter(GENERAL, IMPEXPPATH).toString()) +
//		       QString(settings->parameter(GENERAL, IMPEXPEXPORT).toString());
//    QString fmt = QString::fromUtf8(settings->parameter(GENERAL, IMPEXPFMT).toByteArray());
//    exporter * exp = exporter::createExporter(fmt);
//    if(!exp) return;
//    exp->open(fileName);
//    alDataOrder * orders = new alDataOrder(this);
//    if(type==0)
//    {
//	orders->select("status=2");
//    }
//    else
//    {
//	QString filter = QString("orderdate>='%1' AND orderdate<='%2' AND timeopen>'%3' AND timeopen<'%4' AND (status=2 OR status=4)")
//			 .arg(begin.date().toString("yyyy-MM-dd"))
//			 .arg(end.date().toString("yyyy-MM-dd"))
//			 .arg(begin.time().toString())
//			 .arg(end.time().toString()) ;
//	orders->select(filter);
//    }
//    startTransaction();
//    int tranz = 1;
//    if(orders->first()) do
//    {
//	alOrderRecord * order = (alOrderRecord *)orders->current();
//    qDebug() << QString("export order #%1").arg(order->num());
//	alDataOrderTable * orderTab = order->getDocumentTable();
//	orderTab->select();
//	for(int r=0;r<orderTab->count();r++)
//	{
//	    alOrderLine * line = orderTab->getLine(r);
//	    alGoodsRecord * item = line->item();
//	    map m;
//	    m["01"] = tranz++;
//	    m["02"] = order->date().toString("dd.MM.yyyy");
//	    m["03"] = order->timeOpen().toString();
//	    m["04"] = "11";
//	    m["05"] = "1";
//	    m["06"] = order->num();
//	    m["07"] = "1";
//	    m["08"] = item ? item->externalCode() : "0";
//	    m["09"] = "1";
//	    m["10"] = line->price();
//	    m["11"] = line->amount();
//	    m["12"] = line->summ();
//	    exp->fromMap(m);
//	    alDiscountRecord * discount;
//	    if((discount = order->discount()))
//	    {
//		if(discount->type()==0)
//		{
//		    if(discount->code().isEmpty())  m["04"] = "17";
//		    else m["04"]="70";
//		}
//		else
//		{
//		    if(discount->code().isEmpty()) m["04"] = "15";
//		    else m["04"]="70";
//		}
//		m["08"] = discount->code();
//		m["09"] = "1";
//		m["10"] = "";
//		m["11"] = discount->value();
//		m["12"] = line->amount()*line->price()-line->summ();
//		exp->fromMap(m);
//	    }
//	}
//	map m;
//	m["01"] = tranz++;
//	m["02"] = order->date().toString("dd.MM.yyyy");
//	m["03"] = order->timeOpen().toString();
//	m["04"] = "55";
//	m["05"] = "1";
//	m["06"] = order->num();
//	m["07"] = "1";
//	m["08"] = "0";
//	m["09"] = "1";
//	m["10"] = "";
//	m["11"] = "";
//	m["12"] = "";
//	exp->fromMap(m);
//	order->setStatus(alDataOrder::Exported);
//	order->update();
//	app->processEvents();
//    }while(orders->next());
//    delete exp;
//    commitTransaction();
    
//    if(settings->parameter(GENERAL, IMPEXPFTP).toInt())
//    {
//	QFile * file = new QFile(fileName);
//    file->open(QIODevice::ReadOnly);
//	QString remotePath = settings->parameter(GENERAL, IMPEXPFTPRDIR).toString();
//	if(remotePath.right(1)!="/") remotePath += "/";
//	ftpput(settings->parameter(GENERAL, IMPEXPFTPHOST).toString(),
//			settings->parameter(GENERAL, IMPEXPFTPPORT).toInt(),
//			settings->parameter(GENERAL, IMPEXPFTPLOGIN).toString(),
//			settings->parameter(GENERAL, IMPEXPFTPPASSWORD).toString(),
//			*file,
//			remotePath + QString(settings->parameter(GENERAL, IMPEXPEXPORT).toString()));
//    }
}

void alEngine::error(QString err)
{
    QMessageBox::critical(NULL, "aldebaran", err);
}

/*
Обработка закрытия программы
*	- Сохранение настроек
*	- Закрытие базы данных	
*	- Завершение работы приложения
*/
void alEngine::exitApp()
{
    if(server)
        delete server;
    //TODO uncomment

    //eqWorker::kill();
    settings->flush();
    delete settings;
    settings = NULL;
    if(dbInited)
    {
        fDB.close();
        //TODO fixit
        //QSqlDatabase::removeDatabase(fDB);
    }
#ifdef DEBUG	
    qDebug() << tr("Program successfully terminated").utf8();
#endif
    qApp->exit(0);
}

double alEngine::calculator(double initVal)
{
//TODO reimplement
//    alCalculator * calc = new alCalculator();
//    calc->setValue(initVal);
//    int answer = calc->exec();
//    if(answer) return calc->value();
//    else return -1.0;
//    return initVal;
}

void alEngine::zReport()
{
    eqJob * job =createECRJob("", "ZReport");
    if(!job) error(tr("ERROR: default ECR not connected"));
    else
    {
	int res = job->process();
	if(res)
	{
	    res = QMessageBox::critical(NULL, "aldebaran", QString(tr("%1:%2")).arg(res).arg(job->errorMsg()));
	    return;
	}     	
	delete job;
    }    
}

void alEngine::xReport()
{
    eqJob * job =createECRJob("", "XReport");
    if(!job) error(tr("ERROR: default ECR not connected"));
    else
    {
	int res = job->process();
	if(res)
	{
	    res = QMessageBox::critical(NULL, "aldebaran", QString(tr("%1:%2")).arg(res).arg(job->errorMsg()));
	    return;
	}     	
	delete job;
    }    
}

void alEngine::payin()
{
    double val = calculator();
    if(val==0.) return;
    eqJob * job =createECRJob("", "payin");
    if(!job) error(tr("ERROR: default ECR not connected"));
    else
    {

	job->setData(val);
	int res = job->process();
	if(res)
	{
	    res = QMessageBox::critical(NULL, "aldebaran", QString(tr("%1:%2")).arg(res).arg(job->errorMsg()));
	    return;
	}     	
	delete job;
    }    
}

void alEngine::payout()
{
    double val = calculator();
    if(val==0.) return;
    eqJob * job =createECRJob("", "payout");
    if(!job) error(tr("ERROR: default ECR not connected"));
    else
    {

	job->setData(val);
	int res = job->process();
	if(res)
	{
	    res = QMessageBox::critical(NULL, "aldebaran", QString(tr("%1:%2")).arg(res).arg(job->errorMsg()));
	    return;
	}     	
	delete job;
    }    
}

//TODO uncomment
void alEngine::readerData(int track, QString line)
{
//    QMap<QString, QVariant> data;
//    data["track"] = track;
//    data["line"] = line;
//    emit(event(EVENT_MSCREADER, data));
}

//TODO uncomment
void alEngine::barcodeReaderData(QString line)
{
//    QMap<QString, QVariant> data;
//    data["line"] = line;
//    emit(event(EVENT_BARCODEREADER, data));
}

void alEngine::onError(int errorCode)
{
    QString senderName = sender()->metaObject()->className();
    if(senderName=="QFtp")
    {
//TODO reimplement
//        QFtp * ftp = (QFtp*)sender();
//        if(ftp->error()!=QFtp::NoError)
//        {
//            qDebug() << ftp->errorString().utf8();
//        }
//        else
//        {
//            if(ftp->currentDevice()) delete ftp->currentDevice();
//        }
    }
    if(sender()->inherits("eqDriver"))
    {
        eqDriver * device = (eqDriver*)sender();
//TODO error messages	
//	error(device->errorMsg());
//TODO reimplement
        //qDebug() << QString("%1:%2").arg(errorCode).arg(device->errorMsg().toUtf8());
    }
}

//TODO reimplement
void alEngine::endFTPExport(int, bool error)
{
//    if(error) return;
//    QFtp * ftp = (QFtp*)sender();
//    if(ftp->currentDevice())
//    {
//	QFile * file = (QFile*)ftp->currentDevice();
//	file->remove();
//    }
}

//TODO reimplement
QFtp * alEngine::ftpput(QString host, int port, QString login, QString password, const QFile& local, QString remotefile)
{
//    QFtp * ftp = new QFtp();
//    connect(ftp, SIGNAL(commandFinished(int, bool)), SLOT(endFTPExport(int, bool)));
//    connect(ftp, SIGNAL(commandFinished(int, bool)), SLOT(onError(int)));
//    ftp->connectToHost(host, port);
//    ftp->login(login, password);
//    ftp->put((QIODevice*)&local, remotefile);
//    return ftp;
}

//TODO reimplement
QFtp * alEngine::ftpget(QString host, int port, QString login, QString password, QString remotefile, const QFile& local)
{
//    QFtp * ftp = new QFtp();
//    connect(ftp, SIGNAL(commandFinished(int, bool)), SLOT(onError(int)));
//    ftp->connectToHost(host, port);
//    ftp->login(login, password);
//    ftp->get(remotefile, (QIODevice*)&local);
//    return ftp;
}

alValueList alEngine::processJob(eqJob *job)
{
    alValueList res;
    res["error"] = 0;
    res["msg"] = "";
    if(!job)
    {
	res["error"] = ERR_NODEVICE;
	res["msg"] = "";
	return res;
    }
    job->process();
    int err = job->error();
    if(err)
    {
	res["error"] = err;
	res["msg"] = job->errorMsg();
        qDebug() << res["msg"].toString();
        cancelCheque(job->device()->objectName());
    }
    return res;
}

void alEngine::cancelCheque(QString devName)
{
    eqJob * job = createECRJob(devName, "cancelCheck");
    if(!job) return;
    job->process();    
}

//TODO uncomment
alValueList alEngine::cheque(QString devName, alValueTable tab, alValueTable totals)
{
//    alValueList res;
//    eqJob * job = createECRJob(devName, "openSale");
//    res = processJob(job);
//    if(res["error"].toInt()) return res;
    
//    for(int r=0;r<tab.rowCount();r++)
//    {
//        job = createECRJob("", "addItem");
//        job->setData(tab[r]->asValueList());
//        res = processJob(job);
//    	if(res["error"].toInt())
//            return res;
//    }
//    job = createECRJob("", "closeCheck");
//    job->setData(totals[0]->asValueList());
//    res = processJob(job);
//    if(res["error"].toInt()) return res;
//    job = createECRJob("", "cut");
//    res = processJob(job);
//    if(res["error"].toInt()) return res;
//    res["error"] = 0;
//    res["msg"] = "";
//    res["change"] = job->result().toDouble();
//    return res;
}

//TODO move to reports module
//TODO reimplement
QStringList alEngine::advReportGoods(int period, QDateTime begin, QDateTime end)
{
//    QString queryStr  = "";
//    if(period==0)
//    {
//	queryStr = "select name, sum(amount) as amount, sum(summ) as sum, order_table.price from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join goods on id_goods=goods.id "
//		   "where orders.status=2 group by id_goods, name, order_table.price";
//	begin = QDateTime();
//	end = QDateTime();
//    }
//    else
//    {
//	queryStr = QString("select name, sum(amount) as amount, sum(summ), order_table.price as sum from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join goods on id_goods=goods.id "
//		   "where orderdate>='%1' AND orderdate<='%2' AND timeopen>'%3' AND "
//		   "timeopen<'%4' AND (status=2 OR status=4) group by id_goods, name, order_table.price")
//			 .arg(begin.date().toString("yyyy-MM-dd"))
//			 .arg(end.date().toString("yyyy-MM-dd"))
//			 .arg(begin.time().toString())
//			 .arg(end.time().toString()) ;
//    }
    
//    QSqlQuery query(fDB);
//    if(!query.exec(queryStr))
//    {
//	error(tr("Error in query: %1").arg(queryStr));
//	return QString::null;
//    }
    
//    QStringList str;
//    if(query.first())
//    {
//	int pw = printWidth();
//	str << centerString(tr("Advanced report: "), pw)+QString(tr("Goods"));
//	if(!(begin.isNull() || end.isNull())) str << QString(tr("from %1 to %2")).arg(begin.toString()).arg(end.toString());
//	else str << QString(QDateTime::currentDateTime().toString());
//	str << QString("").rightJustify(pw, '-');
//  	QStringList lst;
//	QValueList<int> tabs;
//	double sum = 0.0, sumDiscount = 0.0;
//	do
//	{
//	    lst << query.value(0).toString();
//	    lst << query.value(1).toString();
//	    lst << query.value(2).toString();
//	    tabs << 0 << 5 << 5;
//	    str << alignStrings(lst, tabs, pw);
//	    sum += query.value(2).toDouble();
//	    sumDiscount += query.value(1).toDouble()*query.value(3).toDouble() - query.value(2).toDouble();
//	    lst.clear();
//	    tabs.clear();
//	}while(query.next());
//	str << QString("").rightJustify(pw, '-');
//	lst << tr("Total:");
//	lst << QString("%2").arg(sum, 5, 'f', 2);
//	tabs << 0 << 5;
//	str <<  alignStrings(lst, tabs, pw);
//	lst.clear();
//	lst << tr("Discounts:");
//	lst << QString("%2").arg(sumDiscount, 5, 'f', 2);
//	str <<  alignStrings(lst, tabs, pw);
//	lst.clear();
//	lst << tr("Total without discounts:");
//	lst << QString("%2").arg(sum+sumDiscount, 5, 'f', 2);
//	str <<  alignStrings(lst, tabs, pw);
//	str << "" << "" << "";
//    }
//    return str;
}

//TODO reimplement
QStringList alEngine::advReportHourly(int period, QDateTime begin, QDateTime end)
{
//    QString queryStr  = "";
//    if(period==0)
//    {
//	queryStr = "select sum(amount) as amount, sum(summ) as sum, orderdate, timeclose, order_table.price from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join goods on id_goods=goods.id "
//		   "where orders.status=2 group by orderdate, timeclose, order_table.price "
//		   "order by timeclose";
//	begin = QDateTime();
//	end = QDateTime();
//    }
//    else
//    {
//	queryStr = QString("select sum(amount) as amount, sum(summ) as sum, orderdate, timeclose, order_table.price from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join goods on id_goods=goods.id "
//		   "where orderdate>='%1' AND orderdate<='%2' AND timeopen>'%3' AND "
//		   "timeopen<'%4' AND (status=2 OR status=4) group by orderdate, timeclose, order_table.price "
//		   "order by timeclose")
//			 .arg(begin.date().toString("yyyy-MM-dd"))
//			 .arg(end.date().toString("yyyy-MM-dd"))
//			 .arg(begin.time().toString())
//			 .arg(end.time().toString()) ;
//    }
    
//    QSqlQuery query(fDB);
//    if(!query.exec(queryStr))
//    {
//	error(tr("Error in query:"));
//	qDebug()<< queryStr;
//	return QString::null;
//    }
  
//    QStringList str;
//    if(query.first())
//    {
//	int pw = printWidth();
//	str << centerString(tr("Advanced report: "), pw)+QString(tr("Hourly"));
//	if(!(begin.isNull() || end.isNull())) str  <<  QString(tr("from %1 to %2")).arg(begin.toString()).arg(end.toString());
//	else str << QString(QDateTime::currentDateTime().toString());
//	str << QString("").rightJustify(pw, '-');
//  	QStringList lst;
//	QValueList<int> tabs;
//	int lastHour = -1;
//	double sum = 0.0, amount=0.0, total=0.0, totalDiscount=0.0;
//	do
//	{
//	    QDateTime date = query.value(2).toDateTime();
//	    int hour = query.value(3).toTime().hour();
//	    amount += query.value(0).toDouble();
//	    sum += query.value(1).toDouble();
//	    totalDiscount += query.value(0).toDouble()*query.value(4).toDouble();
//	    if(hour!=lastHour)
//	    {
//		lst << QString("%1:00-%2:00").arg(hour-1).arg(hour);
//		lst << QString("%1").arg(amount, 5, 'f', 3);
//		lst << QString("%2").arg(sum, 5, 'f', 2);
//		tabs << 0 << 5 << 5;
//		str <<  alignStrings(lst, tabs, pw);
//		lst.clear();
//		tabs.clear();
//		total += sum;
//		amount = 0.0;
//		sum = 0.0;
//		lastHour = hour;
//	    }
//	}while(query.next());
//	str << QString("").rightJustify(pw, '-');
//	total+=sum;
//	totalDiscount -= total;
//	lst << tr("Total:");
//	lst << QString("%2").arg(total, 5, 'f', 2);
//	tabs << 0 << 5;
//	str <<  alignStrings(lst, tabs, pw);
//	lst.clear();
//	lst << tr("Discounts:");
//	lst << QString("%2").arg(totalDiscount, 5, 'f', 2);
//	str <<  alignStrings(lst, tabs, pw);
//	lst.clear();
//	lst << tr("Total without discounts:");
//	lst << QString("%2").arg(total+totalDiscount, 5, 'f', 2);
//	str <<  alignStrings(lst, tabs, pw);
	
//	str << "" << "" << "";
//    }
//    return str;
}

//TODO reimplement
QStringList alEngine::advReportCheques(int period, QDateTime begin, QDateTime end)
{
//    QString queryStr  = "";
//    if(period==0)
//    {
//	queryStr = "select sum(amount) as amount, sum(summ) as sum, orders.id, id_goods, goods.name, id_discount, discount.name, tablenum, timeclose, order_table.price from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join goods on id_goods=goods.id "
//		   "left join discount on id_discount=discount.id "
//		   "where orders.status=2 group by orders.id, id_discount, id_goods, goods.name, discount.name, tablenum, timeclose, order_table.price "
//		   "order by orders.id";
//	begin = QDateTime();
//	end = QDateTime();
//    }
//    else
//    {
//	queryStr = QString("select sum(amount) as amount, sum(summ) as sum, orders.id, id_goods, goods.name, id_discount, discount.name, tablenum, timeclose, order_table.price from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join goods on id_goods=goods.id "
//		   "left join discount on id_discount=discount.id "
//		   "where (orderdate>='%1') AND (orderdate<='%2') AND (timeopen>'%3') AND "
//		   "(timeopen<'%4') AND (status=2 OR status=4) group by orders.id, id_discount, id_goods, goods.name, discount.name, tablenum, timeclose, order_table.price "
//		   "order by orders.id")
//			 .arg(begin.date().toString("yyyy-MM-dd"))
//			 .arg(end.date().toString("yyyy-MM-dd"))
//			 .arg(begin.time().toString())
//			 .arg(end.time().toString()) ;
//    }
    
//    QSqlQuery query(fDB);
//    if(!query.exec(queryStr))
//    {
//	error(tr("Error in query:"));
//	qDebug(queryStr);
//	return QString::null;
//    }
    
//    QStringList str;
//    if(query.first())
//    {
//	int pw = printWidth();
//	str << centerString(tr("Advanced report: "), pw)+QString(tr("Cheques"));
//	if(!(begin.isNull() || end.isNull())) str <<  QString(tr("from %1 to %2")).arg(begin.toString("dd.MM.yy hh:mm:ss")).arg(end.toString("dd.MM.yy hh:mm:ss"));
//	else str << QString(QDateTime::currentDateTime().toString());
//	str << QString("").rightJustify(pw, '-');
//  	QStringList lst;
//	QValueList<int> tabs;
//	int lastCheck = -1;
//	double sum = 0.0, amount=0.0, total=0.0, totalDiscount=0.0;
//	QString discount;
//	do
//	{
//	    int check = query.value(2).toInt();
//	    if(check!=lastCheck)
//	    {
//		if(lastCheck!=-1)
//		{
//		    lst << tr("Total:");
//		    lst << QString("%2").arg(sum, 5, 'f', 2);
//		    tabs << 0 << 5;
//		    str << alignStrings(lst, tabs, pw);
//		    str << QString("").rightJustify(pw, '-');
//		    lst.clear();
//		    tabs.clear();
//		}
//		str << QString(tr("Cheque #%1, Table #%2")).arg(check).arg(query.value(7).toString())
//		+ QString(" ")+QString("%1").arg(query.value(8).toString());
//		discount = query.value(6).toString();
//		if(!discount.isEmpty()) str << QString(tr("Discount"))+QString(": ")+discount;
//		str << QString("").rightJustify(pw, '-');
//		total+=sum;
//		amount = 0.0;
//		sum = 0.0;
//		lastCheck = check;
//	    }
//	    totalDiscount+=query.value(0).toDouble()*query.value(9).toDouble();
//	    sum += query.value(1).toDouble();
//	    lst << query.value(4).toString();
//	    lst << query.value(0).toString();
//	    lst << query.value(1).toString();
//	    tabs << 0 << 5 << 5;
//	    str <<  alignStrings(lst, tabs, pw);
//	    lst.clear();
//	    tabs.clear();
//	}while(query.next());
//	lst << tr("Total:");
//	lst << QString("%2").arg(sum, 5, 'f', 2);
//	tabs << 0 << 5;
//	str <<  alignStrings(lst, tabs, pw);
//	str << QString("").rightJustify(pw, '-');
//	total+=sum;
//	totalDiscount -= total;
//	lst << tr("Total:");
//	lst << QString("%2").arg(total, 5, 'f', 2);
//	tabs << 0 << 5;
//	str <<  alignStrings(lst, tabs, pw);
//	lst.clear();
//	lst << tr("Discounts:");
//	lst << QString("%2").arg(totalDiscount, 5, 'f', 2);
//	str <<  alignStrings(lst, tabs, pw);
//	lst.clear();
//	lst << tr("Total without discounts:");
//	lst << QString("%2").arg(total+totalDiscount, 5, 'f', 2);
//	str <<  alignStrings(lst, tabs, pw);
		
//	str << "" << "" << "";
//    }
//    return str;
}

//TODO reimplement
QStringList alEngine::advReportDiscounts(int period, QDateTime begin, QDateTime end)
{
//    QString queryStr  = "";
//    if(period==0)
//    {
//	queryStr = "select  timeclose, discount.name,  sum(price*amount) as fullsumm, sum(summ) as summ, sum(price*amount)-sum(summ) AS discountsumm "
//		   "from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join discount on id_discount=discount.id "
//		   "where orders.status=2 AND id_discount<>0 "
//		   "group by discount.name, discount.type, discount.value, timeclose "
//		   " order by timeclose";
//	begin = QDateTime();
//	end = QDateTime();
//    }
//    else
//    {
//	queryStr = QString("select  timeclose, discount.name,  sum(price*amount) as fullsumm, sum(summ) as summ, sum(price*amount)-sum(summ) AS discountsumm "
//		   "from order_table "
//		   "left join orders on orders.id=id_order "
//		   "left join discount on id_discount=discount.id "
//		   "where orderdate>='%1' AND orderdate<='%2' AND timeopen>'%3' AND "
//		   "timeopen<'%4' AND (orders.status=2 OR status=4) AND id_discount<>0 "
//		   "group by discount.name, discount.type, discount.value, timeclose "
//		   "order by timeclose")
//			 .arg(begin.date().toString("yyyy-MM-dd"))
//			 .arg(end.date().toString("yyyy-MM-dd"))
//			 .arg(begin.time().toString())
//			 .arg(end.time().toString()) ;
//    }
    
//    QSqlQuery query(fDB);
//    if(!query.exec(queryStr))
//    {
//	error(tr("Error in query:"));
//	qDebug(queryStr);
//	return QString::null;
//    }
    
//    if(query.first())
//    {
//	int pw = printWidth();
//	QString str = centerString(tr("Advanced report: "), pw)+QString(tr("Discounts"))+QString("\n");
//	if(!(begin.isNull() || end.isNull())) str +=  QString(tr("from %1 to %2")).arg(begin.toString()).arg(end.toString())+ QString("\n");
//	else str += QString(QDateTime::currentDateTime().toString())+QString("\n");
//	str += QString("").rightJustify(pw, '-') + QString("\n");
//  	QStringList lst;
//	QValueList<int> tabs;
//	double sum = 0.0, fullSumm = 0.0;
//	do
//	{
//	    lst << query.value(0).toString()+":";
//	    lst << query.value(1).toString();
//	    tabs << 0 << 5;
//	    str +=  alignStrings(lst, tabs, pw)+QString("\n");
//	    lst.clear();
//	    tabs.clear();
//	    lst << "";
//	    lst << QString("%1").arg(query.value(2).toDouble(), 5, 'f', 2);
//	    lst << QString("%1").arg(query.value(2).toDouble(), 5, 'f', 2);
//	    lst << QString("%1").arg(query.value(2).toDouble(), 5, 'f', 2);
//	    tabs << 0 << 5 << 5 << 5;
//	    str += alignStrings(lst, tabs, pw)+QString("\n");
//	    sum += query.value(3).toDouble();
//	    fullSumm += query.value(2).toDouble();
//	    lst.clear();
//	    tabs.clear();
//	}while(query.next());
//	str += QString("").rightJustify(pw, '-') + QString("\n");
//	lst << tr("Total:");
//	lst << QString("%2").arg(sum, 5, 'f', 2);
//	tabs << 0 << 5;
//	str +=  alignStrings(lst, tabs, pw)+QString("\n");
//	lst.clear();
//	lst << tr("Discounts:");
//	lst << QString("%2").arg(fullSumm-sum, 5, 'f', 2);
//	str +=  alignStrings(lst, tabs, pw)+QString("\n");
//	lst.clear();
//	lst << tr("Total without discounts:");
//	lst << QString("%2").arg(fullSumm, 5, 'f', 2);
//	str +=  alignStrings(lst, tabs, pw)+QString("\n");
//	str += "\n\n\n";
//	str = str.utf8();
//	return str;
//    }
//    return QString::null;
}

void alEngine::advancedReport(int period, int type, QDateTime begin, QDateTime end)
{
    if(period<0 || period>1 || type<0 || type>3) return;    
    
    eqJob * job = createPrinterJob("", "print");
    if(!job)
    {
	error(tr("Can't print Advanced report"));
	return;
    }
            
    QStringList str;
    if(type==0) str = advReportGoods(period, begin, end);
    else if(type==1) str = advReportHourly(period, begin, end);
    else if(type==2) str = advReportCheques(period, begin, end);
    else if(type==3) str = advReportDiscounts(period, begin, end);
    job->setData(str.join("\n").toUtf8());
    processJob(job);
    job = createPrinterJob("", "cut");
    processJob(job);
    app->processEvents();
}

QByteArray pixmap2bytearray(QPixmap pix)
{
    QByteArray bytea;
    QBuffer buffer( &bytea );
    buffer.open( QIODevice::WriteOnly );
    pix.save( &buffer, "PNG" );
    return bytea;
}

QPixmap bytearray2pixmap(QByteArray bytea)
{
    QPixmap pix;
    QBuffer buffer(&bytea);
    pix.loadFromData(bytea);
    return pix;
}

QDate int2date(int days)
{
    QDate res(1942, 1, 1);
    res = res.addDays(days);
    return res;
}

QTime int2time(int secs)
{
    QTime res(0, 0, 0);
    res = res.addSecs(secs);
    return res;
}

int date2int(QDate d)
{
	QDate zero(1942, 1, 1); // no computers before 1942
	return zero.daysTo(d);
}

int time2int(QTime time)
{
	QTime zero(0, 0, 0);
	return zero.secsTo(time);
}
