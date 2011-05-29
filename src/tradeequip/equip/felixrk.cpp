#include "felixrk.h"
#include "felix-rk.h"
#include "dlgfelixsettings.h"

eqFelixRK::eqFelixRK(const QString& name) :
	eqFR(name)
{
}

eqFelixRK::~eqFelixRK()
{
}

void eqFelixRK::init()
{
    eqFR::init();
    device = new FelixRK(fPortDevice, 0);
    device->setDebugLevel(0);
    device->setPassword(FelixRK::PTAccess, accessPassword);
    device->setPassword(FelixRK::PTOperator, operatorPassword);
    device->setPassword(FelixRK::PTAdmin, adminPassword);
    device->setPortBaudRate(fPortBaudRate);
    device->setPortDataBits((DataBitsType)fPortDataBits);
    device->setPortParity((ParityType)fPortParity);
    device->setPortStopBits((StopBitsType)fPortStopBits);
    device->setPortFlowControl((FlowType)fPortFlowControl);
    checkError(device->open());
}

void eqFelixRK::print(QString line)
{
    fError = 0;
    if(!device) return;
    QStringList lines = QStringList::split("\n", QString::fromUtf8(line), TRUE);
    for(uint l=0;l<lines.count();l++)
    {
	if(checkError(((FelixRK*)device)->internalPrintLine(lines[l].utf8()))) break;
    }
}

void eqFelixRK::cut()
{
    fResult = 0;
    fError = 0;
}

void eqFelixRK::openCheck(int oper)
{
    fError = 0;    
    if(!device) return;
    cancelCheck();
    if(checkError(device->openCheck())) return;
    if(checkError(device->setOperation(oper))) return;
}

void eqFelixRK::cancelCheck()
{
    fError = 0;    
    if(!device) return;
    if(checkError(device->cancelCheck(0))) return;
}

double eqFelixRK::closeCheck(TItem param)
{
    fError = 0;    
    if(!device) return 0;
    FelixRK::Decimal change;
    if(checkError(device->setPayment(param["summ"].toDouble(), param["summType"].toInt()))) return 0;
    if(checkError(device->closeCheck(change, 0))) return 0;
    return change;
}

void eqFelixRK::openCashbox()
{
    fError = 0;    
    if(!device) return;    
    if(checkError(((FelixRK*)device)->openCashbox(0))) return;
}

void eqFelixRK::addItem(TItem item)
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

void eqFelixRK::ZReport()
{
    fError = 0;        
    if(!device) return;
    if(checkError(((FelixRK*)device)->ZReport())) return;
}

void eqFelixRK::XReport()
{
    fError = 0;
    if(!device) return;    
    if(checkError(((FelixRK*)device)->XReport())) return;
}

void eqFelixRK::payin(double summ)
{
    fError = 0;    
    if(!device) return;    
    if(checkError(device->payingin(summ))) return;
}

void eqFelixRK::payout(double summ)
{
    fError = 0;        
    if(!device) return;
    if(checkError(device->payment(summ))) return;
}

void eqFelixRK::beep()
{
    fError = 0;    
    if(!device) return;
    if(checkError(((FelixRK*)device)->internalRing())) return;
}

bool eqFelixRK::dialog()
{
    
    dlgFelixSettings * dlg = new dlgFelixSettings();
    dlg->init(this);
    return dlg->exec();
}

QString eqFelixRK::option(QString name)
{
    if(!device) return "";
    QString res = eqFR::option(name);
    if(name=="print width") return QString("%1").arg(((FelixRK*)device)->getMaxPrint());
    return res;
}

QStringList eqFelixRK::options()
{
    QStringList res = eqFR::options();
    res << "print width";
    return res;
}

bool eqFelixRK::checkError(int res)
{
    bool ret = eqFR::checkError(res);
    fError = ((FelixRK*)device)->deviceError();
    fErrorMsg = ((FelixRK*)device)->devErrorText(fError);
    return ret;
}
