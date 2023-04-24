#include <QtSql/QSqlDatabase>
#include <qbuffer.h>
#include "datapictures.h"
#include "engine.h"

#define TNAME "pictures"

alDataPictures::alDataPictures(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    alData::setName(TNAME, TRUE);    
}

void alDataPictures::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME).size()>0 || !check.count()) return;
#ifdef DEBUG    
    qDebug(QObject::tr("creating table pictures").utf8());
#endif    
    QString query = Queries::tr("CREATE TABLE pictures ("
		    "id int8 NOT NULL, picture bytea,"
		    "CONSTRAINT id_pictures PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    fEngine->db()->exec(query);
#ifdef DEBUG    
    qDebug(QObject::tr("lastError was %1").arg(fEngine->db()->lastError().text()).utf8());
#endif        
}

alDataRecord* alDataPictures::current()
{
    return alPictureRecord::current(this);
}

alPictureRecord * alDataPictures::newElement()
{
    return alPictureRecord::newElement(this);
}

alPictureRecord * alDataPictures::select(Q_ULLONG uid)
{
    alData::select(Queries::tr("id=%1").arg(uid));
    if(first()) return (alPictureRecord*)current();
    return NULL;    
}

bool alDataPictures::select(const QString filter)
{
    return alData::select(filter);
}

bool alDataPictures::delElement()
{
    Q_ULLONG id = value("id").toULongLong();
    QString query = Queries::tr("DELETE FROM pictures WHERE id=%1").arg(id);
    fEngine->db()->exec(query);
    return true;
}

alPictureRecord::alPictureRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    if(!fRecord) return;
    load();
}

alPictureRecord * alPictureRecord::current(alDataPictures * data)
{
    if(!data) return NULL;    
    return new alPictureRecord(data, data->primeUpdate());    
}

alPictureRecord * alPictureRecord::newElement(alDataPictures * data)
{
    if(!data) return NULL;
    QSqlRecord * rec = data->primeInsert();
    rec->setValue("id", data->uid());
    alPictureRecord * res = new alPictureRecord(data, rec);
    res->fIsNew = TRUE;
    return res;        
}

void alPictureRecord::load()
{
    alDataRecord::load();
    fPicture = bytearray2pixmap(fRecord->value("picture").toByteArray());
}

int alPictureRecord::update() 
{
    primeUpdateInsert();
    fRecord->setValue("picture", pixmap2bytearray(fPicture));
    return alDataRecord::update();
}
