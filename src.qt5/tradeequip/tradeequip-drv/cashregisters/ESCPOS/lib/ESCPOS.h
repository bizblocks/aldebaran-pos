#ifndef ESCPOS_H
#define ESCPOS_H

#include "tecashregisterbase.h"

#define ESC	0x1B
#define GS	0x1D
#define RS	0x1E
#define DLE	0x10
#define DC4	0x14

#define RES_OK			0
#define RES_TIMEOUT		1
#define RES_NOTOPENED		2
#define RES_INVALIDARG0	3

#define TIMEOUT			1000

class LIB_EXPORT ESCPOS : public TECashRegisterBase
{
Q_OBJECT

public:
    typedef TECashRegisterBase super;
    ESCPOS();    
    ESCPOS(QString pnum);
    ~ESCPOS();
        
    typedef char Byte;	
    typedef int Result;
    
    void setAbort();

public slots:
    virtual int setCodepage(const QString& cp);
    virtual QStringList codepages();
    
    //cashregister functions    {
    virtual int print(const QString& ln);
    virtual int cut();
    
    virtual bool openCheck();
    virtual int openCheck(int eDocumentType, int & piReserved);
    virtual int closeCheck(double & dChange, int iReserved);    
    virtual bool printCheck(bool) { return FALSE; };        
    virtual bool cancelPrint();    
    virtual int cancelCheck(int iReserved);    
    
    virtual int setOperation(int eOperationType) { fOperation = eOperationType; return 0; };
    virtual int setDiscount(double dDiscount); // absolute value of a discount
    virtual int setDiscountPercent(double); // discount in 0.01% units        
    virtual int setItem(const QString & sName, double dPrice, double dQuantity);
    virtual int setPayment(double dSum, int iType=1);    
    
    virtual int openCashbox(int n=0); // open cash box number n   
    virtual int ZReport() { return -1; };
    virtual int XReport() { return -1; };
    
    virtual int payingin(double) { return -1; };
    virtual int payment(double) {return -1; };    
    
    virtual int beep();
    
    virtual int checkDeviceReady() { return 1; };
    virtual Result printBoldLine(QString ln);
    virtual Result printBarcode(QString barcode);    
    //   end cashregister functions }
    
protected:
    Result sendCmd(Byte * pBuf, int iSize);
    Result toDeviceStr(QString str, QCString & dest);
    void clear();
private:
    Byte m_maxPrn;
    QStringList prnCodepages;
    QStringList qtCodepages;
    
    QString fDocTypeStr;
    
    int fOperation;
    double fItemDiscountPercent;
    double fItemDiscount;
    double fSubTotal;
    double fSumm[4];
        
    void init(); // This initialization function incorporates common constructor code
};

#endif
