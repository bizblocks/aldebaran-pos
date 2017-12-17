#ifndef WHALL_H
#define WHALL_H

#include <qwidget.h>
#include <qpixmap.h>

class QGridLayout;
class alWTable;
class alEngine;
class alDataOrder;

class alWHall : public QWidget
{
Q_OBJECT    
public:
    alWHall(alEngine * e, QWidget * parent=0, QString name=QString::null, int tables = 0, QPixmap image=QPixmap());
    ~alWHall();
public slots:
    virtual int getNumTables() {return fNumTables; }
    virtual alWTable * addTable(int x=-1, int y=-1);
    virtual alWTable * getTable(int num); 
protected:
    void	paintEvent( QPaintEvent * );    
    virtual bool processShema();
private:
    alDataOrder * fOrders;
    QMap<int, alWTable*> tables;
    QGridLayout * grid;
    QPixmap * shema;
    bool shematic;
    int fNumTables, tablesPerCol;
    alEngine * fEngine;
};

#endif
