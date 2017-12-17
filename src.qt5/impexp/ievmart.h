#ifndef IEVMART_H
#define IEVMART_H

#include <qobject.h>
#include <QtNetwork/QTcpServer>
#include "impexp.h"

class QSqlDatabase;
/*class sirius;
class sServerSocket;
class impSirius;*/
class QTimer;

#define VMART_OK				100
#define VMART_NOTOPENED			101
#define VMART_SQLDRIVERNOTAVAILABLE	102

class expVMart : public exporter
{
    Q_OBJECT
public:
    expVMart();
    ~expVMart();
    void setTable(int table) { fTable = table; };
    virtual bool open(QString host, int port, QString db, QString user, QString pass, QString prefix);
    virtual bool open(QString) { /*TODO import from file??*/ return FALSE; };
    virtual map toMap() { return map(); };
    virtual QVariant value(QString) { return QVariant(0); };
    virtual bool fromMap(map) { return FALSE; };
    virtual bool writeValues();
    virtual bool writeHeader(QString) { return FALSE; };
    virtual bool writeHeader(QVariant header);
    virtual bool writeTailer(QString tailer);
    virtual bool isOpened();
    virtual int errorCode();
    virtual QString errorMsg(int e);
    QString host();
    int port();
signals:
    void error();
    void connected();
protected slots:
    void setError(int e);
protected:
    QSqlDatabase * fDb;
    QString fPrefix, fDbName;
    int fTable;
private:
    int fError;
};

class impVMart : public expVMart
{
    Q_OBJECT
public:
    impVMart();    
    virtual bool open(QString host, int port, QString db, QString user, QString pass, QString prefix);
    virtual int count() { return fData.count(); };
    virtual bool seek(int row);
    virtual QVariant value(QString name);
    virtual map toMap();
signals:
    void hasData();
public slots:
    virtual bool close();    
    void checkNewOrder();    
private:
/*    QStringList fields;
    int fCmd;
    impValues fData;
    int fCurrent;*/
    QString fOrderId;
    QString fUserId;
    QTimer * timer;
};

#endif
