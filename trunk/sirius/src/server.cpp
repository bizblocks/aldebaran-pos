#include <unistd.h>
#include <qfile.h>
#include "sirius.h"
#include "server.h"

sServer::sServer(sirius * s) :
	QObject(s)
{
	fSirius = s;
	fIsRunning = FALSE;
	server = NULL;
}

bool sServer::start()
{
	if(isRunning()) stop();
	server = new sServerSocket(this);	
	fIsRunning = server->ok();
	if(isRunning())
	{
		cmd = 0;
		fields = 0;
		size = 0;
		tab.clear();
		line.clear();
		connect(server, SIGNAL(readClient(QSocket*)), this, SLOT(readData(QSocket*)));
	}
	return isRunning();
}

bool sServer::stop()
{
	if(isRunning() && server)
	{
		fIsRunning = FALSE;
		delete server;
		server = NULL;
		if(cmd) fSirius->import(cmd, tab);
		cmd = 0;
		fields = 0;
		size = 0;		
		return TRUE;
	}
	return FALSE;
}

bool sServer::abort()
{
	qDebug("abort");
	line.clear();
	tab.clear();
	cmd = 0;		
	stop();
	return start();
}

bool sServer::restart()
{
	if(isRunning())
	{
		sImportTable tmpTab(tab);
		int tmpCmd = cmd;
		cmd = 0;
		fields = 0;
		size = 0;		
		tab.clear();
		line.clear();		
		if(tmpCmd) fSirius->import(tmpCmd, tmpTab);
		return TRUE;
	}
	return FALSE;
}

void sServer::readData(QSocket * s)
{	
	badLine = FALSE;
	Q_INT32 bytesAvail = s->bytesAvailable();
	for(;;)
	{
		if(cmd<1)
		{	
			if(bytesAvail<1) return;
			cmd = s->getch();
			if(cmd==-1)
			{
				bytesAvail = s->waitForMore(1000);
				continue;
			}
			bytesAvail--;
		}
		else if(fields<1)
		{
			if(bytesAvail<1) return;		
			fields = s->getch();
			if(fields==-1)
			{
				bytesAvail = s->waitForMore(1000);
				continue;			
			}
			else if(fields==255)
			{
				fields = s->getch();
				bytesAvail--;
				if(fields==255) restart();
				else
				{	
					abort();
					return;
				}
			}
			else if(fields==0)
			{
				abort();
				return;
			}
			bytesAvail--;			
		}
	    else if(size<1)
	    {
	    	if((uint)bytesAvail<sizeof(size)) return;
			QDataStream ds(s);
			ds >> size;
			bytesAvail -= sizeof(size);
		}
		else
		{
			if(bytesAvail<size) return;
			// read the packet in a byte array to be sure that you don't
			// read too much or too less
			sImportValue value;
			value.asArray = QByteArray(size);
			s->readBlock(value.asArray.data(), size);
			bytesAvail -= size;
			size = 0;

			QDataStream ds(value.asArray, IO_ReadOnly);
			value.asVariant = QVariant(ds);// >> variant;
			line.append(value);
			if(line.count()==(uint)fields)
			{
				fields = 0;
				tab.append(line);
				line.clear();
			}
		}
	}	
}

sServerSocket::sServerSocket(QObject * parent) :
	QServerSocket(8096, 1, parent)
{
}

void sServerSocket::newConnection(int socket)
{
	QSocket * s = new QSocket(this);
	connect(s, SIGNAL(readyRead()), this, SLOT(emitRead()));
	connect(s, SIGNAL(delayedCloseFinished()), this, SLOT(discardClient()));
	connect(s, SIGNAL(error(int)), this, SLOT(setError(int)));
	s->setSocket(socket);
	emit newConnect();	
}

void sServerSocket::discardClient()
{
	QSocket* socket = (QSocket*)sender();
	delete socket;
	emit endConnect();
}

void sServerSocket::emitRead()
{
	QSocket * s = (QSocket*)sender();
	if(s->bytesAvailable())
	{
		emit readClient(s);
	}
}

void sServerSocket::setError(int e)
{
	qDebug(QString("%1").arg(e));
}

exporter::exporter() :
	QObject(NULL, "exporter")
{
    fSocket = NULL;
    setError(SIRIUS_OK);
}

exporter::~exporter()
{    
    if(fSocket)
    {
	delete fSocket;    
    }
}

bool exporter::open(QString host, int port)
{
    if(fSocket) delete fSocket;
    setError(SIRIUS_OK);
    fSocket = new QSocket(this);
    connect(fSocket, SIGNAL(error(int)), this, SLOT(setError(int)));    
    connect(fSocket, SIGNAL(connected()), this, SLOT(deviceConnected()));    
    fSocket->connectToHost(host, port);
    qDebug(QString("connecting to %1:%2").arg(host).arg(port));
    headerWritten = FALSE;
    return TRUE;
}

void exporter::deviceConnected()
{
	while(queue.count())
	{
		queueElement el = queue[0];
		if(el.type=="writeHeader") writeHeader(el.varData.toString());
		else if(el.type=="fromMap") fromMap(el.data);
		else if(el.type=="writeTailer") writeTailer(el.varData.toString());
		queue.remove(queue.at(0));
	}
}

bool exporter::writeHeader(QString header)
{
    if(!fSocket) return FALSE;
    if(headerWritten) return FALSE;    
    if(fSocket->state()==QSocket::Connecting)
    {
		queueElement el;
		el.type = "writeHeader";
		el.varData = header;
		queue.append(el);
		return TRUE;
    }
    else if (fSocket->state()==QSocket::Idle) return FALSE;
    Q_INT32 bWritten = fSocket->writeBlock(header.ascii(), strlen(header.ascii()));
    headerWritten = bWritten!=-1;
    emit(start());
    return headerWritten;
}

bool exporter::fromMap(sExportLine m)
{
    if(!fSocket) return FALSE;
    if(fSocket->state()==QSocket::Connecting)
    {
		queueElement el;
		el.type = "fromMap";
		el.data = m;
		queue.append(el);
		return TRUE;
    }
    else if (fSocket->state()==QSocket::Idle) return FALSE;    
    if(!headerWritten) return FALSE;
    fSocket->putch((char)m.count());

    for(uint i=0;i<m.count();i++)
    {
		QByteArray a;
		QDataStream stream(a, IO_WriteOnly);
		stream << m[i];
		if(!a.size())
		{
	    	a.resize(1);
	    	a.fill(0);
		}
		QDataStream socketStream(fSocket);
		socketStream << (Q_UINT32)a.size();
		fSocket->writeBlock(a.data(), a.size());
		emit(step(i));
    }    
    fSocket->flush();
    return TRUE;
}

bool exporter::writeTailer(QString)
{
	if(!fSocket) return FALSE;
	if(fSocket->state()==QSocket::Connecting)
    {
		queueElement el;
		el.type = "writeTailer";
		el.varData = "";
		queue.append(el);
		return TRUE;
    }
    else if (fSocket->state()==QSocket::Idle) return FALSE;

    if(!headerWritten) return FALSE;
    for(unsigned char c=0;c<sizeof(Q_UINT16);c++)
    {
		int op = fSocket->putch(255);
		if(op==-1) return FALSE;
    }
    fSocket->flush();
    headerWritten = FALSE;
    emit(finish());
    return TRUE;
}

int exporter::errorCode()
{
    if(!fSocket) return SIRIUS_NOTOPENED;
    int e = fError;
    setError(SIRIUS_OK);
    return e;
}

QString exporter::errorMsg(int e)
{
    QString res = "";
    switch(e)
    {
		case SIRIUS_OK: res = QObject::tr("No Error"); break;
		case SIRIUS_NOTOPENED: res = QObject::tr("Connection isn't opened"); break;
		case QSocket::ErrConnectionRefused: res = QObject::tr("Connection refused"); break;
		case QSocket::ErrHostNotFound: res = QObject::tr("Host not found"); break;
		default: res = QObject::tr("I/O error"); break;
    };
    return res;
}

void exporter::setError(int e)
{
	fError = e;
	if(e!=SIRIUS_OK)
	{
	    emit(error());
		qDebug(QString("there is error %1").arg(fError));
	}    
}
