#include <qmessagebox.h>
#include "engine.h"
#include "ordertable.h"
#include "data/dataordert.h"

#define TABLE "order_table"

alOrderTable::alOrderTable(QWidget * parent, alEngine * engine, alOrderRecord * order) : 
	alDataTable(parent, engine, TABLE)
{
    headers.clear();
    fields.clear();
    headers << tr("#") << tr("item") << tr("amount") << tr("price") << tr("sum");
    fields[tr("#")] = "ln";
    fields[tr("item")] = "item";
    fields[tr("amount")] = "amount";
    fields[tr("price")] = "price";
    fields[tr("sum")] = "summ";
    maxWidthColumn = "item";
    fOrder = order;
}

void alOrderTable::init()
{
    fData = fOrder->getDocumentTable();
    hideVerticalHeader();
    setSelectionMode(NoSelection);    
    alDataTable::init();
    if(fData) ((alDataOrderTable*) fData)->select();
    load();
}

alOrderLine * alOrderTable::newLine()
{
    setNumRows(numRows()+1);
    setCurrentRow(numRows()-1);
    alOrderLine * line = ((alDataOrderTable*)fData)->newLine();
    line->setUser(fEngine->currentUser());
    return line;
}

alOrderLine * alOrderTable::getLine(int r)
{
    return ((alDataOrderTable*)fData)->getLine(r);
}

alOrderLine * alOrderTable::addItem(alGoodsRecord * item)
{
    alOrderLine * line = NULL;
    for(int i=0;i<numRows();i++)
    {
	alOrderLine * l = ((alDataOrderTable*)fData)->getLine(i);
	if(l->item()->id()==item->id())
	{
	    setCurrentRow(i);
	    line = l;
	    break;
	}
    }
    
    if(!line) line = newLine();
    if(!line) return NULL;
    
    line->setItem(item);
    fillLine(currentRow());
    return line;
}

void alOrderTable::fillLine(int r)
{
    if(!fData) return;
    alOrderLine * line = ((alDataOrderTable*)fData)->getLine(r);
    if(!line) return;
    setValue(r, "ln", line->lineNum());
    setValue(r, "item", line->itemText());
    setValue(r, "price", line->price());
    setValue(r, "amount", line->amount());
    setValue(r, "summ", line->summ());
    adjustColumns();
}

double alOrderTable::amount()
{
    if(currentRow()<0) return 0;    
    alOrderLine * line = ((alDataOrderTable*)fData)->getLine(currentRow());    
    if(line) return line->amount();
    return 0;
}

void alOrderTable::setAmount(double q)
{
    if(currentRow()<0) return;
    if(!checkRights(rOrderEditStrangeLines)) return;
    alOrderLine * line = ((alDataOrderTable*)fData)->getLine(currentRow());
    if(!line) return;
    if(q==0.)
    {
	delLine(currentRow());
	return;
    }
    line->setAmount(q);    
    fillLine(currentRow());
}

bool alOrderTable::delLine(int r)
{
    if(!checkRights(rOrderEditStrangeLines)) return FALSE;    
    removeRow(r);
    return ((alDataOrderTable*)fData)->delLine(r);    
}

double alOrderTable::total(QString attr)
{
    return ((alDataOrderTable*)fData)->total(attr);
}

void alOrderTable::load()
{ 
    setNumRows(((alDataOrderTable*)fData)->count());
    for(int r=0;r<((alDataOrderTable*)fData)->count();r++)
    {
	fillLine(r);
    }
}

bool alOrderTable::checkRights(alRights r)
{
    alUserRecord * user = fEngine->currentUser();
    if(!user) return TRUE;
    if(user->right(r)) return TRUE;    
//not ordinary rights
    if(r == rOrderEditStrangeLines)
    {
	alOrderLine * line = ((alDataOrderTable*)fData)->getLine(currentRow());
	if(line->user()->id()!=user->id())
	{
	    QMessageBox::warning(this, "aldebaran", tr("You don't have rights to edit lines of another user"));
	    return FALSE;
	} 
	else return TRUE;
    }
//ordinary rights	    
    else return user->right(r);
    return FALSE;
}
