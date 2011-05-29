#ifndef DATADISCOUNT_H
#define DATADISCOUNT_H

#include "data.h"

class alDiscountRecord;

class alDataDiscount : public alData
{
public:
    alDataDiscount(alEngine * e);
    ~alDataDiscount();
    void import(importer * imp);    
public slots:    
    virtual alDataRecord * current();
    alDiscountRecord * newElement();
    virtual alDiscountRecord * select(Q_ULLONG uid);
    virtual bool select(const QString filter = "");
    bool delElement();
protected:
    virtual void checkTable();
    void update(impValues * values);
};

class alDiscountRecord : public alDataRecord
{
public:
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QString type READ type WRITE setType)
protected:
    alDiscountRecord(alData * data);	
    alDiscountRecord(alData * data, QSqlRecord * rec);    
    virtual void load();
public slots:
    static alDiscountRecord * newElement(alDataDiscount * data);
    static alDiscountRecord * current(alDataDiscount* data);    
    virtual int update();
    QString name() { return fName; };
    void setName(QString n) { fName = n; };
    int type() { return fType; };
    void setType(int t) { fType = t; };
    int value() { return fValue; };
    void setValue(int v) { fValue = v; };    
    void setProtect(bool p) { fProtect = p; };
    bool protect() { return fProtect; };
    QString code() { return fCode; };    
    void setCode(QString c) { fCode = c; };
    virtual bool dialog(QWidget * parent);    
private:
    QString fName, fCode;
    int fType, fValue;
    bool fProtect;
};

#endif
