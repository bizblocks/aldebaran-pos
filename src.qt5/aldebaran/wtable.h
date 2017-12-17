#ifndef WTABLE_H
#define WTABLE_H

#include <qtoolbutton.h>

class QWidget;

class alWTable : public QToolButton
{
Q_OBJECT
public:
    alWTable(QWidget * parent, int num, ULLID order=-1, double sum=0);
    void setOrder(ULLID id, double summ=0);
    void setStatus(int status);
//    int status() { return iStatus; };
    int order() { return orderId; }
    void refresh();
    ~alWTable();
protected slots:
    void on_click();
signals:
    void invoked(int num);    
private:    
    int num;
    ULLID orderId;
    double summ;
    int fStatus;
};

#endif
