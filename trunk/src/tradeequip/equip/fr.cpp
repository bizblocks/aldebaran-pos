#include "teglobal.h"
#include "tecashregisterbase.h"
#include "fr.h"
#include "dlgecrsettings.h"

eqFR::eqFR(const QString& name) :
	eqDriver(name)
{
    fDriver = "";
    device = NULL;    
    fPortDevice = "/dev/null";
    accessPassword = "0";
    operatorPassword = "30";
    adminPassword = "30";
    fPortBaudRate = 115200;
    fPortDataBits = DATA_8;
    fPortParity = PAR_NONE;
    fPortStopBits = STOP_1;
    fPortFlowControl = FLOW_OFF;
}

eqFR::~eqFR()
{
    if(device) 
    {
	device->close();
	delete device;
    }
}

void eqFR::init()
{
    if(device)
    {
	device->close();
	delete device;
	device = NULL;
    }    
    if(!te_driverExists("TECashRegister"+fDriver)) 
	return;
    device = (TECashRegisterBase *) te_createDriverObject("TECashRegister"+fDriver);
#ifdef DEBUG
    if(device)
	qDebug(QString("Device %1 created").arg(fDriver));
    else
	qDebug(QString("Error of device creation %1").arg(fDriver));
    device->setDebugLevel(1);
#endif
//    device->setPassword(FelixRK::PTAccess, accessPassword);
//    device->setPassword(FelixRK::PTOperator, operatorPassword);
//    device->setPassword(FelixRK::PTAdmin, adminPassword);
    device->setPortDevice(fPortDevice);
    device->setPortBaudRate(fPortBaudRate);
    device->setPortDataBits((DataBitsType)fPortDataBits);
    device->setPortParity((ParityType)fPortParity);
    device->setPortStopBits((StopBitsType)fPortStopBits);
    device->setPortFlowControl((FlowType)fPortFlowControl);
}

QStringList eqFR::options()
{
    QStringList res;
    res << "driver" << "device" << "access password";
    res << "operator password" << "administartor password";    
    res << "baudrate" << "data bits" << "parity";
    res << "stopbits" << "flow control";
    return res;
}

QStringList eqFR::driverList()
{
    return te_drivers("TECashRegisterBase");
}

void eqFR::setOption(QString name, QVariant value)
{
    if(name=="device") fPortDevice = value.toString();
    else if(name=="driver") fDriver = value.toString();
    else if(name=="access password") accessPassword = value.toString();    
    else if(name=="operator password") operatorPassword = value.toString();
    else if(name=="administrator password") adminPassword = value.toString();
    else if(name=="baudrate") fPortBaudRate = value.toInt();
    else if(name=="data bits") fPortDataBits = value.toInt();
    else if(name=="parity") fPortParity = value.toInt();
    else if(name=="stopbits") fPortStopBits = value.toInt();
    else if(name=="flow control") fPortFlowControl = value.toInt();
}

QString eqFR::option(QString name)
{
    if(name=="device") return fPortDevice;
    else if(name=="driver") return fDriver;    
    else if(name=="access password") return accessPassword;
    else if(name=="operator password") return operatorPassword;
    else if(name=="administrator password") return adminPassword;
    else if(name=="baudrate") return QString("%1").arg(fPortBaudRate);
    else if(name=="data bits") return QString("%1").arg(fPortDataBits);
    else if(name=="parity") return QString("%1").arg(fPortParity);
    else if(name=="stopbits") return QString("%1").arg(fPortStopBits);
    else if(name=="flow control") return QString("%1").arg(fPortFlowControl);
    return "";
}

void eqFR::print(QString line)
{
    if(!device) return;    
    checkError(device->print(line));
}

void eqFR::cut()
{
    if(!device) return;    
    checkError(device->cut());    
}

void eqFR::openCheck(int oper)
{
    fError = 0;    
    if(!device) return;
    cancelCheck();
    if(checkError(device->openCheck())) return;
    checkError(device->setOperation(oper));
}

void eqFR::cancelCheck()
{
    fError = 0;    
    if(!device) return;
    checkError(device->cancelCheck(0));
}

double eqFR::closeCheck(TItem param)
{
    fError = 0;    
    if(!device) return 0;
    TECashRegisterBase::Decimal change;
    if(checkError(device->setPayment(param["summ"].toDouble(), param["summType"].toInt()))) return 0;
    if(checkError(device->closeCheck(change, 0))) return 0;
    return change;
}

void eqFR::addItem(TItem item)
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

void eqFR::ZReport()
{
    fError = 0;        
    if(!device) return;
    checkError(device->ZReport());
}

void eqFR::XReport()
{
    fError = 0;
    if(!device) return;    
    checkError(device->XReport());
}

void eqFR::payin(double summ)
{
    fError = 0;    
    if(!device) return;    
    checkError(device->payingin(summ));
}

void eqFR::payout(double summ)
{
    fError = 0;        
    if(!device) return;
    checkError(device->payment(summ));
}

void eqFR::openCashbox()
{
    fError = 0;    
    if(!device) return;    
    checkError(device->openCashbox(0));
}

void eqFR::beep()
{
    fError = 0;    
    if(!device) return;
    checkError(device->beep());
}

bool eqFR::dialog()
{    
    dlgECRSettings * dlg = new dlgECRSettings();
    dlg->init(this);
    return dlg->exec();
}


eqJob * eqFR::createJob(QString action)
{
    return new eqFRJob(this, action);
}

void eqFR::prepare()
{
}

void eqFR::end()
{
}

QStringList eqFR::supportedBaudRates()
{
    QStringList res;    
    if(!device) return res;
    QValueList<int> lst = device->supportedBaudRates();
    for(uint i=0;i<lst.count();i++)
	res << QString("%1").arg(lst[i]);
    return res;
}

QStringList eqFR::supportedDataBits()
{
    QStringList res;
    res << "DATA_NOTSET" << "DATA_5" << "DATA_6" << "DATA_7" << "DATA_8";
    return res;
}

QStringList eqFR::supportedParity()
{
    QStringList res;
    res << "PAR_NOTSET" << "PAR_NONE" << "PAR_ODD" << "PAR_EVEN" << "PAR_MARK" << "PAR_SPACE" ;    
    return res;    
}

QStringList eqFR::supportedStopBits()
{
    QStringList res;
    res << "STOP_NOTSET" << "STOP_1" << "STOP_1_5" << "STOP_2";   
    return res;        
}

QStringList eqFR::supportedFlowControl()
{
    QStringList res;
    res << "FLOW_NOTSET" << "FLOW_OFF" << "FLOW_HARDWARE" << "FLOW_XONXOFF";
    return res;            
}

bool eqFR::checkError(int res)
{
    fResult = res;
    fError = device->errorCode();
    fErrorMsg = device->errorText(fError);
    return res;
}

eqFRJob::eqFRJob(eqDriver * device, QString action, QString data) :
	eqJob(device, action)
{
    fData = data;
}

eqFRJob::~eqFRJob()
{
}

void eqFRJob::print()
{
    eqFR * device = (eqFR*)fDevice;
    if(!device) return;    
    QStringList lines = QStringList::split("\n", QString::fromUtf8(fData.toString()), TRUE);
    for(uint l=0;l<lines.count();l++)
    {
	device->print(lines[l].utf8());
	fResult = device->result();	
	fError = device->error();
	fErrorMsg = device->errorMsg();
	if(fError) break;
    }    
}

void eqFRJob::cut()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->cut();
    fResult = device->result();
    fError = device->error();        
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::openSale()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->openCheck(CRO_SELL);
    fResult = device->result();
    fError = device->error();
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::openReturn()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->openCheck(CRO_SELLRET);
    fResult = device->result();    
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::cancelCheck()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->cancelCheck();
    fResult = device->result();
    fError = device->error();
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::addItem()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;  
    device->addItem(fData.toMap());
    fResult = device->result();    
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::closeCheck()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    fResult = device->closeCheck(fData.toMap());
    fError = device->error();
    fErrorMsg = device->errorMsg();
}

void eqFRJob::ZReport()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->ZReport();
    fResult = device->result();        
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::XReport()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->XReport();    
    fResult = device->result();
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::payin()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->payin(fData.toDouble());
    fResult = device->result();
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::payout()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->payout(fData.toDouble());
    fResult = device->result();
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::openCashbox()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->openCashbox();
    fResult = device->result();
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}

void eqFRJob::beep()
{
    eqFR * device = (eqFR *)fDevice;
    if(!device) return;
    device->beep();
    fResult = device->result();
    fError = device->error();    
    fErrorMsg = device->errorMsg();    
}
