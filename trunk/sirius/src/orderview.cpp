#include <qapplication.h>
#include <qheader.h>
#include <qpushbutton.h>
#include <qlistview.h>
#include <qsimplerichtext.h>
#include <qlabel.h>
#include "sirius.h"
#include "orderview.h"

static QPixmap * plus = NULL, * minus = NULL;

class sHeaderItem : public QListViewItem
{
public:
	sHeaderItem(QListView * p, QString text, QString text1, QString text2);
	virtual void setup();
	virtual void paintCell(QPainter * p, const QColorGroup & cg, int column, int width, int align);
protected:
	sHeaderItem(QListViewItem * p);
	sHeaderItem(QListView * p);			
	QColor background;
private:
	int calcHeight;
	QPushButton * btnUp;
	QPushButton * btnDown;
};

sHeaderItem::sHeaderItem(QListView * p, QString text, QString text1, QString text2):
	QListViewItem(p)
{
	setText(0, text);
	setText(1, text1);
	setText(2, text2);
	background = Qt::lightGray;
	btnUp = new QPushButton(listView()->viewport());
	QPixmap up = QPixmap("/usr/share/sirius/images/levelup.png");
	btnUp->setPixmap(up);
	btnDown = new QPushButton(listView()->viewport());
	btnDown->setPixmap(QPixmap("/usr/share/sirius/images/down.png"));
	QObject::connect(btnUp, SIGNAL(clicked()), listView()->parent(), SLOT(onUp()));
	QObject::connect(btnDown, SIGNAL(clicked()), listView()->parent(), SLOT(onDown()));	
	calcHeight = up.height()+2;
}

sHeaderItem::sHeaderItem(QListViewItem * p) :
	QListViewItem(p->listView(), p)
{
	btnUp = NULL;
	btnDown = NULL;
	calcHeight = QApplication::fontMetrics().height()*2+2;
}

sHeaderItem::sHeaderItem(QListView * p) :
	QListViewItem(p)
{
	btnUp = NULL;
	btnDown = NULL;
	calcHeight = QApplication::fontMetrics().height()*2+2;
}

void sHeaderItem::setup()
{
	QListViewItem::setup();
	setHeight(calcHeight);
}

void sHeaderItem::paintCell(QPainter * p, const QColorGroup & cg , int column, int width, int align)
{
	QRect view(0, 0, width, height());
	p->fillRect(view, background);
	QString txt = text(column);
	if(txt.contains("<") && txt.contains(">"))
	{
		QSimpleRichText richText(txt, p->font());   	
		richText.draw(p, 0, 0, view, cg);
	}
	else
	{
		p->drawText(1, 0, width, height(), DontClip | align, txt);
	}
	p->setBrush(Qt::black);
	p->drawLine(1, height(), width, height());
	int posX = listView()->columnWidth(0) + listView()->columnWidth(1)+1;	
	if(column==2 && btnUp && itemPos()+2 != btnUp->y())
	{
		btnUp->hide();
		btnUp->setGeometry(posX, itemPos()+2, width, height()-2);
		btnUp->show();
	}
	if(column==3 && btnDown && itemPos()+2 != btnDown->y())
	{
		btnDown->hide();	
		btnDown->setGeometry(posX+width, itemPos()+2, width, height()-2);
		btnDown->show();		
	}	
}

class sOrderItem : sHeaderItem
{
public:
	sOrderItem(QListView *, QString name = "", int amount = 0, double price=0.0, double sum = 0.0, int row = -1);
	sOrderItem(QListViewItem *, QString name = "", int amount = 0, double price=0.0, double sum = 0.0, int row = -1);
	virtual ~sOrderItem();
	void setName(QString name);
	void setAmount(int amount);
	void setPrice(double price);
	void setSum(double price);	
	void setRow(int row);
	int row() { return fRow; };	
	virtual void paintCell(QPainter * p, const QColorGroup & , int column, int width, int align);
	void hide();
	virtual int width(const QFontMetrics &, const QListView *lv, int column) const { return lv->columnWidth(column); };
protected:
	void init(QString name="", int amount=0, double price=0.0, double sum=0.0, int row=-1);
private:
	int fRow;
	int calcHeight;
	QString fName;
	int fAmount;
	double fPrice;
	double fSum;
};

sOrderItem::sOrderItem(QListViewItem * p, QString name, int amount, double price, double sum, int row) :
	sHeaderItem(p)
{
	init(name, amount, price, sum, row);
}

sOrderItem::sOrderItem(QListView * p, QString name, int amount, double price, double sum, int row) :
	sHeaderItem(p)
{
	init(name, amount, price, sum, row);
}


void sOrderItem::init(QString name, int amount, double price, double sum, int row)
{
	setName(name);
	setAmount(amount);
	setPrice(price);
	setSum(sum);
	calcHeight = QApplication::fontMetrics().height()*2+2;
	fRow = row;
	background = Qt::white;
}

sOrderItem::~sOrderItem()
{
}

void sOrderItem::setName(QString name)
{
	fName = name;
	QString text = QString("<nobr>%1</nobr>\n<font color=#FF0000><b>%2</b></font>").arg(fName).arg(fAmount);
	setText(0, text);
}

void sOrderItem::setAmount(int amount)
{
	fAmount = amount;
	setName(fName);
}

void sOrderItem::setPrice(double price)
{
	fPrice = price;
	QString text = QString("%1\n%2").arg(fPrice, 5, 'F', 2).arg(fSum, 6, 'F', 2);	
	setText(1, text);
}

void sOrderItem::setSum(double sum)
{
	fSum = sum;
	setPrice(fPrice);
}

void sOrderItem::setRow(int row)
{
	fRow = row;
}

void sOrderItem::paintCell(QPainter * p, const QColorGroup & cg, int column, int width, int align)
{
	sHeaderItem::paintCell(p, cg, column, width, align);
	if(column==2) p->drawPixmap((width-(*plus).width())/2, (height()-(*plus).height())/2, *plus);
	if(column==3) p->drawPixmap((width-(*minus).width())/2, (height()-(*minus).height())/2, *minus);	
}

void sOrderItem::hide()
{
	setHeight(0);
}

sOrderView::sOrderView(sirius * s, QWidget * parent):
	QWidget(parent, "orderView")
{
	headerView = new QListView(this, "headerView");
	view = new QListView(this, "view");
		
	headerView->setSelectionMode(QListView::NoSelection);
	headerView->setFocusPolicy(QListView::NoFocus);
	headerView->setAllColumnsShowFocus(TRUE);
	headerView->setSorting(-1);
	headerView->setVScrollBarMode(QListView::AlwaysOff);
	headerView->setHScrollBarMode(QListView::AlwaysOff);
	view->setSelectionMode(QListView::NoSelection);
	view->setFocusPolicy(QListView::NoFocus);
	view->setAllColumnsShowFocus(TRUE);
	view->setSorting(-1);
	view->setVScrollBarMode(QListView::AlwaysOff);
	view->setHScrollBarMode(QListView::AlwaysOff);
	
	totalView = new QLabel(this, "totalView");
	totalView->setAlignment(AlignTop | AlignLeft);
	
	fSirius = s;
	fItems.clear();
	headerView->header()->hide();
	view->header()->hide();	
	for(int col=0;col<4;col++)
	{
		headerView->addColumn("", 100);	
		headerView->setColumnWidthMode(col, QListView::Manual);
		view->addColumn("", 100);	
		view->setColumnWidthMode(col, QListView::Manual);		
	}
	headerView->setColumnAlignment(1, AlignRight);
	view->setColumnAlignment(1, AlignRight);
	fHeader = new sHeaderItem(headerView, _u("Блюдо\nКоличество"), _u("Цена\nСумма"), _u(""));
	connect(view, SIGNAL(clicked(QListViewItem*, const QPoint&, int)), SLOT(onItem(QListViewItem*, const QPoint&, int)));	
//just a little hack
	plus = new QPixmap("/usr/share/sirius/images/plus.png");
	minus = new QPixmap("/usr/share/sirius/images/minus.png");
}

sOrderView::~sOrderView()
{
	if(plus) delete plus;
	if(minus) delete minus;
}

void sOrderView::resizeEvent(QResizeEvent *)
{
	int fullWidth = width();
	int headerHeight = fHeader->height()+4;	
	headerView->setGeometry(0, 0, fullWidth, fHeader->height()+4);
	totalView->setGeometry(0, height()-60, fullWidth, 60);
	view->setGeometry(0, headerHeight, fullWidth, height()-headerHeight-60);
	
	headerView->setColumnWidth(0, fullWidth * 13/24-1);
	headerView->setColumnWidth(1, fullWidth * 5/24);
	headerView->setColumnWidth(2, fullWidth * 3/24-1);
	headerView->setColumnWidth(3, fullWidth * 3/24-1);
	view->setColumnWidth(0, fullWidth * 13/24-1);
	view->setColumnWidth(1, fullWidth * 5/24);
	view->setColumnWidth(2, fullWidth * 3/24-1);
	view->setColumnWidth(3, fullWidth * 3/24-1);	
}

void sOrderView::onItem(QListViewItem * item, const QPoint&, int c)
{
	if(!item) return;
	if(c==2) emit plusClicked(((sOrderItem*)item)->row());	
	if(c==3) emit minusClicked(((sOrderItem*)item)->row());
}

void sOrderView::onUp()
{
	if(fItems.count()) view->scrollBy(0, -((QListViewItem*)fItems[0])->height());
}

void sOrderView::onDown()
{
	if(fItems.count()) view->scrollBy(0, ((QListViewItem*)fItems[0])->height());
}

void sOrderView::setOrder(sDataOrder * order)
{
	fOrder = order;
	connect(order, SIGNAL(rowChanged(int)), SLOT(updateRow(int)));
	connect(this, SIGNAL(plusClicked(int)), fOrder, SLOT(inc(int)));
	connect(this, SIGNAL(minusClicked(int)), fOrder, SLOT(dec(int)));
}

void sOrderView::updateRow(int row)
{
	if(!fOrder) return;
	sDataCursor * goods = fSirius->dataGoods()->select(fOrder->tableValue(row, "id_goods").toUInt());
	if(!goods || !goods->first()) return;
	QString name = _u(goods->value("name").toString());
	int amount = fOrder->tableValue(row, "amount").toUInt();
	double price = fOrder->tableValue(row, "price").toDouble();
	double sum = fOrder->tableValue(row, "sum").toDouble();
	delete goods;
	
	sOrderItem * item = NULL;
	if((uint)row<fItems.count()) item = fItems[row];
	if(!item)
	{
		if(!fItems.count())
		{
			item = new sOrderItem((QListView*)view, name, amount, price, sum, row);
		}
		else
		{
			item = new sOrderItem((QListViewItem*)fItems[fItems.count()-1], name, amount, price, sum, row);
		}
		fItems.append(item);
		onDown();
	}
	else
	{
		if(amount==0)
		{		
			fItems.remove(fItems.at(row));		
			enumerate();
			delete item;			
		}
		else
		{
			item->setName(name);
			item->setAmount(amount);		
			item->setPrice(price);
			item->setSum(sum);
		}
	}
	showTotals();
}

void sOrderView::showTotals()
{
	if(!fOrder) return;
	QString totalText = _u("<font color=#0000FF><b>Гостей: %1 &nbsp; </b></font><font color=#FF0000><b>Итого: %2</b></font><br>Белки: %3, Жиры: %4, Углеводы: %5, Калории: %6");
	totalText = totalText.arg(fOrder->guests);	
	totalText = totalText.arg(fOrder->total("sum"), 6, 'F', 2);
	totalText = totalText.arg(fOrder->total("protein"), 6, 'F', 2);
	totalText = totalText.arg(fOrder->total("fat"), 6, 'F', 2);
	totalText = totalText.arg(fOrder->total("hydrocarbonat"), 6, 'F', 2);
	totalText = totalText.arg(fOrder->total("calories"), 7, 'F', 3);
	totalView->setText(totalText);
}

void sOrderView::enumerate()
{
	for(uint r=0;r<fItems.count();r++)
	{
		fItems[r]->setRow(r);
	}
}

void sOrderView::clear()
{
	fItems.clear();
	view->clear();
}

