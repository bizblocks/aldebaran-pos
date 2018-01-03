#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include "engine.h"

#define TNAME "rights"

alDataRights::alDataRights(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
//    alData::setName(TNAME, TRUE);
}

alDataRights::~alDataRights()
{
}

bool alDataRights::checkTable()
{
    if(alData::checkTable(TNAME))
        return true;
#ifdef DEBUG    
    qDebug() << QObject::tr("creating table rights").toUtf8();
#endif    
    QString query = Queries::tr("CREATE TABLE RIGHTS ("
		    "id int8 NOT NULL, id_owner int8 NOT NULL,"
		    "rule int4, enabled bool,"
		    "CONSTRAINT id_rights PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
#ifdef DEBUG    
    qDebug() << QObject::tr("lastError was %1").arg(engine()->db().lastError().text()).toUtf8();
#endif        
    query = Queries::tr("CREATE INDEX idx_owner ON RIGHTS (id_owner);");
    engine()->db().exec(query);
#ifdef DEBUG
    qDebug() << QObject::tr("lastError was %1").arg(engine()->db().lastError().text()).toUtf8();
#endif
}

alDataRecord * alDataRights::current()
{
    return alRightsRecord::current(this);    
}
    
alRightsRecord * alDataRights::select(ULLID uid)
{
    alData::select(Queries::tr("id=%1").arg(uid));
    if(first()) return (alRightsRecord*)current();
    return NULL;
}

bool alDataRights::selectByOwner(alUserRecord * user)
{
    return alData::select(Queries::tr("id_owner=%1").arg(user->id()));
}

void alDataRights::createSetForUser(alUserRecord * u)
{
    engine()->startTransaction();
    for(int r=1;r<rEnd;r++)
    {
        alRightsRecord * rec = alRightsRecord::newElement(this);
        rec->setOwner(u);
        rec->setRule(r);
        rec->setEnabled(rDefaultSets[u->role()-1][r]);
        rec->update();
    }
    engine()->commitTransaction();
}

alRightsRecord::alRightsRecord(alData * data) :
	alDataRecord(data)
{
    fData = new alDataGoods(data->engine());
    fData->select(Queries::tr("id=%1").arg(fId));
//    fRecord = fData->primeUpdate();
    load();
}

alRightsRecord::alRightsRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    if(!fRecord) return;
    load();
}

alRightsRecord * alRightsRecord::newElement(alDataRights * data)
{
    if(!data)
        return NULL;
    QSqlRecord * rec = data->primeInsert();
    rec->setValue("id", data->uid());
    alRightsRecord * res = new alRightsRecord(data, rec);
    res->fIsNew = TRUE;
    return res;
}

alRightsRecord * alRightsRecord::current(alDataRights * data)
{
    if(!data)
        return NULL;
    return new alRightsRecord(data, data->primeUpdate());
}

void alRightsRecord::load()
{    
    fOwnerId = fRecord->value("id_owner").toULongLong(); 
    fOwner = NULL;
    fRule = fRecord->value("rule").toInt();
    fEnabled = fRecord->value("enabled").toBool();    
}

int alRightsRecord::update() 
{
    primeUpdateInsert();
    if(fOwner) fRecord->setValue("id_owner", fOwner->id());
    fRecord->setValue("rule", fRule);
    fRecord->setValue("enabled", fEnabled);
    return alDataRecord::update();
}

void alRightsRecord::setOwner(alDataRecord * o)
{
    fOwner = o;    
}

alDataRecord * alRightsRecord::owner()
{
    if(!fOwner) fOwner= alDataUsers(fData->engine()).select(fOwnerId);    
    return fOwner; 
}
