#include <qdir.h>
#include "settings.h"
#include "ui_ddbsettings.h"
#include "ui_settingsdialog.h"
#include "data/datasettings.h"
#include "settingsdialog.ui.h"
#include "ddbsettings.ui.h"

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
    qtSettings.insertSearchPath(QSettings::Unix, QString(QDir::homeDirPath())+QString("/.aldebaran"));
    qtSettings.beginGroup("/connection");

    value = qtSettings.readEntry("/TYPE", "", &ok);
    if(!ok) nodb = TRUE;
    dbParams.append(value);

    value = qtSettings.readEntry("/DB", "", &ok);
    if(!ok) nodb = TRUE;
    dbParams.append(value);

    value = qtSettings.readEntry("/ADRESS", "127.0.0.1", &ok);
    if(!ok) nodb = TRUE;
    dbParams.append(value);

    value = qtSettings.readEntry("/PORT", "", &ok);
    if(!ok) nodb = TRUE;
    dbParams.append(value);

    value = qtSettings.readEntry("/USER", "", &ok);
    dbParams.append(value);

    value = qtSettings.readEntry("/PASSWORD", "", &ok);
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

bool alSettings::dbDialog()
{
    QStringList data;
    ddbsettings * dlg = new ddbsettings(0, "dbsettingsdlg", true);
    dlg->setData(dbParams);
    int res = dlg->exec();
    alDBG(QString(tr("ddbsettings dialog returns %1")).arg(res).utf8());
    if(res)
    {
        dbParams = dlg->getData();
        flushqt();
    }
    return res;
}

bool alSettings::dialog()
{
    settingsDialog * dlg = new settingsDialog(NULL);
    dlg->init(fEngine);
    dlg->setData(params);
    int res = dlg->exec();
    alDBG(QString(tr("settings dialog returns %1")).arg(res).utf8());
    if(res)
        params = dlg->getData();
    return res;
}

QStringList alSettings::dbSettings()
{
    return dbParams;
}

void alSettings::flushqt()
{
    QSettings qtSettings;
    qtSettings.insertSearchPath(QSettings::Unix, QString(QDir::homeDirPath())+QString("/.aldebaran"));
    qtSettings.beginGroup("/connection");
    
    qtSettings.writeEntry("/TYPE", dbParams[0]);
    qtSettings.writeEntry("/DB", dbParams[1]);
    qtSettings.writeEntry("/ADRESS", dbParams[2]);
    qtSettings.writeEntry("/PORT", dbParams[3]);
    qtSettings.writeEntry("/USER", dbParams[4]);
    qtSettings.writeEntry("/PASSWORD", dbParams[5]);
    
    qtSettings.endGroup();
}

/*
*/
void alSettings::flushsql()
{
    if(!fEngine->db())
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
    
    if(subSystem.isEmpty())
        subSystem = "%%";
    
    alDataSettings * t = new alDataSettings(fEngine);
    t->select(QString("subsystem LIKE '%1'").arg(subSystem));
    if(t->first()) do
    {
        params[t->value("subsystem").toString()][t->value("valkey").toString()] = t->value("value");
        res[t->value("valkey").toString()] = t->value("value");
    } while(t->next());

    delete t;
    return res;
}


QVariant alSettings::parameter(QString sub, QString key)
{
    return params[sub][key];
}
