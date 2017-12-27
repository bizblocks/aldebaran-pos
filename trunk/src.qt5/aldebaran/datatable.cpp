#include <QHeaderView>
#include <QMenu>
#include "engine.h"
#include "data/data.h"
#include "datatable.h"

alDataTable::alDataTable(QWidget * parent, alEngine * e, QString table) :
    QTableView(parent),
    fEngine(e),
    fData(NULL),
    fModel(NULL)
{    
    setObjectName(QString("table_%1").arg(table));
    contextMenu = new QMenu(this);
    contextMenu->setObjectName("datatable context menu");
    tableName = table; 
    currentFilter = "";
    maxWidthColumn = "";
    headers.clear();
    headers << "id" << "*"; // id, icon - default columns
    fields["id"] = "id";
    connect(this, SIGNAL(contextMenuRequested(int, int, const QPoint&)), this, SLOT(popupMenu(int,int,const QPoint&)));    
    fSelect = FALSE;
}

//TODO reimplement
void alDataTable::init()
{
    if(fModel)
        delete fModel;
    fModel = new QSqlTableModel(this, fEngine->db());
//    setReadOnly(true);
//    setNumCols(headers.count());
//    for(int i=0;i<(int)headers.count();i++)
//    {
//    	QTable::horizontalHeader()->setLabel(i, headers[i]);
//        adjustColumn(i);
//    }
//    hideColumn("id");
}

//TODO reimplement
int alDataTable::popupMenu(int, int, const QPoint & pos)
{    
    if(!contextMenu)
        return -1;
    return -1;
    //return contextMenu->exec(pos);
}

void alDataTable::hideVerticalHeader()
{
    verticalHeader()->hide();
}

void alDataTable::showVerticalHeader()
{
    verticalHeader()->show();
}

//TODO check of we nned this
void alDataTable::load(QString filter)
{
//    setNumRows(0);
//    if(!fData)
//        return;
//    if(filter.isEmpty())
//        fData->select();
//    else
//        fData->select(filter);
//#ifdef DEBUG
//    qDebug(fData->lastQuery());
//#endif
//    if(!fData->first())
//        return;
//    setUpdatesEnabled(FALSE);
//    int iHeight = 0, r=0;
//    int tSize = fData->size();
//    if(tSize>0)
//	setNumRows(tSize);
//    do
//    {
//        fillLine(r);
////	setRowStretchable(r, TRUE);
//        adjustRow(r);
//        iHeight+=rowHeight(r);
//        r++;
//        if(tSize>0 && iHeight>height())
//            break;
//    } while(fData->next());
//    setUpdatesEnabled( TRUE );
//    repaint(rect(), TRUE);
//    adjustColumns();
//    currentFilter = filter;
}

//TODO reimplement
QVariant alDataTable::value(int row, int col)
{
//    QString t = text(row, col);
//    if(!t.isEmpty()) return QVariant(t);
//    if(fields[headers[col]]=="id") return QVariant(0);
//    fData->seek(row);
//    return fData->value(fields[headers[col]]);
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

//TODO reimplemnt
void alDataTable::setValue(int row, int col, QVariant val)
{
//    val = displayValue(fields[headers[col]], val);
//    if(val.type()==QVariant::Pixmap)
//        setPixmap(row, col, val.toPixmap);
//    else setText(row, col, val.toString());
}

void alDataTable::setValue(int row, QString attr, QVariant val)
{
    int col = columnNum(attr);
    if(col>-1) setValue(row, col, val);
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

void alDataTable::fillLine(int r)
{
    for(int i=0;i<(int)headers.count();i++)
    {
	if(!fields[headers[i]].isEmpty()) 
	    setValue(r, QString(fields[headers[i]]), fData->value(fields[headers[i]]));
    }
    setValue(r, "*", pixmap(r));    
//    adjustRow(r);
}

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
    col = headers.indexOf(attr);
    return col;
}

//TODO check if resize mode affects possibility of column resizing
void alDataTable::adjustColumns()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    int swidth = 0;
//    for(int i=0;i<numCols();i++)
//    {
//        if(i!=columnNum(maxWidthColumn))
//        {
//            adjustColumn(i);
//            swidth += QTable::columnWidth(i)+2;
//        }
//    }
//    int scrollWidth = verticalScrollBar()->width();
//    setColumnWidth(maxWidthColumn, width()-swidth-scrollWidth-leftMargin()-rightMargin());
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
