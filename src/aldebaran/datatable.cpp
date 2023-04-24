#include <Q3PopupMenu>
#include "data/data.h"
#include "datatable.h"
#include "engine.h"

alDataTable::alDataTable(QWidget * parent, alEngine * e, QString table) :
    Q3Table(parent, QString("table_%1").arg(table))
{
    fData = NULL;
    contextMenu = new Q3PopupMenu(this, "datatable context menu");
    tableName = table;
    currentFilter = "";
    maxWidthColumn = "";
    fEngine = e;
    headers.clear();
    headers << "id" << "*"; // id, icon - default columns
    fields["id"] = "id";
    connect(this, SIGNAL(contextMenuRequested(int, int, const QPoint&)), this, SLOT(popupMenu(int,int,const QPoint&)));
    fSelect = FALSE;
}

void alDataTable::init()
{
    setReadOnly(true);
    setNumCols(headers.count());
    for(int i=0;i<(int)headers.count();i++)
    {
        Q3Table::horizontalHeader()->setLabel(i, headers[i]);
        adjustColumn(i);
    }
    hideColumn("id");
}

int alDataTable::popupMenu(int, int, const QPoint & pos)
{    
    if(!contextMenu)
        return -1;
    return contextMenu->exec(pos);
}

void alDataTable::hideVerticalHeader()
{
    savedMargin = leftMargin();
    setLeftMargin(0);
}

void alDataTable::showVerticalHeader()
{
    if(!leftMargin())
        setLeftMargin(savedMargin);
}

void alDataTable::load(QString filter)
{
    alDBG("alDataTable::load start");
    setNumRows(0);
    if(!fData)
        return;
    if(filter.isEmpty())
        fData->select();
    else
        fData->select(filter);
    alDBG("Select query for table "+fData->tableName());
    alDBG(fData->lastQuery());
    if(!fData->first())
        return;
    setUpdatesEnabled(FALSE);
    int iHeight = 0, r=0;
    int tSize = fData->size();
    if(tSize>-1)
        setNumRows(tSize);
    do
    {
        if(tSize==-1)
            setNumRows(numRows()+1);
        fillLine(r);
        //	setRowStretchable(r, TRUE);
        adjustRow(r);
        iHeight+=rowHeight(r);
        r++;
        if(tSize>0 && iHeight>height())
            break;
    } while(fData->next());
    setUpdatesEnabled( TRUE );
    repaint(rect(), TRUE);
    adjustColumns();
    currentFilter = filter;
    alDBG("alDataTable::load finish");
}

QVariant alDataTable::value(int row, int col)
{
    QString t = text(row, col);
    if(!t.isEmpty()) return QVariant(t);
    if(fields[headers[col]]=="id") return QVariant(0);
    fData->seek(row);
    return fData->value(fields[headers[col]]);
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
    val = displayValue(fields[headers[col]], val);
    if(val.type()==QVariant::Pixmap)
        setPixmap(row, col, val.value<QPixmap>());
    else
        setText(row, col, val.toString());
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

void alDataTable::paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg )
{
    if(!value(row, "id").toInt())
    {
        fData->seek(row);
        fillLine(row);
    }
    Q3Table::paintCell(p, row, col, cr, selected, cg);
}

void alDataTable::fillLine(int r)
{
    for(int i=0;i<(int)headers.count();i++)
    {
        if(!fields[headers[i]].isEmpty())
            setValue(r, QString(fields[headers[i]]), fData->value(fields[headers[i]]));
    }
    setValue(r, "*", icon(r));
    //    adjustRow(r);
}

/*
*	реализация по-умолчанию возвращает пустую картинку
*	default implementation, return empty pixmap
*/
QIcon alDataTable::icon(int r)
{
    Q_UNUSED(r);
    return QIcon();
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
        Q3Table::hideColumn(col);
}

void alDataTable::showColumn(QString attr)
{
    int col = columnNum(attr);
    if(col>-1)
        Q3Table::hideColumn(col);
}

void alDataTable::setColumnWidth(QString attr, int w)
{
    int col = columnNum(attr);
    if(col>-1)
        Q3Table::setColumnWidth(col, w);
}

int alDataTable::columnWidth(QString attr)
{
    int col = columnNum(attr);
    if(col>-1)
        return Q3Table::columnWidth(col);
    return 0;
}

int alDataTable::columnNum(QString attr)
{
    int col = fields.values().findIndex(attr);
    if(col>-1)
        attr = fields.keys()[col];
    col = headers.findIndex(attr);
    return col;
}

void alDataTable::adjustColumns()
{
    int swidth = 0;
    for(int i=0;i<numCols();i++)
    {
        if(i!=columnNum(maxWidthColumn))
        {
            adjustColumn(i);
            swidth += Q3Table::columnWidth(i)+2;
        }
    }
    int scrollWidth = verticalScrollBar()->width();
    setColumnWidth(maxWidthColumn, width()-swidth-scrollWidth-leftMargin()-rightMargin());
}

void alDataTable::defaultAction(int row, int col, int, const QPoint&)
{
    editCell(row, col);
}

void alDataTable::editCell(int row, int col, bool replace)
{
    Q_UNUSED(replace);
    setCurrentCell(row, col);
    editRowData();
}
