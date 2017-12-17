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
#include "mscreader.h"

void dlgMSCReader::init( eqDriver * device )
{
    fDevice = device;
    if(!fDevice) return;
    editDevice->setText(fDevice->option("device"));
    editHeader->setText(fDevice->option("header"));
    editTrailer->setText(fDevice->option("trailer")); 
    comboBaudRate->insertStringList(((eqMSCReader*)fDevice)->supportedBaudRates());
    comboDataBits->insertStringList(((eqMSCReader*)fDevice)->supportedDataBits());
    comboParity->insertStringList(((eqMSCReader*)fDevice)->supportedParity());
    comboStopBits->insertStringList(((eqMSCReader*)fDevice)->supportedStopBits());
    comboFlowControl->insertStringList(((eqMSCReader*)fDevice)->supportedFlowControl());
    comboBaudRate->setCurrentText(fDevice->option("baudrate"));
    comboDataBits->setCurrentItem(fDevice->option("data bits").toInt());
    comboParity->setCurrentItem(fDevice->option("parity").toInt());
    comboStopBits->setCurrentItem(fDevice->option("stopbits").toInt());
    comboFlowControl->setCurrentItem(fDevice->option("flow control").toInt());    
}

void dlgMSCReader::apply()
{
    if(fDevice)
    {
	fDevice->setOption("device", editDevice->text());
	fDevice->setOption("baudrate", comboBaudRate->currentText());
	fDevice->setOption("parity", comboParity->currentItem());
	fDevice->setOption("data bits", comboDataBits->currentItem());
	fDevice->setOption("stopbits", comboStopBits->currentItem());
	fDevice->setOption("flow control", comboFlowControl->currentItem());
	fDevice->setOption("header", editHeader->text().left(1));
	fDevice->setOption("trailer", editTrailer->text().left(1));	
	accept();
    }
    else reject();
}
