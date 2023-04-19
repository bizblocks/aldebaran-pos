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
#include "settings.h"

void settingsDialog::selectPicture()
{
    QFileDialog fileDlg(QDir::currentDirPath(), "Images (*.png *.jpg *.bmp)");
    fileDlg.setCaption(tr("Open shema picture"));
    if(fileDlg.exec()==QDialog::Accepted)
    {
        pix = QPixmap::fromMimeSource(fileDlg.selectedFile());
        labelPreview->setPixmap(pix);
    }
}

void settingsDialog::disableEnable()
{
    btnPictureSelect->setEnabled(rbShema->isChecked());
    spinTables->setEnabled(rbNumber->isChecked());
}


void settingsDialog::setData(QMap<QString, alValueList> data )
{
    editOrder->setText(data[GENERAL][TPLORDER].toString());
    editBill->setText(data[GENERAL][TPLBILL].toString());
    editPath->setText(data[GENERAL][IMPEXPPATH].toString());
    editImport->setText(data[GENERAL][IMPEXPIMPORT].toString());
    editExport->setText(data[GENERAL][IMPEXPEXPORT].toString());
    comboCP->setCurrentText(data[GENERAL][IMPEXPCP].toString());
    comboFormat->setCurrentText(QString::fromUtf8(data[GENERAL][IMPEXPFMT].toString()));
    pix = bytearray2pixmap(data[GENERAL][SHEMA].toByteArray());
    spinTables->setValue(data[GENERAL][TABLENUM].toString().toInt());
    labelPreview->setPixmap(pix);
    rbShema->setChecked(data[GENERAL][USESHEMA].toString().toInt());
    rbNumber->setChecked(!rbShema->isChecked());
    cbUseFtp->setChecked(data[GENERAL][IMPEXPFTP].toInt());
    editHost->setText(data[GENERAL][IMPEXPFTPHOST].toString());
    spinPort->setValue(data[GENERAL][IMPEXPFTPPORT].toInt());
    editLogin->setText(data[GENERAL][IMPEXPFTPLOGIN].toString());
    editPassword->setText(data[GENERAL][IMPEXPFTPPASSWORD].toString());
    editRDir->setText(data[GENERAL][IMPEXPFTPRDIR].toString());
    editDefPrinter->setText(QString::fromUtf8(data[EQUIPMENT][PRINTER].toString()));
    editDefECR->setText(QString::fromUtf8(data[EQUIPMENT][ECR].toString()));
}


QMap<QString, alValueList> settingsDialog::getData()
{
    QMap<QString, alValueList> res;
    res[GENERAL][TPLORDER] = editOrder->text();
    res[GENERAL][TPLBILL] = editBill->text();
    res[GENERAL][IMPEXPPATH] = editPath->text();
    res[GENERAL][IMPEXPIMPORT] = editImport->text();
    res[GENERAL][IMPEXPEXPORT] = editExport->text();
    res[GENERAL][IMPEXPCP] = comboCP->currentText();
    res[GENERAL][IMPEXPFMT] = comboFormat->currentText().utf8();
    res[GENERAL][TABLENUM] = QString("%1").arg(spinTables->value());
    res[GENERAL][SHEMA] = pixmap2bytearray(pix);
    res[GENERAL][USESHEMA] = rbShema->isChecked();
    res[GENERAL][IMPEXPFTP] = cbUseFtp->isChecked();
    res[GENERAL][IMPEXPFTPHOST] = editHost->text();
    res[GENERAL][IMPEXPFTPPORT] = spinPort->value();
    res[GENERAL][IMPEXPFTPLOGIN] = editLogin->text();
    res[GENERAL][IMPEXPFTPPASSWORD] = editPassword->text();
    res[GENERAL][IMPEXPFTPRDIR] = editRDir->text();
    
    res[EQUIPMENT][PRINTER] = editDefPrinter->text().utf8();
    res[EQUIPMENT][ECR] = editDefECR->text().utf8();
    return res;
}

void settingsDialog::init( alEngine * engine )
{
    editPath->setText(QDir::home().path());
    QTextCodec * codec;
    comboCP->insertItem("");
    for (int i = 0; (codec = QTextCodec::codecForIndex(i)); i++)
        comboCP->insertItem(codec->name());
    
    comboFormat->insertItem("");
    comboFormat->insertStringList(importer::importersList());
    
    new QGridLayout(frameGoods);
    new QGridLayout(frameUsers);
    new QGridLayout(frameEq);
    new QGridLayout(frameDiscount);
    
    fEngine = engine;
    
    alGoodsTable * goodsTab = new alGoodsTable(frameGoods, fEngine);
    frameGoods->layout()->add(goodsTab);
    goodsTab->init();

    alUsersTable * usersTab = new alUsersTable(frameUsers, fEngine);
    frameUsers->layout()->add(usersTab);
    usersTab->init();
    
    alEqTable * eqTab = new alEqTable(frameEq, fEngine);
    frameEq->layout()->add(eqTab);
    eqTab->init();
    
    alDiscountTable * discountTab = new alDiscountTable(frameDiscount, fEngine);
    frameDiscount->layout()->add(discountTab);
    discountTab->init();
    
    connect(btnNew, SIGNAL(clicked()), goodsTab, SLOT(newElement()));
    connect(btnNewGroup, SIGNAL(clicked()), goodsTab, SLOT(newGroup()));
    connect(btnEdit, SIGNAL(clicked()), goodsTab, SLOT(editRowData()));
    connect(btnDelete, SIGNAL(clicked()), goodsTab, SLOT(deleteRowData()));
    connect(btnLevelUp, SIGNAL(clicked()), goodsTab, SLOT(levelUp()));
    connect(btnHome, SIGNAL(clicked()), goodsTab, SLOT(home()));
    
    connect(btnUsersNew, SIGNAL(clicked()), usersTab, SLOT(newElement()));
    connect(btnUsersEdit, SIGNAL(clicked()), usersTab, SLOT(editRowData()));
    connect(btnUsersDelete, SIGNAL(clicked()), usersTab, SLOT(deleteRowData()));

    connect(btnDeviceNew, SIGNAL(clicked()), eqTab, SLOT(newElement()));
    connect(btnDeviceEdit, SIGNAL(clicked()), eqTab, SLOT(editRowData()));
    connect(btnDeviceDelete, SIGNAL(clicked()), eqTab, SLOT(deleteRowData()));
    
    connect(btnDiscountNew, SIGNAL(clicked()), discountTab, SLOT(newElement()));
    connect(btnDiscountEdit, SIGNAL(clicked()), discountTab, SLOT(editRowData()));
    connect(btnDiscountDelete, SIGNAL(clicked()), discountTab, SLOT(deleteRowData()));

}

void settingsDialog::selectImpExpDir()
{
    QString path = QFileDialog::getExistingDirectory(editPath->text(), this, "dlgImportExportDirectory",  tr("Choose directory for import/export"));
    if(!path.isEmpty()) editPath->setText(path);
}

void settingsDialog::selectBill()
{
    QString filename = QFileDialog::getOpenFileName(editBill->text(), tr("Templates *.tpl;;All files *"), this, "dlgSelectBill", tr("Select bill template"));
    if(!filename.isEmpty()) editBill->setText(filename);
}

void settingsDialog::selectOrder()
{
    QString filename = QFileDialog::getOpenFileName(editOrder->text(), tr("Templates *.tpl;;All files *"), this, "dlgSelectOrder", tr("Select order template"));
    if(!filename.isEmpty()) editOrder->setText(filename);
}
