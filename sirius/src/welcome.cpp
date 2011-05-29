#include <qtextview.h>
#include <qtextstream.h>
#include <qlayout.h>
#include <qfontdatabase.h>
#include <qtoolbutton.h>
#include "sirius.h"
#include "mainwin.h"
#include "welcome.h"

sWelcome::sWelcome(QMainWindow * mainWin) :
	QWidget(mainWin, "welcome")
{
	fMainWin = mainWin;
}

void sWelcome::init()
{
	QGridLayout * l = new QGridLayout(this, 2, 1, 10, 10);
	textView = new QTextView(this);
	textView->setText(stringFromFile("/usr/share/sirius/welcome.html"), "/usr/share/sirius/images/");	
	textView->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
	textView->setPaper(QBrush(fMainWin->backgroundColor()));
	l->addWidget(textView, 0, 0);
	QToolButton * btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/right.png"), _u("Далее"), QSize(100, 50));
	connect(btn, SIGNAL(clicked()), fMainWin, SLOT(next()));
	l->addWidget(btn, 1, 0);
	show();	
//	grabMouse();
}

