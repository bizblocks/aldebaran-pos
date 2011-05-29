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

class alListBoxItem : public QListBoxPixmap
{
public:
    alListBoxItem(QPixmap pix, QString text) : QListBoxPixmap(pix, text) { checked = FALSE; };
    bool checked;
};

void dlgUser::setData(alUserRecord * data)
{
    fData = data;
    refresh();
}

void dlgUser::setItem(QListBoxItem * item, bool checked)
{
    QPixmap pxChecked = QPixmap::fromMimeSource("checked.png");
    QPixmap pxUnChecked = QPixmap::fromMimeSource("unchecked.png");     
    alListBoxItem * newItem = NULL;
    if(checked) newItem = new alListBoxItem(pxChecked, item->text());  
    else newItem = new alListBoxItem(pxUnChecked, item->text());
    newItem->checked = checked;
    listRights->changeItem(newItem, listRights->index(item));
}

void dlgUser::refresh()
{
    editName->setText(fData->name());
    for(int r=1;r<rEnd;r++)
	setItem(listRights->item(r-1), fData->right((alRights)r));
}

void dlgUser::check(QListBoxItem * item)
{
    setItem(item, !((alListBoxItem*)item)->checked);
}

void dlgUser::init()
{
    listRights->clear();
    for(int r=1;r<rEnd;r++)
    {
	alListBoxItem * item = new alListBoxItem(QPixmap::fromMimeSource("unchecked.png"), QObject::tr(alRightsStrings[r]));
	listRights->insertItem(item, r-1);
    }
    editPass->setText("1b24bi19qmz03hrpos");	// обманули :))
    fPassword = QString::null;
}


void dlgUser::passwordChanged( const QString & text )
{
    fPassword = text;
}

void dlgUser::ok()
{
    if(fPassword!=QString::null) fData->setPassword(fPassword);
    fData->setName(editName->text());
    for(int r=rStart+1;r<rEnd;r++)
	fData->setRight((alRights)r, ((alListBoxItem*)listRights->item(r-1))->checked);
    accept();
}
