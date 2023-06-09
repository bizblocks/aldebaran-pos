//one more correction
#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "alsqltablemodel.h"
#include "../aldebaran.h"
#include "queries.h"

class QSqlRecord;

class alEngine;
class alDataRecord;

class alData : public alSqlTableModel
{
public:
    alData(alEngine * e, QString table);
    alData(const alData & other);
    ~alData();
    ULLID uid();
    int currentRow() const { return fCurrentRow; }
    virtual alDataRecord * current();
//    virtual int update(ULLID id, bool invalidate = TRUE);
    virtual int update();
    alEngine * engine() { return (alEngine*)parent(); }
    QObject * parent() { return fParent; }
    virtual bool select(const QString filter = "");
    QString lastErrorMsg() { return lastError().text(); }

    QVariant value(const QString& fld);

    bool first();
    bool next();
    bool seek(int row);

    QSqlRecord * primeInsert();
    QSqlRecord * primeUpdate();
    bool insert();
protected:
    virtual bool checkTable(const QString& tname="");
    virtual QSqlIndex defaultSort();
private:
    QObject * fParent;
    int fCurrentRow;
    QSqlRecord * fRecord;
};

class alDataRecord : public QObject
{
    Q_OBJECT
public:
    ~alDataRecord();
protected:
    alDataRecord(alData * data);
    alDataRecord(alData * data, QSqlRecord * rec);
    virtual void primeUpdateInsert();
public slots:
    bool isNew() { return fIsNew; }
    static alDataRecord * current(alData *);
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
