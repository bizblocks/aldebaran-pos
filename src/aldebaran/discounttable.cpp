#include <qmessagebox.h>
#include "discounttable.h"
#include "engine.h"

#define TABLE "discount"

alDiscountTable::alDiscountTable(QWidget * parent, alEngine * engine) :
	alDataTable(parent, engine, TABLE)
{
    headers << tr("name") << tr("type") << tr("value") << tr("protect");
    fields[tr("name")] = "name";
    fields[tr("type")] = "type";
    fields[tr("value")] = "value";
    fields[tr("protect")] = "protect";
}

void alDiscountTable::init()
{
    hideVerticalHeader();    
    fData = new alDataDiscount(fEngine);
    setSelectionMode(NoSelection);    
    alDataTable::init();    
    load();
    setCurrentRow(0);    
}

alDiscountRecord * alDiscountTable::current()
{
    fData->seek(currentRow());
    return (alDiscountRecord*) fData->current();    
}

bool alDiscountTable::dialog(alDiscountRecord * discount)
{
    int row = currentRow();
    if(discount->dialog(this))
    {
	load();
	setCurrentRow(row);
	return TRUE;
    }
    return FALSE;	
}

bool alDiscountTable::editRowData()
{
    return dialog(current());
}

bool alDiscountTable::deleteRowData()
{    
    int row = currentRow();
    fData->seek(row);
    int res;
    res = QMessageBox::question(this, "aldebaran", tr("Delete element??"), QMessageBox::Yes,QMessageBox::No);	
    if(res==QMessageBox::Yes)
    {
	((alDataDiscount*)fData)->delElement();
	load();
    }
    setCurrentRow(row);
    return res;    
}

QVariant alDiscountTable::displayValue(QString attr, QVariant val)
{
    if(attr=="protect" || attr==tr("protect"))
    {
	if(val.toBool()) return QPixmap::fromMimeSource("checked.png");
	else return QPixmap::fromMimeSource("unchecked.png");
    }
    else return val;
}

QPixmap alDiscountTable::pixmap(int r)
{
    Q_UNUSED(r);
    return QPixmap::fromMimeSource("element.png");
}

bool alDiscountTable::newElement()
{
    return dialog(((alDataDiscount*)fData)->newElement());
}
