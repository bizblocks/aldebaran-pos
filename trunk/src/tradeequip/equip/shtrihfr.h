#ifndef SHTRIHFR_H
#define SHTRIHFR_H

#include "driver.h"
#include "fr.h"

class ShtrihFR;
typedef eqFRJob eqShtrihFRJob;

class eqShtrihFR : public eqFR
{
    Q_OBJECT
public:
    eqShtrihFR(const QString& name);
    virtual ~eqShtrihFR();
    virtual void init();    
    virtual QStringList options();
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
