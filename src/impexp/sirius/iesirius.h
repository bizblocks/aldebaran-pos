#ifndef SIRIUS_H
#define SIRIUS_H

#include <qobject.h>
#include <Q3ServerSocket>
#include <Q3CString>
#include "impexp.h"

class Q3Socket;
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
    void readData(Q3Socket * s);
private:
    sServerSocket * server;
    sirius * fSirius;    
};

class sServerSocket : public Q3ServerSocket
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
    void readClient(Q3Socket*);
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
    Q3Socket * fSocket;
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
