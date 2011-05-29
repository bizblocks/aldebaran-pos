#ifndef SIRIUS_H
#define SIRIUS_H

#include <qobject.h>
#include <qdatetime.h>
#include <qdialog.h>

#include "data.h"
#include "datagoods.h"
#include "dataorder.h"
#include "server.h"

#define _u(s) QString::fromUtf8(s)

class QApplication;
class QButton;
class QProgressDialog;
class sMainWin;
class sInputDialog;

class sirius : public QObject
{
	Q_OBJECT
public:
	sirius(int argc, char ** argv);
	~sirius();
	sData * db();
	sDataGoods * dataGoods();
	sDataOrder * dataOrder();
	sMainWin * mainWin() { return fMainWin; };
	QPixmap thumb(QPixmap pic);
	QPixmap goodsPicture(Q_UINT32 id);
public slots:
	int init();
//	void next();
//	void openOrder();	
	void import(char what, sImportTable data);
	void importElement(sImportTable data);	
//	void importGoods(sImportTable data);
	void importOrder(sImportTable data);
	void setServer(sImportTable data);
	void error(QString msg);
	void information(QString msg, uint timeoutsec = 10);	
	bool goodsInfo(sDataCursor * goods);
	void sendOrder(sDataOrder * order);
	void call();
	void about();
	int inputNumber(int initValue, QString caption, int numDigits = 10);
protected slots:
	void startProcess();
	void stepProcess(int);
	void finishProcess();
protected:
	void initDb();	
	void initServer();
private:
	QApplication * app;
	sMainWin * fMainWin;
	sData * fDb;
	sServer * fServer;
	QString fHost, fFTPServer, fFTPPath;
	int fPort, fFTPPort;
	int fTable;
	QMap<int, QVariant> thumbCache;
	QProgressDialog * bar;
	QString progressCaption;
	int progressMax;
	QDialog * dlg;
};

class QLCDNumber;

class sInputDialog : public QDialog
{
	Q_OBJECT
public:
	sInputDialog(QWidget * parent, QString caption, int numDigits = 10, int timeout = 30);
	void setValue(int value);
	int value();
public slots:
	void input();
private:
	int fValue;
	QLCDNumber * lcd;
};

int date2int(QDate);
QDate int2Date(int);
int time2int(QTime);
QTime int2time(int);

QByteArray pixmap2array(QPixmap pix);

QButton * newButton(QWidget * parent, QPixmap pm, QString text, QSize s);

QString stringFromFile(QString fileName);

#endif

