/****************************************************************************
** $Id: tebase.cpp,v 1.11 2006/07/04 06:07:07 red75 Exp $
**
** Trade equipment common portable library project
**
** Copyright (C) 1999-2006 Leader InfoTech.  All rights reserved.
**
** This file is part of the Library of the Ananas
** automation accounting system.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.leaderit.ru/ or email sales@leaderit.ru
**
** Contact org@leaderit.ru if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

/*
    Abstract trade equipment object.
   (c) V.Grazdankin, 1999-2005
*/
#ifndef TEBASE_CPP
#define TEBASE_CPP
#include <qsocket.h>
#include <qsocketdevice.h> 
#include "tebase.h"
#include <tserialport.h>
#include <stdarg.h>

/*!
    \class TEBase tebase.h
    \brief The TEBase is base class for all trade equipment classes.

    Abstract trade equipment object.
    Object have internal text command interpreter
    that give access to object functions.
    \param cmd (in) command text. Command format: <function> '(' <parm1> ',' <parm2> ',' ... <parmN> ')'
    \return - command execution result.
*/


/*!
 * Abstract trade equipment object.
 * Object have internal text command interpreter
 * that give access to object functions.
 * \param cmd (in) command text. Command format: <function> '(' <parm1> ',' <parm2> ',' ... <parmN> ')'
 * \return - command execution result.
 */
TEBase::TEBase( int pname )
{
	init(0);
}

TEBase::TEBase( QString device )
{
	init(0, device);
}

void TEBase::init(int pn, QString device)
{
    m_ee.addFuncBinding1<TEBase,int,int>(
        this, &TEBase::setPortNumber, "setPortNumber");
    m_ee.addFuncBinding0<TEBase,int, ConstFunc0<TEBase,int> >(
        this, &TEBase::portNumber, "portNumber");
    m_ee.addFuncBinding1<TEBase,int,QString>(
        this, &TEBase::setPortDevice, "setPortDevice");
    m_ee.addFuncBinding0<TEBase,QString, ConstFunc0<TEBase,QString> >(
        this, &TEBase::portDevice, "portDevice");        
    m_ee.addProcBinding1<TEBase,int>(
        this,&TEBase::setPollInterval,"setPollInterval");
    m_ee.addFuncBinding0<TEBase,int>(
        this,&TEBase::pollInterval,"pollInterval");
    m_ee.addFuncBinding0<TEBase,QString, ConstFunc0<TEBase,QString> >(this,&TEBase::activationKey,"activationKey");
//    addFuncBinding(m_ee,this,&TEBase::activationKey,"activationKey");
    m_ee.addProcBinding1<TEBase,const QString &>(
        this,&TEBase::setActivationKey,"setActivationKey");
    m_ee.addFuncBinding0<TEBase,int>(
        this,&TEBase::isActivationKeyValid,"isActivationKeyValid");
    m_ee.addFuncBinding0<TEBase,int>(
        this,&TEBase::open,"open");
    m_ee.addFuncBinding0<TEBase,int>(
        this,&TEBase::close,"close");
    m_ee.addProcBinding1<TEBase,int>(
        this,&TEBase::setDebugLevel,"setDebugLevel");
    m_ee.addProcBinding1<TEBase,bool>(
        this,&TEBase::startPoll,"startPoll");
    m_ee.addProcBinding0<TEBase>(
        this,&TEBase::stopPoll,"stopPoll");

    clearPPP();

    vPortNumber = pn;
    vPortDevice = device;
    vDebugLevel = 0;
    vTimeout = 150;
    vTimeoutFlag = false;
    m_eConnectionType = ECT_SERIAL;
    Port = new TSerialPort();
    Socket = new QSocketDevice();
}

/*!
*/
TEBase::~TEBase()
{
//    close();
    delete Port;
}


int
TEBase::setConnectionType( int ct )
{
    switch (ct) 
    {
    case ECT_SERIAL: case ECT_KEYBOARD: case ECT_TCP:
	m_eConnectionType = ct;
	break;
    default:
	setErrorText(tr("Unknown connection type."));
	return 1;
	break;
    }
    return 0;
}


int
TEBase::connectionType()
{
    return m_eConnectionType;
}


int
TEBase::setPortNumber( int pn )
{
    bool o = isOpen();
    if ( o ) o = close();
    vPortNumber = pn;
    if ( o ) o = open();
    return o;
}

int
TEBase::portNumber() const
{
    return vPortNumber;
}

int TEBase::setPortDevice(QString device)
{
    if(device.left(2).upper()="IP")
    {
	setConnectionType(ECT_TCP);
	device = device.mid(2);
    }
    bool o = isOpen();
    if(o) o = close();
    vPortDevice = device;
    if(o) o = open();
    return o;
}

QString TEBase::portDevice() const
{
    return vPortDevice;    
}

int TEBase::serialOpen()
{
    QString pname;
#ifdef Q_OS_WIN32
    pname=QString("COM%1:").arg( portNumber() );
#else
    pname=QString("%1").arg( portDevice() );
#endif    
    Port->setName( pname );
    if (!Port->open())
    {
	setErrorText(tr("Cannot open serial port '%1'.").arg(pname));
	return 0;
    }
    if (m_iPBaudRate!=0)
        Port->setCustomBaudRate((Q_ULONG)m_iPBaudRate);
    if (m_PFlow!=FLOW_NOTSET)
        Port->setFlowControl(m_PFlow);
    if (m_PParity!=PAR_NOTSET)
        Port->setParity(m_PParity);
    if (m_PDataBits!=DATA_NOTSET)
        Port->setDataBits(m_PDataBits);
    if (m_PStopBits!=STOP_NOTSET)
        Port->setStopBits(m_PStopBits);
    Port->setTimeout(0,(unsigned long)vTimeout);
    return 1;    
}

/*
int TEBase::waitConnection()
{
    for(int i=0;i<10;i++)
    {
	QSocket::State state = Socket->state();
	if(state!=QSocket::Connecting)
	    return state==QSocket::Connected ? 1 : 0;
	usleep(100000);
    }
    return 0;
}
*/

int TEBase::tcpOpen()
{
    QStringList addr = QStringList::split(':', portDevice());
    QHostAddress hostaddr;
    hostaddr.setAddress(addr[0]);
    QDEBUG(QString("IP address: %1 port: %2").arg(hostaddr.toString()).arg(addr[1].toUInt()));
    if(!Socket->connect(hostaddr, addr[1].toUInt()))
    {
	QDEBUG(QString("connection error: %1").arg(Socket->error()));
	return 0;
    }
    return 1;
}

int
TEBase::open()
{
    int res = 0;
    switch(m_eConnectionType)
    {
    case ECT_SERIAL:
	res = serialOpen();
	break;
    case ECT_TCP:
	res = tcpOpen();
	break;
    }
    return res;
}

int
TEBase::close()
{
    if (Port->isOpen())
	Port->close();
    if(Socket->isOpen())
	Socket->close();
    return 1;
}


/*!
Check comunication port connection.
*/
int
TEBase::isOpen()
{
    int res = 0;
    switch(m_eConnectionType)
    {
    case ECT_SERIAL:
	return Port->isOpen();
    case ECT_TCP:
	return false;//Socket->state() & IO_Open;
    }
}


int
TEBase::timeout()
{
    return vTimeout;
}

void
TEBase::setTimeout( int timeout )
{
    vTimeout = timeout;
    port()->setTimeout(0,(unsigned long)timeout);
}



int
TEBase::pollInterval()
{
    return vPollInterval;
}



void
TEBase::setPollInterval( int pint )
{
    vPollInterval = pint;
}


bool
TEBase::isTimeout()
{
    return vTimeoutFlag;
}


int
TEBase::debugLevel()
{
    return vDebugLevel;
}

void
TEBase::setDebugLevel( int level )
{
    vDebugLevel = level;
}


/*!
Put character
*/
int
TEBase::putch( int b )
{        
    int res = -1;
    switch(m_eConnectionType)
    {
    case ECT_SERIAL:
	res=Port->putch( b );
	break;
    case ECT_TCP:
	res = Socket->putch(b)==b ? 0 : 1;
	break;
    default:
	break;
    }
#ifdef DEBUG
    if ( vDebugLevel ){
	    printf(">%02X ", b & 0xff );
    	    fflush(stdout);
	}
#endif
    return res;
}


/*!
Get character.
*/
int
TEBase::getch()
{
//    int t = vTimeout;
//    vTimeoutFlag = true;
//    while ( readCount()<=0 && (t--)>0) Sleep(1);
//    if (readCount()>0)
//    {
    int res = -1;    
    switch(m_eConnectionType)
    {
    case ECT_SERIAL:
	res=Port->getch();
	vTimeoutFlag = res==-1;	
	break;
    case ECT_TCP:
	Socket->waitForMore(vTimeout, &vTimeoutFlag);
	if(vTimeoutFlag) break;
	res=Socket->getch();
	break;
    default:
	break;
    }        
//    }
//    else
//        i=-1;
#ifdef DEBUG
    if ( vDebugLevel )
    {
	if (res==-1) printf("<XX "); 
	else printf("<%02X ", res & 0xff );
	fflush(stdout);
    }
#endif
    return res;
}


/*!
Write data block to device.
*/
Q_ULONG
TEBase::writeBlock( const char *data, Q_ULONG len )
{
    Q_ULONG i;
#ifdef DEBUG
    if ( vDebugLevel ) printf("\n-");
#endif
    for (i=0;i<len; i++) {
        putch( data[i] );
    }
    return i;
}


/*!
Read data block from device.
*/
Q_ULONG
TEBase::readBlock( char *data, Q_ULONG maxlen )
{
    Q_ULONG offs=0;
    int b = -1;
#ifdef DEBUG
    if ( vDebugLevel ) printf("\n-");
#endif
//  if ( readCount()< maxlen )
    while (offs< maxlen ) {
        b = getch() & 0xff;
        if ( isTimeout() ) break;
        //  if ( b<0 ) break;
        data[offs] = (char)b; // & 0xff;
        offs++;
    }
    return offs;
}


Q_ULONG
TEBase::readCount()
{
    int c = 0;
    switch(m_eConnectionType)
    {
    case ECT_SERIAL:
	c = Port->bytesWaiting();
	break;
    case ECT_TCP:
	c = Socket->bytesAvailable();
	break;
    default:
	break;
    }
    if ( c < 0 ) c = 0;
    return (Q_ULONG)c;
}


/*!
.
*/
void
TEBase::startPoll(  int PollInterval, bool defaultProc )
{
    if ( defaultProc ) connect( this, SIGNAL( deviceEvent( int ) ), SLOT( processEvent( int ) ) );
    startTimer( PollInterval );
}




/*!
.
*/
void
TEBase::startPoll( bool defaultProc )
{
    startPoll( pollInterval(), defaultProc );
}



/*!
.
*/
void
TEBase::stopPoll()
{
    killTimers();
}


/*!
*/
void
TEBase::processEvent( int )
{
}


/*!
*/
int
TEBase::poll()
{
    return 0;
}


/*!
Poll device on timer event.
*/
void
TEBase::timerEvent( QTimerEvent * )
{
    poll();
}


/*!
Return pointer to device serial port object.
*/
TSerialPort *
TEBase::port()
{
    return Port;
}


/*!
 * Execute command.
 * Object have internal text command interpreter
 * that give access to object functions.
 * \param cmd (in) command text. Command format: <function> '(' <parm1> ',' <parm2> ',' ... <parmN> ')'
 * \return - command execution result.
 */
QStringList
TEBase::execCommand( const QString &cmd )
{
//    Q_UNUSED( cmd )
    QStringList l;
    int res=m_ee.execute(cmd);
    if (res)
        l << QString("999;\"")+m_ee.error()+QString("\"");
    else
    {
        l << "0;\"Ok\"";
        l << m_ee.result();
    };
    return l;
}


QCString
TEBase::utf8ToDevice( const QString &text )
{
    return ( const char *) text;
}

QString
TEBase::deviceToUtf8( const QCString &text )
{
    return text;
}


void
TEBase::startIOTransaction()
{
}


void
TEBase::stopIOTransaction()
{
}

QString
TEBase::activationKey() const
{
    return vActivationKey;
}

void
TEBase::setActivationKey( const QString &key )
{
    vActivationKey = key;
    isActivationKeyValid();
}

int
TEBase::isActivationKeyValid()
{
    return 1;
}

void TEBase::setPortBaudRate(int iBaudRate)
{
    m_iPBaudRate=iBaudRate;
    if (m_iPBaudRate!=0 && Port->isOpen())
        Port->setCustomBaudRate((Q_ULONG)m_iPBaudRate);
}

void TEBase::setPortFlowControl(FlowType PFlow)
{
    m_PFlow=PFlow;
    if (m_PFlow!=FLOW_NOTSET && Port->isOpen())
        Port->setFlowControl(m_PFlow);
}

void TEBase::setPortParity(ParityType PPar)
{
    m_PParity=PPar;
    if (m_PParity!=PAR_NOTSET && Port->isOpen())
        Port->setParity(m_PParity);
}

void TEBase::setPortDataBits(DataBitsType PDB)
{
    m_PDataBits=PDB;
    if (m_PDataBits!=DATA_NOTSET && Port->isOpen())
        Port->setDataBits(m_PDataBits);
}

void TEBase::setPortStopBits(StopBitsType PSB)
{
    m_PStopBits=PSB;
    if (m_PStopBits!=STOP_NOTSET && Port->isOpen())
        Port->setStopBits(m_PStopBits);
}

void TEBase::clearPPP()
{
    m_iPBaudRate=0;
    m_PFlow=FLOW_NOTSET;
    m_PParity=PAR_NOTSET;
    m_PDataBits=DATA_NOTSET;
    m_PStopBits=STOP_NOTSET;
}

QValueList<int> TEBase::supportedBaudRates()
{
  QValueList<int> ret;
  
  return ret;
}

#endif // TEBASE_CPP
