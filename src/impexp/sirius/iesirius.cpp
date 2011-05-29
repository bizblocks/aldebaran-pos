#include <qsocket.h>
#include "iesirius.h"

sServer::sServer(QObject * p) :
	ieServer(p)
{
    server = NULL;
}

bool sServer::start()
{
    ieServer::start();
    server = new sServerSocket(this);	
    fIsRunning = server->ok();
    if(isRunning())
    {
	connect(server, SIGNAL(readClient(QSocket*)), this, SLOT(readData(QSocket*)));
    }
    return isRunning();
}

bool sServer::stop()
{
    impSirius * sirius = (impSirius*)importer::createImporter(tr("Sirius"));    
    fImporter = sirius;
    return ieServer::stop();
}

bool sServer::restart()
{
    impSirius * sirius = (impSirius*)importer::createImporter(tr("Sirius"));
    fImporter = sirius;
    return ieServer::restart();
}

void sServer::readData(QSocket * s)
{    
    Q_UINT32 bytesAvail = s->bytesAvailable();
    for(;;) 
    {
	if(cmd<1)
	{	
	    if(bytesAvail<1) return;		
	    cmd = s->getch();
	    if(cmd>-1) bytesAvail--;
	    else return;			
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
	    if (bytesAvail<sizeof(size)) return;
	    QDataStream ds(s);
	    ds >> size;
	    bytesAvail -= sizeof(size);
	    if(size==0) 
	    {
		restart();
		return;
	    }
	}
	else
	{
	    if (bytesAvail<size) return;
	    QByteArray ba(size);
	    s->readBlock(ba.data(), size);
	    bytesAvail -= size;
	    size = 0;
	    
	    QDataStream ds(ba, IO_ReadOnly);
	    QVariant variant = QVariant(ds);
	    line[QString("%1").arg(line.count())] = variant;
	    if(line.count()==(uint)fields)
	    {
		fields = 0;
		tab[QString("%1").arg(tab.count())] = line;
		line.clear();
	    }
	}
    }
}

sServerSocket::sServerSocket(QObject * parent) :
	QServerSocket(8100, 1, parent)
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

expSirius::expSirius() :
	exporter()
{
    fSocket = NULL;
    setError(SIRIUS_OK);
    fields.clear();
    fields << "id" << "parent" << "isgroup" << "name" << "description" << "picture" << "price";
}

expSirius::~expSirius()
{    
    close();
}

bool expSirius::open(QString host, int port)
{
    if(fSocket) delete fSocket;
    setError(SIRIUS_OK);
    fSocket = new QSocket(this);
    connect(fSocket, SIGNAL(error(int)), this, SLOT(setError(int)));    
    connect(fSocket, SIGNAL(connected()), this, SLOT(deviceConnected()));    
    fSocket->connectToHost(host, port);
    headerWritten = FALSE;
    return TRUE;
}

bool expSirius::close()
{
    if(fSocket)
    {
	fSocket->clearPendingData();
	fSocket->close();
	delete fSocket;    
	fSocket = NULL;
	return TRUE;
    }
    return FALSE;
}

void expSirius::deviceConnected()
{
    setError(SIRIUS_OK);
    emit connected();
}

bool expSirius::writeHeader(QString header)
{
    if(!fSocket) return FALSE;
    int st = fSocket->state();
    if(st!=QSocket::Connected) return FALSE;
    if(headerWritten) return FALSE;
    Q_LONG bWritten = fSocket->writeBlock(header.ascii(), strlen(header.ascii()));
    headerWritten = bWritten!=-1;
    return headerWritten;
}

bool expSirius::fromMap(map m)
{
    
    if(!fSocket) return FALSE;
    int st = fSocket->state();    
    if(st!=QSocket::Connected) return FALSE;
    if(!headerWritten) return FALSE;
    fSocket->putch((char)m.count());
    for(uint i=0;i<m.count();i++)
    {
	QByteArray a;
	QDataStream stream(a, IO_WriteOnly);
	stream << m[m.keys()[i]];
	if(!a.size())
	{
	    a = QByteArray(1);
	    a.fill(0);
	}
	QDataStream socketStream(fSocket);
	socketStream << (Q_UINT32)a.size();
	fSocket->writeBlock(a.data(), a.size());
    }
    fSocket->flush();
    return TRUE;
}

bool expSirius::writeTailer(QString tailer)
{
    if(!fSocket) return FALSE;
    int st = fSocket->state();    
    if(st!=QSocket::Connected) return FALSE;
    if(!headerWritten) return FALSE;
    int op = 0;
    if(strlen(tailer.ascii())) op = fSocket->writeBlock(tailer.ascii(), strlen(tailer.ascii()));
    if(op==-1) return FALSE;
    op = fSocket->putch(255);
    if(op==-1) return FALSE;    
    op = fSocket->putch(255);
    if(op==-1) return FALSE;    
    fSocket->flush();    
    headerWritten = FALSE;
    return TRUE;
}

int expSirius::errorCode()
{
    if(!fSocket) return SIRIUS_NOTOPENED;
    int e = fError;
    setError(SIRIUS_OK);
    return e;
}

QString expSirius::errorMsg(int e)
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

void expSirius::setError(int e)
{
    fError = e;
    if(e!=SIRIUS_OK) emit(error());
}

bool expSirius::writeValues()
{
    return fromMap(values);
}

QString expSirius::host()
{
    if(!fSocket) return "127.0.0.1";
    return fSocket->address().toString();
}

int expSirius::port()
{
    return 8100;
}

bool expSirius::isOpened()
{
    if(!fSocket) return FALSE;
    return fSocket->state()==QSocket::Connected;
}

impSirius::impSirius() :
	expSirius()
{
    setName("Sirius");
    fCmd = 0;
    fCurrent = -1;
    fields.clear();
}

bool impSirius::seek(int row)
{
    if(row<0 || (uint)row>=fData.count()) return FALSE;
    fields.clear();
    if(fCmd=='O')
    {
	if(!row) fields << "id" << "date" << "time" << "status" << "id_client" << "guests" << "table";
	else fields << "id_goods" << "amount" << "price" << "sum" << "printed";	
    }
    else if(fCmd=='W')
    {
    	fields << "table";
    }
    fCurrent = row;
    return TRUE;
}

QVariant impSirius::value(QString name)
{
    if(fCurrent<0 || (uint)fCurrent>=fData.count()) return QVariant();
    int index = fields.findIndex(name);
    if(index<0) return QVariant();
    return fData[QString("%1").arg(fCurrent)][QString("%2").arg(index)];
}

map impSirius::toMap()
{
    map res;
    if(fCurrent<0 || (uint)fCurrent>=fData.count()) return res;
    for(uint index=0;index<fields.count();index++)
	res[fields[index]] = fData[fData.keys()[fCurrent]][QString("%1").arg(index)];    
    return res;
}
