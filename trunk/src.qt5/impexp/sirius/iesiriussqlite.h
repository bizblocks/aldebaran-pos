#ifndef  SQLITESIRIUS_H
#define SQLITESIRIUS_H

#include <qobject.h>
#include "impexp.h"

class sData;

class expSiriusSQLite : public exporter
{
    Q_OBJECT
public:
    expSiriusSQLite();
    ~expSiriusSQLite();
    virtual bool open(QString path);
    virtual map toMap() { return map(); };
    virtual QVariant value(QString) { return QVariant(0); };
    virtual bool fromMap(map m);
    virtual bool writeValues();
    virtual bool writeHeader(QString) { return true; };
    virtual bool writeTailer(QString);
    virtual bool isOpened() { return fDb; };
    virtual bool close();
    virtual int errorCode();
    virtual QString errorMsg(int e);
        
signals:
    void error();
    void connected();
private:
    sData * fDb;
    QString fPath;
};

#endif
