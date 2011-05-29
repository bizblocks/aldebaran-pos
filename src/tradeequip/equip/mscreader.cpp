#include "mscreader.h"
#include "tereaderbarcode.h"
#include "dlgmscreader.h"

eqMSCReader::eqMSCReader(QString name) :
	eqDriver(name)
{
    reader = NULL;
    fPortDevice = "/dev/null";
    fPortBaudRate = 9600;
    fPortDataBits = DATA_8;
    fPortParity = PAR_NONE;
    fPortStopBits = STOP_1;
    fPortFlowControl = FLOW_OFF;
    fHeader = ';';
    fTrailer = '?';
}


eqMSCReader::~eqMSCReader()
{
    if(reader) 
    {
	reader->close();
	delete reader;
    }
}

void eqMSCReader::init()
{
    if(reader)
    {
	reader->close();
	delete reader;
    }
    reader = new TEReaderBarcode;
//    reader->setDebugLevel(0);
    reader->setPortDevice(fPortDevice);
    reader->setPortBaudRate(fPortBaudRate);
    reader->setPortDataBits((DataBitsType)fPortDataBits);
    reader->setPortParity((ParityType)fPortParity);
    reader->setPortStopBits((StopBitsType)fPortStopBits);
    reader->setPortFlowControl((FlowType)fPortFlowControl);
    connect(reader, SIGNAL(deviceEvent(int)), this,SLOT(onData(int)));
    fResult = reader->startDriver();
}

void eqMSCReader::onData(int ev)
{
//    if (ev==EVENT_READER_DATAARRIVED)
    {	
	QString text = "";
	if(reader)
	{
	    text = reader->text();
	    qDebug(QString("EVENT_READER_DATAARRIVED: %1").arg(text));	    
	    qDebug(QString("header is %1, trailer is %2, first char is %3").arg(fHeader).arg(fTrailer).arg(text[0]));
	    if(text[0]==fHeader) 
	    {
		text = text.mid(1);
		if(text[text.length()-1]==fTrailer) 
		{
		    text = text.left(text.length()-1);
		    emit data(1, text); //TODO replace with truck no
		}
		else if(text[text.length()-2]==fTrailer)
		{
		    text = text.left(text.length()-2);
		    emit data(1, text); //TODO replace with truck no
		}
	    }
	    reader->next();    	    
	}
    }
}

QStringList eqMSCReader::options()
{
    QStringList res;
    res << "device" << "baudrate" << "data bits" << "parity";
    res << "stopbits" << "flow control";
    res << "header" << "trailer";
    return res;
}

QString eqMSCReader::option(QString name)
{
    if(!reader) return "";
    if(name=="device") return fPortDevice;
    else if(name=="baudrate") return QString("%1").arg(fPortBaudRate);
    else if(name=="data bits") return QString("%1").arg(fPortDataBits);
    else if(name=="parity") return QString("%1").arg(fPortParity);
    else if(name=="stopbits") return QString("%1").arg(fPortStopBits);
    else if(name=="flowcontrol") return QString("%1").arg(fPortFlowControl);
    else if(name=="header") return QString("%1").arg(fHeader);    
    else if(name=="trailer") return QString("%1").arg(fTrailer);        
    return "";
}

void eqMSCReader::setOption(QString name, QVariant value)
{
    if(name=="device") fPortDevice = value.toString();
    else if(name=="baudrate") fPortBaudRate = value.toInt();
    else if(name=="data bits") fPortDataBits = value.toInt();
    else if(name=="parity") fPortParity = value.toInt();
    else if(name=="stopbits") fPortStopBits = value.toInt();
    else if(name=="flow control") fPortFlowControl = value.toInt();
    else if(name=="header") fHeader = value.toString().isEmpty() ? 0 : value.toString().ascii()[0];
    else if(name=="trailer") fTrailer = value.toString().isEmpty() ? 0 : value.toString().ascii()[0];
}

eqJob * eqMSCReader::createJob(QString action)
{
    return new eqJob(this, "");
}

bool eqMSCReader::dialog()
{
    dlgMSCReader * dlg = new dlgMSCReader();
    dlg->init(this);
    return dlg->exec();
}

QStringList eqMSCReader::supportedBaudRates()
{
    QStringList res;    
    if(!reader) return res;
    QValueList<int> lst = reader->supportedBaudRates();
    for(uint i=0;i<lst.count();i++)
	res << QString("%1").arg(lst[i]);
    return res;
}

QStringList eqMSCReader::supportedDataBits()
{
    QStringList res;
    res << "DATA_NOTSET" << "DATA_5" << "DATA_6" << "DATA_7" << "DATA_8";
    return res;
}

QStringList eqMSCReader::supportedParity()
{
    QStringList res;
    res << "PAR_NOTSET" << "PAR_NONE" << "PAR_ODD" << "PAR_EVEN" << "PAR_MARK" << "PAR_SPACE" ;    
    return res;    
}

QStringList eqMSCReader::supportedStopBits()
{
    QStringList res;
    res << "STOP_NOTSET" << "STOP_1" << "STOP_1_5" << "STOP_2";   
    return res;        
}

QStringList eqMSCReader::supportedFlowControl()
{
    QStringList res;
    res << "FLOW_NOTSET" << "FLOW_OFF" << "FLOW_HARDWARE" << "FLOW_XONXOFF";
    return res;            
}
