#include <qdir.h>
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>
#include "settings.h"
#include "ui_ddbsettings.h"
#include "ui_settingsdialog.h"
#include "data/datasettings.h"

alSettings::alSettings(alEngine * e) : 
    QObject(),
    dbdlg(NULL)
{
	fEngine = e;
	if(fEngine) connect(fEngine, SIGNAL(initialized()), this, SLOT(subSystemSettings()));
	init();
}

alSettings::~alSettings()
{
    if(dbdlg)
        delete dbdlg;
}

/*
Инициализация настроек
	- Настройки базы данных, не настроена - сообщить, запросить
TODO	- Поиск таблицы в базе данных, создание при отсутствии
*/
void alSettings::init()
{
	QString value;	
	dbParams.clear();
    QSettings qtSettings("Lobo, Koba & Satan", "aldebaran");
	qtSettings.beginGroup("/connection");

    value = qtSettings.value("/TYPE", "nodb").toString();
	dbParams.append(value);
	
    value = qtSettings.value("/DB", "aldebaran").toString();
	dbParams.append(value);

    value = qtSettings.value("/ADRESS", "127.0.0.1").toString();
	dbParams.append(value);

    value = qtSettings.value("/PORT", "5432").toString();
	dbParams.append(value);
	
    value = qtSettings.value("/USER", "aldebaran").toString();
	dbParams.append(value);
	
    value = qtSettings.value("/PASSWORD", "aldebran").toString();
	dbParams.append(value);
	
	qtSettings.endGroup();
	
	QStringList k;
	k<<TABLENUM<<SHEMA<<USESHEMA<<IMPEXPCP<<IMPEXPFMT;
	k<<IMPEXPPATH<<IMPEXPIMPORT<<IMPEXPEXPORT;
	k<<TPLORDER<<TPLBILL;	
	k<<IMPEXPFTP<<IMPEXPFTPHOST<<IMPEXPFTPPORT<<IMPEXPFTPLOGIN<<IMPEXPFTPPASSWORD;
	k<<IMPEXPFTPRDIR;
	
	addSubSystem(GENERAL, k);
	k.clear();
	k<<PRINTER<<ECR;
	addSubSystem(EQUIPMENT, k);
}

bool alSettings::dbDialog()
{    
    QDialog dlg;
    dbdlg = new Ui::ddbsettings();//(0, "dbsettingsdlg", true);
    dbdlg->setupUi(&dlg);
    connect(dbdlg->btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTest_clicked()));
    this->setDBData(dbParams);
    int res = dlg.exec();
#ifdef DEBUG
    qDebug(QString(tr("ddbsettings dialog returns %1")).arg(res).toUtf8());
#endif
    if(res)
    {
        dbParams = this->getDBData();
        flushqt();
    }
    return res;
}

bool alSettings::dialog()
{    
    QDialog dlg;
    settingsDialog = new Ui::settingsDialog();
    settingsDialog->setupUi(&dlg);
    this->initDialog(fEngine);
    this->setData(params);
    int res = dlg.exec();
#ifdef DEBUG
    qDebug() << QString(tr("settings dialog returns %1")).arg(res).toUtf8();
#endif
    if(res)
    params = this->getData();
    return res;
}

QStringList alSettings::dbSettings()
{
    return dbParams;
}

//TODO reimplement
void alSettings::flushqt()
{
    QSettings qtSettings("Lobo, Koba & Satan", "aldebaran");
//    qtSettings.insertSearchPath(QSettings::Unix, QString(QDir::homeDirPath())+QString("/.aldebaran"));
    qtSettings.beginGroup("/connection");
    
    qtSettings.setValue("/TYPE", dbParams[0]);
    qtSettings.setValue("/DB", dbParams[1]);
    qtSettings.setValue("/ADRESS", dbParams[2]);
    qtSettings.setValue("/PORT", dbParams[3]);
    qtSettings.setValue("/USER", dbParams[4]);
    qtSettings.setValue("/PASSWORD", dbParams[5]);
    
    qtSettings.endGroup();
}

/*
*/
//TODO uncomment
void alSettings::flushsql()
{
    if(!fEngine->db().isOpen())
        return;
    fEngine->startTransaction();
    alDataSettings * t = new alDataSettings(fEngine);
    for(int s=0;s<(int)subSystems.count();s++)
        for(int v=0;v<(int)keys[subSystems[s]].count();v++)
            t->save(subSystems[s], keys[subSystems[s]][v], params[subSystems[s]][keys[subSystems[s]][v]]);
    fEngine->commitTransaction();
    delete t;
}

/*
*  Сохраняет все настройки на диск и в БД.
*/
void alSettings::flush()
{
    flushqt();
    flushsql();
}

alValueList alSettings::subSystemSettings(QString subSystem)
{
    alValueList res;
    res.clear();
    
    if(subSystem.isEmpty())	subSystem = "%%";
    
    //TODO uncomment
//    alDataSettings * t = new alDataSettings(fEngine);
//    t->select(QString("subsystem LIKE '%1'").arg(subSystem));
//    if(t->first()) do
//    {
//        params[t->value("subsystem").toString()][t->value("valkey").toString()] = t->value("value");
//        res[t->value("valkey").toString()] = t->value("value");
//    } while(t->next());
  
//    delete t;
    return res;
}


QVariant alSettings::parameter(QString sub, QString key)
{
    return params[sub][key];
}

void alSettings::setDBData( QStringList data )
{
    dbdlg->cmbDBType->clear();
    QStringList drivers = QSqlDatabase::drivers();
    dbdlg->cmbDBType->insertItems(0, drivers);
#ifdef DEBUG
    qDebug() << tr("available drivers: %s").arg(drivers.join(", ")).toUtf8();
#endif
    if(!data[0].isEmpty())
    dbdlg->cmbDBType->setCurrentText(data[0]);
    dbdlg->editDBName->setText(data[1]);
    dbdlg->editAdress->setText(data[2]);
    dbdlg->editPort->setText(data[3]);
    dbdlg->editUser->setText(data[4]);
    dbdlg->editPassword->setText(data[5]);
}

QStringList alSettings::getDBData()
{
    QStringList res;
    res.append(dbdlg->cmbDBType->currentText());
    res.append(dbdlg->editDBName->text());
    res.append(dbdlg->editAdress->text());
    res.append(dbdlg->editPort->text());
    res.append(dbdlg->editUser->text());
    res.append(dbdlg->editPassword->text());
    return res;
}

void alSettings::on_btnTest_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(dbdlg->cmbDBType->currentText(), "testconnectiondb");
    db.setDatabaseName(dbdlg->editDBName->text());
    db.setHostName(dbdlg->editAdress->text());
    db.setPort(dbdlg->editPort->text().toInt());
    bool res = db.open(dbdlg->editUser->text(), dbdlg->editPassword->text());
    if(res)
        QMessageBox::information(NULL, "aldebaran", QObject::tr("Successfully connected"));
    else
        QMessageBox::critical(NULL, "aldebaran", QObject::tr("Can't connect database:")+"\n"+db.lastError().text());
    QSqlDatabase::removeDatabase("testconnectiondb");
}

//void settingsDialog::selectPicture()
//{
//    QFileDialog fileDlg(QDir::currentDirPath(), "Images (*.png *.jpg *.bmp)");
//    fileDlg.setCaption(tr("Open shema picture"));
//    if(fileDlg.exec()==QDialog::Accepted)
//    {
//    pix = QPixmap::fromMimeSource(fileDlg.selectedFile());
//    labelPreview->setPixmap(pix);
//    }
//}

//void settingsDialog::disableEnable()
//{
//    btnPictureSelect->setEnabled(rbShema->isChecked());
//    spinTables->setEnabled(rbNumber->isChecked());
//}


void alSettings::setData(QMap<QString, alValueList> data )
{
    settingsDialog->editOrder->setText(data[GENERAL][TPLORDER].toString());
    settingsDialog->editBill->setText(data[GENERAL][TPLBILL].toString());
    settingsDialog->editPath->setText(data[GENERAL][IMPEXPPATH].toString());
    settingsDialog->editImport->setText(data[GENERAL][IMPEXPIMPORT].toString());
    settingsDialog->editExport->setText(data[GENERAL][IMPEXPEXPORT].toString());
    settingsDialog->comboCP->setCurrentText(data[GENERAL][IMPEXPCP].toString());
    settingsDialog->comboFormat->setCurrentText(data[GENERAL][IMPEXPFMT].toString());
    settingsDialog->spinTables->setValue(data[GENERAL][TABLENUM].toString().toInt());
    settingsDialog->cbUseFtp->setChecked(data[GENERAL][IMPEXPFTP].toInt());
    settingsDialog->editHost->setText(data[GENERAL][IMPEXPFTPHOST].toString());
    settingsDialog->spinPort->setValue(data[GENERAL][IMPEXPFTPPORT].toInt());
    settingsDialog->editLogin->setText(data[GENERAL][IMPEXPFTPLOGIN].toString());
    settingsDialog->editPassword->setText(data[GENERAL][IMPEXPFTPPASSWORD].toString());
    settingsDialog->editRDir->setText(data[GENERAL][IMPEXPFTPRDIR].toString());
    settingsDialog->editDefPrinter->setText(data[EQUIPMENT][PRINTER].toString());
    settingsDialog->editDefECR->setText(data[EQUIPMENT][ECR].toString());
}


QMap<QString, alValueList> alSettings::getData()
{
    QMap<QString, alValueList> res;
    res[GENERAL][TPLORDER] = settingsDialog->editOrder->text();
    res[GENERAL][TPLBILL] = settingsDialog->editBill->text();
    res[GENERAL][IMPEXPPATH] = settingsDialog->editPath->text();
    res[GENERAL][IMPEXPIMPORT] = settingsDialog->editImport->text();
    res[GENERAL][IMPEXPEXPORT] = settingsDialog->editExport->text();
    res[GENERAL][IMPEXPCP] = settingsDialog->comboCP->currentText();
    res[GENERAL][IMPEXPFMT] = settingsDialog->comboFormat->currentText();
    res[GENERAL][TABLENUM] = QString("%1").arg(settingsDialog->spinTables->value());
    res[GENERAL][IMPEXPFTP] = settingsDialog->cbUseFtp->isChecked();
    res[GENERAL][IMPEXPFTPHOST] = settingsDialog->editHost->text();
    res[GENERAL][IMPEXPFTPPORT] = settingsDialog->spinPort->value();
    res[GENERAL][IMPEXPFTPLOGIN] = settingsDialog->editLogin->text();
    res[GENERAL][IMPEXPFTPPASSWORD] = settingsDialog->editPassword->text();
    res[GENERAL][IMPEXPFTPRDIR] = settingsDialog->editRDir->text();

    res[EQUIPMENT][PRINTER] = settingsDialog->editDefPrinter->text();
    res[EQUIPMENT][ECR] = settingsDialog->editDefECR->text();
    return res;
}

void alSettings::initDialog( alEngine * engine )
{
    settingsDialog->editPath->setText(QDir::home().path());
    settingsDialog->comboCP->addItem("");
    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    for (int i = 0; i<codecs.size(); i++)
        settingsDialog->comboCP->addItem(codecs.value(i).data());

    settingsDialog->comboFormat->addItem("");
    //settingsDialog->comboFormat->addItems(importer::importersList());

    new QGridLayout(settingsDialog->frameGoods);
    new QGridLayout(settingsDialog->frameUsers);
    new QGridLayout(settingsDialog->frameEq);
    new QGridLayout(settingsDialog->frameDiscount);

    fEngine = engine;

    settingsDialog->goodsTab->init(engine);
    settingsDialog->usersTab->init(engine);

//    alEqTable * eqTab = new alEqTable(frameEq, fEngine);
//    frameEq->layout()->add(eqTab);
//    eqTab->init();

//    alDiscountTable * discountTab = new alDiscountTable(frameDiscount, fEngine);
//    frameDiscount->layout()->add(discountTab);
//    discountTab->init();

    connect(settingsDialog->btnNew, SIGNAL(clicked()), settingsDialog->goodsTab, SLOT(newElement()));
//    connect(settingsDialog->btnNewGroup, SIGNAL(clicked()), settingsDialog->goodsTab, SLOT(newGroup()));
    connect(settingsDialog->btnEdit, SIGNAL(clicked()), settingsDialog->goodsTab, SLOT(editRowData()));
    connect(settingsDialog->btnDelete, SIGNAL(clicked()), settingsDialog->goodsTab, SLOT(deleteRowData()));
    connect(settingsDialog->btnLevelUp, SIGNAL(clicked()), settingsDialog->goodsTab, SLOT(levelUp()));
    connect(settingsDialog->btnHome, SIGNAL(clicked()), settingsDialog->goodsTab, SLOT(home()));

//    connect(btnUsersNew, SIGNAL(clicked()), usersTab, SLOT(newElement()));
//    connect(btnUsersEdit, SIGNAL(clicked()), usersTab, SLOT(editRowData()));
//    connect(btnUsersDelete, SIGNAL(clicked()), usersTab, SLOT(deleteRowData()));

//    connect(btnDeviceNew, SIGNAL(clicked()), eqTab, SLOT(newElement()));
//    connect(btnDeviceEdit, SIGNAL(clicked()), eqTab, SLOT(editRowData()));
//    connect(btnDeviceDelete, SIGNAL(clicked()), eqTab, SLOT(deleteRowData()));

//    connect(btnDiscountNew, SIGNAL(clicked()), discountTab, SLOT(newElement()));
//    connect(btnDiscountEdit, SIGNAL(clicked()), discountTab, SLOT(editRowData()));
//    connect(btnDiscountDelete, SIGNAL(clicked()), discountTab, SLOT(deleteRowData()));

}

//void settingsDialog::selectImpExpDir()
//{
//    QString path = QFileDialog::getExistingDirectory(editPath->text(), this, "dlgImportExportDirectory",  tr("Choose directory for import/export"));
//    if(!path.isEmpty()) editPath->setText(path);
//}

//void settingsDialog::selectBill()
//{
//    QString filename = QFileDialog::getOpenFileName(editBill->text(), tr("Templates *.tpl;;All files *"), this, "dlgSelectBill", tr("Select bill template"));
//    if(!filename.isEmpty()) editBill->setText(filename);
//}

//void settingsDialog::selectOrder()
//{
//    QString filename = QFileDialog::getOpenFileName(editOrder->text(), tr("Templates *.tpl;;All files *"), this, "dlgSelectOrder", tr("Select order template"));
//    if(!filename.isEmpty()) editOrder->setText(filename);
//}
