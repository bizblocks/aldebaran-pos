#include <qmessagebox.h>
#include <qpopupmenu.h>
#include "data/datagoods.h"
#include "data/.ui/goodselement.h"
#include "data/.ui/goodsgroup.h"
#include "goodstable.h"
#include "engine.h"

#define TABLE "goods"

alGoodsTable::alGoodsTable(QWidget * parent, alEngine * engine) :
	alDataTable(parent, engine, TABLE)
{
    currentGroup = 0;
    headers << tr("name") << tr("price") << tr("ext.code");
    fields[tr("name")] = "name";
    fields[tr("price")] = "price";
    fields[tr("ext.code")] = "externalcode";
    maxWidthColumn = "name";
}

void alGoodsTable::init()
{
    contextMenu->clear();
    if(!fSelect)
    {
	contextMenu->insertItem(QIconSet(QPixmap::fromMimeSource("element.png")), tr("New element"), this, SLOT(newElement()));
	contextMenu->insertItem(QIconSet(QPixmap::fromMimeSource("group.png")), tr("New group"), this, SLOT(newGroup()));
	contextMenu->insertItem(QIconSet(QPixmap::fromMimeSource("edit.png")), tr("Edit"), this, SLOT(editRowData()));
	contextMenu->insertItem(QIconSet(QPixmap::fromMimeSource("delete.png")), tr("Delete"), this, SLOT(deleteRowData()));
	contextMenu->insertSeparator();    
    }
    contextMenu->insertItem(QIconSet(QPixmap::fromMimeSource("up.png")), tr("Level up"), this, SLOT(levelUp()));
    contextMenu->insertItem(QIconSet(QPixmap::fromMimeSource("home.png")), tr("Home"), this, SLOT(home()));
    
    connect(this, SIGNAL(doubleClicked(int, int, int, const QPoint&)), this, SLOT(defaultAction(int, int, int, const QPoint&)));
    
    fData = new alDataGoods(fEngine);
    hideVerticalHeader();
    setSelectionMode(NoSelection);    
    alDataTable::init();
    load(currentGroup);
}

void alGoodsTable::load(alGoodsRecord * parent)
{
    currentGroup = parent;
    alDataTable::load(QString("parent=%1").arg((!parent ? 0 : parent->id()))); 
}


/*
*	возвращает иконку элемента или группы
*	return pixmap of element or group
*/
QPixmap alGoodsTable::pixmap(int r)
{
    if(value(r, "isgroup").toBool())
	return QPixmap::fromMimeSource("group.png");
    else
	return QPixmap::fromMimeSource("element.png");
}

bool alGoodsTable::internalNew(bool isgroup)
{
    QDialog * dlg;
    alGoodsRecord * rec;
    if(isgroup)
    {
	dlg = new GoodsGroup();
	rec = alGoodsRecord::newGroup((alDataGoods*)fData, currentGroup);
	((GoodsGroup*)dlg)->setData(rec);
    }
    else
    {
	dlg = new GoodsElement();	
	rec = alGoodsRecord::newElement((alDataGoods*)fData, currentGroup);
	((GoodsElement*)dlg)->setData(rec);
    }
    int res = dlg->exec();
    if(res)
    {
	rec->update();
	fEngine->sendElement(rec);
	load(currentGroup);
    }
    delete dlg;
    return res;  
}

bool alGoodsTable::newElement()
{   
    return internalNew(false);
}

bool alGoodsTable::newGroup()
{
    return internalNew(true);
}

bool alGoodsTable::editRowData()
{
    int row = currentRow();
    QDialog * dlg;
    fData->seek(row);
    alGoodsRecord * rec = (alGoodsRecord*) fData->current();
    if(rec->isGroup())
    {
	dlg = new GoodsGroup();
	((GoodsGroup*)dlg)->setData(rec);
    }
    else
    {
	dlg = new GoodsElement();    
	((GoodsElement*)dlg)->setData(rec);	
    }    
    int res = dlg->exec();
    if(res)
    {
	rec->update();
	load(currentGroup);
	setCurrentRow(row);
	fEngine->sendElement(rec);	
    }
    dlg->deleteLater();
    return res;
}

bool alGoodsTable::deleteRowData()
{
    int row = currentRow();
    fData->seek(row);
    int res;
    if(((alGoodsRecord*)(fData->current()))->isGroup())
    {
	res = QMessageBox::question(this, "aldebaran", tr("Delete group??"), QMessageBox::Yes, QMessageBox::No);
	if(res==QMessageBox::Yes)
	{	    
	    ((alDataGoods*)fData)->delGroup();
	    load(currentGroup);	    
	}
    }
    else
    {
	res = QMessageBox::question(this, "aldebaran", tr("Delete element??"), QMessageBox::Yes,QMessageBox:: No);	
	if(res==QMessageBox::Yes)
	{
	    ((alDataGoods*)fData)->delElement();
	    load(currentGroup);	    
	}
    }
    setCurrentRow(row);
    return res;
}

bool alGoodsTable::levelUp()
{
    if(currentGroup) load(currentGroup->parent());
    else return false;
    return true;
}

bool alGoodsTable::home()
{
    load(0);
    return true;
}

void alGoodsTable::editCell(int row, int col, bool replace)
{
    Q_UNUSED(replace);
    fData->seek(row);
    if(fData->value("isgroup").toBool() && (headers[col]=="*" || fSelect))
    {
	alGoodsRecord * group = (alGoodsRecord*) fData->current();
	load(group);
	return;
    }
    
    if(fSelect)
    {
	emit selected((alGoodsRecord*) fData->current());
	return;
    }

    setCurrentRow(row);
    editRowData();
}
