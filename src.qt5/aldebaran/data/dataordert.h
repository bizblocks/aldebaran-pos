#ifndef DATAORDERT_H
#define DATAORDERT_H

#include <QVariant>
#include <qstring.h>
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
    ULLID orderId() { if(fOrder) return fOrder->id(); return -1; }
    int count();
    virtual bool select();
    alOrderLine * getLine(int row);
    alOrderLine * newLine();
    bool delLine(int r);
    double total(QString attr);
    alOrderRecord * order() { return fOrder; }
protected:
    virtual bool checkTable();
    virtual QSqlIndex defaultSort();    
private:
    alOrderRecord * fOrder;
    QList<alOrderLine*> lines;
};

typedef alUserRecord * pUserRecord;
typedef alGoodsRecord * pGoodsRecord;

class alOrderLine : QObject
{
    Q_OBJECT
    Q_PROPERTY(ULLID id READ order)
    Q_PROPERTY(int lineNum READ lineNum)
    Q_PROPERTY(pGoodsRecord item READ item WRITE setItem)
    Q_PROPERTY(QString externalCode READ externalCode WRITE setExternalCode)
    Q_PROPERTY(double amount READ amount WRITE setAmount)
    Q_PROPERTY(double price READ price WRITE setPrice)
    Q_PROPERTY(double summ READ summ WRITE setSumm)
    Q_PROPERTY(pUserRecord user READ user WRITE setUser)
public:
    alOrderLine(alDataOrderTable * data);
public slots:
    static alOrderLine * newLine(alDataOrderTable * data);
    void recalc();
    ULLID order() const { return fOrderID; }
    int lineNum() const { return fLineNum; }
    pGoodsRecord item() const {return fItem; }
    QString itemText() { return fItemText; }
    void setItem(pGoodsRecord item);
    QString externalCode() const { return fExternalCode; }
    void setExternalCode(const QString& ex) { fExternalCode = ex; }
    double price() const { return fPrice; }
    void setPrice(double p) { fPrice = p; }
    double amount() const { return fAmount; }
    void setAmount(double p) { fAmount = p; recalc();}
    double summ() const { return fSumm; }
    void setSumm(double p) { fSumm = p; }
    pUserRecord user() const {return fUser; }
    void setUser(pUserRecord u) { fUser = u; }
    bool printed() { return fPrinted; }
    void setPrinted(bool p) { fPrinted = p; }
    QVariant value(QString attr) { return property(attr.toLatin1().data()); }
private:
    alDataOrderTable * fData;
    ULLID fOrderID;
    int fLineNum;
    alGoodsRecord * fItem;
    QString fExternalCode;
    QString fItemText;
    double fAmount, fPrice, fSumm;
    pUserRecord fUser;
    bool fPrinted;
};

#endif
