#ifndef DATAEQ_H
#define DATAEQ_H

#include <QMap>
#include "data.h"

class alEqRecord;

class alDataEq : public alData
{
public:
    alDataEq(alEngine * e);
    ~alDataEq();
public slots:    
    virtual alDataRecord* current();
    alEqRecord * newElement();
    bool delElement();    
protected:
    virtual void checkTable();
};

class alEqRecord : public alDataRecord
{
public:
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QString type READ type WRITE setType)
protected:
    alEqRecord(alData * data);	
    alEqRecord(alData * data, QSqlRecord * rec);    
    virtual void load();
public slots:
    static alEqRecord * newElement(alDataEq * data);
    static alEqRecord * current(alDataEq * data);    
    virtual int update();
    QString name() { return fName; };
    void setName(QString n) { fName = n; };
    QString type() { return fType; };
    void setType(QString t) { fType = t; };
    bool enabled() { return fEnabled; };
    void setEnabled(bool e) { fEnabled = e; };
    void setOption(QString n, QString v);
    QStringList options();    
    QString option(QString n);
    virtual bool dialog(QWidget * parent);    
private:
    QString fType, fName;
    QMap<QString, QString> fOptions;
    bool fEnabled;
};

#endif
