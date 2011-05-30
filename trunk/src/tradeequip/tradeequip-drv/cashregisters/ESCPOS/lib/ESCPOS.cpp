#include <errno.h>
#include <linux/lp.h>
#include "posix_qextserialport.h"
#include "ESCPOS.h"

ESCPOS::ESCPOS() :
	TECashRegisterBase("/dev/null", 0)
{    
    codepages.clear();    
    qtCodepages.clear();
    init();
}

ESCPOS::ESCPOS(QString pname) :
	TECashRegisterBase( pname, 0 )
{    
    codepages.clear();    
    qtCodepages.clear();
    init();
    setPortDevice(pname);
}

ESCPOS::~ESCPOS()
{
}

void ESCPOS::init()
{
    setName("TEPrinterESCPOS");
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
    m_maxPrn = 0; 
    
    codepages << "PC473" << "Katakana" << "PC850" << "PC860" << "PC863";
    codepages << "PC865" << "PC852" << "PC866" << "PC857" << "WPC1252";
    
    qtCodepages << "" << "" << "IBM 850" << "" << "";
    qtCodepages << "" << "" << "IBM 866" << "" << "CP1252";
    fCodepage = "PC866";
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
    setAbort();
    //    int count = 0;
    return writeBlock(pBuf, iSize);
}

QStringList ESCPOS::getCodepages()
{
    return codepages;
}

ESCPOS::Result ESCPOS::toDeviceStr(QString str, QCString & dest)
{
    dest = "";
    QTextCodec * utf8=QTextCodec::codecForName("UTF-8");
    QString unicodetext = utf8->toUnicode(str);
    QTextCodec * cp=QTextCodec::codecForName(qtCodepages[codepages.findIndex(fCodepage)]); 
    if(cp) dest = cp->fromUnicode(unicodetext);
    else dest = QCString(str);
    return RES_OK;
}

ESCPOS::Result ESCPOS::setCodepage(QString cp)
{
    fCodepage = cp;
    int index = codepages.findIndex(cp);
    Byte cmd[3] = {ESC, 't', (Byte)index};
    Result res = sendCmd(cmd, 3);
    return res;
}

int ESCPOS::print(QString ln)
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
    Byte cmdBold[3] = {ESC, '!', 0x08};
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
    if(res) return res;
    Byte bcType = 2;
    if(barcode.length()<=8) bcType = 3;
    Byte cmd[3] = {GS, 'k', bcType};
    res = sendCmd(cmd, 3);
    if(res) return res;
    QCString bcstr;
    res = toDeviceStr(barcode, bcstr);
    const Byte * buf = (const char*)bcstr;
    if((res=sendCmd((char *)buf, bcstr.length()))) return res;
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
    QCString buf;
    Result res = toDeviceStr(fCheckHeader, buf);
    if(res) return res;
    const Byte * pBuf = (const char*)buf;
    res = sendCmd((char *)pBuf, buf.length());
    
    for(int ind=0;ind<4;ind++) fSumm[ind] = 0;
    fSubTotal = 0;
    
    return res;   
}

int ESCPOS::closeCheck(double & dChange, int iReserved)
{
    //TODO total and change print    
    QCString buf;
    Result res = toDeviceStr(fCheckFooter, buf);
    if(res) return res;
    const Byte * pBuf = (const char*)buf;
    res = sendCmd((char *)pBuf, buf.length());
    double summ = 0.0;
    for(int ind=0;ind<4;ind++) summ += fSumm[ind];
    dChange = summ-fSubTotal;
    return res;
}

int ESCPOS::setPayment(double dSum, int iType)
{
    if(iType<1 || iType>4) return -1;
    fSumm[iType-1] = dSum;
}

int ESCPOS::cancelCheck(int iReserved)
{
    //TODO print check cancel msg
    return -1;
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
    Result res;
    Byte cmd[3] = {RS};
    res = sendCmd(cmd, 1);
    return res;
}
