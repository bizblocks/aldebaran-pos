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

class dlgECRSettings : public QDialog, Ui::dlgECRSettings
{
public:
    dlgECRSettings(QWidget * parent = 0) : QDialog(parent), Ui::dlgECRSettings() {};
public slots:
    void init( eqDriver * device );
    void apply();
private:
    eqFR * fDevice;
};


void dlgECRSettings::init( eqDriver * device )
{
    fDevice = (eqFR*)device;
    if(!fDevice) return;
    
    QStringList drvList = fDevice->driverList();
    for(int i=0;i<drvList.size();i++) drvList[i] = drvList[i].replace("TECashRegister", "");

    comboDriver->insertStringList(drvList);
    comboBaudRate->insertStringList(fDevice->supportedBaudRates());
    comboDataBits->insertStringList(fDevice->supportedDataBits());
    comboParity->insertStringList(fDevice->supportedParity());
    comboStopBits->insertStringList(fDevice->supportedStopBits());
    comboFlowControl->insertStringList(fDevice->supportedFlowControl());
    comboCP->insertStringList(fDevice->codepages());
    
    editDevice->setText(fDevice->option("device"));
    comboDriver->setCurrentText(fDevice->option("driver"));
    comboBaudRate->setCurrentText(fDevice->option("baudrate"));
    comboDataBits->setCurrentItem(fDevice->option("data bits").toInt());
    comboParity->setCurrentItem(fDevice->option("parity").toInt());
    comboStopBits->setCurrentItem(fDevice->option("stopbits").toInt());
    comboFlowControl->setCurrentItem(fDevice->option("flow control").toInt());
    comboCP->setCurrentText(fDevice->option("codepage"));
    
    editAccessPassword->setText(fDevice->option("access password"));
    editOperatorPassword->setText(fDevice->option("operator password"));
    editAdminPassword->setText(fDevice->option("administrator password"));
    editHeader->setText(fDevice->option("header"));
    editFooter->setText(fDevice->option("footer"));
}

void dlgECRSettings::apply()
{
    if(fDevice)
    {
        fDevice->setOption("driver", comboDriver->currentText());
        fDevice->setOption("device", editDevice->text());
        fDevice->setOption("baudrate", comboBaudRate->currentText());
        fDevice->setOption("parity", comboParity->currentItem());
        fDevice->setOption("data bits", comboDataBits->currentItem());
        fDevice->setOption("stopbits", comboStopBits->currentItem());
        fDevice->setOption("flow control", comboFlowControl->currentItem());
        fDevice->setOption("access password", editAccessPassword->text());
        fDevice->setOption("operator password", editOperatorPassword->text());
        fDevice->setOption("administrator password", editAdminPassword->text());
        fDevice->setOption("codepage", comboCP->currentText());
        fDevice->setOption("header", editHeader->text());
        fDevice->setOption("footer", editFooter->text());
        accept();
    }
    else reject();
}
