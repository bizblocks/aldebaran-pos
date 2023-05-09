#include <qmessagebox.h>
#include <QDirIterator>
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
    hideVerticalHeader();
    fData = new alDataUsers(fEngine);
    setSelectionMode(NoSelection);
    alDataTable::init();
    load();
    setCurrentRow(0);
}

/*
*	возвращает иконку пользователя
*	return pixmap of user
*/
QIcon alUsersTable::icon(int r)
{
    Q_UNUSED(r);
    return QIcon(":/images/people.png");
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
