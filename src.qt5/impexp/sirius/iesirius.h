#ifndef SIRIUS_H
#define SIRIUS_H

#include <qobject.h>
#include <QtNetwork/QTcpServer>
#include "impexp.h"

class QSocket;
class sirius;
class sServerSocket;
class impSirius;

class sServer : public ieServer
{
    Q_OBJECT
public:
    sServer(QObject * p);
    virtual bool start();
    virtual bool stop();
    virtual bool restart();
protected slots:
    void readData(QSocket * s);
private:
    sServerSocket * server;
    sirius * fSirius;    
};

class sServerSocket : public QTcpServer
{
    Q_OBJECT
public:
    sServerSocket(QObject *);
    virtual void newConnection(int socket);
public slots:	
    void setError(int);
signals:
    void newConnect();
    void endConnect();
    void readClient(QSocket*);	
private slots:
    void emitRead();
    void discardClient();
};

#define SIRIUS_OK			100
#define SIRIUS_NOTOPENED		101

class expSirius : public exporter
{
    Q_OBJECT
public:
    expSirius();
    ~expSirius();
    virtual bool open(QString host, int port);
    virtual bool open(QString) { /*TODO import from file??*/ return FALSE; };
    virtual map toMap() { return map(); };
    virtual QVariant value(QString) { return QVariant(0); };
    virtual bool fromMap(map m);
    virtual bool writeValues();
    virtual bool writeHeader(QString header);
    virtual bool writeTailer(QString tailer);
    virtual bool isOpened();
    virtual int errorCode();
    virtual QString errorMsg(int e);
    QString host();
    int port();
public slots:
    virtual bool close();    
signals:
    void error();
    void connected();
protected slots:
    void setError(int e);
    void deviceConnected();
private:
    QSocket * fSocket;
    int fError;
};

class impSirius : public expSirius
{
    Q_OBJECT
public:
    impSirius();
    virtual int count() { return fData.count(); };
    virtual bool seek(int row);
    virtual QVariant value(QString name);
    virtual map toMap();
private:
    QStringList fields;
    int fCurrent;
};

#endif
