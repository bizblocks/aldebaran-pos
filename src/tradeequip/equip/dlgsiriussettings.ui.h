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

class dlgSiriusSettings : public QDialog, Ui::dlgSiriusSettings
{
public:
    dlgSiriusSettings(QWidget * parent = 0) : QDialog(parent), Ui::dlgSiriusSettings() {};
public slots:
    void init( eqDriver * device );
    void apply();
private:
    eqDriver * fDevice;
};

void dlgSiriusSettings::init( eqDriver * device )
{
    fDevice = device;
    if(!fDevice) return;
    editHost->setText(fDevice->option("host"));
    spinPort->setValue(fDevice->option("port").toInt());
    spinTable->setValue(fDevice->option("table").toInt());
}

void dlgSiriusSettings::apply()
{
    if(fDevice)
    {
        fDevice->setOption("host", editHost->text());
        fDevice->setOption("port", spinPort->value());
        fDevice->setOption("table", spinTable->value());
        accept();
    }
    else reject();
}
