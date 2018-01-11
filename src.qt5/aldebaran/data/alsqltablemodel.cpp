#include <QSqlRecord>
#include "alsqltablemodel.h"

alSqlTableModel::alSqlTableModel(alEngine * parent, QSqlDatabase db, const QString& table) :
    QSqlTableModel((QObject*)parent, db)
{
    fHeaders.clear();
    setTable(table);
}

QVariant alSqlTableModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole || orientation == Qt::Vertical)
        return QSqlTableModel::headerData(section, orientation, role);

    return fHeaders[section];
}


void alSqlTableModel::addHeaders(QStringList headers)
{
     for(int j=0;j<headers.count();j++)
     {
         insertColumn(this->columnCount());
         setHeaderData(this->columnCount()-1, headers[j]);
     }
}


QVariant alSqlTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int c = index.column();
    int r = index.row();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(fHeaders[c]=="*")
            return QString();
        QString field = fHeaders[c].toString();
        int f = fieldIndex(field);
        QModelIndex i = this->index(r, f);
        return QSqlTableModel::data(i, role);
    }
    else if(role==Qt::DecorationRole)
    {
        if(fHeaders[c]=="*")
            return QVariant(pixmap(r));
    }
    return
            QVariant();
}

QSqlRecord alSqlTableModel::record(int row)
{
    if (row < 0)
        return QSqlTableModel::record();

    QSqlRecord rec = QSqlTableModel::record();
    for (int i = 0; i < rec.count(); ++i)
        rec.setValue(i, QSqlTableModel::data(createIndex(row, i), Qt::EditRole));
    return rec;
}

QPixmap alSqlTableModel::pixmap(int) const
{
    return QPixmap();
}

bool alSqlTableModel::removeColumns(int column, int count, const QModelIndex&)
{
    while(count--)
    {
        if(fHeaders.count()<column)
            fHeaders.removeAt(column);
        else
            return false;
    }
    return true;
}

int alSqlTableModel::columnCount(const QModelIndex&) const
{
    return fHeaders.count();
}

bool alSqlTableModel::insertColumn(int column, const QModelIndex &)
{
    fHeaders << tr("Column %1").arg(column);
    return true;
}

bool alSqlTableModel::setHeaderData(int section, Qt::Orientation, const QVariant &value, int)
{
    fHeaders[section] = value;
    return true;
}

bool alSqlTableModel::setHeaderData(int section, const QVariant &value)
{
    setHeaderData(section, Qt::Horizontal, value);
    return true;
}

int alSqlTableModel::columnNum(QString attr)
{
    return fHeaders.indexOf(attr);
}
