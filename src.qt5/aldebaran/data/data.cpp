//correct one
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QException>
#include "data.h"
#include "engine.h"

alData::alData(alEngine * e, QString table) :
    alSqlTableModel(e, e->db(), table),
    fParent(e),
    fCurrentRow(-1),
    fRecord(NULL)
{
}

alData::alData(const alData & other) :
    alSqlTableModel((alEngine*)fParent, other.database(), other.tableName())
{
}

alData::~alData()
{
    if(fRecord)
        delete fRecord;
}

bool alData::checkTable(const QString& tname)
{
    if(!engine()->db().isOpen())
        throw new QException();
    QStringList check = engine()->db().tables();
    if(check.contains(tname, Qt::CaseInsensitive	))
        return true;
    return false;
}

ULLID alData::uid()
{
    if(!engine()->db().isOpen())
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
    if(rowCount()>0)
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
    if(!fRecord)
        return 0;
    return setRecord(fCurrentRow, *fRecord);
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
#ifdef DEBUG
    qDebug() << selectStatement();
#endif
    return QSqlTableModel::select(); /*, defaultSort()*/
}

QSqlRecord * alData::primeInsert()
{
    fCurrentRow = QSql::AfterLastRow;
    if(fRecord)
        delete fRecord;
    fRecord = new QSqlRecord(QSqlTableModel::record());
    return fRecord;
}

QSqlRecord * alData::primeUpdate()
{
    if(fRecord)
        delete fRecord;
    fRecord = new QSqlRecord(record(fCurrentRow));
    return fRecord;
}

bool alData::insert()
{
    if(!fRecord)
        return false;
    if(insertRecord(fCurrentRow, *fRecord))
    {
        return submit();
    }
    return false;
}

QVariant alData::value(const QString &fld)
{
    int column = QSqlTableModel::record().indexOf(fld);
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

alDataRecord::alDataRecord(alData * data, QSqlRecord * rec) :
    QObject()
{
    fIsNew = FALSE;    
    fData = data;
    fRecord = new QSqlRecord(*rec);
}

alDataRecord::~alDataRecord()
{
    if(fRecord)
        delete fRecord;
}

void alDataRecord::load()
{
    if(!fRecord)
        return;
    fId = fRecord->value("id").toULongLong();    
}

alDataRecord * alDataRecord::current(alData*)
{
    return NULL;
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

void alDataRecord::primeUpdateInsert()
{
    if(isNew())
        fRecord = fData->primeInsert();
    else
        fRecord = fData->primeUpdate();
    fRecord->setValue("id", fId);
}
