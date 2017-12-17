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

void equipmentDialog::init(alEngine * e)
{
    inAction = 0;
    fEngine = e;
    fill(0);
}

void equipmentDialog::setItem(QListBoxItem * item, bool checked)
{
    QPixmap pxChecked = QPixmap::fromMimeSource("checked.png");
    QPixmap pxUnChecked = QPixmap::fromMimeSource("unchecked.png");     
    alListBoxItem * newItem = NULL;
    if(checked) newItem = new alListBoxItem(pxChecked, item->text());  
    else newItem = new alListBoxItem(pxUnChecked, item->text());
    newItem->checked = checked;
    listDevices->changeItem(newItem, listDevices->index(item));
}

void equipmentDialog::check(QListBoxItem * item)
{
    if(item) setItem(item, !((alListBoxItem*)item)->checked);
}

void equipmentDialog::execute()
{
    inAction = 1;
    QString action = cbActions->currentText();
    if(action==tr("reload data")) fEngine->prepareGoods(toolbox->itemLabel(toolbox->currentIndex()));
    for(uint i=0;i<listDevices->count();i++)
    {
	bool res = FALSE;
	if(!((alListBoxItem*)listDevices->item(i))->checked) continue;
	else if(action==tr("reload data")) res = fEngine->exportGoods(listDevices->text(i));
	else if(action==tr("reset")) res = fEngine->resetDevice(listDevices->text(i));	
	else if(action==tr("shutdown")) res = fEngine->shutdownDevice(listDevices->text(i));	
	else if(action==tr("update")) res = fEngine->updateDevice(listDevices->text(i));
	else if(action==tr("connect")) res = fEngine->connectDevice(listDevices->text(i));
	if(res) check(listDevices->item(i));
    }
    if(inAction>2) reject();
}

void equipmentDialog::fill(int n)
{
    cbActions->clear();
    listDevices->clear();
    QString type="nothing";
    if(!n)
    {
	cbActions->insertItem("");
	cbActions->insertItem(tr("reload data"));
	cbActions->insertItem(tr("reset"));
	cbActions->insertItem(tr("shutdown"));
	cbActions->insertItem(tr("update"));	
	cbActions->insertItem(tr("connect"));
	type = toolbox->itemLabel(n);
    }
    alDataEq * eq = new alDataEq(fEngine);    
    eq->select(QString("type='%1'").arg(type));
    if(eq->first()) do
    {
	alListBoxItem * item = new alListBoxItem(QPixmap::fromMimeSource("unchecked.png"), eq->value("name").toString());
	listDevices->insertItem(item);
    }while(eq->next());
}

void equipmentDialog::checkAll()
{
    for(uint i=0;i<listDevices->count();i++)
    {
	if(((alListBoxItem*)listDevices->item(i))->checked) continue;
	check(listDevices->item(i));
    }
}

void equipmentDialog::unCheckAll()
{
    for(uint i=0;i<listDevices->count();i++)
    {
	if(!((alListBoxItem*)listDevices->item(i))->checked) continue;
	check(listDevices->item(i));
    }
}

void equipmentDialog::checkClose()
{
    inAction++;
    if(inAction>1) hide();
    else reject();
}
