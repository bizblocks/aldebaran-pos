/****************************************************************************
 *
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
#include <QFileDialog>
#include <QTextCodec>
#include "settings.h"
#include "settingsdialog.h"
#include "goodstable.h"
#include "userstable.h"
#include "eqtable.h"
#include "discounttable.h"


void settingsDialog::selectPicture()
{
    QFileDialog fileDlg(this, tr("Open shema picture") ,QDir::currentDirPath(), "Images (*.png *.jpg *.bmp)");
    if(fileDlg.exec()==QDialog::Accepted)
    {
        pix = QPixmap(fileDlg.selectedFile());
        ui->labelPreview->setPixmap(pix);
    }
}

void settingsDialog::disableEnable()
{
    ui->btnPictureSelect->setEnabled(ui->rbShema->isChecked());
    ui->spinTables->setEnabled(ui->rbNumber->isChecked());
}


void settingsDialog::setData(QMap<QString, alValueList> data )
{
    ui->editOrder->setText(data[GENERAL][TPLORDER].toString());
    ui->editBill->setText(data[GENERAL][TPLBILL].toString());
    ui->editPath->setText(data[GENERAL][IMPEXPPATH].toString());
    ui->editImport->setText(data[GENERAL][IMPEXPIMPORT].toString());
    ui->editExport->setText(data[GENERAL][IMPEXPEXPORT].toString());
    ui->comboCP->setCurrentText(data[GENERAL][IMPEXPCP].toString());
    ui->comboFormat->setCurrentText(QString::fromUtf8(data[GENERAL][IMPEXPFMT].toString()));
    pix = bytearray2pixmap(data[GENERAL][SHEMA].toByteArray());
    ui->spinTables->setValue(data[GENERAL][TABLENUM].toString().toInt());
    ui->labelPreview->setPixmap(pix);
    ui->rbShema->setChecked(data[GENERAL][USESHEMA].toString().toInt());
    ui->rbNumber->setChecked(!ui->rbShema->isChecked());
    ui->cbUseFtp->setChecked(data[GENERAL][IMPEXPFTP].toInt());
    ui->editHost->setText(data[GENERAL][IMPEXPFTPHOST].toString());
    ui->spinPort->setValue(data[GENERAL][IMPEXPFTPPORT].toInt());
    ui->editLogin->setText(data[GENERAL][IMPEXPFTPLOGIN].toString());
    ui->editPassword->setText(data[GENERAL][IMPEXPFTPPASSWORD].toString());
    ui->editRDir->setText(data[GENERAL][IMPEXPFTPRDIR].toString());
    ui->editDefPrinter->setText(QString::fromUtf8(data[EQUIPMENT][PRINTER].toString()));
    ui->editDefECR->setText(QString::fromUtf8(data[EQUIPMENT][ECR].toString()));
}


QMap<QString, alValueList> settingsDialog::getData()
{
    QMap<QString, alValueList> res;
    res[GENERAL][TPLORDER] = ui->editOrder->text();
    res[GENERAL][TPLBILL] = ui->editBill->text();
    res[GENERAL][IMPEXPPATH] = ui->editPath->text();
    res[GENERAL][IMPEXPIMPORT] = ui->editImport->text();
    res[GENERAL][IMPEXPEXPORT] = ui->editExport->text();
    res[GENERAL][IMPEXPCP] = ui->comboCP->currentText();
    res[GENERAL][IMPEXPFMT] = ui->comboFormat->currentText().utf8();
    res[GENERAL][TABLENUM] = QString("%1").arg(ui->spinTables->value());
    res[GENERAL][SHEMA] = pixmap2bytearray(pix);
    res[GENERAL][USESHEMA] = ui->rbShema->isChecked();
    res[GENERAL][IMPEXPFTP] = ui->cbUseFtp->isChecked();
    res[GENERAL][IMPEXPFTPHOST] = ui->editHost->text();
    res[GENERAL][IMPEXPFTPPORT] = ui->spinPort->value();
    res[GENERAL][IMPEXPFTPLOGIN] = ui->editLogin->text();
    res[GENERAL][IMPEXPFTPPASSWORD] = ui->editPassword->text();
    res[GENERAL][IMPEXPFTPRDIR] = ui->editRDir->text();
    
    res[EQUIPMENT][PRINTER] = ui->editDefPrinter->text().utf8();
    res[EQUIPMENT][ECR] = ui->editDefECR->text().utf8();
    return res;
}

void settingsDialog::init( alEngine * engine )
{
    ui->editPath->setText(QDir::home().path());
    QTextCodec * codec;
    ui->comboCP->insertItem("");
    for (int i = 0; (codec = QTextCodec::codecForIndex(i)); i++)
        ui->comboCP->insertItem(codec->name());
    
    ui->comboFormat->insertItem("");
    ui->comboFormat->insertStringList(importer::importersList());
    
    new QGridLayout(ui->frameGoods);
    new QGridLayout(ui->frameUsers);
    new QGridLayout(ui->frameEq);
    new QGridLayout(ui->frameDiscount);
    
    fEngine = engine;
    
    alGoodsTable * goodsTab = new alGoodsTable(ui->frameGoods, fEngine);
    ui->frameGoods->layout()->add(goodsTab);
    goodsTab->init();

    alUsersTable * usersTab = new alUsersTable(ui->frameUsers, fEngine);
    ui->frameUsers->layout()->add(usersTab);
    usersTab->init();
    
    alEqTable * eqTab = new alEqTable(ui->frameEq, fEngine);
    ui->frameEq->layout()->add(eqTab);
    eqTab->init();
    
    alDiscountTable * discountTab = new alDiscountTable(ui->frameDiscount, fEngine);
    ui->frameDiscount->layout()->add(discountTab);
    discountTab->init();
    
    connect(ui->btnNew, SIGNAL(clicked()), goodsTab, SLOT(newElement()));
    connect(ui->btnNewGroup, SIGNAL(clicked()), goodsTab, SLOT(newGroup()));
    connect(ui->btnEdit, SIGNAL(clicked()), goodsTab, SLOT(editRowData()));
    connect(ui->btnDelete, SIGNAL(clicked()), goodsTab, SLOT(deleteRowData()));
    connect(ui->btnLevelUp, SIGNAL(clicked()), goodsTab, SLOT(levelUp()));
    connect(ui->btnHome, SIGNAL(clicked()), goodsTab, SLOT(home()));
    
    connect(ui->btnUsersNew, SIGNAL(clicked()), usersTab, SLOT(newElement()));
    connect(ui->btnUsersEdit, SIGNAL(clicked()), usersTab, SLOT(editRowData()));
    connect(ui->btnUsersDelete, SIGNAL(clicked()), usersTab, SLOT(deleteRowData()));

    connect(ui->btnDeviceNew, SIGNAL(clicked()), eqTab, SLOT(newElement()));
    connect(ui->btnDeviceEdit, SIGNAL(clicked()), eqTab, SLOT(editRowData()));
    connect(ui->btnDeviceDelete, SIGNAL(clicked()), eqTab, SLOT(deleteRowData()));
    
    connect(ui->btnDiscountNew, SIGNAL(clicked()), discountTab, SLOT(newElement()));
    connect(ui->btnDiscountEdit, SIGNAL(clicked()), discountTab, SLOT(editRowData()));
    connect(ui->btnDiscountDelete, SIGNAL(clicked()), discountTab, SLOT(deleteRowData()));

}

void settingsDialog::selectImpExpDir()
{
    QString path = QFileDialog::getExistingDirectory(ui->editPath->text(), this, "dlgImportExportDirectory",  tr("Choose directory for import/export"));
    if(!path.isEmpty())
        ui->editPath->setText(path);
}

void settingsDialog::selectBill()
{
    QString filename = QFileDialog::getOpenFileName(ui->editBill->text(), tr("Templates *.tpl;;All files *"), this, "dlgSelectBill", tr("Select bill template"));
    if(!filename.isEmpty())
        ui->editBill->setText(filename);
}

void settingsDialog::selectOrder()
{
    QString filename = QFileDialog::getOpenFileName(ui->editOrder->text(), tr("Templates *.tpl;;All files *"), this, "dlgSelectOrder", tr("Select order template"));
    if(!filename.isEmpty())
        ui->editOrder->setText(filename);
}
