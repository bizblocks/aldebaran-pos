#ifndef ORDERWIN_H
#define ORDERWIN_H

#include <qwidget.h>
#include <qtoolbutton.h>
#include <qscrollview.h>

class QLabel;
class sMainWin;
class sDataGoods;
class sGoodsRecord;
class sirius;
class sItem;

typedef QValueList<sItem *> sItemList;

#define ITEMS_IN_ROW		3

class sOrderView;
class sScrollView;
class sDataOrder;

class sOrderWin : public QWidget
{
	Q_OBJECT
public:
	sOrderWin(sirius * s, sMainWin * w);
	void init();
	void reload();
	void openOrder(Q_INT32 id=-1);
protected:
	void addItem();
	void addGoodsItem(QPixmap p, QString t, bool inactive, Q_UINT32 id);
	void clearItems();
public slots:
	void itemClicked();
	void setInfoMode();
	void help();
	void ok();
	bool close();	
	void cancel();
private:
	sirius * fSirius;
	sDataGoods * fDataGoods;
	sScrollView * svGoods;
	sOrderView * otOrder;
	sDataOrder * fOrder;
	Q_UINT32 currentGroup;
	sMainWin * fMainWin;
	sItemList buttons;
	int fCalcBtnSize;
	bool infoMode;
};

class sItem : public QToolButton
{
	Q_OBJECT
public:
	sItem(QWidget * p, QPixmap pix, QString text, bool inactive, Q_UINT32 id);
	Q_UINT32 id() { return fId; };
	bool inactive() { return fInactive; }; 
protected:
	virtual void drawButtonLabel(QPainter * p);
private:
	Q_UINT32 fId;
	bool fInactive;
};

class sScrollView : public QScrollView
{
	Q_OBJECT
public:
	sScrollView(QWidget * parent, QString name);
protected:
	virtual void setVBarGeometry(QScrollBar & vbar, int x, int y, int w, int h);
	bool sizeChanged;
};

#endif
