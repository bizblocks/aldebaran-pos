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

void dlgDevice::setData(alEqRecord * data)
{
    if(!fEngine)
    {
	close();
	return;
    }
    fData = data;
    refresh();
    driverSelected(comboType->currentText());
}

void dlgDevice::refresh()
{
    editName->setText(fData->name());
    comboType->insertItem("");    
    comboType->insertStringList(fEngine->driverList());
    comboType->setCurrentText(fData->type());
    chkEnabled->setChecked(fData->enabled());
}

void dlgDevice::init(alEngine * e)
{
    fEngine = e;
    fDevice = NULL;
}

void dlgDevice::driverSelected(const QString & type)
{
    if(type.isEmpty())
        return;
    eqWorker * fWorker = eqWorker::worker();
    fDevice = fWorker->getDevice(editName->text());    
    if(!fDevice && fData->enabled())
    {
        QMessageBox::warning(this, "aldebaran", QString(tr("Can't create device of type %1\nSave element first.")).arg(type));
        return;
    }
    if(fDevice)
        fDevice->init();
}

void dlgDevice::settingsDialog()
{
    if(!fDevice)
        return;
    if(!fDevice->dialog())
        return;
}

void dlgDevice::apply()
{
    if(editName->text().isEmpty())
    {
	QMessageBox::information(this, "aldebaran", tr("You must input device name"));
	return;
    }
    if(comboType->currentText().isEmpty())
    {	
	QMessageBox::information(this, "aldebaran", tr("You must input device type"));
	return;    
    }
    fData->setName(editName->text());
    fData->setType(comboType->currentText());
    fData->setEnabled(chkEnabled->isChecked());
    if(!fDevice && fData->enabled())
    {
	eqWorker * fWorker = eqWorker::worker();
	fDevice = fWorker->createDevice(fData->type(), fData->name());
    }
    if(!fDevice) 
    {
	QMessageBox::information(this, "aldebaran", tr("Driver doesn't exist"));
	return;    	    
    }
    
    QStringList opts = fDevice->options();
    for(uint i=0;i<opts.count();i++)
	fData->setOption(opts[i], fDevice->option(opts[i]));
    accept();
}
