#ifndef FR_H
#define FR_H

#include "driver.h"

class TECashRegisterBase;
typedef QMap<QString, QVariant> TItem;

class eqFR : public eqDriver
{
    Q_OBJECT
public:
    eqFR(const QString& name);
    virtual ~eqFR();
    virtual void init();    
    virtual eqJob * createJob(QString action="");    
    virtual void prepare();
    virtual void end();
    
    virtual QStringList options();
    virtual QStringList driverList();
    virtual QStringList supportedBaudRates();
    virtual QStringList supportedDataBits();
    virtual QStringList supportedParity();
    virtual QStringList supportedStopBits();
    virtual QStringList supportedFlowControl();
    
    virtual void setOption(QString name, QVariant value);
    virtual QString option(QString name);
    
    virtual bool dialog();
    
    virtual void print(QString line);
    virtual void cut();
    virtual void openCheck(int oper);
    virtual void cancelCheck();
    virtual double closeCheck(TItem param);
    virtual void addItem(TItem item);    
    virtual void ZReport();
    virtual void XReport();
    virtual void payin(double summ);
    virtual void payout(double summ);
    virtual void openCashbox();
    virtual void beep();    
protected:
    virtual bool checkError(int res);
    
    TECashRegisterBase * device;
    QString fDriver;
    QString fPortDevice;
    QString accessPassword, operatorPassword, adminPassword;
    QString fCodepage;
    int fPortBaudRate, fPortDataBits, fPortParity, fPortStopBits, fPortFlowControl;
    int fPrintWidth;
};

class eqFRJob : public eqJob
{
    Q_OBJECT
public:
    eqFRJob(eqDriver * device, QString action, QString data="");
    virtual ~eqFRJob();
public slots:
    void print();
    void cut();    
    void openSale();
    void openReturn();
    void cancelCheck();
    void addItem();
    void closeCheck();
    void ZReport();
    void XReport();
    void payin();
    void payout();
    void openCashbox();
    void beep();
};

#endif
