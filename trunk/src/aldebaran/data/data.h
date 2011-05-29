#ifndef DATA_H
#define DATA_H

#include <qsqlcursor.h>
#include <qsqlrecord.h>
#include "queries.h"

class alEngine;
class alDataRecord;

class alData : public QSqlCursor
{
public:
    alData(alEngine * e, QString table);
    alData(const alData & other);
    ~alData();
    Q_ULLONG uid();
    virtual alDataRecord * current();
    virtual int update(Q_ULLONG id, bool invalidate = TRUE);        
    alEngine * engine() { return fEngine; };
    QString tableName() {return fTableName; };
    virtual bool select(const QString filter = "");
    QString lastErrorMsg() { return lastError().text(); };
protected:
    alEngine * fEngine;    
    virtual void checkTable() = 0;
    virtual QSqlIndex defaultSort();
private:
    QString fTableName;
};

class alDataRecord : public QObject
{
    Q_OBJECT
protected:
    alDataRecord(alData * data);
    alDataRecord(alData * data, QSqlRecord * rec);    
    virtual void primeUpdateInsert();
public slots:
    bool isNew() { return fIsNew; };
    static alDataRecord * current(alData * data);
    virtual int update();    
    virtual void load();
    Q_ULLONG id() { return fId; };
    virtual bool dialog(QWidget * parent);
protected:
    alData * fData;
    Q_ULLONG fId;
    QSqlRecord * fRecord;
    bool fIsNew;
};

#ifdef UTF8_CONV
#define UTF8(str) (str).utf8()
#else
#define UTF8(str) (str)
#endif

#endif
