#ifndef WELCOME_H
#define WELCOME_H

#include <qwidget.h>

class QMainWindow;
class QTextView;

class sWelcome : public QWidget
{
	Q_OBJECT
public:
	sWelcome(QMainWindow * mainWin);
public slots:
	void init();
private:
	QMainWindow * fMainWin;
	QTextView * textView;
};

#endif
