#ifndef DATATABLE_H
#define DATATABLE_H

#include <qtable.h>

class QWidget;
class QPopupMenu;
class alEngine;
class alData;
class alDataRecord;

class alDataTable : public QTable
{
Q_OBJECT
public:
    alDataTable(QWidget * parent, alEngine * e, QString table);
    virtual void init();
    virtual void load(QString filter="");
    QString filter() { return currentFilter; };
    virtual void paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg );    
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
    virtual void setCurrentRow(int row) { setCurrentCell(row, 0); };
    int popupMenu(int row, int col, const QPoint & pos);
    void setSelectable(bool s) { fSelect = s; };
    bool selectable() { return fSelect; };
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
    QPopupMenu * contextMenu;
    bool fSelect;
    QString maxWidthColumn;
private:
    QString tableName;
    QString currentFilter;
    QValueList<int> ids;
    QWidget * rowEditor;
    int savedMargin;
};	

#endif
