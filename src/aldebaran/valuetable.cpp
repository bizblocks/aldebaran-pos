#include "valuetable.h"

alValueTable::alValueTable() :
	QObject()
{
    fColumns.clear();
    fData.clear();
}

alValueTable::alValueTable(const alValueTable& tab) :
	QObject()
{
    fData = tab.fData;
    fColumns = tab.fColumns;
}

alValueTable::~alValueTable()
{
    fColumns.clear();
    fData.clear();
}

alValueTableRow* alValueTable::addRow()
{
    alValueTableRow newRow(this);
    return &*fData.append(newRow);
}

alValueTableRow* alValueTable::operator[](uint i)
{
    if(i>fData.count()-1) return &*fData.end();
    return &*fData.at(i);
}

int alValueTable::rowCount()
{
    return fData.count();
}

int alValueTable::addColumn(const QString& header)
{
    if(fColumns.contains(header)) return -1;
    fColumns.append(header);
    return fColumns.count()-1;
}

alValueTableRow::alValueTableRow() :
	QObject(), fOwner(NULL)
{
}

alValueTableRow::alValueTableRow(alValueTable * owner) :
	QObject(owner)
{
    fOwner = owner;
}

alValueTableRow::alValueTableRow(const alValueTableRow& row) :
	QObject(row.fOwner)
{
    fRowData = row.fRowData;
    fOwner = row.fOwner;
}

alValueList alValueTableRow::asValueList()
{
    alValueList res;
    res.clear();
    if(!fOwner) return res;    
    for(QStringList::Iterator it=fOwner->fColumns.begin();it!=fOwner->fColumns.end();++it)
    {
	res[*it] = value(*it);
    }
    return res;
}

//QVariant&  alValueTableRow::operator[](const QString& header)
//{
//    QVariant val;    
//    if(!fOwner) return *fRowData.end();
//    if(!fOwner->fColumns.contains(header)) return *fRowData.end();
//    int index = fOwner->fColumns.findIndex(header);
//    if(fRowData.at(index)==fRowData.end()) return *fRowData.append(val);
//    return *fRowData.at(index);
//}

void alValueTableRow::setValue(const QString& header, QVariant value)
{
    if(!fOwner) return;
    if(!fOwner->fColumns.contains(header)) return;
    fRowData[header] = value;
}

QVariant alValueTableRow::value(const QString& header)
{
    if(!fOwner) return QVariant();
    if(!fOwner->fColumns.contains(header)) return QVariant();
    return fRowData[header];
}
