/****************************************************************************
This file is part of Sirius Embedded Application written by Artel-GNU.
Author: Anton Sokolov
Created: 15.01.2008
See LICENSE.GPL for more information
Copyleft
*****************************************************************************/

#include <qapplication.h>
#include <qmessagebox.h>
#include <qtoolbutton.h>
#include <qfile.h>
#include <qtextcodec.h>
#include <qtabdialog.h>
#include <qtextview.h>
#include <qlayout.h>
#include <qlcdnumber.h>
#include <qimage.h>
#include <qprogressdialog.h>
#include <qtimer.h>
#include "sirius.h"
#include "mainwin.h"
#include "goodsinfo.h"

sirius::sirius(int argc, char ** argv)
{
	QApplication::setColorSpec(QApplication::ManyColor);	
	app = new QApplication(argc, argv);
	QFont font("dejavu", 12, 50, FALSE, QFont::Unicode);
	app->setFont(font);
	fMainWin = NULL;
	fServer = NULL;
	fDb = NULL;
	fHost = "";
	fPort = 0;
	bar = NULL;
	dlg = NULL;
}

sirius::~sirius()
{
	if(fDb) delete fDb;
	app->quit();
}

#include "welcome.h"

int sirius::init()
{
	thumbCache.clear();
	
	QString settings = stringFromFile("/usr/share/sirius/table");
	fTable = settings.toUInt();
	
	qDebug(QString("table number %1").arg(fTable));
	initDb();
	qDebug("database initialized");
	initServer();
	qDebug("server initialized");
	fMainWin = new sMainWin(this);
	app->setMainWidget(fMainWin);
	return qApp->exec();
}

void sirius::initDb()
{
	if(fDb) delete fDb;
	fDb = sData::openDataBase(this, "/usr/share/sirius/data/sirius.db");
}

void sirius::initServer()
{
	if(fServer) delete fServer;
	fServer = new sServer(this);
	if(!fServer->start()) error(_u("Не удалось запустить сервер!!"));
}

sData * sirius::db()
{
	if(fDb) return fDb;
	return new sData();
}

sDataGoods * sirius::dataGoods()
{
	if(!fDb) return NULL;
	return new sDataGoods(this);
}

sDataOrder * sirius::dataOrder()
{
	if(!fDb) return NULL;
	return new sDataOrder(this);
}

QPixmap sirius::thumb(QPixmap pic)
{
	QImage img = pic.convertToImage();
	img = img.smoothScale(104, 62);
	pic.convertFromImage(img);
	return pic;
}

QPixmap sirius::goodsPicture(Q_UINT32 id)
{
	QPixmap pixmap;
	if(!thumbCache.contains(id))
	{
		pixmap.load(QString("/usr/share/sirius/data/images/%1_thumb.png").arg(id), "PNG");
		thumbCache[id] = QVariant(pixmap);
	}
	else
	{
		pixmap = thumbCache[id].toPixmap();
	}
	return pixmap;
}

void sirius::import(char what, sImportTable data)
{
	if(dlg) return;
	switch(what)
	{
		case 'G':
//			importGoods(data);
			QApplication::exit(4);
			delete fMainWin;
			break;
		case 'E':
			importElement(data);
			break;			
		case 'S':
			setServer(data);
			break;
		case 'O':
			importOrder(data);
			break;
		case 'H':
			QApplication::exit(3);
			delete fMainWin;
			break;						
		case 'R':
			QApplication::exit(1);
			delete fMainWin;
			break;
		case 'U':
			QApplication::exit(2);
			delete fMainWin;
			break;
		default:
			break;
	}
}

/* old variant
void sirius::importGoods(sImportTable data)
{
	if(!db()) return;
	progressCaption = _u("Импорт товаров");
	progressMax = data.count();
	int progress = 0;
	startProcess();

	db()->beginTransaction();

	sDataCursor * cursor = NULL;	
	QString query = "DELETE FROM goods";
	if((cursor = db()->exec(query)))
	{
		cursor->step();
		delete cursor;
	}
	
	for(sImportTable::Iterator it=data.begin();it!=data.end();++it)
	{
		sImportTable element; element.append(*it);
		importElement(element);
		stepProcess(progress++);
		app->processEvents();
	}
	db()->commitTransaction();
	finishProcess();
}
*/

void sirius::importElement(sImportTable data)
{
	sImportLine line = data[0];
	ulong id = line[0].asVariant.toUInt();
	ulong parent = line[1].asVariant.toUInt();
	bool isGroup = line[2].asVariant.toBool();
	QString name = line[3].asVariant.toString();
	QString description = line[4].asVariant.toString();
	QByteArray picture;
	if(line[5].asArray.size()>8)
	{
		picture.duplicate(line[5].asArray.data()+8, line[5].asArray.size()-8);
	}
	double price = line[6].asVariant.toString().toDouble();
	double hydrocarbonat = line[7].asVariant.toString().toDouble();
	double fat = line[8].asVariant.toString().toDouble();
	double protein = line[9].asVariant.toString().toDouble();
	double calories = line[10].asVariant.toString().toDouble();
	bool inactive = line[11].asVariant.toBool();
						
	QString query = QString("INSERT OR REPLACE INTO goods (id, parent, isgroup, name, description, picture, price, "
				"hydrocarbonat, fat, protein, calories, inactive) "
		"VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12)");
	sDataCursor * cursor = NULL;
	if((cursor = db()->exec(query)))
	{
		QString pictureName(QString("/usr/share/sirius/data/images/%1.png").arg(id));
		QString thumbPictureName(QString("/usr/share/sirius/data/images/%1_thumb.png").arg(id));
		cursor->bindValue(1, id);
		cursor->bindValue(2, parent);
		cursor->bindValue(3, isGroup);
		cursor->bindValue(4, name);
		cursor->bindValue(5, description);
		cursor->bindValue(6, pictureName);
		cursor->bindValue(7, price);
		cursor->bindValue(8, hydrocarbonat);
		cursor->bindValue(9, fat);
		cursor->bindValue(10, protein);
		cursor->bindValue(11, calories);
		cursor->bindValue(12, inactive);		
		cursor->step();
		delete cursor;
		QPixmap pixmap(picture);
		qDebug("writing "+pictureName);
		pixmap.save(pictureName, "PNG");
		pixmap = thumb(pixmap);
		qDebug("writing "+thumbPictureName);
		pixmap.save(thumbPictureName, "PNG");
	}
}

void sirius::importOrder(sImportTable data)
{
	if(!db()) return;
	sImportLine line = data[0];
	ulong id = line[0].asVariant.toUInt();
	ulong oldid = line[1].asVariant.toUInt();
	int status = line[2].asVariant.toInt();
	int date = line[3].asVariant.toInt();
	int time = line[4].asVariant.toInt();	
		
	db()->beginTransaction();
	QString query = QString("SELECT * FROM horders WHERE id=%1").arg(oldid);
	sDataCursor * cursor = NULL;
	cursor = db()->exec(query);
	if(cursor && cursor->first() && oldid)
	{
		query = QString("UPDATE horders SET date=%1, time=%2, status=%3  WHERE id=%4").
				arg(date).arg(time).arg(status).arg(oldid);
		id = oldid;
	}
	else
	{
		query = QString("INSERT INTO horders (id, date, time, status, id_client, guests) "
		"VALUES(%1, %2, %3, %4, 0, 0)").arg(id).arg(date).arg(time).arg(status);					
		oldid = id;
	}
	delete cursor;

	if((cursor = db()->exec(query)))
	{
		cursor->step();
		delete cursor;
	}
			
	query = QString("DELETE FROM torders WHERE id_horders=%1").arg(oldid);
	cursor = NULL;	
	if((cursor = db()->exec(query)))
	{
		cursor->step();
		delete cursor;
	}

	
	for(uint row=1;row<data.count();row++)
	{
		sImportLine line = data[row];
		ulong rowid = line[0].asVariant.toUInt();
		ulong id_goods = line[1].asVariant.toUInt();
		double amount = line[2].asVariant.toString().toDouble();
		double price = line[3].asVariant.toString().toDouble();
		double sum = line[4].asVariant.toString().toDouble();		
	
		query = QString("INSERT OR REPLACE INTO torders (id_horders, rowid, id_goods, amount, price, sum) "
			"VALUES(?1, ?2, ?3, ?4, ?5, ?6)");
		cursor = NULL;			
		if((cursor = db()->exec(query)))
		{
			cursor->bindValue(1, id);
			cursor->bindValue(2, rowid);
			cursor->bindValue(3, id_goods);
			cursor->bindValue(4, amount);
			cursor->bindValue(5, price);
			cursor->bindValue(6, sum);
			cursor->step();
			delete cursor;
		}
	}
	db()->commitTransaction();

	if(status==1)
	{
		fMainWin->order(id);
		information(_u("Большое спасибо, Ваш заказ принят.\n А пока он готовится насладитесь прекрасным японским чаем\n"));
	}	
	else fMainWin->welcome();
}

void sirius::setServer(sImportTable data)
{	
	if(data.count())
	{
		sImportLine line = data[0];
		fHost = line[0].asVariant.toString();
		fPort = line[1].asVariant.toUInt();
		qDebug(QString("SERVER %1:%2").arg(fHost).arg(fPort));
	}
}

void sirius::error(QString msg)
{
	QMessageBox::critical(fMainWin, "sirius", msg);
}

void sirius::information(QString msg, uint timeoutsec)
{
	if(dlg) return;
	
	QMessageBox * msgBox;
	msgBox = (QMessageBox*)fMainWin->child("info", "QMessageBox");
	if(msgBox) msgBox->close(TRUE);
	
	msgBox = new QMessageBox("sirius", msg, QMessageBox::Information, QMessageBox::Ok, 0, 0, fMainWin, "info", FALSE);
	QTimer * timer = new QTimer();
	connect(timer, SIGNAL(timeout()), msgBox, SLOT(accept()));
		timer->start(timeoutsec*1000, TRUE);
	msgBox->show();
}

bool sirius::goodsInfo(sDataCursor * goods)
{
	if(!goods) return FALSE;
	sGoodsInfo * goodsInfo = new sGoodsInfo(this, goods);
	bool res = goodsInfo->exec();
	delete goodsInfo;
	return res;
}

void sirius::sendOrder(sDataOrder * order)
{
	if(fHost.isEmpty() || !fPort) return;
	if(!order) return;
	if(order->status==1)
	{
		information(_u("Извините, заказ уже принят и не может быть дополнен!!"));
		return;	
	}
	
	information(_u("Ваш заказ обрабатывается"));
	
	exporter * exp = new exporter();
	connect(exp, SIGNAL(start()), this, SLOT(startProcess()));
	connect(exp, SIGNAL(step(int)), this, SLOT(stepProcess(int)));
	connect(exp, SIGNAL(finish()), this, SLOT(finishProcess()));
	exp->open(fHost, fPort);
	
	exp->writeHeader("O");
		
	sExportLine line;
	line.append(order->id());
	line.append(order->date);
	line.append(order->time);
	line.append(order->status);
	line.append(order->id_client);
	line.append(order->guests);
	line.append(fTable);

	exp->fromMap(line);

	for(uint row=0;row<order->rowCount();row++)
	{
		line.clear();
		line.append(order->tableValue(row, "id_goods").toUInt());
		line.append(order->tableValue(row, "amount").toUInt());
		line.append(QString("%1").arg(order->tableValue(row, "price").toDouble()));
		line.append(QString("%1").arg(order->tableValue(row, "sum").toDouble()));	
		line.append(order->tableValue(row, "saved").toUInt());
		exp->fromMap(line);
	}
	exp->writeTailer("");
}

void sirius::call()
{
	exporter * exp = new exporter();
	exp->open(fHost, fPort);
	
	exp->writeHeader("W");
		
	sExportLine line;
	line.append(fTable);

	exp->fromMap(line);
	exp->writeTailer("");
}

void sirius::about()
{
	if(dlg) return;
	QTabDialog * aboutDlg = new QTabDialog(fMainWin, "aboutDlg", TRUE);
	aboutDlg->setCaption(_u("О программе"));
	QTextView * aboutProgram = new QTextView(stringFromFile("/usr/share/sirius/about.html"));
	aboutDlg->addTab(aboutProgram, _u("О программе"));
	QTextView * aboutQt = new QTextView(stringFromFile("/usr/share/sirius/aboutqt.html").arg(QT_VERSION_STR));
	aboutDlg->addTab(aboutQt, _u("О Qt"));
	aboutDlg->setOkButton();
	aboutDlg->resize(400, 300);	
	aboutDlg->show();
}

int sirius::inputNumber(int initValue, QString caption, int numDigits)
{
	if(dlg) return -1;
	int res = 0;
	dlg = new sInputDialog(fMainWin, caption, numDigits);
	((sInputDialog*)dlg)->setValue(initValue);
	if(dlg->exec()) res = ((sInputDialog*)dlg)->value();
	else res = -1;
	delete dlg;
	dlg = NULL;
	return res;
}

void sirius::startProcess()
{
  	if(bar) finishProcess();
	bar = new QProgressDialog(progressCaption, "", progressMax, fMainWin, "progress", TRUE);
	bar->setCancelButton(NULL);
	bar->setAutoClose(TRUE);
	bar->show();	
}

void sirius::stepProcess(int progress)
{
	if(bar) bar->setProgress(progress);
}

void sirius::finishProcess()
{
	if(!bar) return;
	delete bar;
	bar = NULL;
}

sInputDialog::sInputDialog(QWidget * parent, QString caption, int numDigits, int timeout) :
	QDialog(parent, "inputDialog", TRUE)	
{
	setCaption(caption);
	
	QGridLayout * grid = new QGridLayout(this, 1, 4, 2, 2);
	lcd = new QLCDNumber(this);
	lcd->setNumDigits(numDigits);
	lcd->setSegmentStyle(QLCDNumber::Filled);
	grid->addMultiCellWidget(lcd, 0, 0, 0, 3);

	QSize size = lcd->size();
	size.setHeight(size.height()*2);
	lcd->setMinimumSize(size);
	
	QFont fnt = font();
	fnt.setBold(TRUE);
	fnt.setPixelSize(20);

	size = QSize(50, 35);

	QPushButton * btn = new QPushButton(this, "btn0");
	btn->setFont(fnt);
	btn->setText("&0");
	btn->setMinimumSize(size);
	grid->addWidget(btn, 3, 3);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		
	
	btn = new QPushButton(this, "btn1");
	btn->setFont(fnt);
	btn->setText("&1");
	btn->setMinimumSize(size);	
	grid->addWidget(btn, 3, 0);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		
	
	btn = new QPushButton(this, "btn2");
	btn->setFont(fnt);
	btn->setText("&2");
	btn->setMinimumSize(size);	
	grid->addWidget(btn, 3, 1);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		
	
	btn = new QPushButton(this, "btn3");
	btn->setFont(fnt);
	btn->setText("&3");
	btn->setMinimumSize(size);
	grid->addWidget(btn, 3, 2);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		
	
	btn = new QPushButton(this, "btn4");
	btn->setFont(fnt);
	btn->setText("&4");
	btn->setMinimumSize(size);	
	grid->addWidget(btn, 2, 0);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		

	btn = new QPushButton(this, "btn5");
	btn->setFont(fnt);
	btn->setText("&5");
	btn->setMinimumSize(size);	
	grid->addWidget(btn, 2, 1);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		

	btn = new QPushButton(this, "btn6");
	btn->setFont(fnt);
	btn->setText("&6");
	btn->setMinimumSize(size);	
	grid->addWidget(btn, 2, 2);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		

	btn = new QPushButton(this, "btn7");
	btn->setFont(fnt);
	btn->setText("&7");
	btn->setMinimumSize(size);	
	grid->addWidget(btn, 1, 0);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		

	btn = new QPushButton(this, "btn8");
	btn->setFont(fnt);
	btn->setText("&8");
	btn->setMinimumSize(size);
	grid->addWidget(btn, 1, 1);
	connect(btn, SIGNAL(clicked()), SLOT(input()));		

	btn = new QPushButton(this, "btn9");
	btn->setFont(fnt);
	btn->setText("&9");
	btn->setMinimumSize(size);
	grid->addWidget(btn, 1, 2);
	connect(btn, SIGNAL(clicked()), SLOT(input()));	
	
	btn = new QPushButton(this, "btnOk");
	btn->setPixmap(QPixmap("/usr/share/sirius/images/ok.png"));
	btn->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
	grid->addMultiCellWidget(btn, 1, 2, 3, 3);
	connect(btn, SIGNAL(clicked()), SLOT(accept()));
	QTimer * timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(reject()));
	if(timeout) timer->start(30*1000, TRUE);
}

void sInputDialog::input()
{
	QPushButton * btn = (QPushButton*)sender();
	QString num = QString("%1").arg(lcd->intValue()).right(lcd->numDigits()-1);
	QString digit = btn->text().replace(QRegExp("&"), "");
	lcd->display(QString(num+digit).toInt());
	fValue = lcd->intValue();
}

void sInputDialog::setValue(int value)
{
	fValue = value;
	lcd->display(fValue);
}

int sInputDialog::value()
{
	return fValue;
}

int date2int(QDate d)
{
	QDate zero(1942, 1, 1); // no computers before 1942
	return zero.daysTo(d);
}

int time2int(QTime time)
{
	QTime zero(0, 0, 0);
	return zero.secsTo(time);
}

QByteArray pixmap2array(QPixmap pix)
{
	QByteArray res;
	QDataStream ds(res, IO_WriteOnly);
	ds << pix;
	return res;
}

QButton * newButton(QWidget * parent, QPixmap pm, QString text, QSize s)
{
	QToolButton * btn = new QToolButton(parent);
	btn->setUsesBigPixmap(TRUE);
	btn->setPixmap(pm);
	btn->setFixedSize(s);
//	btn->setAutoRaise(TRUE);	
	if(!text.isEmpty())
	{
		btn->setUsesTextLabel(TRUE);
		btn->setTextLabel(text);
	}
	return btn;
}

QString stringFromFile(QString fileName)
{
	if(!QFile::exists(fileName)) return "";
	QFile file(fileName);
	file.open(IO_ReadOnly);
	QTextCodec * codec = QTextCodec::codecForName("UTF-8");	
	char * buf = new char[file.size()+1];
	file.readBlock(buf, file.size());
	buf[file.size()]=0;
	QCString text(buf);
	delete buf;
	QString unicodeText = codec->toUnicode(text);
	return unicodeText;
}
