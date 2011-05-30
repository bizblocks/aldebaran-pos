#ifndef ESCPOS_H
#define ESCPOS_H

#include "tecashregisterbase.h"

#define ESC	0x1B
#define GS	0x1D
#define RS	0x07

#define RES_OK			0
#define RES_TIMEOUT		1
#define RES_NOTOPENED		2
#define RES_INVALIDARG0	3

#define TIMEOUT			1000

class LIB_EXPORT ESCPOS : public TECashRegisterBase
{
Q_OBJECT

public:

    ESCPOS();    
    ESCPOS(QString pnum);
    ~ESCPOS();
        
    typedef char Byte;	
    typedef int Result;
    
    void setAbort();
    QStringList getCodepages();
    QString codepage() {return fCodepage; };
public slots:
    virtual Result setCodepage(QString cp);
    
    //cashregister functions    {
    virtual int print(QString ln);
    virtual int cut();
    
    virtual bool openCheck();    
    virtual int closeCheck(double & dChange, int iReserved);    
    virtual bool printCheck(bool returnFlag) { 
#warning TODO    
    };        
    virtual bool cancelPrint() { return false; };    
    virtual int cancelCheck(int iReserved);    
    
    virtual int setOperation(int eOperationType) { fOperation = eOperationType; return 0; };
    virtual int setDiscount(double dDiscount); // absolute value of a discount
    virtual int setDiscountPercent(double); // discount in 0.01% units        
    virtual int setItem(const QString & sName, double dPrice, double dQuantity){
#warning TODO    
    };    
    virtual int setPayment(double dSum, int iType=1);    
    
    virtual int openCashbox(int n){
#warning TODO    
    } ; // open cash box number n   
    virtual int ZReport() { return -1; };
    virtual int XReport() { return -1; };
    
    virtual int payingin(double) { return -1; };
    virtual int payment(double) {return -1; };    
    
    virtual int beep();
    
    virtual int checkDeviceReady() { return 1; };
    //   end cashregister functions }
    
    virtual Result printBoldLine(QString ln);
    virtual Result printBarcode(QString barcode);
    
protected:
    Result sendCmd(Byte * pBuf, int iSize);
    Result toDeviceStr(QString str, QCString & dest);
private:
    Byte m_maxPrn;
    QStringList codepages;
    QStringList qtCodepages;
    QString fCodepage;
    
    int fOperation;
    QString fItemName;
    double fItemPrice;
    double fItemQuantity;
    double fItemDiscountPercent;
    double fItemDiscount;
    double fSubTotal;
    double fSumm[4];
    
    QString fCheckHeader;
    QString fCheckFooter;
    
    void init(); // This initialization function incorporates common constructor code
};

#endif
