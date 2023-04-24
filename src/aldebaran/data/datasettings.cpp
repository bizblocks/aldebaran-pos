#include <QtSql/QSqlDatabase>
#include <qobject.h>
#include "datasettings.h"
#include "engine.h"

#define TNAME "settings"

alDataSettings::alDataSettings(alEngine * e) :
    alData(e, TNAME)
{
    checkTable();
    setName(TNAME, TRUE);
}

void alDataSettings::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME, false).size()>0)
        return;
    QString query = Queries::tr("create_settings");
    qDebug(query);
    fEngine->db()->exec(query);
    query = Queries::tr("create_settings_idx_subsys");
    fEngine->db()->exec(query);
    query = Queries::tr("create_settings_idx_name");
    fEngine->db()->exec(query);
    query = Queries::tr("create_settings_idx_settings");
    fEngine->db()->exec(query);
}

void alDataSettings::save(QString subsystem, QString key, QVariant val)
{
    Q_ULLONG id = 0;
    QSqlRecord * rec;
    select(Queries::tr("subsystem='%1' AND valkey='%2'").arg(subsystem).arg(key));
    if(!first())
    {
        rec = primeInsert();
        id = uid();
        rec->setValue("id", id);
        rec->setValue("value", 0);
        if(insert())
        {
            select(Queries::tr("id=%1").arg(id));
            if(!first()) return;
        }
        else return;
    }
    else id = value("id").toULongLong();
    
    rec = primeUpdate();
    rec->setValue("subsystem", subsystem);
    rec->setValue("valkey", key);
    QByteArray bytea = val.toByteArray();
    rec->setValue("value", bytea);
    update(id);
}
