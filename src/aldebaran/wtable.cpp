#include <qtooltip.h>
#include "wtable.h"

alWTable::alWTable(QWidget * parent, int num, Q_ULLONG order, double sum) :
	QToolButton(parent, QString(tr("Table #%1")).arg(num))
{
    fStatus = 0;
    setUsesTextLabel(true);
    setUsesBigPixmap(true);
    setTextPosition(BesideIcon);
    orderId = order;
    summ = sum;    
    this->num = num;
    refresh();
    connect(this, SIGNAL(clicked()), this, SLOT(on_click()));
}

alWTable::~alWTable()
{

}

void alWTable::refresh()
{
    QString tip = "";
    if(orderId>0)
        tip= QString(tr("Order #%1\nSumm %2")).arg(orderId).arg(summ,0, 'f', 2);
    setTextLabel(QString(tr("Table #%1\nSumm %2")).arg(num).arg(summ,0, 'f', 2), FALSE);
    QToolTip::add(this, tip);
    if(fStatus==1)
        setIcon(QIcon(":/images/peoples.png"));
    else
        setIcon(QIcon());
}

void alWTable::setOrder(Q_ULLONG ordernum, double sum)
{
    orderId = ordernum;
    summ = sum;
    refresh();
}

void alWTable::setStatus(int status)
{
    fStatus = status;    
    if(status!=1) 
    {
	orderId = 0;
	summ =0;
    }
    refresh();
}

void alWTable::on_click()
{
    emit(invoked(num));
}
