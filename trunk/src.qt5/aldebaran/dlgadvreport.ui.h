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

void dlgAdvReport::init()
{
    cmbType->setCurrentItem(0);
    cmbReport->setCurrentItem(0);
    QDateTime t = QDateTime::currentDateTime();
    t.setTime(QTime(0,0,0));
    dteBegin->setDateTime(t);
    t.setTime(QTime(23,59,59));
    dteEnd->setDateTime(t);
    refresh(cmbType->currentItem());
}

void dlgAdvReport::refresh(int t)
{
    dteBegin->setEnabled(t==1);
    dteEnd->setEnabled(t==1);    
}

QDateTime dlgAdvReport::begin()
{
    return dteBegin->dateTime();
}

QDateTime dlgAdvReport::end()
{
    return dteEnd->dateTime();
}

int dlgAdvReport::period()
{
    return cmbType->currentItem();
}

int dlgAdvReport::type()
{
    return cmbReport->currentItem();
}
