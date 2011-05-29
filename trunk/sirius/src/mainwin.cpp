#include <qlayout.h>
#include "sirius.h"
#include "welcome.h"
#include "orderwin.h"
#include "mainwin.h"
#include "help.h"

sMainWin::sMainWin(sirius * s) :
	QMainWindow(0, "siriusMainWindow")
{
	fSirius = s;
	currentWidget = NULL;	
	widgetLooper = 0;
	connect(this, SIGNAL(widgetClosed()), this, SLOT(next()));
	next();
}

void sMainWin::welcome()
{
	if(currentWidget) delete currentWidget;
	sWelcome * welcome = new sWelcome(this);
	welcome->init();
	currentWidget = welcome;
	maximizeWidget();
	widgetLooper = 1;	
}

void sMainWin::order(int id)
{
	sOrderWin * order = NULL;
	if(currentWidget) delete currentWidget;
	order = new sOrderWin(fSirius, this);
	order->init();
	currentWidget = order;
	maximizeWidget();
	widgetLooper = 3;	
	order->openOrder(id);		
}

void sMainWin::help(bool btnNext)
{
	sHelp * help = new sHelp(this, btnNext);
	help->init();
	if(btnNext)
	{
		if(currentWidget) delete currentWidget;
		currentWidget = help;
		maximizeWidget();		
	}
	else
	{
		help->setGeometry(geometry());	
	}
	widgetLooper = 2;
}

void sMainWin::maximizeWidget()
{
	showFullScreen();
	if(currentWidget) currentWidget->setGeometry(geometry());	
}

void sMainWin::next()
{
	if(!isVisible()) maximizeWidget();
	switch(widgetLooper)
	{
		case 0:
			welcome();
			break;
		case 1:
			help(TRUE);
			break;
		case 2:
			order(-1);
			break;
		default:
			widgetLooper = 0;
			next();
			break;
	}
}

void sMainWin::resizeEvent(QResizeEvent * e)
{	
	if(e->size().width()<639) resize(QSize(maximumWidth(), maximumHeight()));
	else if(e->size().height()<479) resize(QSize(maximumWidth(), maximumHeight()));
	else QWidget::resizeEvent(e);
}


void sMainWin::closeEvent(QCloseEvent * e)
{
	e->ignore();
}
