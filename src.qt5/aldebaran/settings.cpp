#include <qdir.h>
#include "settings.h"
#include "ui_ddbsettings.h"
#include "ui_settingsdialog.h"
#include "data/datasettings.h"

alSettings::alSettings(alEngine * e) : 
	QObject()
{
	fEngine = e;
	if(fEngine) connect(fEngine, SIGNAL(initialized()), this, SLOT(subSystemSettings()));
	init();
}

alSettings::~alSettings()
{
}

/*
Инициализация настроек
	- Настройки базы данных, не настроена - сообщить, запросить
TODO	- Поиск таблицы в базе данных, создание при отсутствии
*/
void alSettings::init()
{
	bool nodb = FALSE;
	bool ok;
	QString value;	
	dbParams.clear();
	QSettings qtSettings;	    
    //qtSettings.insertSearchPath(QSettings::Unix, QString(QDir::homeDirPath())+QString("/.aldebaran"));
	qtSettings.beginGroup("/connection");

    value = qtSettings.value("/TYPE", "nodb").toString();
    if(value=="nodb") nodb = TRUE;
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

	if(nodb) dbDialog();
	
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
    QStringList data;
    QDialog dlg;
    Ui::ddbsettings dlgui;//(0, "dbsettingsdlg", true);
    dlgui.setupUi(&dlg);
    //dlgui.setData(dbParams);
    int res = dlg.exec();
#ifdef DEBUG
    qDebug(QString(tr("ddbsettings dialog returns %1")).arg(res).utf8());
#endif
    if(res)
    {
//        dbParams = dlg->getData();
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
//    QSettings qtSettings;
//    qtSettings.insertSearchPath(QSettings::Unix, QString(QDir::homeDirPath())+QString("/.aldebaran"));
//    qtSettings.beginGroup("/connection");
    
//    qtSettings.writeEntry("/TYPE", dbParams[0]);
//    qtSettings.writeEntry("/DB", dbParams[1]);
//    qtSettings.writeEntry("/ADRESS", dbParams[2]);
//    qtSettings.writeEntry("/PORT", dbParams[3]);
//    qtSettings.writeEntry("/USER", dbParams[4]);
//    qtSettings.writeEntry("/PASSWORD", dbParams[5]);
    
//    qtSettings.endGroup();
}

/*
*/
//TODO uncomment
void alSettings::flushsql()
{
    if(!fEngine->db().isOpen())
        return;
//    fEngine->startTransaction();
//    alDataSettings * t = new alDataSettings(fEngine);
//    for(int s=0;s<(int)subSystems.count();s++)
//	for(int v=0;v<(int)keys[subSystems[s]].count();v++)
//	    t->save(subSystems[s], keys[subSystems[s]][v], params[subSystems[s]][keys[subSystems[s]][v]]);
//    fEngine->commitTransaction();
//    delete t;
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
