#include <errno.h>
#include <linux/lp.h>
#include "posix_qextserialport.h"
#include "ESCPOS.h"

#define PRINT_WIDTH	42

ESCPOS::ESCPOS() :
	TECashRegisterBase("/dev/null", 0)
{    
    prnCodepages.clear();    
    qtCodepages.clear();
    
    prnCodepages << "PC473" << "Katakana" << "PC850" << "PC860" << "PC863";
    prnCodepages << "PC865" << "PC852" << "PC866" << "PC857" << "WPC1252";
    
    qtCodepages << "" << "" << "IBM 850" << "" << "";
    qtCodepages << "" << "" << "IBM 866" << "" << "CP1252";    
    
    init();
}

ESCPOS::ESCPOS(QString pname) :
	TECashRegisterBase( pname, 0 )
{    
    prnCodepages.clear();    
    qtCodepages.clear();
    
    prnCodepages << "PC473" << "Katakana" << "PC850" << "PC860" << "PC863";
    prnCodepages << "PC865" << "PC852" << "PC866" << "PC857" << "WPC1252";
    
    qtCodepages << "" << "" << "IBM 850" << "" << "";
    qtCodepages << "" << "" << "IBM 866" << "" << "CP1252";    
    
    init();
    setPortDevice(pname);
}

ESCPOS::~ESCPOS()
{
}

void ESCPOS::init()
{
    setName("TECashRegisterESCPOS");
    /*
    m_ee.addFuncBinding(this,&FelixRK::readMachineNumber,"readMachineNumber");
    m_ee.addFuncBinding<FelixRK,int>(this,&FelixRK::open,"open");
    m_ee.addFuncBinding<FelixRK,int>(this,&FelixRK::close,"close");
    m_ee.addFuncBinding<FelixRK,int,int,int&>(this,&FelixRK::openCheck,"openCheck");
    m_ee.addFuncBinding(this,&FelixRK::cancelPrint,"cancelPrint");
    m_ee.addFuncBinding(this,&FelixRK::sellAdd,"addSell");
    m_ee.addFuncBinding(this,&FelixRK::printCheck,"printCheck");
    m_ee.addFuncBinding(this,&FelixRK::internalOpenCashbox,"openCashbox");
    m_ee.addFuncBinding<FelixRK,QString>(this,&FelixRK::errorText,"errorText");
    m_ee.addFuncBinding<FelixRK,int,int>(this,&FelixRK::setPortNumber,"setPortNumber");
    m_ee.addProcBinding1<FelixRK,int>(this,&FelixRK::setPortBaudRate,"setBaudRate");
    m_ee.addFuncBinding(this,&FelixRK::setPassword,"setPassword");
    m_ee.addFuncBinding(this,&FelixRK::internalReadOptions,"readOptions");
    m_ee.addFuncBinding(this,&FelixRK::internalDailyReportAndClear,"dailyReportAndClear")
    m_ee.addFuncBinding(this,&FelixRK::internalCancelCheck,"internalCancelCheck");
    m_ee.addFuncBinding<FelixRK,QVariant,const QString &>(this,&FelixRK::value,"value");
*/
    clear();
    m_maxPrn = PRINT_WIDTH; 
    super::setCodepage("PC866");
    setErrorCode(0);
    /*    qtCodepages[19] = "";
    qtCodepages[26] = "TIS-620";	
    qtCodepages[40] = "TIS-620";
    qtCodepages[255] = "";    */
}

void ESCPOS::setAbort()
{
    if(connectionType()!=ECT_SERIAL)
	return;
    //from tunelp.c sources
    Posix_QextSerialPort * p = port();
    int h = p->handle();
    int abort = 1;
    int offset = 0, irq;
    /* We don't understand the new ioctls */    
    if (LPGETIRQ >= 0x0600 && ioctl(h, LPGETIRQ, &irq) < 0 && errno == EINVAL) offset = 0x0600;
    if (ioctl(h, LPABORT - offset, &abort) < 0) qDebug("tunelp: ioctl");
}

ESCPOS::Result ESCPOS::sendCmd(Byte * pBuf, int iSize)
{
    if(!isOpen())
	if(!open()) return -1;    
    setAbort();
    int res = writeBlock(pBuf, iSize);
    return res==iSize ? 0 : -1;
}

QStringList ESCPOS::codepages()
{
    return prnCodepages;
}

ESCPOS::Result ESCPOS::toDeviceStr(QString str, QCString & dest)
{
    dest = "";
    QTextCodec * utf8=QTextCodec::codecForName("UTF-8");
    QString unicodetext = utf8->toUnicode(str);
    QTextCodec * cp=QTextCodec::codecForName(qtCodepages[prnCodepages.findIndex(codepage())]); 
    if(cp) dest = cp->fromUnicode(unicodetext);
    else dest = QCString(str);
    return RES_OK;
}

int ESCPOS::setCodepage(const QString& cp)
{
    super::setCodepage(cp);
    int index = prnCodepages.findIndex(cp);
    Byte cmd[3] = {ESC, 't', (Byte)index};
    Result res = sendCmd(cmd, 3);
    return res;
}

int ESCPOS::print(const QString& ln)
{
    QCString buf;
    Result res = toDeviceStr(ln, buf);
    if(res) return res;
    const Byte * pBuf = (const char*)buf;
    res = sendCmd((char *)pBuf, buf.length());
    return res;
}

ESCPOS::Result ESCPOS::printBoldLine(QString ln)
{
    Result res;
    Byte cmdBold[3] = {ESC, '!', 0x30};
    res = sendCmd(cmdBold, 3);
    if(res) return res;
    res = print(ln);
    Byte cmdNorm[3] = {ESC, '!', 0x00};
    res = sendCmd(cmdNorm, 3);
    return res;
}

ESCPOS::Result ESCPOS::printBarcode(QString barcode)
{
    if(barcode.length()>13) return RES_INVALIDARG0;
    Result res;
    Byte cmdPos[3] = {GS, 'H', 2};
    res = sendCmd(cmdPos, 3);
    if(res)	return res;
    Byte bcType = 2;
    if(barcode.length()<=8) bcType = 3;
    Byte cmd[3] = {GS, 'k', bcType};
    res = sendCmd(cmd, 3);
    if(res)	return res;
    QCString bcstr;
    res = toDeviceStr(barcode, bcstr);
    const Byte * buf = (const char*)bcstr;
    if((res=sendCmd((char *)buf, bcstr.length()))) 
	return res;
    Byte null = 0;
    res = sendCmd(&null , 1);
    return res;
}

ESCPOS::Result ESCPOS::cut()
{
    Result res;
    Byte cmd[3] = {GS, 'V', 0x01};
    res = sendCmd(cmd, 3);
    return res;
}

bool ESCPOS::openCheck()
{
    int tmp;
    return openCheck(CRO_SELL, tmp);
}

int ESCPOS::openCheck(int eDocumentType, int &)
{
    switch(eDocumentType)
    {
    case CRO_SELL: default:
	fDocTypeStr = "Продажа";
	break;
    case CRO_SELLRET:
	fDocTypeStr = "Возврат";
	break;
    }
    clear();
    print(checkHeader());
    return true;
}

void ESCPOS::clear()
{
    for(int ind=0;ind<4;ind++) fSumm[ind] = 0.0;
    fSubTotal = 0.0;
    fItemDiscount = 0.0;
    fItemDiscountPercent = 0.0;
}

QString justify(int len, QString left, QString right)
{
    QString uleft = QString::fromUtf8(left);
    QString uright = QString::fromUtf8(right);
    return QString(uleft+uright.rightJustify(len-uleft.length(), ' ', TRUE)).left(len).utf8();
}

int ESCPOS::closeCheck(double & dChange, int /*iReserved*/)
{
    double summ = 0.0;
    for(int ind=0;ind<4;ind++) summ += fSumm[ind];
    if(!summ)
    {
	summ = fSubTotal;
	fSumm[0] = fSubTotal;
    }
    dChange = summ-fSubTotal;
    int res = 0;
    if((res = print(QString("").rightJustify(PRINT_WIDTH, '-', TRUE)+"\n"))) return res;
    if((res = printBoldLine(justify(PRINT_WIDTH/2, "ИТОГО", QString("=%1").arg(fSubTotal, 6, 'f', 2))+"\n"))) return res;
    if(fSumm[0]>0)
	if((res = print(justify(PRINT_WIDTH, " Наличные", QString("=%1").arg(fSumm[0], 6, 'f', 2))+"\n"))) return res;
    if(fSumm[1]>0)
	if((res = print(justify(PRINT_WIDTH, " Платежная карта", QString("=%1").arg(fSumm[1], 6, 'f', 2))+"\n"))) return res;
    if(dChange>0)
	if((res = print(justify(PRINT_WIDTH, " СДАЧА", QString("=%1").arg(dChange, 6, 'f', 2))+"\n"))) return res;
    print(checkFooter());    
    if((res = print("\n\n\n"))) return res;
    clear();
    res = openCashbox();
    return res;
}

int ESCPOS::setItem(const QString & sName, double dPrice, double dQuantity)
{
    double sum = dQuantity*dPrice;
    int res = 0;
    if((res = print(sName.left(PRINT_WIDTH*2)+"\n"))) return res;
    if((res = print(justify(PRINT_WIDTH, QString("%1 X %2").arg(dQuantity, 7, 'f', 3).arg(dPrice, 6, 'f', 2), 
			    QString("=%1").arg(sum, 6, 'f', 2))+"\n"))) return res;
    if(fItemDiscountPercent!=0.0)
    {
	sum = sum * ( 1 - fItemDiscountPercent/100);
	if((res = print(justify(PRINT_WIDTH, QString(" Скидка %1 %%").arg(fItemDiscountPercent, 5, 'f', 2), 
				QString("=%1").arg(dQuantity*dPrice-sum, 6, 'f', 2))+"\n"))) return res;
    }
    if(fItemDiscount!=0.0)
    {
	sum = sum - fItemDiscount;
	if((res = print(justify(PRINT_WIDTH, QString(" Скидка %1").arg(fItemDiscountPercent, 5, 'f', 2), 
				QString("=%1").arg(fItemDiscount, 6, 'f', 2))+"\n"))) return res;
    }
    fSubTotal += sum;    
    return res;
}

int ESCPOS::setPayment(double dSum, int iType)
{
    if(iType<1 || iType>4) return -1;
    fSumm[iType-1] = dSum;
    return 0;
}

int ESCPOS::cancelCheck(int /*iReserved*/)
{        
    clear();
    return TRUE;
}

bool ESCPOS::cancelPrint()
{
    clear();    
    return print("\nЧек аннулирован\n");    
}

int ESCPOS::setDiscountPercent(double p)
{
    fItemDiscountPercent = p;
    return 0;
}

int ESCPOS::setDiscount(double s)
{
    fItemDiscount = s;
    return 0;
}

int ESCPOS::beep()
{
    int res;
    Byte cmd[1] = {RS};
    res = sendCmd(cmd, 1);
    return res;
}

int ESCPOS::openCashbox(int m)
{
    int res;
//    Byte cmd[5] = {DLE, DC4,  1, m, 0xab};
    m = 1; //HACK
    Byte cmd[5] = {ESC, 'p',  m, 0xfa, 0xff};    
    res = sendCmd(cmd, 5);
    return res;    
}

#include "teplugin.h"
//template TEPlugin<FelixRK>;
typedef TEPlugin<ESCPOS> TECashRegisterESCPOSPlugin;
TE_EXPORT_PLUGIN( TECashRegisterESCPOSPlugin )
