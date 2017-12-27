#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <qobject.h>
#include "datasettings.h"
#include "engine.h"

#define TNAME "settings"

alDataSettings::alDataSettings(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
//    setName(TNAME, TRUE);
}

bool alDataSettings::checkTable()
{
    if(alData::checkTable(TNAME))
        return true;
    QString query = Queries::tr("CREATE TABLE settings ("
		    "id int8 NOT NULL, subsystem varchar(20), valkey varchar(20), value bytea,"
		    "CONSTRAINT id_settings PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
    query = Queries::tr("CREATE INDEX idx_subsys ON settings (subsystem);");
    engine()->db().exec(query);
    query = Queries::tr("CREATE INDEX idx_name ON settings (valkey);");
    engine()->db().exec(query);
    query = Queries::tr("CREATE INDEX idx_setting ON settings (subsystem, valkey);");
    engine()->db().exec(query);
}

void alDataSettings::save(QString subsystem, QString key, QVariant val)
{
    ULLID id = 0;
    QSqlRecord * rec;
    select(Queries::tr("subsystem='%1' AND valkey='%2'").arg(subsystem).arg(key));
    bool existed = first();
    if(!existed)
    {
        rec = primeInsert();
        id = uid();
        rec->setValue("id", id);
    }
    else
    {
        rec = primeUpdate();
        id = value("id").toULongLong();
    }    

    rec->setValue("subsystem", subsystem);
    rec->setValue("valkey", key);
    QByteArray bytea = val.toByteArray();
    rec->setValue("value", bytea);    
}
