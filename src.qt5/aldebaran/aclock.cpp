/****************************************************************************
** $Id: qt/aclock.cpp   3.3.7   edited Aug 31 2005 $
**
** Copyright (C) 1992-2005 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/
#include <QMouseEvent>
#include <qtimer.h>
#include <qpainter.h>
#include <qbitmap.h>
#include "aclock.h"

//
// Constructs an analog clock widget that uses an internal QTimer.
//

AnalogClock::AnalogClock( QWidget *parent, const char *name )
    : QWidget( parent )
{
    setObjectName(name);
    time = QTime::currentTime();		// get current time
    internalTimer = new QTimer( this );	// create internal timer
    connect( internalTimer, SIGNAL(timeout()), SLOT(timeout()) );
    internalTimer->start( 5000 );		// emit signal every 5 seconds
}

void AnalogClock::mousePressEvent( QMouseEvent *e )
{
    if(isTopLevel()) 
        clickPos = e->pos() + QPoint(geometry().topLeft() - frameGeometry().topLeft());
}

void AnalogClock::mouseMoveEvent( QMouseEvent *e )
{
    if(isTopLevel())
        move( e->globalPos() - clickPos );
}

//
// The QTimer::timeout() signal is received by this slot.
//

//
// When we set an explicit time we don't want the timeout() slot to be 
// called anymore as this relies on currentTime()
//
void AnalogClock::setTime( const QTime & t )
{
    time = t;
    disconnect( internalTimer, SIGNAL(timeout()), this, SLOT(timeout()) );
    update();
}


void AnalogClock::timeout()
{
    QTime old_time = time;
    time = QTime::currentTime();
    if ( old_time.minute() != time.minute() 
    || old_time.hour() != time.hour() )
    {	// minute or hour has changed
        update();
    }
}


void AnalogClock::paintEvent( QPaintEvent * )
{
    QPainter paint( this );
    paint.setBrush( palette().windowText() );
    drawClock( &paint );
}

// If the clock is transparent, we use updateMask()
// instead of paintEvent()

void AnalogClock::updateMask()	// paint clock mask
{
    QBitmap bm( size() );
    bm.fill( Qt::color0 );			//transparent

    QPainter paint;
    paint.begin( &bm );//,this
    paint.setBrush( Qt::color1 );		// use non-transparent color
    paint.setPen( Qt::color1 );

    drawClock( &paint );

    paint.end();
    setMask( bm );
}

//
// The clock is painted using a 1000x1000 square coordinate system, in
// the a centered square, as big as possible.  The painter's pen and
// brush colors are used.
//
void AnalogClock::drawClock( QPainter *paint )
{
    paint->save();
    
    paint->setWindow( -500,-500, 1000,1000 );

    QRect v = paint->viewport();
    int d = qMin( v.width(), v.height() );
    paint->setViewport( v.left() + (v.width()-d)/2,
			v.top() + (v.height()-d)/2, d, d );
    
    QPolygon pts;

    paint->save();
    paint->rotate( 30*(time.hour()%12-3) + time.minute()/2 );
    pts.setPoints( 4, -20,0,  0,-20, 300,0, 0,20 );
    paint->drawConvexPolygon( pts );
    paint->restore();

    paint->save();
    paint->rotate( (time.minute()-15)*6 );
    pts.setPoints( 4, -10,0, 0,-10, 400,0, 0,10 );
    paint->drawConvexPolygon( pts );
    paint->restore();

    for ( int i=0; i<12; i++ )
    {
        paint->drawLine( 440,0, 460,0 );
        paint->rotate( 30 );
    }

    paint->restore();
}


