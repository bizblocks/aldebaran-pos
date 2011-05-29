#ifndef WORKER_H
#define WORKER_H

#include <qobject.h>
#include <qmap.h>
#include <qvaluelist.h>
#include <qvariant.h>
#include <qthread.h>

#include <qmessagebox.h>
#define EQ_NOT_IMPLEMENTED     QMessageBox::information(NULL, "aldebaran-equipment", QObject::tr("NOT IMPLEMENTED"));

class eqJob;
class eqDriver;
class QSignal;
class alDataEq;

class eqWorker : public QObject
{
    Q_OBJECT
public:
    static eqWorker * worker();
    static void kill();
    void runJob(eqJob * job);    
    eqJob * createJob(QString deviceName, QString action="");
    eqDriver * createDevice(QString driverName, QString deviceName, bool queue=TRUE);
    void addDevice(eqDriver * device);    
    eqDriver * getDevice(QString deviceName);
    virtual void setOption(QString deviceName, QString option, QVariant value);
    virtual QVariant option(QString deviceName, QString optionName);
    QStringList driverList();
    int deviceCount() { return devices.count(); };
    QString getDeviceName(int devnum) { return devices.keys()[devnum]; };
    void initEquipment(alDataEq * eq);
protected slots:
    void onError(int);
signals:
    void deviceError(int);
protected:
    friend class eqWorkerJob;
private:
    eqWorker();
    ~eqWorker();
    QMap<QString, eqDriver*> devices;
    QValueList<QThread*> threads;
};

class eqJob : public QObject
{
    Q_OBJECT
public:
    eqJob(eqDriver * device, QString action);
    virtual ~eqJob();
    virtual void setData(QVariant d) { fData=d; };    
    virtual void setAction(QString a) { fAction=a; };
    QString action() { return fAction; };
    virtual int process();
    eqDriver * device() { return fDevice; };
    virtual QVariant result() { return fResult; };
    virtual int error() { int res = fError; fError = 0; return res; };
    virtual QString errorMsg() { return fErrorMsg; };
    void wait();
    bool waitTimeout(Q_ULLONG sec);
signals:
protected:
    void setError(int e, QString msg) { fError = e; fErrorMsg = msg; };
    eqDriver * fDevice;
    QString fAction;
    QSignal * fSignal;
    QVariant fData, fResult;
    int fError;
    QString fErrorMsg;
    bool processed;
};

class eqWorkerJob : public eqJob
{
    Q_OBJECT
public:    
    eqWorkerJob();
    virtual int process();    
public slots:
};

#endif
