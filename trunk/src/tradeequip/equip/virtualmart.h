#ifndef VIRTUALMART_H
#define VIRTUALMART_H

#include <qpixmap.h>
#include "driver.h"
#include "ievmart.h"

#define VMART_NODEVICE		200
#define VMART_INVALIDARG		201

class eqJob;
class eqVMJob;

class eqVirtualMart : public eqDriver
{
    Q_OBJECT
public:
    eqVirtualMart(QString name);
    ~eqVirtualMart();
    virtual eqJob * createJob(QString action="");
    virtual void prepare() {};
    virtual void end() {};    
    virtual void setOption(QString option, QVariant value);
    virtual QStringList options();
    virtual QString option(QString name);
    virtual bool dialog();
public slots:
    virtual void init();    
    void header(QVariant data);
    void line(QVariant data);
    void tailer(QString data);
    QString serverHost();
    int serverPort();
protected slots:
    void checkError();
    virtual void onData();
    virtual void deviceConnected();
signals:
    void data(importer*);
private:
    impVMart * vMart;
    int port, table;
    QString host, db, login, password, prefix;
    struct queueElement
    {
	QString type;
	QVariant data;
    };
    QValueList<queueElement> queue;
};

class eqVMJob : public eqJob
{
    Q_OBJECT
public:
    eqVMJob(eqDriver * device, QString action, QString data="");
    virtual ~eqVMJob();
public slots:
    void connect();
//    void goodsStart();
//    void goodsEnd();
//    void elementStart();
//    void elementEnd();
    void orderStart();
    void orderEnd();
    void line();
};

#endif
