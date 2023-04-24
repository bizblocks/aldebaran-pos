class dlgVMSettings : public QDialog, Ui::dlgVMSettings
{
public:
    dlgVMSettings(QWidget * parent=0) : QDialog(parent), Ui::dlgVMSettings() {};
public slots:
    void init(eqDriver * device);
private:
    eqDriver * fDevice;
};

void dlgVMSettings::init(eqDriver *device)
{
    fDevice = device;
}
