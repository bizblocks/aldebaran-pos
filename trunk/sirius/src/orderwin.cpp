#include <qapplication.h>
#include <qframe.h>
#include <qlayout.h>
#include <qscrollview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qimage.h>
#include <qpaintdevicemetrics.h>
#include "sirius.h"
#include "mainwin.h"
#include "orderwin.h"
#include "orderview.h"

sOrderWin::sOrderWin(sirius * s, sMainWin * w) :
	QWidget((QWidget*)w, "orderWin", 0),
	fDataGoods(NULL),
	fOrder(NULL),
	fMainWin(w)
{
	infoMode = FALSE;
	currentGroup = 0;
	fSirius = s;
	if(fSirius)
	{
		fDataGoods = fSirius->dataGoods();
		fOrder = fSirius->dataOrder();
	}
	fCalcBtnSize = 60;	
}

void sOrderWin::init()
{
	QWidget * d = QApplication::desktop();
	int width = d->width();
	int height = d->height();
// 2/3 - scrollable table with goods
// 1/3 - order's table
	QFrame * goodsFrame = new QFrame(this, "goodsFrame");
	goodsFrame->move(2, 2);
	width = width*7/12-4;
	height -= 4;
	goodsFrame->resize(width, height);
	QGridLayout * grid = new QGridLayout(goodsFrame, 2, 1);
	svGoods = new sScrollView(goodsFrame, "goods");
	grid->addWidget(svGoods, 0, 0);
	fCalcBtnSize = (width-svGoods->verticalScrollBar()->width()-12) / ITEMS_IN_ROW;
	
	QFrame * btnFrame = new QFrame(goodsFrame, "btnFrame");	
	grid->addWidget(btnFrame, 1, 0);
	QGridLayout * btnGrid = new QGridLayout(btnFrame, 1, 5);
	
	QSize s(60, 60);
	QButton * btn;
	btn = newButton(btnFrame, QPixmap("/usr/share/sirius/images/ok.png"), _u("Заказ"), s);
	btnGrid->addWidget(btn, 0, 0);
	connect(btn, SIGNAL(clicked()), SLOT(ok()));	
	
	btn = newButton(btnFrame, QPixmap("/usr/share/sirius/images/stop_cancel.png"), _u("Отмена"), s);
	btnGrid->addWidget(btn, 0, 1);	
	connect(btn, SIGNAL(clicked()), SLOT(cancel()));
	
	btn = newButton(btnFrame, QPixmap("/usr/share/sirius/images/help.png"), _u("Помощь"), s);
	btnGrid->addWidget(btn, 0, 2);
	connect(btn, SIGNAL(clicked()), SLOT(help()));

	btn = newButton(btnFrame, QPixmap("/usr/share/sirius/images/info.png"), _u("О блюде"), s);
	btnGrid->addWidget(btn, 0, 3);
	connect(btn, SIGNAL(clicked()), SLOT(setInfoMode()));

	btn = newButton(btnFrame, QPixmap("/usr/share/sirius/images/call.png"), _u("Вызов"), s);
	btnGrid->addWidget(btn, 0, 4);
	if(fSirius) connect(btn, SIGNAL(clicked()), fSirius, SLOT(call()));	

	btn = newButton(btnFrame, QPixmap("/usr/share/sirius/images/about.png"), _u("О ..."), s);
	btnGrid->addWidget(btn, 0, 6);
	if(fSirius) connect(btn, SIGNAL(clicked()), fSirius, SLOT(about()));	
	
	otOrder = new sOrderView(fSirius, this);
	otOrder->move(width+4, 2);
	otOrder->resize(width*5/7, height);

	reload();
	show();
}

void sOrderWin::reload()
{
	clearItems();
	if(!fDataGoods)	return;
	QPixmap grPixmap = QPixmap("/usr/share/sirius/images/group.png");
	QPixmap elPixmap = QPixmap("/usr/share/sirius/images/element.png");
	if(currentGroup)
	{
		QPixmap levelUp = QPixmap("/usr/share/sirius/images/levelup.png");
		addGoodsItem(levelUp, _u("На уровень выше"), FALSE, 0);
	}
	fDataGoods->useParent(currentGroup);
	sDataCursor * cursor = fDataGoods->select();
	if(!cursor) qDebug("reload select fail");
	if(cursor)
	{
		if(cursor->first()) do
		{		
			QString name = cursor->value("name").toString();
			bool isgroup = cursor->value("isgroup").toBool();
			bool inactive = cursor->value("inactive").toBool();
//			QPixmap pic = fDataGoods->picture(cursor);
			Q_UINT32 id = cursor->value("id").toUInt();
			QPixmap pic = fSirius->goodsPicture(id);
			if(isgroup) addGoodsItem(grPixmap, _u(name), inactive, id);
			else
			{
				if(pic.isNull()) addGoodsItem(elPixmap, _u(name), inactive, id);
				else addGoodsItem(pic, _u(name), inactive, id);
			}
		}while(cursor->next());
		delete cursor;
	}
	svGoods->resizeContents(svGoods->contentsWidth(), (fCalcBtnSize+2) * (buttons.count()/ITEMS_IN_ROW+1) +2 );
	svGoods->verticalScrollBar()->setSteps(fCalcBtnSize, svGoods->verticalScrollBar()->pageStep());
	svGoods->setContentsPos(0, 0);	
}

void sOrderWin::clearItems()
{
	for(sItemList::Iterator it=buttons.begin();it!=buttons.end();++it)
	{
		delete *it;
	}
	buttons.clear();
}

void sOrderWin::addGoodsItem(QPixmap p, QString t, bool inactive, Q_UINT32 id)
{
	sItem * item = new sItem(svGoods, p, t, inactive, id);
	connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
	item->setFixedSize(fCalcBtnSize, fCalcBtnSize);
	int x = (fCalcBtnSize+2) * (buttons.count()%ITEMS_IN_ROW) + 2;
	int y = (fCalcBtnSize+2) * (buttons.count()/ITEMS_IN_ROW) + 2;
	buttons.append(item);	
	svGoods->moveChild(item, x, y);
	item->show();
}

void sOrderWin::itemClicked()
{
	if(!fDataGoods) return;
	sItem * item = (sItem*) sender();
	if(!item) return;
	if(item->inactive() && !infoMode) return;	
	Q_UINT32 id = item->id();
	sDataCursor * cursor = NULL;
	if(id) cursor = fDataGoods->select(id);
	else cursor = fDataGoods->select(currentGroup);
	item = NULL;
	if(cursor)
	{
		cursor->first();
		if(cursor->value("isgroup").toBool())
		{
			if(!id) id = cursor->value("parent").toUInt();
			currentGroup = id;
			reload();
		}
		else
		{
			bool addItem = TRUE;
			if(infoMode)
			{
				setInfoMode();
				addItem = fSirius->goodsInfo(cursor);
			}
			if(fOrder && addItem) fOrder->addItem(cursor);
		}
		delete cursor;		
	}
}

void sOrderWin::openOrder(Q_INT32 id)
{
	if(!fSirius) return;
	if(id>0) fOrder->select(id);
	else if(!id)
	{
		fOrder->newOrder();
		fOrder->guests = 1;
	}
	else
	{
		int g = fSirius->inputNumber(0, _u("Сколько Вас??"), 2);
		if(g<0)
		{
			cancel(); 
			return;
		}		
		else if(!g) g = 1;
		fOrder->newOrder();
		fOrder->guests = g;
	}
	otOrder->clear();
	otOrder->setOrder(fOrder);
	fOrder->selectRows();
}

void sOrderWin::setInfoMode()
{
	infoMode = !infoMode;
}

void sOrderWin::help()
{
	fMainWin->help(FALSE);
}

void sOrderWin::ok()
{	
	fOrder->save();
	fSirius->sendOrder(fOrder);
}

bool sOrderWin::close()
{
	if(fOrder) fOrder->save();
	return QWidget::close();
}

void sOrderWin::cancel()
{
	if(fOrder->status)
	{
		fSirius->information(_u("Извините, но ваш заказ сохранён и может быть отменён только администратором!!"));
		return;
	}
	fOrder->kill();
	otOrder->clear();
	delete fOrder;
	fOrder = NULL;
	fMainWin->next();
}

sItem::sItem(QWidget * p, QPixmap pm, QString text, bool inactive, Q_UINT32 id):
	QToolButton(p)
{
	fId = id;
	fInactive = inactive;
	setPixmap(pm);
	setTextLabel(text, true);
	setUsesBigPixmap(true);
	setUsesTextLabel(true);
}

void sItem::drawButtonLabel(QPainter * p)
{
	int x, y, w, h;
	style().toolButtonRect(0, 0, width(), height() ).rect( &x, &y, &w, &h );
	int fh = fontMetrics().height() * 3;	
	QPixmap pm = *pixmap();

	style().drawItem( p, x, y, w, h - fh, AlignCenter, colorGroup(), TRUE, &pm, QString::null );
	p->setFont(font());
	style().drawItem( p, x, h - fh, w, fh+1,
		AlignCenter | WordBreak,
		colorGroup(), isEnabled(),
		0, textLabel() );
	if(fInactive)
	{
		QFont fnt = font();
		fnt.setPointSize(12);
		fnt.setBold(TRUE);
		p->setFont(fnt);
		style().drawItem( p, x, y, w, h-fh,
			AlignRight | WordBreak,
			colorGroup(), isEnabled(),
			0, _u("отсутствует"),  -1, new QColor(0xFF, 0x00, 0x00));
	}
}

sScrollView::sScrollView(QWidget * parent, QString name) :
	QScrollView(parent, name)
{
	sizeChanged = FALSE;
	enableClipper(TRUE);
	setFrameShadow(QFrame::Raised);
	setStaticBackground(FALSE);
	QColorGroup gr = colorGroup();
	gr.setColor(QColorGroup::Dark, parent->backgroundColor());
	setPalette(QPalette(gr, gr, gr));
	setBackgroundColor(parent->backgroundColor());
	setVScrollBarMode(QScrollView::AlwaysOn);
	setMargins(0, 0, verticalScrollBar()->width(), 0);	
	verticalScrollBar()->setFixedWidth(verticalScrollBar()->width()*2);
}

void sScrollView::setVBarGeometry(QScrollBar & vbar, int x, int y, int w, int h)
{	
	vbar.setGeometry(x-w, y, w, h);
}

