#ifndef SIRIUSTERMINAL_H
#define SIRIUSTERMINAL_H

#include <qpixmap.h>
#include "driver.h"

#define SIRIUS_NODEVICE		200
#define SIRIUS_INVALIDARG		201

class expSirius;
class eqJob;
class eqSiriusJob;
class importer;

class eqSirius : public eqDriver
{
    Q_OBJECT
public:
    eqSirius(QString name);
    ~eqSirius();
    virtual eqJob * createJob(QString action="");
    virtual void prepare() {};
    virtual void end() {};    
    virtual void setOption(QString option, QVariant value);
    virtual QStringList options();
    virtual QString option(QString name);
    virtual bool dialog();
public slots:
    virtual void init();    
    void header(QString data);
    void line(QVariant data);
    void tailer(QString data);
    QString serverHost();
    int serverPort();
protected slots:
    void checkError();
    virtual void onData(importer*);
    virtual void deviceConnected();
signals:
    void data(importer*);
private:
    expSirius * sirius;
    int port, table;
    QString host;
    struct queueElement
    {
	QString type;
	QVariant data;
    };
    QValueList<queueElement> queue;
};

class eqSiriusJob : public eqJob
{
    Q_OBJECT
public:
    eqSiriusJob(eqDriver * device, QString action, QString data="");
    virtual ~eqSiriusJob();
public slots:
    void connect();
    void goodsStart();
    void goodsEnd();
    void elementStart();
    void elementEnd();
    void orderStart();
    void orderEnd();
    void line();
    void resetDevice();
    void haltDevice();    
    void updateDevice();
};

extern eqDriver * createDevice(QString name);

#endif
