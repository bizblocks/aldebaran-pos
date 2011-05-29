#include <qmessagebox.h>
#include "eqtable.h"
#include "engine.h"

#define TABLE "equipment"

alEqTable::alEqTable(QWidget * parent, alEngine * engine) :
	alDataTable(parent, engine, TABLE)
{
    headers << tr("name") << tr("type");
    fields[tr("name")] = "name";
    fields[tr("type")] = "type";
}

void alEqTable::init()
{
    hideVerticalHeader();    
    fData = new alDataEq(fEngine);
    setSelectionMode(NoSelection);    
    alDataTable::init();    
    load();
    setCurrentRow(0);    
}

alEqRecord * alEqTable::current()
{
    fData->seek(currentRow());
    return (alEqRecord*) fData->current();    
}

bool alEqTable::dialog(alEqRecord * device)
{
    int row = currentRow();
    if(device->dialog(this))
    {
	load();
	setCurrentRow(row);
	return TRUE;
    }
    return FALSE;	
}

bool alEqTable::editRowData()
{
    return dialog(current());
}

bool alEqTable::deleteRowData()
{    
    int row = currentRow();
    fData->seek(row);
    int res;
    res = QMessageBox::question(this, "aldebaran", tr("Delete element??"), QMessageBox::Yes,QMessageBox::No);	
    if(res==QMessageBox::Yes)
    {
	((alDataEq*)fData)->delElement();
	load();
    }
    setCurrentRow(row);
    return res;    
}

QPixmap alEqTable::pixmap(int r)
{
    Q_UNUSED(r);
    return QPixmap::fromMimeSource("device.png");
}

bool alEqTable::newElement()
{
    return dialog(((alDataEq*)fData)->newElement());
}
