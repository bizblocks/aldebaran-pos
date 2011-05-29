#include <qprocess.h>
#include <qsocket.h>
#include "engine.h"
#include "equipmentserver.h"
#include "server.h"
#include "clientserver.h"

eqServer::eqServer(alEngine * engine) :
	QObject((QObject*)engine, "equipment client")
{
    fOk = TRUE;
    serverProcess = NULL;
    serverSocket = NULL;
//TODO from settings start or connect    
    //    started();
}

eqServer::~eqServer()
{
    shutdown();    
    if(serverProcess) delete serverProcess;
}

void eqServer::start()
{
    if(serverProcess) 
    {
	connect(serverProcess, SIGNAL(processExited()), this, SLOT(restart()));
	shutdown();
	return;
    }
    serverProcess = new QProcess((const QString&)"/usr/bin/aldebaran-server", this); // TODO change to path from settings
    connect(serverProcess, SIGNAL(readyReadStdout()), this, SLOT(started()));    
    serverProcess->start();
}

void eqServer::restart()
{
    if(serverProcess)
    {
	delete serverProcess;
	serverProcess = NULL;
    }
    start();
}

void eqServer::started()
{
    disconnect(serverProcess, SIGNAL(readyReadStdout()), this, SLOT(started()));
    serverProcess->setCommunication(0);
    QString strPort = serverProcess->readLineStdout();
    ALDEBUG(tr("Equipment server binded to port %1").arg(strPort));
    int port = strPort.toInt(); // TODO or from settings
    serverSocket = new alSocket(this, 0);
    connect(serverSocket, SIGNAL(connected()), this, SLOT(connected()));    
    connect(serverSocket, SIGNAL(error(int)), this, SLOT(onSocketError(int)));
    connect(serverSocket, SIGNAL(received(alSocket *)), this, SLOT(onData(alSocket *)));
    serverSocket->connectToHost("localhost", port); //TODO change localhost with address    
}

void eqServer::shutdown()
{
    argMap args;
    args["cmd"] = "shutdown";
    serverSocket->sendMap(args);
    delete serverSocket;
    serverSocket = NULL;
}

void eqServer::connected()
{
    argMap args;
    args["cmd"] = "driverList";
    serverSocket->sendMap(args);
}

void eqServer::read()
{
}

void eqServer::sendFail()
{
    if(!serverProcess) return;    
    argMap args;
    args["cmd"] = "FAIL";
    serverSocket->sendMap(args);
}

void eqServer::_driverList()
{
}

void eqServer::onSocketError(int error)
{
    fOk = FALSE;
    ALERROR(tr("socket error %1").arg(error));
//TODO emit server error 
}

void eqServer::onData(alSocket * s)
{
    argMap args = s->map();
    if(!args["device"].toString().length()) 
    {
	ALDEBUG(args["data"].typeName());
    }
}
