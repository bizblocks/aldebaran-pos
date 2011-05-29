#ifndef CTS300PRINTER_H
#define CTS300PRINTER_H

#include <qpixmap.h>
#include "driver.h"

class CTS300;
class eqJob;
class eqCTS300Job;

class eqCTS300Printer : public eqDriver
{
    Q_OBJECT
public:
    eqCTS300Printer(QString name);
    ~eqCTS300Printer();
    virtual void init();
    void setPrintText(QString text) { fText = text; };
//    void setPrintPicture(QPixmap picture);
    void setPrintBarcode(QString barcode);
    virtual eqJob * createJob(QString action="");
    virtual void prepare();
    virtual void end();    
    virtual void setOption(QString option, QVariant value);    
    virtual QStringList options();
    virtual QString option(QString name);
    virtual bool dialog();
    QStringList codepages();
public slots:
    void print();
    void cut();
private:
    QString fText;
//    QPixmap fPixmap;
    CTS300 * printer;
    QString fDeviceName;
    QString fCodepage;
    int fPrintWidth;
};

class eqCTS300Job : public eqJob
{
    Q_OBJECT
public:
    eqCTS300Job(eqDriver * device, QString action, QString data="");
    virtual ~eqCTS300Job();
public slots:
    void print();
    void cut();
};

#endif
