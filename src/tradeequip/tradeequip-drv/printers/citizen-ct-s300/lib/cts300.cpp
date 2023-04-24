#include <errno.h>
#include <linux/lp.h>
#include "posix_qextserialport.h"
#include "cts300.h"

CTS300::CTS300(QString pname) :
    TEBase( pname )
{    
    codepages.clear();
    qtCodepages.clear();
    init();
    setPortDevice(pname);
}

CTS300::~CTS300()
{
}

void CTS300::init()
{
    setName("TEPrinterCTS300");
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

void CTS300::setAbort()
{
    //from tunelp.c sources
    Posix_QextSerialPort * p = port();
    int h = p->handle();
    int abort = 1;
    int offset = 0, irq;
    /* We don't understand the new ioctls */
    if (LPGETIRQ >= 0x0600 && ioctl(h, LPGETIRQ, &irq) < 0 && errno == EINVAL) offset = 0x0600;
    if (ioctl(h, LPABORT - offset, &abort) < 0) qDebug("tunelp: ioctl");
}

CTS300::Result CTS300::sendCmd(Byte * pBuf, int iSize)
{
    setAbort();
    //    int count = 0;
    for(int b=0;b<iSize;b++)
    {
        if(port()->putch(pBuf[b])==-1)
        {
            //		if(!b || (count++<3)) sendCmd(pBuf, iSize);
            return RES_TIMEOUT;
        }
        usleep(1);
    }
    return RES_OK;
}

QStringList CTS300::getCodepages()
{
    return codepages;
}

CTS300::Result CTS300::toDeviceStr(QString str, Q3CString & dest)
{
    dest = "";
    QTextCodec * utf8=QTextCodec::codecForName("UTF-8");
    QString unicodetext = utf8->toUnicode(str);
    QTextCodec * cp=QTextCodec::codecForName(qtCodepages[codepages.findIndex(fCodepage)]);
    if(cp)
        dest = cp->fromUnicode(unicodetext);
    else
        //TODO check
        dest = Q3CString(str.toUtf8());
    return RES_OK;
}

CTS300::Result CTS300::setCodepage(QString cp)
{
    fCodepage = cp;
    int index = codepages.findIndex(cp);
    Byte cmd[3] = {ESC, 't', (Byte)index};
    Result res = sendCmd(cmd, 3);
    return res;
}

CTS300::Result CTS300::printLine(QString ln)
{
    Q3CString buf;
    Result res = toDeviceStr(ln, buf);
    if(res) return res;
    const Byte * pBuf = (const char*)buf;
    res = sendCmd((char *)pBuf, buf.length());
    return res;
}

CTS300::Result CTS300::printBoldLine(QString ln)
{
    Result res;
    Byte cmdBold[3] = {ESC, '!', 0x08};
    res = sendCmd(cmdBold, 3);
    if(res) return res;
    res = printLine(ln);
    Byte cmdNorm[3] = {ESC, '!', 0x00};
    res = sendCmd(cmdNorm, 3);
    return res;
}

CTS300::Result CTS300::printBarcode(QString barcode)
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
    Q3CString bcstr;
    res = toDeviceStr(barcode, bcstr);
    const Byte * buf = (const char*)bcstr;
    if((res=sendCmd((char *)buf, bcstr.length()))) return res;
    Byte null = 0;
    res = sendCmd(&null , 1);
    return res;
}

CTS300::Result CTS300::cut()
{
    Result res;
    Byte cmd[3] = {GS, 'V', 0x01};
    res = sendCmd(cmd, 3);
    return res;
}

