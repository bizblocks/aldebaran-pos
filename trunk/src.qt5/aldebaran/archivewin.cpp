#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qdatetimeedit.h>
#include <qmessagebox.h>
#include "archivewin.h"
#include "archivetable.h"

alArchiveWindow::alArchiveWindow(alEngine * e, QWidget * parent, QString name) :
	QWidget(parent, name)
{
    fEngine = e;
    grid = new QGridLayout(this, 2, 1);
}

void alArchiveWindow::init()
{
    if(!fEngine) return;
    
    QFrame * btnGroup = new QFrame(this, "grpOrderButtons");
    btnGroup->setMargin(5);
    grid->addWidget(btnGroup, 0, 0);
    
    QGridLayout * btnGrid = new QGridLayout(btnGroup, 1, 13, 11, 6, "buttonsLayout");    
    
    arcTab = new alArchiveTable(this, fEngine);
    arcTab->init();
    grid->addWidget(arcTab, 1, 0);
//    connect(arcTab, SIGNAL(selected(Q_ULLONG)), arcTab, SLOT(editRowData()));
    connect(arcTab, SIGNAL(exitOrder()), this, SLOT(refresh()));
	    
    QPushButton * btn = new QPushButton(btnGroup, "btnEdit");
    btn->setPixmap(QPixmap::fromMimeSource("edit.png"));
    btn->setFixedSize(60,60);
    connect(btn, SIGNAL(clicked()), arcTab, SLOT(editRowData()));
    btnGrid->addWidget(btn, 0, 0);     
    
    btn = new QPushButton(btnGroup, "btnDelete");
    btn->setPixmap(QPixmap::fromMimeSource("delete.png"));
    btn->setFixedSize(60,60);
    connect(btn, SIGNAL(clicked()), arcTab, SLOT(deleteRowData()));
    btnGrid->addWidget(btn, 0, 1);     

    dBegin = new QDateEdit(QDate::currentDate(), btnGroup, "dBegin");
    connect(dBegin, SIGNAL(valueChanged(const QDate &)), this, SLOT(applyFilter()));
    btnGrid->addWidget(dBegin, 0, 2);
    dEnd = new QDateEdit(QDate::currentDate(), btnGroup, "dEnd");
    connect(dEnd, SIGNAL(valueChanged(const QDate &)), this, SLOT(applyFilter()));    
    btnGrid->addWidget(dEnd, 0, 3);    
    
    btn = new QPushButton(btnGroup, "btnExit");
    btn->setAccel(Key_Escape);
    btn->setPixmap(QPixmap::fromMimeSource("exit.png"));
    btn->setFixedSize(60,60);
    connect(btn, SIGNAL(clicked()), this, SLOT(close()));
    btnGrid->addWidget(btn, 0, 4);    
}

void alArchiveWindow::refresh()
{

}

void alArchiveWindow::close()
{
    emit(exit());
}

void alArchiveWindow::applyFilter()
{
    QString filter = QString("orderdate>='%1' AND orderdate<='%2'").arg(dBegin->date().toString("yyyy-MM-dd")).arg(dEnd->date().toString("yyyy-MM-dd"));
    arcTab->load(filter);
}
