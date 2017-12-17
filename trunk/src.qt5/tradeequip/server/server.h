#ifndef ALSERVER_H
#define ALSERVER_H

#include <qapplication.h>
#include <qsocket.h>
#include <qserversocket.h>
#include <qmap.h>
#include <qvariant.h>

class alServerSocket;
class QSqlDatabase;

class alServer : public QApplication
{
Q_OBJECT
public:
    alServer(int argc, char ** argv);
    void setSocket(int socket);
public slots:
    void read();
    void errorOccured(int error);
    void backReport(int);
    
    void openDatabase();
    void driverList();    
    void openDevice();
    void deviceCommand();
    void lastError();
protected:
    void process();
signals:
    void signal();
    void done(int);
private:
    int port;
    alServerSocket * server;
    Q_UINT32 packetSize;
    QString command;
    QMap<QString, QVariant> args;
    QSqlDatabase * db;
};

class alServerSocket : public QServerSocket
{
public:
    alServerSocket();
private:    
    virtual void newConnection(int socket);
};

#endif
