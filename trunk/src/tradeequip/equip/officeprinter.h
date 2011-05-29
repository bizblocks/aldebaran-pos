#ifndef OFFICEPRINTER_H
#define OFFICEPRINTER_H

#include <qpixmap.h>
#include "driver.h"

class eqJob;
class eqPrinterJob;
class QPixmap;
class QPainter;
class QPrinter;
class QTextBrowser;
class QFont;

class eqOfficePrinter : public eqDriver
{
    Q_OBJECT
public:
    eqOfficePrinter(QString name);
    ~eqOfficePrinter();
    virtual void init() { init(""); };
    virtual void init(QString printerName);
    void setPrintText(QString text) { fText = text; };
    void setPrintPicture(QPixmap picture);
    virtual eqJob * createJob(QString action="");
    virtual void prepare();
    virtual void end();
    virtual void setOption(QString option, QVariant value) { Q_UNUSED(option); Q_UNUSED(value); };
    virtual QStringList options() { return QStringList(); };
    virtual QString option(QString) { return ""; };    
    virtual bool dialog();
public slots:
    void print();
private:
    QString fText;
    QPixmap fPixmap;
    QTextBrowser * fBrowser;
    QPainter * p;
    QPrinter * prn;
};

class eqPrinterJob : public eqJob
{
    Q_OBJECT
public:
    eqPrinterJob(eqDriver * device, QString action, QString data="");
    virtual ~eqPrinterJob();
    virtual int process();
public slots:
    void print();
};

#endif
