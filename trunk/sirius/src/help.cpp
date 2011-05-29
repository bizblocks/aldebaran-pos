#include <qtextview.h>
#include <qtextstream.h>
#include <qlayout.h>
#include <qfontdatabase.h>
#include <qtoolbutton.h>
#include "sirius.h"
#include "mainwin.h"
#include "help.h"

sHelp::sHelp(sMainWin * mainWin, bool nextBtn) :
	QWidget(mainWin, "welcome"),
	fMainWin(mainWin),
	fNextBtn(nextBtn)
{	
}

void sHelp::init()
{
	QGridLayout * l = new QGridLayout(this, 2, 1, 10, 10);
	textView = new QTextView(this);
	textView->setText(stringFromFile("/usr/share/sirius/help.html"), "/usr/share/sirius/images/");
	textView->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
	textView->setPaper(QBrush(fMainWin->backgroundColor()));
	l->addWidget(textView, 0, 0);
	
	QGridLayout * btnGrid = new QGridLayout(l, 1, 3);
	QToolButton * btn;
	if(fNextBtn) btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/right.png"), _u("Далее"), QSize(100, 50));
	else btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/stop_cancel.png"), _u("Закрыть"), QSize(100, 50));
	if(fNextBtn) connect(btn, SIGNAL(clicked()), SLOT(next()));
	else connect(btn, SIGNAL(clicked()), SLOT(close()));
	btnGrid->addWidget(btn, 0, 1, AlignCenter);
	
	btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/levelup.png"), _u("Вверх"), QSize(120, 50));
	connect(btn, SIGNAL(clicked()), SLOT(scrollUp()));
	btnGrid->addWidget(btn, 0, 0, AlignCenter);

	btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/down.png"), _u("Вниз"), QSize(120, 50));
	connect(btn, SIGNAL(clicked()), SLOT(scrollDown()));
	btnGrid->addWidget(btn, 0, 2, AlignCenter);
	
	show();	
}

void sHelp::next()
{
	fMainWin->next();
}

void sHelp::scrollUp()
{
	textView->scrollBy(0, -textView->height());
	textView->update();
}

void sHelp::scrollDown()
{
	textView->scrollBy(0, textView->height());
	textView->update();	
}

