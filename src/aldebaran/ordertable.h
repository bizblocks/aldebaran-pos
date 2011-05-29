#ifndef ORDERTABLE_H
#define ORDERTABLE_H

#include "datatable.h"
#include "rights.h"

class alOrderRecord;
class alOrderLine;
class alGoodsRecord;

class alOrderTable : public alDataTable
{
    Q_OBJECT
public:
    alOrderTable(QWidget * parent, alEngine * engine, alOrderRecord* order);
    virtual void init();
    virtual void load();
    alOrderLine * addItem(alGoodsRecord * item);        
    alOrderLine * newLine();
    alOrderLine * getLine(int r);
    bool delLine(int r);
    virtual void paintCell( QPainter * p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg ) { QTable::paintCell(p, row, col, cr, selected, cg); } ;        
//    QString info();
    double total(QString attr);
public slots:
    double amount();
    void setAmount(double q);
    virtual bool editRowData() { return FALSE; };
    virtual bool deleteRowData() { return FALSE; };
protected slots:
    virtual void fillLine(int r);
protected:
    bool checkRights(alRights right);    
private:
    alOrderRecord * fOrder;
};

#endif
