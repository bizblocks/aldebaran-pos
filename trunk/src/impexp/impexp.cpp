#include <qobject.h>
#include <qtextcodec.h>
#include "impexp.h"
#include "ieshtrih.h"
#include "sirius/iesirius.h" 
#include "sirius/iesiriussqlite.h" 
#include "ievmart.h" 
#include "iecsv.h"

importer::importer() 
{
    fCurrent = -1; 
    lines.clear();    
    fCodec = QTextCodec::codecForName("UTF-8");
}

QStringList importer::importersList()
{
    QStringList lst;
    lst << tr("Shtrih-M");
    lst << tr("Sirius");
    lst << tr("CSV");
    return lst;
}

importer * importer::createImporter(QString name)
{
    importer * res = NULL;
    if(name==tr("Shtrih-M")) res = new impShtrihM();
    else if(name==tr("Sirius")) res = new impSirius();
    else if(name==tr("CSV")) res = new impCSV();    
    else if(name==tr("VirtualMart")) res = new impVMart();
    return res;
}

void importer::setCodepage(QString cp)
{
    if(cp.isEmpty())
	cp = "UTF-8";
    fCodepage = cp;
    fCodec = QTextCodec::codecForName(fCodepage);
}

exporter::exporter() : 
	importer()
{
}

exporter::~exporter()
{
}

exporter * exporter::createExporter(QString name)
{
    if(name==QObject::tr("Shtrih-M")) return (exporter*)(new expShtrihM());
    else if(name==QObject::tr("Sirius")) return new expSirius();
    else if(name==QObject::tr("SiriusSQLite")) return new expSiriusSQLite();
    return NULL;
}

QStringList exporter::exportersList()
{
    QStringList lst;
    lst << QObject::tr("Sirius");
    lst << QObject::tr("Shtrih-M");    
    return lst;    
}

bool exporter::setValue(QString name, QVariant value)
{
    values[name] = value;
    return TRUE;
}

ieServer::ieServer(QObject * p) :
	QObject(p)
{
    fIsRunning = FALSE;
    fImporter = NULL;
}

ieServer::~ieServer()
{
    if(fImporter) delete fImporter;
}

bool ieServer::start()
{    
    cmd = 0;
    fields = 0;
    size = 0;
    tab.clear();
    line.clear();
    fIsRunning = TRUE;
    return isRunning();
}

bool ieServer::stop()
{
    if(isRunning())
    {
	fIsRunning = FALSE;
	if(cmd) 
	{
	    fImporter->setCmd(cmd);
	    fImporter->setData(tab);	    
	    emit hasData(fImporter);
	    delete fImporter;
	}
	return TRUE;
    }
    return FALSE;
}

bool ieServer::abort()
{
    line.clear();
    tab.clear();		
    stop();
    return start();
}

bool ieServer::restart()
{
    if(isRunning())
    {
	impValues tmpTab(tab);
	int tmpCmd = cmd;
	cmd = 0;
	fields = 0;
	size = 0;		
	tab.clear();
	line.clear();		
	if(tmpCmd && fImporter)
	{
	    fImporter->setCmd(tmpCmd);
	    fImporter->setData(tmpTab);	    
	    emit hasData(fImporter);
	    delete fImporter;
	}
	fImporter = NULL;
	return TRUE;
    }
    return FALSE;
}
