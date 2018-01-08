#include <QDebug>
#include <QHeaderView>
#include <QMenu>
#include <QScrollBar>
#include "engine.h"
#include "data/data.h"
#include "datatable.h"

alDataTable::alDataTable(QWidget * parent, alEngine * e, QString table) :
    QTableView(parent),
    fEngine(e),
    fData(NULL)
{    
    setObjectName(QString("table_%1").arg(table));
    contextMenu = new QMenu(this);
    contextMenu->setObjectName("datatable context menu");
    tableName = table; 
    currentFilter = "";
    maxWidthColumn = "";
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popupMenu(const QPoint&)));
    fSelect = FALSE;
    fields["id"] = "id";
}

void alDataTable::init(alEngine * e)
{
    if(e)
        fEngine = e;
    if(!fData)
        fData = new alData(e, tableName);
    fData->insertColumn(0);
    fData->setHeaderData(0, "id");
    fData->insertColumn(1);
    fData->setHeaderData(1, "*");
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

QAction * alDataTable::popupMenu(const QPoint & pos)
{    
    if(!contextMenu)
        return NULL;
    return contextMenu->exec(pos);
}

void alDataTable::hideVerticalHeader()
{
    verticalHeader()->hide();
}

void alDataTable::showVerticalHeader()
{
    verticalHeader()->show();
}

//TODO use of filter
void alDataTable::load(QString filter)
{
    if(!fData)
        return;
    bool res = fData->select(filter);
    if(!res)
    {
        qDebug() << fData->database().isOpen();
        qDebug() << fData->query().lastError().driverText();
    }
    this->setModel(fData);

    hideColumn("id");
    adjustColumns();
//    currentFilter = filter;
    fData->select();
}

QVariant alDataTable::value(int row, int col)
{
    return fData->data(fData->index(row, col), Qt::DisplayRole);
}

QVariant alDataTable::value(int row, QString attr)
{
    int col = columnNum(attr);
    if(col>-1) 
	return value(row, col);
    fData->seek(row);
    return fData->value(attr);
}

QVariant alDataTable::value(QString attr)
{
    return value(currentRow(), attr);
}

void alDataTable::setValue(int row, int col, QVariant val)
{
    fData->setData(fData->index(row, col), val);
}

void alDataTable::setValue(int row, QString attr, QVariant val)
{
    int col = columnNum(attr);
    if(col>-1)
        setValue(row, col, val);
}

void alDataTable::setValue(QString attr, QVariant val)
{
    setValue(currentRow(), attr, val);
}

//TODO reimplement
//void alDataTable::paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg )
//{
//    if(!value(row, "id").toInt())
//    {
//        fData->seek(row);
//        fillLine(row);
//    }
//    QTable::paintCell(p, row, col, cr, selected, cg);
//}

/*
*	реализация по-умолчанию возвращает пустую картинку
*	default implementation, return empty pixmap
*/
QPixmap alDataTable::pixmap(int r)
{
    Q_UNUSED(r);
    return QPixmap();
}

/*
*	реализация по-умолчанию возвращает val с применением toString()
*	default implementation, return val applying toString()
*/
QVariant alDataTable::displayValue(QString attr, QVariant val)
{
    Q_UNUSED(attr); 
    return val;
}

void alDataTable::hideColumn(QString attr)
{
    int col = columnNum(attr);
    if(col>-1)
        QTableView::hideColumn(col);
}

void alDataTable::showColumn(QString attr)
{
    int col = columnNum(attr);
    if(col>-1)
        QTableView::hideColumn(col);
}

void alDataTable::setColumnWidth(QString attr, int w)
{
    int col = columnNum(attr);
    if(col>-1)
        QTableView::setColumnWidth(col, w);
}
	
int alDataTable::columnWidth(QString attr)
{
    int col = columnNum(attr);
    if(col>-1)
        return QTableView::columnWidth(col);
    return 0;
}

int alDataTable::columnNum(QString attr)
{
    int col = fields.values().indexOf(attr);
    if(col>-1)
        attr = fields.keys()[col];
    return fData->columnNum(attr);
}

void alDataTable::adjustColumns()
{
    resizeColumnsToContents();
    horizontalHeader()->setSectionResizeMode(columnNum("*"), QHeaderView::Fixed);
    horizontalHeader()->setSectionResizeMode(columnNum(maxWidthColumn), QHeaderView::Stretch);
}

void alDataTable::defaultAction(int row, int col, int, const QPoint&)
{
    editCell(row, col);
}

//TODO reimplement
void alDataTable::editCell(int row, int col, bool replace)
{
    Q_UNUSED(replace);
    QModelIndex idx = rootIndex();
    setCurrentIndex(idx.child(row, col));
    editRowData();
}

int alDataTable::currentRow()
{
    return currentIndex().row();
}

