#include <QDebug>
#include <qmessagebox.h>
#include "userstable.h"
#include "datausers.h"
#include "engine.h"


#define TABLE "users"

alUsersTable::alUsersTable(QWidget * parent, alEngine * engine) :
	alDataTable(parent, engine, TABLE)
{
    fields[tr("name")] = "name";
    maxWidthColumn = "name";    
}

void alUsersTable::init(alEngine * e)
{
    fData = new alDataUsers(e);
    alDataTable::init(e);
    hideVerticalHeader();
    this->addHeaders(QStringList(tr("name")));
    //setSelectionMode(NoSelection); //??
    load();
    setCurrentRow(0);
}

alUserRecord * alUsersTable::current()
{
    fData->seek(currentRow());
    return (alUserRecord*) fData->current();
}

bool alUsersTable::dialog(alUserRecord * user)	
{
    int row = currentRow();
    if(user->dialog(this))
    {
        load();
        setCurrentRow(row);
        return TRUE;
    }
    return FALSE;	
}

bool alUsersTable::newElement()
{
    return dialog(((alDataUsers*)fData)->newElement());
}

bool alUsersTable::editRowData()
{
    return dialog(current());
}

bool alUsersTable::deleteRowData()
{
    int row = currentRow();
    fData->seek(row);
    int res;
    res = QMessageBox::question(this, "aldebaran", tr("Delete element??"), QMessageBox::Yes,QMessageBox::No);	
    if(res==QMessageBox::Yes)
    {
        ((alDataUsers*)fData)->delElement();
        load();
    }
    setCurrentRow(row);
    return res;    
}
