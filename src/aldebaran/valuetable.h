#ifndef VALUETABLE_H
#define VALUETABLE_H

#include <qvariant.h>
#include <qobject.h>
#include <qstringlist.h>

typedef QMap<QString, QVariant> alValueList;

class alValueTableRow;

class alValueTable : public QObject
{
public:
    alValueTable();
    alValueTable(const alValueTable&);
    ~alValueTable();
    
    int addColumn(const QString & header);
    alValueTableRow* addRow();
    alValueTableRow* operator[] (uint i);
    int rowCount();
    int colCount();
        
private:
    friend class alValueTableRow;
    QStringList fColumns;
    QList<alValueTableRow> fData;
};

class alValueTableRow : public QObject
{
public:
    alValueTableRow(alValueTable * owner);
    alValueTableRow(const alValueTableRow &);
    alValueList asValueList();    
    void setValue(const QString& header, QVariant value);
    void setValue(uint col, QVariant value);    
    QVariant value(const QString& header);
    QVariant value(uint col);    
    inline alValueTableRow& operator=(const alValueTableRow& row) { fRowData = row.fRowData; fOwner = row.fOwner; return *this; };
private:
    alValueTableRow();
    alValueList fRowData;
    alValueTable * fOwner;
    friend class alValueTable;
    //friend class QValueListNode<alValueTableRow>;
};

#endif
