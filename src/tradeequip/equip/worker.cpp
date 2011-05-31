#include <qapplication.h>
#include <qtimer.h>
#include <qsignal.h>
#include <qthread.h>
#include "worker.h"
#include "driver.h"
#include "officeprinter.h"
#include "cts300printer.h"
#include "shtrihfr.h"
#include "felixrk.h"
#include "siriusterminal.h"
#include "mscreader.h"
#include "barcodereader.h"
#include "virtualmart.h"
#include "dataeq.h"

class jobThread : public QThread
{
public:
    jobThread(eqJob * o, QMutex * m);
    void run();
    void stop();
    
    QMutex * mutex;    
private:
    eqJob * job;
};

jobThread::jobThread(eqJob * o, QMutex * m) :
	    mutex(m), job(o)
{
}

void jobThread::run()
{
    mutex->lock();
    job->device()->prepare();    
    job->process();
    job->device()->end();        
    job =NULL;
    mutex->unlock();    
}

bool hasWorkers = FALSE;
eqWorker * fWorker;

eqWorker::eqWorker() :
	QObject(NULL, "equipmentWorker")
{
    hasWorkers = TRUE;
    fWorker = this;
    devices.clear();
    threads.clear();
}

eqWorker::~eqWorker()
{    
    for(QValueList<QThread*>::iterator it=threads.begin();it!=threads.end();++it)
    {
	jobThread * thread = (jobThread*)(*it);
	if(thread)
	{
	    thread->mutex->lock();
	    thread->mutex->unlock();
	    delete thread->mutex;
	    delete thread;
	}
    }
    
    for(int i=0;i<(int)devices.keys().count();i++)
    {
	eqDriver * device = devices[devices.keys()[i]];
	if(device) delete device;
    }
}

eqWorker * eqWorker::worker()
{
    if(hasWorkers) return fWorker;
    eqWorker * res = new eqWorker();    
    return res;	    
}

void eqWorker::kill()
{
    if(hasWorkers) delete fWorker;
}

void eqWorker::runJob(eqJob * job)
{
    QMutex * mutex = new QMutex();    
    jobThread * thread = new jobThread(job, mutex);
    threads.append(thread);
}

eqDriver * eqWorker::createDevice(QString driverName, QString deviceName, bool queue)
{
    eqDriver * dev = NULL;
    if(driverName=="Office Printer") dev = new eqOfficePrinter(deviceName);
    else if(driverName=="Sirius") dev = new eqSirius(deviceName);
    else if(driverName=="MSC Reader") dev = new eqMSCReader(deviceName);    
    else if(driverName=="Barcode Reader") dev = new eqBarcodeReader(deviceName);
    else if(driverName=="Virtual Mart") dev = new eqVirtualMart(deviceName);
    else if(driverName=="ECR") dev = new eqFR(deviceName);    
    if(dev && queue)
    {
	addDevice(dev);
    }	
    return dev;
}

eqDriver * eqWorker::getDevice(QString deviceName)
{
    return devices[deviceName];
}

void eqWorker::addDevice(eqDriver * device)
{
    if(device) devices[device->name()] = device;
}

eqJob * eqWorker::createJob(QString deviceName, QString action)
{
    eqDriver * drv = devices[deviceName];
    if(!drv) return NULL;
    return drv->createJob(action);
}

void eqWorker::setOption(QString deviceName, QString option, QVariant value)
{
    eqDriver * drv = devices[deviceName];
    if(!drv) return;
    drv->setOption(option, value);
}

QVariant eqWorker::option(QString deviceName, QString optionName)
{
    QVariant res;
    eqDriver * drv = devices[deviceName];
    if(drv) res = drv->option(optionName);
    return res;
}

QStringList eqWorker::driverList()
{
    QStringList lst;
    lst << "Sirius" 
	    << "ECR"
	    << "Office Printer" 
	    << "MSC Reader" 
	    << "Barcode Reader"
	    << "Virtual Mart";
    return lst;
}
	
eqJob::eqJob(eqDriver * device, QString action) : 
	QObject(device, QString("%1_job").arg(device->name()))
{
    fResult = 0;
    setError(0, "");
    fDevice = device;
    fAction = action;
    fSignal = new QSignal(this);
    fData.clear();
    processed = FALSE;
}

eqJob::~eqJob()
{
    if(fSignal) delete fSignal;
}

int eqJob::process()
{
    if(fAction.isEmpty()) return 0;
    fSignal->connect(this, QString(SLOT(%1())).arg(fAction));
    fSignal->activate();
    fSignal->disconnect(this, QString(SLOT(%1())).arg(fAction));
    processed = TRUE;
    return fSignal->value().toInt();     
}

void eqJob::wait()
{
    while(!processed)
    {
	usleep(1000);
    }
}

bool eqJob::waitTimeout(Q_ULLONG sec)
{
    for(Q_ULLONG i=0;i<sec*10;i++)
    {
	usleep(1000);
	if(processed) return processed;
    }
    return processed;    
}

eqWorkerJob::eqWorkerJob() : 
	eqJob(new eqDummyDriver("worker"), "exit thread") 
{
}

int eqWorkerJob::process()
{
    return 0;
}

void eqWorker::initEquipment(alDataEq * eq)
{
    eq->select();    
    if(eq->first()) do
    {
	alEqRecord * device = (alEqRecord*)eq->current();
	if(!device->enabled()) continue;
	eqDriver * dev = fWorker->createDevice(device->type(), device->name(), FALSE);
	QStringList opts = device->options();
	for(uint i=0;i<opts.count();i++)
	{
	    dev->setOption(opts[i], device->option(opts[i]));
//	    qDebug(opts[i]+"="+device->option(opts[i]));
	}
	connect(dev, SIGNAL(deviceError(int)), this, SLOT(onError(int)));
	dev->init();
	this->addDevice(dev);
    } while (eq->next());
}

void eqWorker::onError(int err)
{
    emit deviceError(err);
}

