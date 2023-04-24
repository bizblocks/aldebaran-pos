#include <Q3PopupMenu>
#include "engine.h"
#include "orderwin.h"
#include "archivetable.h"
#include "data/dataorder.h"

#define TABLE "orders"

alArchiveTable::alArchiveTable(QWidget * parent, alEngine * engine) :
    alDataTable(parent, engine, TABLE)
{
    headers << tr("number") << tr("date") << tr("check number")
            << tr("table") << tr("sum") << tr("user");
    fields[tr("number")] = "num";
    fields[tr("date")] = "orderdate";
    fields[tr("check number")] = "checknum";
    fields[tr("table")] = "table";
    fields[tr("sum")] = "sum";
    fields[tr("user")] = "user";
    maxWidthColumn = "";
}

void alArchiveTable::init()
{
    contextMenu->clear();
    if(!fSelect)
    {
        contextMenu->insertItem(QIconSet(QIcon(":/images/edit.png")), tr("Edit"), this, SLOT(editRowData()));
        contextMenu->insertItem(QIconSet(QIcon(":/images/delete.png")), tr("Delete"), this, SLOT(deleteRowData()));
        contextMenu->insertSeparator();
    }
    
    connect(this, SIGNAL(doubleClicked(int, int, int, const QPoint&)), this, SLOT(defaultAction(int, int, int, const QPoint&)));
    
    fData = new alDataOrder(fEngine);
    hideVerticalHeader();
    setSelectionMode(NoSelection);
    alDataTable::init();
    QDate today = QDate::currentDate();
    load(QString("orderdate='%1'").arg(today.toString("yyyy-MM-dd")));
}

void alArchiveTable::fillLine(int r)
{
    if(!fData) return;
    fData->seek(r);
    alOrderRecord * order = (alOrderRecord *)fData->current();
    if(!order) return;
    setValue(r, "id", order->id());
    setValue(r, "num", order->num());
    setValue(r, "orderdate", order->date());
    setValue(r, "checknum", order->checkNum());
    setValue(r, "table", order->table());
    setValue(r, "sum", QString("%1").arg(order->total("summ"), 15, 'F', 2));
    setValue(r, "*", icon(r));
    adjustRow(r);
}

QIcon alArchiveTable::icon(int r)
{
    QIcon p;
    fData->seek(r);
    alOrderRecord * order = (alOrderRecord *)fData->current();
    if(!order) return QPixmap();
    alDataOrder::Status status = order->status();
    if(status == alDataOrder::Closed)
        p = QIcon(":/images/document-closed.png");
    else if(status == alDataOrder::Canceled)
        p = QIcon(":/images/document-cancelled.png");
    else
        p = QIcon(":/images/document.png");
    return p;
}

bool alArchiveTable::editRowData()
{
    orderWin = new alOrderWindow(fEngine, NULL, "order window", value("id").toULongLong());
    connect(orderWin, SIGNAL(exit()), this, SLOT(closeOrder()));
    orderWin->init();
    orderWin->showFullScreen();
    return TRUE;
}

bool alArchiveTable::deleteRowData()
{
    int r = currentRow();
    if(!fData) return FALSE;
    fData->seek(r);
    alOrderRecord * order = (alOrderRecord *)fData->current();
    if(!order) return FALSE;
    if(order->status()==alDataOrder::Canceled) order->setStatus(alDataOrder::Saved);
    else order->setStatus(alDataOrder::Canceled);
    order->update();
    fillLine(r);
    return TRUE;
}

void alArchiveTable::closeOrder()
{
    if(orderWin) delete orderWin;
    int row = currentRow();
    load(filter());
    setCurrentRow(row);
    emit(exitOrder());
}
