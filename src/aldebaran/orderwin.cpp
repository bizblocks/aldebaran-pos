#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qsplitter.h>
#include <qmessagebox.h>
#include "engine.h"
#include "orderwin.h"
#include "data/dataorder.h"
#include "goodstable.h"
#include "ordertable.h"
#include "htmltemplate.h"
#include "worker.h"
#include "dlgselectdiscount.h"

alOrderWindow::alOrderWindow(alEngine * e, QWidget * parent, QString name, Q_ULLONG orderId) :
	QWidget(parent, name)
{
    fEngine = e;
    fOrderID = orderId;
    fOrder = NULL;
    fSummType = 1;
    grid = new QGridLayout(this, 3, 3);
}

void alOrderWindow::init()
{
    if(!fEngine) return;
    
    fOrders = new alDataOrder(fEngine);
    fOrder = fOrders->select(fOrderID);
    if(!fOrder) fOrder = alOrderRecord::newDocument(fOrders);
    fOrderID = fOrder->id();
    
    QLabel * label = new QLabel(this, "lblOrderHeader");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    grid->addWidget(label, 0, 0); 
    lblHeader = label;
    
    label = new QLabel(this, "lblOrderInfo");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    grid->addWidget(label, 0, 2);  
    lblOrderInfo = label;
    
    QFrame * btnGroup = new QFrame(this, "grpOrderButtons");
    btnGroup->setMargin(5);
    grid->addWidget(btnGroup, 1, 0);
    
    QGridLayout * btnGrid = new QGridLayout(btnGroup, 1, 13, 11, 6, "buttonsLayout");
    
    goodsTab = new alGoodsTable(this, fEngine);
    goodsTab->setSelectable(true);
    goodsTab->init();
//    goodsTab->hideColumn("price");
    goodsTab->hideColumn("externalcode");
    grid->addWidget(goodsTab, 2, 0);
    connect(goodsTab, SIGNAL(selected(alDataRecord *)), this, SLOT(add(alDataRecord *)));
      
    orderTab = new alOrderTable(this, fEngine, fOrder);
    orderTab->init();
    grid->addWidget(orderTab, 2, 2);
    
    QPushButton * btn = new QPushButton(btnGroup, "btnLevelUp");
    btn->setPixmap(QPixmap::fromMimeSource("up.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), goodsTab, SLOT(levelUp()));
    btnGrid->addWidget(btn, 0, 0); 
    
    btn = new QPushButton(btnGroup, "btnHome");
    btn->setPixmap(QPixmap::fromMimeSource("home.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), goodsTab, SLOT(home()));    
    btnGrid->addWidget(btn, 0, 1);    

    btn = new QPushButton(btnGroup, "btnSave");
    btn->setPixmap(QPixmap::fromMimeSource("save.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(update()));
    btnGrid->addWidget(btn, 0, 7);
    
    btn = new QPushButton(btnGroup, "btnCancel");
    btn->setPixmap(QPixmap::fromMimeSource("stop_cancel.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(cancel()));        
    btnGrid->addWidget(btn, 0, 8);
        
    btn = new QPushButton(btnGroup, "btnPrintOrder");
    btn->setPixmap(QPixmap::fromMimeSource("printorder.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(printOrder()));
    btnGrid->addWidget(btn, 0, 9);    
    
    btn = new QPushButton(btnGroup, "btnPrintBill");
    btn->setPixmap(QPixmap::fromMimeSource("printbill.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(printBill()));
    btnGrid->addWidget(btn, 0, 10);
    
    btn = new QPushButton(btnGroup, "btnCheck");
    btn->setPixmap(QPixmap::fromMimeSource("geld.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(check()));    
    btnGrid->addWidget(btn, 0, 11);
    
    btn = new QPushButton(btnGroup, "btnBankCard");
    btn->setPixmap(QPixmap::fromMimeSource("Finance.png"));
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(cardCheck()));    
    btnGrid->addWidget(btn, 0, 12);
    
    btn = new QPushButton(btnGroup, "btnClose");
    btn->setPixmap(QPixmap::fromMimeSource("exit.png"));
    btn->setAccel(Key_Escape);
    btn->setFixedSize(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(exitOrder()));    
    btnGrid->addWidget(btn, 0, 13);
        
    btnGroup = new QFrame(this, "grpOrderTableButtons");
    btnGroup->setMargin(5);
    grid->addWidget(btnGroup, 1, 2);

    btnGrid = new QGridLayout(btnGroup, 1, 12, 11, 6, "gridOrderTableButtons");    
    
    btn = new QPushButton(btnGroup, "btnPlus");
    btn->setPixmap(QPixmap::fromMimeSource("plus.png"));
    btn->setFixedSize(50,50);    
    btnGrid->addWidget(btn, 0, 9);
    connect(btn, SIGNAL(clicked()), this, SLOT(plus()));
    
    btn = new QPushButton(btnGroup, "btnMinus");
    btn->setPixmap(QPixmap::fromMimeSource("minus.png"));
    btn->setFixedSize(50,50);    
    btnGrid->addWidget(btn, 0, 10);
    connect(btn, SIGNAL(clicked()), this, SLOT(minus()));
    
    btn = new QPushButton(btnGroup, "btnCalc");
    btn->setPixmap(QPixmap::fromMimeSource("calc.png"));
    btn->setFixedSize(50,50);    
    btnGrid->addWidget(btn, 0, 11);
    connect(btn, SIGNAL(clicked()), this, SLOT(calc()));    
    
    btn = new QPushButton(btnGroup, "btnDiscount");
    btn->setPixmap(QPixmap::fromMimeSource("discount.png"));    
    btn->setFixedSize(50,50);        
    btnGrid->addWidget(btn, 0, 12);
    connect(btn, SIGNAL(clicked()), this, SLOT(chooseDiscount()));    
    
    connect(fEngine, SIGNAL(event(int, QVariant)), SLOT(onEvent(int, QVariant)))  ;
    
    refresh();    
}

void alOrderWindow::plus(double q)
{
    orderTab->setAmount(orderTab->amount()+q);
    refresh();
}

void alOrderWindow::minus(double q)
{
    orderTab->setAmount(orderTab->amount()-q);
    refresh();
}

void alOrderWindow::calc()
{
    double val = fEngine->calculator(orderTab->amount());
    if(val<0) val = 0;
    orderTab->setAmount(val);
    refresh();    
}

void alOrderWindow::add(alDataRecord * item)
{
    orderTab->addItem((alGoodsRecord *)item);
    refresh();
}

void alOrderWindow::refresh()
{
    lblHeader->setText("<b><font size=8>"+QString(tr("Order #%1").arg(fOrder->num()))+"</font></b>");
    lblOrderInfo->setText("<b>"+fOrder->info()+"</b> "+fOrder->comment());
    orderTab->load();
   
    alUserRecord * user = fEngine->currentUser();    
    if(!user) return;
    QPushButton * btn = (QPushButton*)child("btnBankCard");
    btn->setEnabled(user->right(rCard));
    
}

void alOrderWindow::cancel()
{
    if(QMessageBox::question(this, "aldebaran", tr("Cancel order??"), YES, NO)==NO)
	return;
    fOrder->setStatus(alDataOrder::Canceled);
    fOrder->update();
    emit orderUpdated(fOrder);
    emit(exit());
}

void alOrderWindow::update()
{
    fOrder->setStatus(alDataOrder::Saved);    
    fOrder->update();
    emit orderUpdated(fOrder);    
    emit(exit());
}

void alOrderWindow::printOrder()
{
//    alHTMLTemplate * tpl = alHTMLTemplate::fromFile("/home/knorr/src/aldebaran/src/aldebaran/templates/order.tpl");
//    tpl->setValue("number", fOrder->num());
//    tpl->setValue("table", orderTab->info());
//    tpl->addSection("DOCHEADER");
//    tpl->setValue("item", "some");
//    tpl->setValue("amount", 15);
//    tpl->addSection("ROW");    
//    tpl->addSection("DOCFOOTER");
    fOrder->setStatus(alDataOrder::Saved);    
    fOrder->update();    
    emit orderUpdated(fOrder);    
    fOrder->printOrder();
}

void alOrderWindow::printBill()
{
    fOrder->setStatus(alDataOrder::Saved);
    fOrder->update();
    emit orderUpdated(fOrder);    
    fOrder->printBill();
}

void alOrderWindow::check()
{
    if(fOrder->status()==alDataOrder::Closed) return;
    double clientSumm = orderTab->total("summ");
    if(fSummType==1) clientSumm = fEngine->calculator(clientSumm);
    if(clientSumm<0) return;
        
    alValueTable cheq;
    cheq.addColumn("name");
    cheq.addColumn("price");
    cheq.addColumn("amount");
    cheq.addColumn("discount");
    for(int r=0;r<orderTab->numRows();r++)
    {
	alOrderLine * line = orderTab->getLine(r);
	if(!line->item()) continue;	
	alValueTableRow * row = cheq.addRow();
	
	row->setValue("name", orderTab->text(r, orderTab->columnNum(tr("item"))));
	row->setValue("price", orderTab->value(r, "price").toDouble());
	row->setValue("amount", orderTab->value(r, "amount").toDouble());
	if(fOrder && fOrder->discount()) row->setValue("discount", row->value("price").toDouble()*row->value("amount").toDouble() - orderTab->value(r, "summ").toDouble());
    }
    alValueTable totals;
    totals.addColumn("summ");
    totals.addColumn("summType");
    alValueTableRow * row = totals.addRow();
    row->setValue("summ", clientSumm==0. ?  orderTab->total("summ") : clientSumm);
    row->setValue("summType", fSummType);
    
    alValueList res = fEngine->cheque("", cheq, totals);
    if(res["error"]==0)
    {
	if(res["change"].toDouble()!=0.) QMessageBox::information(this, "aldebaran", QString(tr("Change: %1").arg(res["change"].toDouble(), 10, 'f', 2)));
	fOrder->setStatus(alDataOrder::Closed);
    }
    else if(res["error"]==ERR_NODEVICE)	
    {
	if(QMessageBox::question(this, "aldebaran", QString(tr("Can't create job for ECR\nClose order anyway??")), YES, NO)==YES)
	    fOrder->setStatus(alDataOrder::Closed);
	else
	{
	    fOrder->setStatus(alDataOrder::Saved);
	    return;
	}
    }
    else
    {
	if(QMessageBox::question(this, "aldebaran", QString(tr("Check isn't closed, error %1:%2\nTry again??")).arg(res["error"].toInt()).arg(res["msg"].toString()), RETRY, ABORT)==RETRY)
	{
	    check();
	    return;
	}
	else
	{
	    fOrder->setStatus(alDataOrder::Saved);
	    return;
	}
    }	
    
    fOrder->setSummType(fSummType);
    fOrder->setStatus(alDataOrder::Closed);        
    fOrder->update();
    emit orderUpdated(fOrder);        
    emit(exit());                   
}

void alOrderWindow::cardCheck()
{
    fSummType = 4;
    check();
}

void alOrderWindow::exitOrder()
{
    if(QMessageBox::question(this, "aldebaran", tr("Save before exit??"), YES, NO)==YES)
    {
	fOrder->setStatus(alDataOrder::Saved);
	fOrder->update();
	delete fOrder;
	fOrder = NULL;
    }
    emit(exit());
}

void alOrderWindow::setTable(int tableNum) 
{ 
    if(fOrder) fOrder->setTable(tableNum);
    refresh();
}

void alOrderWindow::chooseDiscount()
{
    dlgSelectDiscount * dlg = new dlgSelectDiscount(this);
    dlg->init(fEngine);
    if(dlg->exec())
    {
	alDataDiscount * d = new alDataDiscount(fEngine);
	alDiscountRecord * discount = d->select(dlg->resultId());
	alUserRecord * user = fEngine->currentUser();
	if(!user) return;
	bool allow = user->right(rDiscount);
	if (allow && discount->protect()) allow = allow && ((discount->protect() && user->right(rDiscountProtected)));
	if(!allow)
	{
	    fEngine->error(tr("You don't have rights to set this discount"));
	    return;
	}	
	fOrder->setDiscount(discount);
	refresh();
    }    
}

void alOrderWindow::closeEvent(QCloseEvent * e)
{
    e->ignore();
    exitOrder();
}

void alOrderWindow::onEvent(int type, QVariant data)
{	
    if(isHidden())
	return;
    if(type == EVENT_MSCREADER)
    {
//	qDebug(QString("data %1").arg(data.toMap()["line"].toString()));
	alDataDiscount * d = new alDataDiscount(fEngine);    
	d->select(QString("code='%1'").arg(data.toMap()["line"].toString()));
	if(d->first())
	{
	    fOrder->setDiscount((alDiscountRecord*)d->current());
	    refresh();
	}
	else QMessageBox::information(this, "aldebaran" ,tr("card not found"));
    }
    else if(type == EVENT_BARCODEREADER)
    {
	alDataGoods * g = new alDataGoods(fEngine);
	g->select(QString("barcode='%1'").arg(data.toMap()["line"].toString()));
	if(g->first())
	{
	    add(g->current());
	}
	else QMessageBox::information(this, "aldebaran" ,tr("item, with barcode %1 not found").arg(data.toMap()["line"].toString()));
    }
}
