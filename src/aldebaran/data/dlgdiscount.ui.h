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
#include <qmessagebox.h>

class dlgDiscount : public QDialog, Ui::dlgDiscount
{
public:
    dlgDiscount(QWidget * parent = 0) : QDialog(parent), Ui::dlgDiscount() {};
public slots:
    void setData(alDiscountRecord * data);
    void refresh();
    void init(alEngine * e);
    void typeSelected(int type);
    void apply();
private:
    alEngine * fEngine;
    alDiscountRecord * fData;
};

void dlgDiscount::setData(alDiscountRecord * data)
{
    if(!fEngine)
    {
        close();
        return;
    }
    fData = data;
    refresh();
    typeSelected(comboType->currentItem());
}

void dlgDiscount::refresh()
{
    editName->setText(fData->name());
    editCode->setText(fData->code());
    comboType->insertItem(tr("procentage"));
    comboType->insertItem(tr("monetary"));
    comboType->setCurrentItem(fData->type());
    spinValue->setValue(fData->value());
    chkProtect->setChecked(fData->protect());
}

void dlgDiscount::init(alEngine * e)
{
    fEngine = e;
}

void dlgDiscount::typeSelected(int type)
{
    if(type==0)
    {
        spinValue->setMaxValue(100);
        if(spinValue->value()>100) spinValue->setValue(100);
    }
    else if(type==1)
    {
        spinValue->setMaxValue(10000);
        if(spinValue->value()>10000) spinValue->setValue(10000);
    }
}

void dlgDiscount::apply()
{
    if(editName->text().isEmpty())
    {
        QMessageBox::information(this, "aldebaran", tr("You must input discount name"));
        return;
    }
    fData->setName(editName->text());
    fData->setType(comboType->currentItem());
    fData->setValue(spinValue->value());
    fData->setProtect(chkProtect->isChecked());
    fData->setCode(editCode->text());
    accept();
}
