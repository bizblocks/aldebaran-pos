#ifndef DATATABLE_H
#define DATATABLE_H

#include <QTableView>
#include "aldebaran.h"

class QWidget;
class QMenu;
class QSqlTableModel;
class alEngine;
class alData;
class alDataRecord;

class alDataTable : public QTableView
{
Q_OBJECT
public:
    alDataTable(QWidget * parent, alEngine * e, QString table);
    virtual void init();
    virtual void load(QString filter="");
    QString filter() { return currentFilter; }
    //TDOD reimplement
    //virtual void paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg );
public slots:
    void hideVerticalHeader();
    void showVerticalHeader();
    int columnNum(QString col);
    virtual void hideColumn(QString col);
    virtual void showColumn(QString col);    
    virtual void setColumnWidth(QString col, int w);
    virtual int columnWidth(QString col);        
    virtual QVariant value(int row, int col);
    virtual QVariant value(int row, QString attr);
    virtual QVariant value(QString attr);
    virtual void setValue(int row, int col, QVariant val);
    virtual void setValue(int row, QString attr, QVariant val);
    virtual void setValue(QString attr, QVariant val);
    virtual QVariant displayValue(QString attr, QVariant val);
    virtual QPixmap pixmap(int r);
    virtual void setCurrentRow(int row) { selectRow(row); }
    virtual int currentRow();
    int popupMenu(int row, int col, const QPoint & pos);
    void setSelectable(bool s) { fSelect = s; }
    bool selectable() { return fSelect; }
    void adjustColumns();
    virtual bool editRowData() = 0;
    virtual bool deleteRowData() = 0;    
    virtual void defaultAction(int row, int col, int button, const QPoint & pos);
    virtual void editCell(int row, int col, bool replace = FALSE);    
protected slots:
    virtual void fillLine(int r);
signals:
    void selected(alDataRecord *);
protected:
    QStringList headers;
    QMap<QString, QString> fields;    
    alEngine * fEngine;
    alData * fData;
    QMenu * contextMenu;
    bool fSelect;
    QString maxWidthColumn;
private:
    QString tableName;
    QString currentFilter;
    QList<int> ids;
    QWidget * rowEditor;
    int savedMargin;
    QSqlTableModel * fModel;
};	

#endif
