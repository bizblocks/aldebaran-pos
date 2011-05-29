#include <qvariant.h>
#include <qsignal.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h> 
#include <qsimplerichtext.h> 
#include <qstylesheet.h> 
#include <qpalette.h> 
#include <qtextbrowser.h>
#include <qapplication.h>
#include "officeprinter.h"
#include "worker.h"

eqOfficePrinter::eqOfficePrinter(QString name) :
	eqDriver(name)
{
    fBrowser = new QTextBrowser();    
    p = new QPainter();
    prn = new QPrinter(QPrinter::PrinterResolution);    
}

eqOfficePrinter::~eqOfficePrinter() 
{
    delete fBrowser;    
    delete p;    
    delete prn;
}

void eqOfficePrinter::init(QString n)
{
    if(n.isEmpty())
    {
	prn->setOutputToFile(TRUE);
	prn->setOutputFileName("printerJob.ps");
    } 
    else prn->setPrinterName(n);	
    fText = "";
    fPixmap = QPixmap();
}

void eqOfficePrinter::setPrintPicture(QPixmap picture)
{
    fPixmap = picture;
}

eqJob * eqOfficePrinter::createJob(QString action)
{
    return new eqPrinterJob(this, action);
}

void eqOfficePrinter::prepare()
{
    prn->setFullPage(TRUE);
    QPaintDeviceMetrics screen(prn);
    prn->setResolution(screen.logicalDpiY());
    if( !p->begin(prn) ) return;    
}

void eqOfficePrinter::end()
{
    p->end();
    fText = "";
    fPixmap = QPixmap();    
}

void eqOfficePrinter::print()
{    
    //    prn->setup(this) ) show printer dialog
    fBrowser->setText(fText);
    fBrowser->setTextFormat(Qt::RichText);
    QPaintDeviceMetrics metrics( p->device() );
    QRect view( 0, 0, metrics.width(), metrics.height());
    QSimpleRichText richText(fBrowser->text(), QFont("DejaVu Sans", 10), fBrowser->context(),
			     fBrowser->styleSheet(), fBrowser->mimeSourceFactory());   
    richText.setWidth( p, view.width() );
    int page = 1;
    do
    {
	richText.draw( p, 0, 0, view, fBrowser->colorGroup() );
	view.moveBy( 0, view.height() );
	p->translate( 0 , -view.height() );
	if ( view.top() >= richText.height() ) break;
	prn->newPage();
	page++;
    } while (TRUE);
    for(int i=0;i>-1;i++);
}

bool eqOfficePrinter::dialog()
{
    EQ_NOT_IMPLEMENTED
    return FALSE;
}

eqPrinterJob::eqPrinterJob(eqDriver * device, QString action, QString data) :
	eqJob(device, action)
{
    fData = QVariant(data);
}

eqPrinterJob::~eqPrinterJob()
{
}

int eqPrinterJob::process()
{
    fSignal->connect(this, QString(SLOT(%1)).arg(fAction));
    fSignal->activate();
    fSignal->disconnect(this, QString(SLOT(%1)).arg(fAction));
    return fSignal->value().toInt();     
}

void eqPrinterJob::print()
{
    if(fDevice)
    {
	eqOfficePrinter * prn = (eqOfficePrinter *)fDevice;
	if(fData.type()==QVariant::Pixmap) prn->setPrintPicture(fData.toPixmap());
	else prn->setPrintText(fData.toString());
	prn->print();
    }
}

