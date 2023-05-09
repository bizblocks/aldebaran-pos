/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <Q3ListBoxPixmap>
#include <Q3ListBoxItem>
#include "dlguser.h"

class alListBoxItem : public Q3ListBoxPixmap
{
public:
    alListBoxItem(QPixmap pix, QString text) : Q3ListBoxPixmap(pix, text) { checked = FALSE; };
    bool checked;
};

void dlgUser::setData(alUserRecord * data)
{
    fData = data;
    refresh();
}

void dlgUser::setItem(Q3ListBoxItem * item, bool checked)
{
    QPixmap pxChecked = QPixmap(":/images/checked.png");
    QPixmap pxUnChecked = QPixmap(":/images/unchecked.png");
    alListBoxItem * newItem = NULL;
    if(checked)
        newItem = new alListBoxItem(pxChecked, item->text());
    else
        newItem = new alListBoxItem(pxUnChecked, item->text());
    newItem->checked = checked;
    ui->listRights->changeItem(newItem, ui->listRights->index(item));
}

void dlgUser::refresh()
{
    ui->editName->setText(fData->name());
    for(int r=1;r<rEnd;r++)
        setItem(ui->listRights->item(r-1), fData->right((alRights)r));
}

void dlgUser::check(Q3ListBoxItem * item)
{
    setItem(item, !((alListBoxItem*)item)->checked);
}

void dlgUser::init()
{
    ui->listRights->clear();
    for(int r=rStart+1;r<rEnd;r++)
    {
        qDebug(QObject::tr(alRightsStrings[r]));
        alListBoxItem * item = new alListBoxItem(QPixmap(":/images/unchecked.png"), QObject::tr(alRightsStrings[r]));
        ui->listRights->insertItem(item, r-1);
    }
    ui->editPass->setText("1b24bi19qmz03hrpos");
    fPassword = QString::null;
}


void dlgUser::passwordChanged( const QString & text )
{
    fPassword = text;
}

void dlgUser::ok()
{
    if(fPassword!=QString::null)
        fData->setPassword(fPassword);
    fData->setName(ui->editName->text());
    for(int r=rStart+1;r<rEnd;r++)
        fData->setRight((alRights)r, ((alListBoxItem*)ui->listRights->item(r-1))->checked);
    accept();
}
