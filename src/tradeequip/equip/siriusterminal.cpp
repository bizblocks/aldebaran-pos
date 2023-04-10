#include <qtimer.h>
#include <unistd.h>
#include "sirius/iesirius.h"
#include "sirius/iesiriussqlite.h"
#include "siriusterminal.h"
#include "dlgsiriussettings.h"

eqSirius::eqSirius(QString name) :
	eqDriver(name)
{
    sirius = NULL;
    port = 8096;
    table = 0;
    host = "";
    path = "";
}

eqSirius::~eqSirius()
{
    if(sirius) delete sirius;
}

void eqSirius::init()
{
    if(sirius) delete sirius;
    if(!path.length())
    {
	sirius = new expSirius();
	((expSirius*)sirius)->open(host, port);	
    }
    else
    {
	sirius = new expSiriusSQLite();
	sirius->open(path);	
    }
    connect(sirius, SIGNAL(error()), this, SLOT(checkError()));    
    connect(sirius, SIGNAL(connected()), this, SLOT(deviceConnected()));
    queue.clear();
}

void eqSirius::deviceConnected()
{
    header("S");
    map m;
    m["host"] = serverHost();
    m["port"] = serverPort();
    line(QVariant(m));
    tailer("");
    while(queue.count())
    {
	usleep(1000);
	queueElement el = queue[0];
	if(el.type=="header") header(el.data.toString());
	else if(el.type=="line") line(el.data);
	else if(el.type=="tailer") tailer(el.data.toString());
	queue.remove(queue.at(0));
    }
}

eqJob * eqSirius::createJob(QString action)
{
    return new eqSiriusJob(this, action);
}

void eqSirius::setOption(QString o, QVariant v)
{
    if(o=="host") host = v.toString();
    else if(o=="port") port = v.toInt();
    else if(o=="table") table = v.toInt();
    else if(o=="path") path = v.toString();
    else return;
}

QStringList eqSirius::options()
{
    QStringList res;
    res << "host" << "port" << "table";
    return res;
}

QString eqSirius::option(QString name)
{
    if(name=="host") return host;
    else if(name=="port") return QString("%1").arg(port);
    else if(name=="table") return QString("%1").arg(table);
    else if(name=="path") return path;
    return "";
}

void eqSirius::checkError()
{
    if(!sirius) return setError(SIRIUS_NODEVICE, tr("No device"));
    int e = sirius->errorCode();
    if(e==SIRIUS_OK) 
    {
	setError(0, sirius->errorMsg(e));
	return;
    }
    else setError(e+1, sirius->errorMsg(e));
    emit deviceError(error());
    delete sirius;
    sirius = NULL;
    //Queue reconnect
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(init()));
    timer->start(60*1000, TRUE);
}

void eqSirius::onData(importer * sirius)
{
    emit data(sirius);
}

void eqSirius::header(QString data)
{
    if(!sirius) return setError(SIRIUS_NODEVICE, tr("No device"));
    if(!sirius->isOpened())
    {
	queueElement el;
	el.type = "header";
	el.data = data;
	queue.append(el);
	return;
    }
    if(sirius->errorCode()!=SIRIUS_OK) return;
    sirius->writeHeader(data);
}

void eqSirius::line(QVariant data)
{
    if(!sirius) return setError(SIRIUS_NODEVICE, tr("No device"));        
    if(!sirius->isOpened())
    {
	queueElement el;
	el.type = "line";
	el.data = data;
	queue.append(el);
	return;
    }
    if(sirius->errorCode()!=SIRIUS_OK)
    {
	qDebug(QString("error %1").arg(sirius->errorMsg(0)));
	return;
    }
    if(!data.canCast(QVariant::Map)) return setError(SIRIUS_INVALIDARG, tr("Wrong parameter"));
    map m = data.toMap();
    sirius->fromMap(m);
}

void eqSirius::tailer(QString data)
{
    if(!sirius) return setError(SIRIUS_NODEVICE, tr("No device"));
    if(!sirius->isOpened())
    {
	queueElement el;
	el.type = "tailer";
	el.data = data;
	queue.append(el);
	return;
    }        
    if(sirius->errorCode()!=SIRIUS_OK) return;    
    if(!sirius->writeTailer(data)) return;
}

bool eqSirius::dialog()
{
    dlgSiriusSettings * dlg = new dlgSiriusSettings();
    dlg->init(this);
    return dlg->exec();
}

QString eqSirius::serverHost()
{
    return ((expSirius*)sirius)->host();
}

int eqSirius::serverPort()
{
    return ((expSirius*)sirius)->port();
}

eqSiriusJob::eqSiriusJob(eqDriver * device, QString action, QString data) :
	eqJob(device, action)
{
    fData = QVariant(data);
}

eqSiriusJob::~eqSiriusJob()
{    
}

void eqSiriusJob::connect()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->init();
	setError(s->error(), s->errorMsg());
    }    
}

void eqSiriusJob::line()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->line(fData);
	setError(s->error(), s->errorMsg());	
    }
}

void eqSiriusJob::goodsStart()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->header("G");
	setError(s->error(), s->errorMsg());
    }
}

void eqSiriusJob::goodsEnd()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->tailer("");
	setError(s->error(), s->errorMsg());	
    }    
}

void eqSiriusJob::elementStart()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->header("E");
	setError(s->error(), s->errorMsg());
    }
}

void eqSiriusJob::elementEnd()
{
    goodsEnd();
}

void eqSiriusJob::resetDevice()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->header("R");
	s->tailer("");
	setError(s->error(), s->errorMsg());
    }    
}

void eqSiriusJob::haltDevice()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->header("H");
	s->tailer("");
	setError(s->error(), s->errorMsg());
    }    
}

void eqSiriusJob::updateDevice()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->header("U");
	s->tailer("");
	setError(s->error(), s->errorMsg());
    }    
}

void eqSiriusJob::orderStart()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->header("O");
	s->line(fData);
	setError(s->error(), s->errorMsg());
    }
}

void eqSiriusJob::orderEnd()
{
    if(fDevice)
    {
	eqSirius * s = (eqSirius *)fDevice;
	s->tailer("");
	setError(s->error(), s->errorMsg());	
    }    
}
