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

#include "felixrk.h"

void dlgFelixSettings::init( eqDriver * device )
{
    fDevice = device;
    if(!fDevice) return;
    editDevice->setText(fDevice->option("device"));
    comboBaudRate->insertStringList(((eqFelixRK*)fDevice)->supportedBaudRates());
    comboDataBits->insertStringList(((eqFelixRK*)fDevice)->supportedDataBits());
    comboParity->insertStringList(((eqFelixRK*)fDevice)->supportedParity());
    comboStopBits->insertStringList(((eqFelixRK*)fDevice)->supportedStopBits());
    comboFlowControl->insertStringList(((eqFelixRK*)fDevice)->supportedFlowControl());
    comboBaudRate->setCurrentText(fDevice->option("baudrate"));
    comboDataBits->setCurrentItem(fDevice->option("data bits").toInt());
    comboParity->setCurrentItem(fDevice->option("parity").toInt());
    comboStopBits->setCurrentItem(fDevice->option("stopbits").toInt());
    comboFlowControl->setCurrentItem(fDevice->option("flow control").toInt());
    editAccessPassword->setText(fDevice->option("access password"));
    editOperatorPassword->setText(fDevice->option("operator password"));
    editAdminPassword->setText(fDevice->option("administrator password"));
}

void dlgFelixSettings::apply()
{
    if(fDevice)
    {
	fDevice->setOption("device", editDevice->text());
	fDevice->setOption("baudrate", comboBaudRate->currentText());
	fDevice->setOption("parity", comboParity->currentItem());
	fDevice->setOption("data bits", comboDataBits->currentItem());
	fDevice->setOption("stopbits", comboStopBits->currentItem());
	fDevice->setOption("flow control", comboFlowControl->currentItem());
	fDevice->setOption("access password", editAccessPassword->text());
	fDevice->setOption("operator password", editOperatorPassword->text());
	fDevice->setOption("administrator password", editAdminPassword->text());
	accept();
    }
    else reject();
}
