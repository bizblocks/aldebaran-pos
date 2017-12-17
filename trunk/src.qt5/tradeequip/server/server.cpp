#include <iostream>
#include <qsqldatabase.h>
#include <qmetaobject.h>
#include "server.h"
#include "errors.h"

alServer::alServer(int argc, char ** argv) :
	QApplication(argc, argv, FALSE)
{
    db = NULL;
    packetSize = 0;
    server = new alServerSocket();
    port = -1;
    if(server->ok()) port = server->port();    
    if(port!=-1)
    {
	std::cout << port << std::endl;
	connect(this, SIGNAL(done(int)), this, SLOT(backReport(int)));
    }
    else exit();
}

void alServer::setSocket(int socket)
{
    packetSize = 0;
    command = "";
    QSocket * s = new QSocket(this);
    connect(s, SIGNAL(readyRead()), this, SLOT(read()));
    connect(s, SIGNAL(error(int)), this, SLOT(errorOccured(int)));
    s->setSocket(socket);
}

void alServer::errorOccured(int error)
{
    exit(error);
}

void alServer::read()
{
    QSocket * s = (QSocket*)sender();
    Q_ULONG bytesAvail = s->bytesAvailable();
    for ( ;; ) 
    {
	if ( packetSize == 0 ) 
	{
	    if ( bytesAvail < 4 ) return;	    
	    QDataStream ds(s);
	    ds >> packetSize;
	    bytesAvail -= 4;
	} 
	else 
	{
	    if (bytesAvail < packetSize) return;
	    QByteArray ba( packetSize );
	    s->readBlock( ba.data(), packetSize );
	    bytesAvail -= packetSize;
	    packetSize = 0;

	    QVariant variant;
	    QDataStream ds( ba, IO_ReadOnly );
	    ds >> variant;
	    switch ( variant.type() ) 
	    {
	    case QVariant::String:
		command = QString(SLOT(%1())).arg(variant.toString());
		qDebug(command);
		break;
	    case QVariant::Map:
		args = variant.toMap();
		break;
	    default:
		break;
	    }
	}
    }    
}

void alServer::process()
{
    QMetaObject *rmeta = this->metaObject();
    int member_index = rmeta->findSlot( command, TRUE );
    if(member_index<0)
    {
	emit done(ERRNOSUCHCMD);
	return;
    }
    connect(this, SIGNAL(signal()), this, command);
    emit signal();
    disconnect(this, SIGNAL(signal()), this, command);
}

void alServer::openDatabase()
{
    int res = ERRNOERROR;
    if(!db) 
    {
	db = QSqlDatabase::addDatabase(args["driver"].toString());
	if(!db) res = ERRDRIVER;
	else
	{
	    db->setDatabaseName(args["name"].toString());
	    db->setHostName(args["host"].toString());
	    db->setPort(args["port"].toInt());
	    db->setUserName(args["user"].toString());
	    db->setPassword(args["password"].toString());
	    if(!db->open()) res = ERRDBOPEN;
	}
    }
    else res = ERRDBOPENED;
    emit done(res);
}

void alServer::lastError()
{
    args.clear();
    int res = ERRNOERROR;
    if(db)
    {
	if(db->lastError().type()!=QSqlError::None)
	{
	    res = db->lastError().number();
	    args["errorText"] = db->lastError().text();
	    emit done(res);
	    return;
	}
    }
    //another errors    
}

void alServer::backReport(int error)
{
    Q_UNUSED(error);
}

alServerSocket::alServerSocket() :
	QServerSocket(0, 1)
{
}

void alServerSocket::newConnection (int socket)
{
    alServer * app = (alServer*)qApp;
    app->setSocket(socket);
}

int main(int argc, char** argv)
{
    alServer * server = new alServer(argc, argv);
    return server->exec();
}
