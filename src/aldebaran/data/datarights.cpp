#include <QtSql/QSqlDatabase>
#include "engine.h"

#define TNAME "rights"

alDataRights::alDataRights(alEngine * e) :
    alData(e, TNAME)
{
    checkTable();
    alData::setName(TNAME, TRUE);
}

alDataRights::~alDataRights()
{
}

void alDataRights::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME, false).size()>0)
        return;
    alDBG(QObject::tr("creating table rights").utf8());
    QString query = Queries::tr("create_rights");
    fEngine->db()->exec(query);
    alDBG(QObject::tr("lastError was %1").arg(fEngine->db()->lastError().text()).utf8());
    query = Queries::tr("CREATE INDEX idx_owner ON RIGHTS (id_onwer);");
    fEngine->db()->exec(query);
}

alDataRecord * alDataRights::current()
{
    return alRightsRecord::current(this);
}

alRightsRecord * alDataRights::select(Q_ULLONG uid)
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
    fEngine->startTransaction();
    for(int r=1;r<rEnd;r++)
    {
        alRightsRecord * rec = alRightsRecord::newElement(this);
        rec->setOwner(u);
        rec->setRule(r);
        rec->setEnabled(rDefaultSets[u->role()-1][r]);
        rec->update();
    }
    fEngine->commitTransaction();
}

alRightsRecord::alRightsRecord(alData * data) :
    alDataRecord(data)
{
    fData = new alDataGoods(data->engine());
    fData->select(Queries::tr("id=%1").arg(fId));
    fRecord = fData->primeUpdate();
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
    if(!data) return NULL;
    QSqlRecord * rec = data->primeInsert();
    rec->setValue("id", data->uid());
    alRightsRecord * res = new alRightsRecord(data, rec);
    res->fIsNew = TRUE;
    return res;
}

alRightsRecord * alRightsRecord::current(alDataRights * data)
{
    if(!data) return NULL;
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
