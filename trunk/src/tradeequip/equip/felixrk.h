#ifndef FELIXRK_H
#define FELIXRK_H

#include "driver.h"
#include "fr.h"

class FelixRK;

typedef eqFRJob eqFelixRKJob;

class eqFelixRK : public eqFR
{
    Q_OBJECT
public:
    eqFelixRK(const QString& name);
    virtual ~eqFelixRK();
    virtual void init();    
    virtual QStringList options();
    virtual QString option(QString name);
    virtual bool dialog();
    
    void print(QString line);
    void cut();
    void openCheck(int oper);
    void cancelCheck();
    void addItem(TItem item);
    double closeCheck(TItem param);
    void ZReport();
    void XReport();
    void payin(double summ);
    void payout(double summ);
    void openCashbox();        
    void beep();
protected:
    virtual bool checkError(int res);    
};

#endif
