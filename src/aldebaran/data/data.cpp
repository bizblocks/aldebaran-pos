#include <QtSql/QSqlDatabase>
#include <QtGui/QMessageBox>
#include "data.h"
#include "engine.h"

alData::alData(alEngine * e, QString table) :
    Q3SqlCursor(table, FALSE, *e->db())
{
    fTableName = table;
    fEngine = e;
}

alData::alData(const alData & other) :
    Q3SqlCursor(other)
{
    fTableName = other.fTableName;
    fEngine = other.fEngine;
}

alData::~alData()
{
    
}

Q_ULLONG alData::uid()
{
    if(!fEngine->db()) return 0;
    Q_ULLONG uid = 0;
    QString query = QString(Queries::tr("SELECT MAX(id) as max_id from %1")).arg(fTableName);
    QSqlQuery q = fEngine->db()->exec( query );
    if(q.first()) uid = q.value(0).toULongLong();
    return uid+1;
}

alDataRecord* alData::current()
{
    return alDataRecord::current(this);
}

int alData::update (Q_ULLONG id, bool invalidate )
{
    if(!id) return 0;
    return Q3SqlCursor::update(Queries::tr("id=%1").arg(id), invalidate);
}

QSqlIndex alData::defaultSort()
{
    return this->index(QStringList::split(",", "id"));
}

bool alData::select(const QString filter)
{
    return Q3SqlCursor::select(filter, defaultSort());
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

int alDataRecord::update()
{
    if(isNew())
    {
	fIsNew = FALSE;
	return fData->insert(); 
    }
    else return fData->update(fId, false);
    return 0;
}

bool alDataRecord::dialog(QWidget * parent)
{
    return QMessageBox::information(parent, "aldebaran", tr("Abstract data record dialog"));
}

void alDataRecord::primeUpdateInsert()
{
    if(isNew()) fRecord = fData->primeInsert();
    else fRecord = fData->primeUpdate();
    fRecord->setValue("id", fId);    
}
