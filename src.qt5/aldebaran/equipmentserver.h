#ifndef EQUIPMENTSERVER_H
#define EQUIPMENTSERVER_H

#include <qobject.h>
#include <qvariant.h>

class QProcess;
class QSocket;
class alEngine;
class alSocket;

class eqServer : public QObject
{
    Q_OBJECT
public:    
    eqServer(alEngine * engine);
    ~eqServer();
    
    bool ok() { return fOk; };
    QStringList driverList();
public slots:
    void start();
    void restart();
    void shutdown();
protected slots:
    void connected();
    void sendFail();
    void started();
    void read();
    
    void _driverList();
protected slots:
    void onSocketError(int);
    void onData(alSocket *);
signals:
    void send();
    void data();
    void signal();
private:
    bool fOk;
    alSocket * serverSocket;
    QProcess * serverProcess;
    QStringList fDriverList;
};

#endif
