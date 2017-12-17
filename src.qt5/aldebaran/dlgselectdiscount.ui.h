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

void dlgSelectDiscount::init(alEngine * e)
{
    fResult = -1;
    fEngine = e;
    new QGridLayout(frameDiscount);    
    tab = new alDiscountTable(frameDiscount, e);
    tab->setSelectable(true);    
    tab->init();
    frameDiscount->layout()->add(tab);    
    adjustSize();
    connect(tab, SIGNAL(selected(Q_ULLONG)), this, SLOT(selected(Q_ULLONG))); 
}

void dlgSelectDiscount::selected(Q_ULLONG id)
{
    fResult = id;
    accept();
}

void dlgSelectDiscount::selected()
{
    if(tab) fResult = tab->value("id").toULongLong();
    accept();
}

Q_ULLONG dlgSelectDiscount::resultId()
{
    return fResult;
}
