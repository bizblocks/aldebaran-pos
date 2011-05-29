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


void dlgCTS300Settings::init( eqDriver * device )
{
    fDevice = device;
    if(!fDevice) return;
    editDevice->setText(fDevice->option("device"));
    comboCP->insertItem("");
    comboCP->insertStringList(((eqCTS300Printer *)fDevice)->codepages());
    comboCP->setCurrentText(fDevice->option("codepage"));
    spinPrintWidth->setValue(fDevice->option("print width").toInt());
}

void dlgCTS300Settings::apply()
{
    if(fDevice)
    {
	fDevice->setOption("device", editDevice->text());
	fDevice->setOption("codepage", comboCP->currentText());
	fDevice->setOption("print width", spinPrintWidth->value());
	accept();	
    } 
    else reject();
}
