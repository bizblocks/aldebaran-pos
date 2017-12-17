#include "cts300.h"
#include "cts300printer.h"
#include "dlgcts300settings.h"

eqCTS300Printer::eqCTS300Printer(QString name) :
	eqDriver(name)
{
    fPrintWidth = 48;
    fDeviceName="/dev/null";
    printer = NULL;
}

eqCTS300Printer::~eqCTS300Printer() 
{
    printer->close();    
}

void eqCTS300Printer::init()
{
    if(printer)
    {
	printer->close();
	delete printer;
    }
    printer = new CTS300(fDeviceName);    
    printer->open();
    printer->setCodepage(fCodepage);
}

eqJob * eqCTS300Printer::createJob(QString action)
{
    return new eqCTS300Job(this, action);
}

void eqCTS300Printer::prepare()
{
}

void eqCTS300Printer::end()
{
}

void eqCTS300Printer::setOption(QString o, QVariant v)
{
    if(o=="codepage") 
    {
	if(printer) printer->setCodepage(v.toString());
	fCodepage = v.toString();
    }
    else if(o=="device") fDeviceName = v.toString();
    else if(o=="print width") fPrintWidth = v.toInt();
}

void eqCTS300Printer::print()
{
    printer->printLine(fText);
}

void eqCTS300Printer::cut()
{
    printer->cut();
}

QStringList eqCTS300Printer::options()
{
    QStringList res;
    res << "device" << "codepage" << "print width";
    return res;
}

QString eqCTS300Printer::option(QString name)
{
    if(!printer) return "";
    if(name=="device") return fDeviceName;
    else if(name=="codepage")
    {
	if(printer) return printer->codepage();
	else return fCodepage;
    }
    else if(name=="print width") return QString("%1").arg(fPrintWidth);
    return "";
}

bool eqCTS300Printer::dialog()
{
    dlgCTS300Settings * dlg = new dlgCTS300Settings();
    dlg->init(this);
    return dlg->exec();
}

QStringList eqCTS300Printer::codepages()
{
    QStringList res = "";
    if(printer) res = printer->getCodepages();
    return res;
}

eqCTS300Job::eqCTS300Job(eqDriver * device, QString action, QString data) :
	eqJob(device, action)
{
    fData = QVariant(data);
}

eqCTS300Job::~eqCTS300Job()
{
}

void eqCTS300Job::print()
{
    if(fDevice)
    {
	if(fData.type()==QVariant::String)
	{
	    eqCTS300Printer * prn = (eqCTS300Printer *)fDevice;
	    prn->setPrintText(fData.toString());
	    prn->print();
	}
	else if(fData.type()==QVariant::StringList)
	{
	    QStringList lst = fData.toStringList();
	    eqCTS300Printer * prn = (eqCTS300Printer *)fDevice;
	    for(int i=0;i<lst.count();i++)
	    {
		QString str = lst[i];
		qDebug(str.utf8());
		prn->setPrintText(QString("%1\n").arg(str).utf8());
		prn->print();	    
	    }
	}
    }
}

void eqCTS300Job::cut()
{
    if(fDevice)
    {
	eqCTS300Printer * prn = (eqCTS300Printer *)fDevice;
	prn->cut();
    }
}

