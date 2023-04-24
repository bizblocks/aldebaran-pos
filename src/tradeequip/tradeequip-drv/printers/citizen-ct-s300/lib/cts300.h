#ifndef CTS300_H
#define CTS300_H

#include "tebase.h"

#define ESC	0x1B
#define GS	0x1D

#define RES_OK			0
#define RES_TIMEOUT		1
#define RES_NOTOPENED		2
#define RES_INVALIDARG0	3

#define TIMEOUT			1000

class LIB_EXPORT CTS300 : public TEBase
{
Q_OBJECT

public:

    CTS300(QString pnum);
    ~CTS300();
        
    typedef char Byte;	
    typedef int Result;
    
    void setAbort();
    QStringList getCodepages();
    QString codepage() {return fCodepage; };
public slots:
    virtual Result setCodepage(QString cp);    
    virtual Result printLine(QString ln);
    virtual Result printBoldLine(QString ln);
    virtual Result printBarcode(QString barcode);
    virtual Result cut();
    
protected:
    Result sendCmd(Byte * pBuf, int iSize);
    Result toDeviceStr(QString str, Q3CString & dest);
private:
    Byte m_maxPrn;
    QStringList codepages;
    QStringList qtCodepages;
    QString fCodepage;
    void init(); // This initialization function incorporates common constructor code
};

#endif
