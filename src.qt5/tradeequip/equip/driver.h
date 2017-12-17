#ifndef DRIVER_H
#define DRIVER_H

#include <qobject.h>
#include "worker.h"

class eqDriver : public QObject
{
    Q_OBJECT
public:
    eqDriver(QString name) : QObject(NULL) { setObjectName(name); setError(0, ""); }
    virtual void init()=0;    
    virtual eqJob * createJob(QString action="") = 0;    
    virtual void prepare() = 0;
    virtual void end() = 0;
    virtual void setOption(QString name, QVariant value) = 0;
    virtual QStringList options() = 0;
    virtual QString option(QString name) = 0;
    virtual bool dialog() = 0;
    virtual int error() { int e = fError; fError = 0; return e; }
    virtual QString errorMsg() { QString e = fErrorMsg; fErrorMsg = ""; return e; }
    virtual QVariant result() { return fResult; }
signals:
    void deviceError(int);
protected:
    void setError(int error, QString errorMsg) { fError = error; fErrorMsg = errorMsg; }
    QString fAction, fErrorMsg;
    QVariant fResult;
    int fError;
};

class eqDummyDriver : public eqDriver
{
public:
    eqDummyDriver(QString name) : eqDriver(name) {}
    eqDummyDriver() : eqDriver("dummyDriver") {}
public:
    virtual void init() { /*do nothing*/ }
    virtual eqJob * createJob(QString action="") { fAction = action; return NULL; }
    virtual void prepare() {}
    virtual void end() {}
    virtual void setOption(QString option, QVariant value) { Q_UNUSED(option); Q_UNUSED(value); }
    virtual QStringList options() { return QStringList(); }
    virtual QString option(QString name) { Q_UNUSED(name); return ""; }
    virtual bool dialog() { return FALSE; }
};

#endif
