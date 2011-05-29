#include <qsqldatabase.h>
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
    if(check.grep(TNAME).size()>0) return;
    QString query = Queries::tr("CREATE TABLE settings ("
		    "id int8 NOT NULL, subsystem varchar(20), valkey varchar(20), value bytea,"
		    "CONSTRAINT id_settings PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    fEngine->db()->exec(query);
    query = Queries::tr("CREATE INDEX idx_subsys ON settings (subsystem);");
    fEngine->db()->exec(query);
    query = Queries::tr("CREATE INDEX idx_name ON settings (valkey);");
    fEngine->db()->exec(query);
    query = Queries::tr("CREATE INDEX idx_setting ON settings (subsystem, valkey);");
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
