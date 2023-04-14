#include <qmessagebox.h>
#include "userstable.h"
#include "engine.h"


#define TABLE "users"

alUsersTable::alUsersTable(QWidget * parent, alEngine * engine) :
	alDataTable(parent, engine, TABLE)
{
    headers << tr("name");
    fields[tr("name")] = "name";
    maxWidthColumn = "name";    
}

void alUsersTable::init()
{
    alDBG("alUsersTable::init start");
    hideVerticalHeader();    
    fData = new alDataUsers(fEngine);
    setSelectionMode(NoSelection);    
    alDataTable::init();    
    load();
    setCurrentRow(0);
    alDBG("alUsersTable::init finish");
}

/*
*	возвращает иконку пользователя
*	return pixmap of user
*/
QPixmap alUsersTable::pixmap(int r)
{
    Q_UNUSED(r);
    return QPixmap::fromMimeSource("people.png");
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
