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


class alListBoxItem : public Q3ListBoxPixmap
{
public:
    alListBoxItem(QPixmap pix, QString text) : Q3ListBoxPixmap(pix, text) { checked = FALSE; };
    bool checked;
};

class dlgUser : public QDialog, Ui::dlgUser
{
public:
    dlgUser(QWidget * parent = 0) : QDialog(parent), Ui::dlgUser() {};
public slots:
    void setData(alUserRecord * data);
    void setItem(Q3ListBoxItem * item, bool checked);
    void refresh();
    void check(Q3ListBoxItem * item);
    void init();
    void passwordChanged( const QString & text );
    void ok();
private:
    alUserRecord * fData;
    QString fPassword;
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

void dlgUser::check(Q3ListBoxItem * item)
{
    setItem(item, !((alListBoxItem*)item)->checked);
}

void dlgUser::init()
{
    listRights->clear();
    for(int r=rStart+1;r<rEnd;r++)
    {
	qDebug(QObject::tr(alRightsStrings[r]));
    alListBoxItem * item = new alListBoxItem(QPixmap(":/images/unchecked.png"), QObject::tr(alRightsStrings[r]));
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
