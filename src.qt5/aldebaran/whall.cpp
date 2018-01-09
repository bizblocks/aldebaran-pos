#include <math.h>
#include <QGridLayout>
#include <QPaintEvent>
#include <qimage.h>
#include <qpainter.h>
#include <qlayout.h>
#include "whall.h"
#include "wtable.h"
#include "engine.h"
#include "data/dataorder.h"

alWHall::alWHall(alEngine * e, QWidget * parent, QString name, int tables, QPixmap image) :
    QWidget(parent)
{
    setObjectName(name);
    fEngine = e;
    fNumTables = 0;
    grid = NULL;
    shema = NULL;
    if(!image.isNull())
	shema = new QPixmap(image);
    else
    {
        grid = new QGridLayout(this);//, 1, 1, 5, 5);
        if(tables<1)
            tables = 1; // we must have at least one table
        tablesPerCol = (int)sqrt(tables);
        for(int i=0;i<tables;i++)
            addTable(-1, -1);
    }
    processShema();
}

alWHall::~alWHall()
{
}

int n[8][2]={{-1,-1}, {-1, 0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

bool alWHall::processShema()
{
    return FALSE;
//    if(!shema)
//        return FALSE;
//    QImage img = shema->convertToImage();
//    QSize ssize = img.size();
//    for(int x=0;x<ssize.width();x++)
//    {
//	for(int y=0;y<ssize.height();y++)
//	{
//	    if(img.pixel(x,y)==qRgb(0,0,0))
//	    {
//#ifdef DEBUG
//		qDebug(tr("found black point").utf8());
//#endif
//		bool hasn = FALSE;
//		for(int i=0;i<8;i++)
//		{
//		    if(x+n[i][0]<0) continue;
//		    if(y+n[i][1]<0) continue;
//		    if(x+n[i][0]>ssize.width()-1) continue;
//		    if(y+n[i][1]>ssize.height()-1) continue;
//		    hasn = img.pixel(x+n[i][0],y+n[i][1])==qRgb(0,0,0);
//		    if(hasn) break;
//		}
//		if(!hasn)
//		    addTable(x, y);
//#ifdef DEBUG
//		if(hasn)
//		    qDebug(tr("black point has neighbours").utf8());
//#endif
//	    }
//	}
//    }
//    return TRUE;
}

void alWHall::paintEvent( QPaintEvent *e )
{
    if (!shema)
    {    
        QWidget::paintEvent(e);
        return;
    }
    if ( shema->size() != QSize( 0, 0 ) ) 
    {
        QPainter painter(this);
        painter.setClipRect(e->rect());
        painter.drawPixmap(0, 0, *shema);
    }
}

alWTable * alWHall::addTable(int x, int y)
{
    alWTable * table;    
    fNumTables++;
    
    alOrderRecord * order = fEngine->tableOrder(fNumTables);
    int status = 0, orderNum = 0;
    double summ = 0.;    
    if(order) summ = order->total("summ");		
    if(order) status = order->status();
    if(order) orderNum = order->num();
    
    if(x<0 || y<0)
    {
        if(grid)
        {
            table = new alWTable(this, fNumTables);
            table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            grid->addWidget(table, (fNumTables-1)%tablesPerCol, (fNumTables-1)/tablesPerCol);
        }
        else
        {
            table = new alWTable(this, fNumTables);
            table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layout()->addWidget(table);
        }
    }
    else
    {
        table = new alWTable(this, fNumTables);
        table->setGeometry( QRect( x-55, y-30, 110, 60 ) );
    }
    table->setOrder(orderNum, summ);
    table->setStatus(status);	        
    tables[fNumTables] = table;
    connect(table, SIGNAL(invoked(int)), fEngine, SLOT(openOrder(int)));
    return table;
}

alWTable * alWHall::getTable(int num)
{
    return tables[num];
}
