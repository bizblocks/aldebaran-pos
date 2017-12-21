#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QException>
#include "data.h"
#include "engine.h"

alData::alData(alEngine * e, QString table) :
    QSqlQuery(table, e->db())
{
    fTableName = table;
    fEngine = e;
}

alData::alData(const alData & other) :
    QSqlQuery(other)
{
    fTableName = other.fTableName;
    fEngine = other.fEngine;
}

alData::~alData()
{
    
}

bool alData::checkTable(const QString& tname)
{
    if(!fEngine->db().isOpen())
        throw new QException();
    QStringList check = fEngine->db().tables();
    if(check.contains(tname))
        return true;
    return false;
}

ULLID alData::uid()
{
    if(fEngine->db().isOpen())
        return 0;
    ULLID uid = 0;
    QString query = QString(Queries::tr("SELECT MAX(id) as max_id from %1")).arg(fTableName);
    QSqlQuery q = fEngine->db().exec( query );
    if(q.first()) uid = q.value(0).toULongLong();
    return uid+1;
}

alDataRecord* alData::current()
{
    return alDataRecord::current(this);
}

//TODO uncomment
int alData::update (ULLID id, bool invalidate )
{
//    if(!id)
//        return 0;
//    return QSqlQuery::update(Queries::tr("id=%1").arg(id), invalidate);
    return 0;
}

//TODO implement
QSqlIndex alData::defaultSort()
{
//    return QSqlIndex::fromStringList(QStringList::split(",", "id"), this);
}

//TODO implement
bool alData::select(const QString filter)
{
    //return QSqlQuery::select(filter, defaultSort());
}

alDataRecord::alDataRecord(alData * data) : QObject()
{
    fIsNew = FALSE;
    fData = data;
    fRecord = NULL;    
    fId = data->value("id").toULongLong();
}

alDataRecord::alDataRecord(alData * data, QSqlRecord * rec) : QObject()
{
    fIsNew = FALSE;    
    fData = data;
    fRecord = rec;
    load();
}

void alDataRecord::load()
{
    if(!fRecord) return;
    fId = fRecord->value("id").toULongLong();    
}

alDataRecord * alDataRecord::current(alData * data)
{
    if(!data) return NULL;
    alDataRecord * res = new alDataRecord(data);
    return res;
}

//TODO rewrite
int alDataRecord::update()
{
    if(isNew())
    {
        fIsNew = FALSE;
        //return fData->insert();
    }
    else
        return fData->update(fId, false);
    return 0;
}

bool alDataRecord::dialog(QWidget * parent)
{
    return QMessageBox::information(parent, "aldebaran", tr("Abstract data record dialog"));
}

//TODO implement
void alDataRecord::primeUpdateInsert()
{
//    if(isNew())
//        fRecord = fData->primeInsert();
//    else
//        fRecord = fData->primeUpdate();
//    fRecord->setValue("id", fId);
}
