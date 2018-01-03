#include <qdir.h>
#include <QMessageBox>
#include <QDebug>
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

//TODO reimplement
bool alSettings::dbDialog()
{    
    QDialog dlg;
    dbdlg = new Ui::ddbsettings();//(0, "dbsettingsdlg", true);
    dbdlg->setupUi(&dlg);
    connect(dbdlg->btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTest_clicked()));
    this->setData(dbParams);
    int res = dlg.exec();
#ifdef DEBUG
    qDebug(QString(tr("ddbsettings dialog returns %1")).arg(res).toUtf8());
#endif
    if(res)
    {
        dbParams = this->getData();
        flushqt();
    }
    return res;
}

bool alSettings::dialog()
{    
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

void alSettings::setData( QStringList data )
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

QStringList alSettings::getData()
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

void alSettings::on_pushButton_clicked()
{
    QMessageBox::information(NULL, "aldebaran", QObject::tr("Successfully connected"));
}
