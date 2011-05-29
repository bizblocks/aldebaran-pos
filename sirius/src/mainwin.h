#ifndef MAINWIN_H
#define MAINWIN_H

#include <qmainwindow.h>

class sirius;

class sMainWin : public QMainWindow
{
	Q_OBJECT
public:
	sMainWin(sirius * s);
	void maximizeWidget();
public slots:
	void next();
	void welcome();
	void order(int id=0);
	void help(bool btnNext = FALSE);
signals:
	void widgetClosed();
protected:
	virtual void resizeEvent(QResizeEvent *);
	virtual void closeEvent(QCloseEvent *);
private:
	QWidget * currentWidget;
	sirius * fSirius;
	int widgetLooper;
};

#endif
