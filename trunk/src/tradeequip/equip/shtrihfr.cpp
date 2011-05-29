#include "shtrih-fr.h"
#include "shtrihfr.h"
#include "dlgshtrihsettings.h"

eqShtrihFR::eqShtrihFR(const QString& name) :
	eqFR(name)
{    
}

eqShtrihFR::~eqShtrihFR()
{
}

void eqShtrihFR::init()
{
    eqFR::init();
    device = new ShtrihFR(fPortDevice, 0);
    device->setDebugLevel(0);
    device->setPassword(ShtrihFR::PTOperator, operatorPassword);
    device->setPassword(ShtrihFR::PTAdmin, adminPassword);
    device->setPortBaudRate(fPortBaudRate);
    device->setPortDataBits((DataBitsType)fPortDataBits);
    device->setPortParity((ParityType)fPortParity);
    device->setPortStopBits((StopBitsType)fPortStopBits);
    device->setPortFlowControl((FlowType)fPortFlowControl);
    checkError(device->open());    
}

void eqShtrihFR::print(QString line)
{
    fError = 0;
    if(!device) return;
    QStringList lines = QStringList::split("\n", QString::fromUtf8(line), TRUE);
    for(uint l=0;l<lines.count();l++)
    {
	if(checkError(((ShtrihFR*)device)->internalPrintLine(lines[l].utf8(), TRUE, FALSE))) break;
    }
}

void eqShtrihFR::cut()
{
    fError = 0;    
    if(!device) return;    
    checkError(((ShtrihFR*)device)->internalCutCheck(1));    
}

void eqShtrihFR::openCheck(int oper)
{
    fError = 0;    
    if(!device) return;
    cancelCheck();
    if(checkError(device->openCheck())) return;
    if(checkError(device->setOperation(oper))) return;
}

void eqShtrihFR::cancelCheck()
{
    fError = 0;    
    if(!device) return;
    if(checkError(device->cancelCheck(0))) return;
}

double eqShtrihFR::closeCheck(TItem param)
{
    fError = 0;    
    if(!device) return 0;
    ShtrihFR::Decimal change;
    if(checkError(device->setPayment(param["summ"].toDouble(), param["summType"].toInt()))) return 0;
    if(checkError(device->closeCheck(change, 0))) return 0;
    return change;
}

void eqShtrihFR::openCashbox()
{
    fError = 0;    
    if(!device) return;    
    if(checkError(((ShtrihFR*)device)->openCashbox(0))) return;
}

void eqShtrihFR::addItem(TItem item)
{
    fError = 0;        
    if(!device) return;
    double price = item["price"].toDouble();
    double amount = item["amount"].toDouble();
    qDebug(QString("amount: %1").arg(item["amount"].toString()));
    if(item["discount"].toDouble()!=0.) 
    {
	if(checkError(device->setDiscount(item["discount"].toDouble()))) return;
    }
    else
    {
	if(checkError(device->setDiscountPercent(item["discountPercent"].toDouble()))) return;	
    }
    
    if(checkError(device->setItem(item["name"].toString().utf8(), price, amount))) return;	    
}

void eqShtrihFR::ZReport()
{
    fError = 0;        
    if(!device) return;
    if(checkError(((ShtrihFR*)device)->ZReport())) return;
}

void eqShtrihFR::XReport()
{
    fError = 0;
    if(!device) return;    
    if(checkError(((ShtrihFR*)device)->XReport())) return;
}

void eqShtrihFR::payin(double summ)
{
    fError = 0;    
    if(!device) return;    
    if(checkError(device->payingin(summ))) return;
}

void eqShtrihFR::payout(double summ)
{
    fError = 0;        
    if(!device) return;
    if(checkError(device->payment(summ))) return;
}

void eqShtrihFR::beep()
{
    fError = 0;    
    if(!device) return;
    if(checkError(((ShtrihFR*)device)->internalRing())) return;
}

bool eqShtrihFR::dialog()
{    
    dlgShtrihSettings * dlg = new dlgShtrihSettings();
    dlg->init(this);
    return dlg->exec();
}

QStringList eqShtrihFR::options()
{
    QStringList res = eqFR::options();
    res << "print width";
    return res;
}

bool eqShtrihFR::checkError(int res)
{
    bool ret = eqFR::checkError(res);
    fError = ((ShtrihFR*)device)->deviceError();
    fErrorMsg = ((ShtrihFR*)device)->devErrorText(fError);
    return ret;
}
