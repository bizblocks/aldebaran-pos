#ifndef HELP_H
#define HELP_H

#include <qwidget.h>

class sMainWin;
class QTextView;

class sHelp : public QWidget
{
	Q_OBJECT
public:
	sHelp(sMainWin * mainWin, bool nextBtn = FALSE);
public slots:
	void init();
	void scrollUp();
	void scrollDown();	
protected slots:
	virtual void next();
private:
	sMainWin * fMainWin;
	QTextView * textView;
	bool fNextBtn;
};

#endif
