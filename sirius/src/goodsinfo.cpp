#include <qapplication.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qlayout.h>
#include <qtextcodec.h>
#include <qtextview.h>
#include <qtoolbutton.h>
#include <qstylesheet.h>
#include "mainwin.h"
#include "sirius.h"
#include "goodsinfo.h"

class sStyleSheet : public QStyleSheet
{
public:
	sStyleSheet(QObject * parent) : QStyleSheet(parent) {};
	QString stylize(QString text)
	{
		int count = 0;
		int index;
		while((index=text.find("<span "))>-1)
		{	
			QString tag = QString("span%1").arg(count++);
			int rb = text.find(">", index);
			QString styleText = text.mid(index+6, rb-index-6);
			text = text.left(index)+"<"+tag+">"+ text.mid(rb+1);
			index = text.find("</span>");
			text = text.left(index) + "</" + tag + ">" + text.mid(index+7);
			QStyleSheetItem * style = new QStyleSheetItem(this, tag);
//			qDebug(styleText);
			styleText = styleText.replace(QRegExp("style=\""), "").replace(QRegExp("\""), "");
			QStringList pairs = QStringList::split(";", styleText);
			for(uint p=0;p<pairs.count();p++)
			{
				QStringList kv = QStringList::split(":", pairs[p]);
				if(kv[0]=="font-weight")
				{
					style->setFontWeight(kv[1].toUInt()/8);
				}
				else if(kv[0]=="color")
				{
					style->setColor(kv[1]);
				}
				else if(kv[0]=="text-decoration")
				{
					if(kv[1]=="underline") style->setFontUnderline(TRUE);
				}
				else if(kv[0]=="font-style")
				{
					if(kv[1]=="italic") style->setFontItalic(TRUE);
				}
			}
		}	
		return text;
	}
};

sGoodsInfo::sGoodsInfo(sirius * s, sDataCursor * goods):
	QDialog(s->mainWin(), "goodsInfo", TRUE)
{
	fSirius = s;
	name = _u(goods->value("name").toString());
	price = goods->value("price").toDouble();
	description = _u(goods->value("description").toString());
	hc = goods->value("hydrocarbonat").toDouble();
	fat = goods->value("fat").toDouble();
	protein = goods->value("protein").toDouble();
	calories = goods->value("calories").toDouble();			
	picture = sDataGoods::picture(goods);
	if(picture.isNull()) picture = QPixmap("/usr/share/sirius/images/binfo.png");
	init();
}

sGoodsInfo::~sGoodsInfo()
{
	if(tv) delete tv;
}

void sGoodsInfo::init()
{
	QWidget * d = QApplication::desktop();
	int width = d->width();
	int height = d->height();

	QGridLayout * grid = new QGridLayout(this, 2, 1);
		
	QString unicodeText = stringFromFile("/usr/share/sirius/template.html")
		.arg(name)
		.arg(description)
		.arg(price, 5, 'F', 2)
		.arg(protein, 6, 'F', 2)
		.arg(fat, 6, 'F', 2)
		.arg(hc, 6, 'F', 2)
		.arg(calories, 6, 'F', 2);

	tv = new QTextView(this);
	sStyleSheet * sh = new sStyleSheet(tv);	
	tv->setStyleSheet(sh);
	
	QPixmap pic;
	tv->mimeSourceFactory()->setPixmap("picture", picture);	
	tv->setText(sh->stylize(unicodeText), "");	
	tv->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
	tv->setPaper(QBrush(fSirius->mainWin()->backgroundColor()));
	grid->addWidget(tv, 0, 0);

	QGridLayout * btnGrid = new QGridLayout(grid, 1, 4);
	QToolButton * btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/ok.png"), _u("Добавить в заказ"), QSize(120, 50));
	connect(btn, SIGNAL(clicked()), SLOT(accept()));
	btnGrid->addWidget(btn, 0, 0);

	btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/stop_cancel.png"), _u("Отмена"), QSize(120, 50));
	connect(btn, SIGNAL(clicked()), SLOT(reject()));
	btnGrid->addWidget(btn, 0, 1);

	btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/levelup.png"), _u("Вверх"), QSize(120, 50));
	connect(btn, SIGNAL(clicked()), SLOT(scrollUp()));
	btnGrid->addWidget(btn, 0, 2);

	btn = (QToolButton*)newButton(this, QPixmap("/usr/share/sirius/images/down.png"), _u("Вниз"), QSize(120, 50));
	connect(btn, SIGNAL(clicked()), SLOT(scrollDown()));
	btnGrid->addWidget(btn, 0, 3);
	
	setFixedSize(width-30, height-30);	
}

void sGoodsInfo::scrollUp()
{
	tv->scrollBy(0, -tv->height());
	tv->update();
}

void sGoodsInfo::scrollDown()
{
	tv->scrollBy(0, tv->height());
	tv->update();	
}


