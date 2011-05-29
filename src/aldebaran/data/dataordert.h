#ifndef DATAORDERT_H
#define DATAORDERT_H

#include "dataorder.h"

class alEngine;
class alUserRecord;
class alGoodsRecord;
class alOrderRecord;
class alOrderLine;

class alDataOrderTable : public alData
{
protected:
    alDataOrderTable(alEngine  * engine, alOrderRecord * order);
    QString updateQuery();
    friend class alOrderRecord;    
public:    
    Q_ULLONG orderId() { if(fOrder) return fOrder->id(); return -1; };
    int count();
    virtual bool select();
    alOrderLine * getLine(int row);
    alOrderLine * newLine();
    bool delLine(int r);
    double total(QString attr);
    alOrderRecord * order() { return fOrder; };
protected:
    virtual void checkTable();
    virtual QSqlIndex defaultSort();    
private:
    alOrderRecord * fOrder;
    QValueList<alOrderLine*> lines;
};

typedef alUserRecord * pUserRecord;

class alOrderLine : QObject
{
    Q_OBJECT
    Q_PROPERTY(Q_ULLONG id READ order)
    Q_PROPERTY(int lineNum READ lineNum)
    Q_PROPERTY(Q_ULLONG item READ item WRITE setItem)
    Q_PROPERTY(double amount READ amount WRITE setAmount)
    Q_PROPERTY(double price READ price WRITE setPrice)
    Q_PROPERTY(double summ READ summ WRITE setSumm)
    Q_PROPERTY(pUserRecord user READ user WRITE setUser)
public:
    alOrderLine(alDataOrderTable * data);
public slots:
    static alOrderLine * newLine(alDataOrderTable * data);
    void recalc();
    Q_ULLONG order() const { return fOrderID; };
    int lineNum() const { return fLineNum; };
    alGoodsRecord * item() const {return fItem; };
    QString itemText() { return fItemText; };
    void setItem(alGoodsRecord * item);
    double price() const { return fPrice; };
    void setPrice(double p) { fPrice = p; };
    double amount() const { return fAmount; };
    void setAmount(double p) { fAmount = p; recalc();};
    double summ() const { return fSumm; };
    void setSumm(double p) { fSumm = p; };
    pUserRecord user() const {return fUser; };
    void setUser(pUserRecord u) { fUser = u; };
    bool printed() { return fPrinted; };
    void setPrinted(bool p) { fPrinted = p; };
    QVariant value(QString attr) { return property(attr); };
private:
    alDataOrderTable * fData;
    Q_ULLONG fOrderID;
    int fLineNum;
//TODO replace with alGoodsRecord (no data)
    alGoodsRecord * fItem;
    QString fItemText;
    double fAmount, fPrice, fSumm;
    pUserRecord fUser;
    bool fPrinted;
};

#endif
