#include <qtimer.h>
#include "virtualmart.h"
#include "ui_dlgvmsettings.h"
#include "dlgvmsettings.ui.h"

eqVirtualMart::eqVirtualMart(QString name) :
    eqDriver(name)
{
    vMart = NULL;
    port = 3306;
    host = "127.0.0.1";
    db = "";
}

eqVirtualMart::~eqVirtualMart()
{
    if(vMart) delete vMart;
}

void eqVirtualMart::init()
{
    if(vMart) delete vMart;
    vMart = new impVMart();
    vMart->setTable(table);
    connect(vMart, SIGNAL(error()), this, SLOT(checkError()));
    connect(vMart, SIGNAL(connected()), this, SLOT(deviceConnected()));
    connect(vMart, SIGNAL(error()), this, SLOT(checkError()));
    vMart->open(host, port, db, login, password, prefix);
    queue.clear();
}

eqJob * eqVirtualMart::createJob(QString action)
{
    return new eqVMJob(this, action);
}

void eqVirtualMart::setOption(QString o, QVariant v)
{
    if(o=="host") host = v.toString();
    else if(o=="port") port = v.toInt();
    else if(o=="db") db = v.toString();
    else if(o=="login") login = v.toString();
    else if(o=="password") password = v.toString();
    else if(o=="table") table = v.toInt();
    else if(o=="prefix") prefix = v.toString();
}

QStringList eqVirtualMart::options()
{
    QStringList res;
    res << "host" << "port" << "db" << "login" << "password" << "prefix" << "table";
    return res;
}

QString eqVirtualMart::option(QString name)
{
    if(name=="host") return host;
    else if(name=="port") return QString("%1").arg(port);
    else if(name=="db") return QString("%1").arg(db);
    else if(name=="login") return QString("%1").arg(login);
    else if(name=="table") return QString("%1").arg(table);
    else if(name=="prefix") return QString("%1").arg(prefix);
    else if(name=="password") return QString("%1").arg(password);
    return "";
}

void eqVirtualMart::deviceConnected()
{
    connect(vMart, SIGNAL(hasData()), this, SLOT(onData()));
}

void eqVirtualMart::onData()
{
    emit data(vMart);
}

void eqVirtualMart::checkError()
{
    if(!vMart) return setError(VMART_NODEVICE, tr("No device"));
    int e = vMart->errorCode();
    if(e==VMART_OK)
    {
        setError(0, vMart->errorMsg(e));
        return;
    }
    else setError(e+1, vMart->errorMsg(e));
    emit deviceError(error());
    delete vMart;
    vMart = NULL;
    //Queue reconnect
    QTimer::singleShot(60*1000, this, SLOT(init()));
}

void eqVirtualMart::header(QVariant data)
{
    if(!vMart) return setError(VMART_NODEVICE, tr("No device"));
    if(!vMart->isOpened())
    {
        queueElement el;
        el.type = "header";
        el.data = data;
        queue.append(el);
        return;
    }
    if(vMart->errorCode()!=VMART_OK) return;
    vMart->writeHeader(data);
}

void eqVirtualMart::line(QVariant data)
{
    if(!vMart) return setError(VMART_NODEVICE, tr("No device"));
    if(!vMart->isOpened())
    {
        queueElement el;
        el.type = "line";
        el.data = data;
        queue.append(el);
        return;
    }
    if(vMart->errorCode()!=VMART_OK) return;
    if(!data.canCast(QVariant::Map)) return setError(VMART_INVALIDARG, tr("Wrong parameter"));
    map m = data.toMap();
    //TODO ??
    if(!vMart->fromMap(m))
    {
        ;
    }
}

void eqVirtualMart::tailer(QString data)
{
    if(!vMart) return setError(VMART_NODEVICE, tr("No device"));
    if(!vMart->isOpened())
    {
        queueElement el;
        el.type = "tailer";
        el.data = data;
        queue.append(el);
        return;
    }
    if(vMart->errorCode()!=VMART_OK) return;
    if(!vMart->writeTailer(data)) return;
}

bool eqVirtualMart::dialog()
{
    dlgVMSettings * dlg = new dlgVMSettings();
    dlg->init(this);
    return dlg->exec();
}

QString eqVirtualMart::serverHost()
{
    return vMart->host();
}

int eqVirtualMart::serverPort()
{
    return vMart->port();
}

eqVMJob::eqVMJob(eqDriver * device, QString action, QString data) :
    eqJob(device, action)
{
    fData = QVariant(data);
}

eqVMJob::~eqVMJob()
{    
}

void eqVMJob::connect()
{
    if(fDevice)
    {
        eqVirtualMart * s = (eqVirtualMart *)fDevice;
        s->init();
        setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::line()
{
    if(fDevice)
    {
        eqVirtualMart * s = (eqVirtualMart *)fDevice;
        s->line(fData);
        setError(s->error(), s->errorMsg());
    }
}

/*void eqVMJob::goodsStart()
{
    if(fDevice)
    {
    eqVirtualMart * s = (eqVirtualMart *)fDevice;
    s->header("G");
    setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::goodsEnd()
{
    if(fDevice)
    {
    eqVirtualMart * s = (eqVirtualMart *)fDevice;
    s->tailer("");
    setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::elementStart()
{
    if(fDevice)
    {
    eqVirtualMart * s = (eqVirtualMart *)fDevice;
    s->header("E");
    setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::elementEnd()
{
    goodsEnd();
}

void eqVMJob::resetDevice()
{
    if(fDevice)
    {
    eqVirtualMart * s = (eqVirtualMart *)fDevice;
    s->header("R");
    s->tailer("");
    setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::haltDevice()
{
    if(fDevice)
    {
    eqVirtualMart * s = (eqVirtualMart *)fDevice;
    s->header("H");
    s->tailer("");
    setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::updateDevice()
{
    if(fDevice)
    {
    eqVirtualMart * s = (eqVirtualMart *)fDevice;
    s->header("U");
    s->tailer("");
    setError(s->error(), s->errorMsg());
    }
}*/

void eqVMJob::orderStart()
{
    if(fDevice)
    {
        eqVirtualMart * s = (eqVirtualMart *)fDevice;
        s->header(fData);
        setError(s->error(), s->errorMsg());
    }
}

void eqVMJob::orderEnd()
{
    if(fDevice)
    {
        eqVirtualMart * s = (eqVirtualMart *)fDevice;
        s->tailer("");
        setError(s->error(), s->errorMsg());
    }
}
