#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../aldebaran.h"
#include "queries.h"

class alEngine;
class alDataRecord;


class alData : public QSqlQuery
{
public:
    alData(alEngine * e, QString table);
    alData(const alData & other);
    ~alData();
    ULLID uid();
    virtual alDataRecord * current();
    virtual int update(ULLID id, bool invalidate = TRUE);
    alEngine * engine() { return fEngine; };
    QString tableName() {return fTableName; };
    virtual bool select(const QString filter = "");
    QString lastErrorMsg() { return lastError().text(); };
protected:
    alEngine * fEngine;    
    virtual bool checkTable(const QString& tname="");
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
    bool isNew() { return fIsNew; }
    static alDataRecord * current(alData * data);
    virtual int update();    
    virtual void load();
    ULLID id() { return fId; }
    virtual bool dialog(QWidget * parent);
protected:
    alData * fData;
    ULLID fId;
    QSqlRecord * fRecord;
    bool fIsNew;
};

#ifdef UTF8_CONV
#define UTF8(str) (str).utf8()
#else
#define UTF8(str) (str)
#endif

#endif
