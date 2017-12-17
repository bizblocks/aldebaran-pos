#ifndef MSCREADER_H
#define MSCREADER_H

#include <qpixmap.h>
#include "driver.h"

class TEReaderBarcode;
class eqJob;

class  eqMSCReader : public eqDriver
{
    Q_OBJECT
public:
    eqMSCReader(QString name);
    ~eqMSCReader();
    virtual void init();
    virtual eqJob * createJob(QString action="");
    virtual void prepare() {};
    virtual void end() {};    
    virtual void setOption(QString option, QVariant value);    
    virtual QStringList options();
    virtual QString option(QString name);
    virtual bool dialog();
    
    QStringList supportedBaudRates();
    QStringList supportedDataBits();
    QStringList supportedParity();
    QStringList supportedStopBits();
    QStringList supportedFlowControl();    
signals:
    void data(int, QString);
protected slots:
    virtual void onData(int);
protected:
    TEReaderBarcode * reader;
    QString fPortDevice;
    int fPortBaudRate, fPortDataBits, fPortParity, fPortStopBits, fPortFlowControl;
    char fHeader, fTrailer;
};

#endif
