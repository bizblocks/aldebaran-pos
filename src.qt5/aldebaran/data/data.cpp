#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QException>
#include "data.h"
#include "engine.h"

alData::alData(alEngine * e, QString table) :
    QSqlTableModel(e, e->db()),
    fParent(e),
    fCurrent(NULL),
    fCurrentRow(-1)
{
    setTable(table);
}

alData::alData(const alData & other) :
    QSqlTableModel(fParent, other.database())
{
    setTable(other.tableName());
}

alData::~alData()
{
}

bool alData::checkTable(const QString& tname)
{
    if(!engine()->db().isOpen())
        throw new QException();
    QStringList check = engine()->db().tables();
    if(check.contains(tname))
        return true;
    return false;
}

ULLID alData::uid()
{
    if(engine()->db().isOpen())
        return 0;
    ULLID uid = 0;
    QString query = QString(Queries::tr("SELECT MAX(id) as max_id from %1")).arg(tableName());
    QSqlQuery q = engine()->db().exec(query);
    if(q.first())
        uid = q.value(0).toULongLong();
    return uid+1;
}

alDataRecord* alData::current()
{
    return alDataRecord::current(this);
}

bool alData::first()
{
    fCurrentRow = -1;
    if(hasIndex(0, 0))
    {
        fCurrentRow = 0;
        return true;
    }
    return false;
}

bool alData::next()
{
    if(fCurrentRow<0)
        return false;
    if(hasIndex(fCurrentRow+1, 0))
    {
        fCurrentRow++;
        return true;
    }
    return false;
}

bool alData::seek(int row)
{
    if(hasIndex(row, 0))
    {
        fCurrentRow = row;
        return true;
    }
    return false;
}

//TODO implement
//int alData::update (ULLID id, bool invalidate )
int alData::update()
{
    if(!fCurrent)
        return 0;
    return setRecord(fCurrentRow, *fCurrent);
}

//TODO implement
QSqlIndex alData::defaultSort()
{
//    return QSqlIndex::fromStringList(QStringList::split(",", "id"), this);
    QSqlIndex res;
    //res.append();
    return res;
}

//TODO reimplement with sort
bool alData::select(const QString filter)
{
    setFilter(filter);
    return QSqlTableModel::select(); /*, defaultSort()*/
}

QSqlRecord * alData::primeInsert()
{
    if(fCurrent)
        delete fCurrent;
    fCurrent = new QSqlRecord(record());
    fCurrentRow = QSql::AfterLastRow;
    return fCurrent;
}

QSqlRecord * alData::primeUpdate()
{
    return fCurrent;
}

bool alData::insert()
{
    if(!fCurrent)
        return false;
    fCurrentRow = rowCount();
    if(insertRow(fCurrentRow))
         return setRecord(fCurrentRow, *fCurrent);
    return false;
}

QVariant alData::value(const QString &fld)
{
    int column = record().indexOf(fld);
    if(column<0)
        return QVariant();
    return data(index(fCurrentRow, column));
}

alDataRecord::alDataRecord(alData * data) :
    QObject()
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
    if(!fRecord)
        return;
    fId = fRecord->value("id").toULongLong();    
}

alDataRecord * alDataRecord::current(alData * data)
{
    if(!data)
        return NULL;
    alDataRecord * res = new alDataRecord(data);
    return res;
}

//TODO rewrite
int alDataRecord::update()
{
    if(isNew())
    {
        fIsNew = FALSE;
        return fData->insert();
    }
    else
        return fData->update();
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
