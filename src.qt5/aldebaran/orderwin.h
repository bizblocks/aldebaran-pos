#ifndef ORDERWIN_H
#define ORDERWIN_H

#include <qwidget.h>
#include <qpixmap.h>
#include <qvariant.h>

class QGridLayout;
class QLabel;
class alDataRecord;
class alOrderRecord;
class alDataOrder;
class alGoodsTable;
class alGoodsRecord;
class alOrderTable;
class alEngine;

class alOrderWindow : public QWidget
{
    Q_OBJECT
public:
    alOrderWindow(alEngine * e, QWidget * parent=0, QString name=QString::null, Q_ULLONG orderId=-1);
    void init();
public slots:    
    void cancel();
    void update();
    void add(alDataRecord * item);
    void refresh();
    void plus(double q=1.);
    void minus(double q=1.);
    void calc();
    void printOrder();
    void printBill();
    void check();
    void cardCheck();
    void exitOrder();
    void setTable(int tableNum);
    alOrderRecord * order() { return fOrder; };
    void chooseDiscount();
    void onEvent(int type, QVariant data);
protected:
    virtual void closeEvent(QCloseEvent * e); 
signals:
    void exit();
    void orderUpdated(alOrderRecord *);
private:
    Q_ULLONG fOrderID;
    alOrderRecord * fOrder;
    alDataOrder * fOrders;
    alEngine * fEngine;
    QGridLayout * grid;
    alGoodsTable * goodsTab;
    alOrderTable * orderTab;
    QLabel * lblHeader, * lblOrderInfo;
    char fSummType;
};

#endif
