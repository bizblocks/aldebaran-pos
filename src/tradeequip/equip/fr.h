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
    virtual void setOption(QString name, QVariant value);
    virtual QStringList options();
    virtual QStringList supportedBaudRates();
    virtual QStringList supportedDataBits();
    virtual QStringList supportedParity();
    virtual QStringList supportedStopBits();
    virtual QStringList supportedFlowControl();
    virtual QString option(QString name);
    virtual bool dialog() = 0;
    
    virtual void print(QString line) = 0;
    virtual void cut() = 0;
    virtual void openCheck(int oper) = 0;
    virtual void cancelCheck() = 0;
    virtual void addItem(TItem item) = 0;
    virtual double closeCheck(TItem param) = 0;
    virtual void ZReport() = 0;
    virtual void XReport() = 0;
    virtual void payin(double summ) = 0;
    virtual void payout(double summ) = 0;
    virtual void openCashbox() = 0;
    virtual void beep() = 0;    
protected:
    virtual bool checkError(int res);
    
    TECashRegisterBase * device;
    QString fPortDevice;
    QString accessPassword, operatorPassword, adminPassword;
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
