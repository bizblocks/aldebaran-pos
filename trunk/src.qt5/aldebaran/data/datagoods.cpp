#include <qobject.h>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include "datagoods.h"
#include "engine.h"

#define TNAME "goods"

alDataGoods::alDataGoods(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    //alData::setName(TNAME, TRUE);
}

bool alDataGoods::checkTable()
{
    if(alData::checkTable(TNAME))
        return true;
#ifdef DEBUG    
    qDebug() << QObject::tr("creating table goods").toUtf8();
#endif    
    QString query = Queries::tr("CREATE TABLE goods ("
		    "id int8 NOT NULL, parent int8, isgroup bool DEFAULT false,"
		    "name varchar(200), price numeric(12,2), maxdiscount int2 DEFAULT 100, description bytea,"
		    "externalcode varchar(15), barcode varchar(13), id_pictures int8,"
		    "hydrocarbonat numeric(6,3), fat numeric(6,3), protein numeric(6,3), calories numeric(7,3),"
		    "outofstore bool DEFAULT false,"
		    "eqexport bool DEFAULT true,"
		    "CONSTRAINT id_goods PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
#ifdef DEBUG    
    qDebug() << QObject::tr("lastError was %1").arg(lastError().text()).toUtf8();
#endif        
    query = Queries::tr("CREATE INDEX idx_parent ON goods (parent);"); 
    engine()->db().exec(query);
    query = Queries::tr("CREATE INDEX idx_name ON goods (name);");
    engine()->db().exec(query);
    query = Queries::tr("CREATE INDEX idx_extcode ON goods (extrnalcode);");
    engine()->db().exec(query);
// do not use UNIQUE due '' barcode    
    query = Queries::tr("CREATE INDEX idx_barcode ON goods USING btree (barcode);");
    engine()->db().exec(query);
}

void alDataGoods::exportpictures()
{
    select(Queries::tr("isgroup='f'"), defaultSort());
    engine()->startTransaction();
    if(first()) do
    {
        alGoodsRecord * rec = (alGoodsRecord *)current();
        qDebug()<< QString("converting %1").arg(rec->id());
        rec->update();
    } while(next());
    engine()->commitTransaction();
}

alGoodsRecord * alDataGoods::select(int uid)
{
    alData::select(Queries::tr("id=%1").arg(uid));
    if(first()) return (alGoodsRecord*)current();
    return NULL;
}

alDataRecord* alDataGoods::current()
{
    return alGoodsRecord::current(this);
}

//TODO reimplement
bool alDataGoods::select(const QString & filter, const QSqlIndex & sort)
{
    //QStringList lst = sort.toStringList();
    //lst.prepend("goods.isgroup DESC");
    //QSqlIndex idx =QSqlIndex::fromStringList(lst, this);
    //return QSqlCursor::select(filter, idx);
    return false;
}

//TODO reimplement
QSqlIndex alDataGoods::defaultSort()
{
    //return QSqlIndex::fromStringList(QStringList::split(",", "isgroup DESC, name"), this);
}

alGoodsRecord * alDataGoods::internalNew(alGoodsRecord * parent, bool group)
{
    alGoodsRecord * rec = NULL;
    if(group)  rec = alGoodsRecord::newGroup(this, parent);	
    else rec = alGoodsRecord::newElement(this, parent);
    return rec;
}

alGoodsRecord * alDataGoods::newElement(alGoodsRecord * parent)
{
    return internalNew(parent, FALSE);
}

alGoodsRecord * alDataGoods::newGroup(alGoodsRecord * parent)
{
    return internalNew(parent, TRUE);
}

bool alDataGoods::delGroup()
{
    if(!value("isgroup").toBool())
	return false;
    ULLID id = value("id").toULongLong();
    delElement();
    QString query = Queries::tr("DELETE FROM goods WHERE parent=%1").arg(id);
    engine()->db().exec(query);
    return true;
}

bool alDataGoods::delElement()
{
    ULLID id = value("id").toULongLong();
    QString query = Queries::tr("DELETE FROM goods WHERE id=%1").arg(id);
    engine()->db().exec(query);
    return true;    
}


//TODO reimplement
void alDataGoods::update(impValues * values)
{
//    alGoodsRecord * rec;
//    impValues::iterator it;
//    map map;
    
//    QMap<QString, alGoodsRecord *> groups;
//    select(Queries::tr("isgroup=true"));
//    if(first()) do
//    {
//    	groups[value("externalcode").toString()] = (alGoodsRecord*)current();
//    } while(next());
//    select("");
////first variant high-level
//    engine()->startTransaction();
    
//    if(first()) do
//    {
//        it = values->find(value("externalcode").toString());
//        if(it==values->end())
//            continue;
//        rec = (alGoodsRecord*)current();
//        map = *it;
//        update(map, rec);
//        values->remove(it);
//    }while(next());

//    engine()->commitTransaction();
//    engine()->startTransaction();
    
//    for(it=values->begin();it!=values->end();it++)
//    {
//	map = *it;
//	if(map["externalcode"].toString().isEmpty()) continue;
//	if(!map["isgroup"].toInt()) continue;
//	alGoodsRecord * parent = groups[map["parentcode"].toString()];
//	rec = newGroup(parent);
//	update(map, rec);
//	if(rec->isGroup()) groups[rec->externalCode()] = rec;
//    }
    
//    engine()->commitTransaction();
//    engine()->startTransaction();
    
//    for(it=values->begin();it!=values->end();it++)
//    {
//	map = *it;
//	if(map["externalcode"].toString().isEmpty()) continue;
//	if(map["isgroup"].toInt()) continue;
//	alGoodsRecord * parent = groups[map["parentcode"].toString()];
//	rec = newElement(parent);
//	update(map, rec);
//    }
    
//    engine()->commitTransaction();
////second variant low-level
}

void alDataGoods::update(map map, alGoodsRecord * rec)
{
    if(!rec) return;
    if(map["isgroup"].toInt())
    {
	rec->setName(map["name"].toString());
	rec->setPrice(0.0);
	rec->setExternalCode(map["externalcode"].toString());
    }
    else
    {
	rec->setName(map["name"].toString());
	rec->setPrice(map["price"].toDouble());
	rec->setExternalCode(map["externalcode"].toString());
	rec->setHydroCarbonat(map["hydrocarbonat"].toDouble());
	rec->setFat(map["fat"].toDouble());
	rec->setProtein(map["protein"].toDouble());
	rec->setCalories(map["calories"].toDouble());
    rec->setBarcode(map["barcode"].toString().trimmed());
	rec->setMaxDiscount(map["maxdiscount"].toInt());
	QString description = map["description"].toString();
	if(!description.isEmpty()) rec->setDescription(description);
	QString fileName = map["picturename"].toString();
	if(!fileName.isEmpty())
	{
        QString path = QString(engine()->parameter(GENERAL, IMPEXPPATH).toString());
	    if(path.right(1)!="/") path += "/";	    
	    fileName = path + fileName;
	    QPixmap pix(fileName);
	    rec->setPicture(pix);
	}	
    }
    rec->update();    
}

void alDataGoods::import(importer * imp)
{	
    impValues values;
    for(int lineNum=0;lineNum<imp->count();lineNum++)
    {
	imp->seek(lineNum);
	values[imp->value("externalcode").toString()] = imp->toMap();
    }        
    update(&values);
}

//TODO reimplement
alGoodsRecord::alGoodsRecord(alData * data) :
	alDataRecord(data)
{
    fData->select(QString("id=%1").arg(fId));
    //fRecord = fData->primeUpdate();
    load();
}

alGoodsRecord::alGoodsRecord(alData * data, QSqlRecord * rec) : 
	alDataRecord(data, rec)
{
    fParent = NULL;
    if(!fRecord) return;
    load();
}

//TODO reimplement
alGoodsRecord * alGoodsRecord::current(alDataGoods * data)
{
    if(!data) return NULL;    
    //return new alGoodsRecord(data, data->primeUpdate());
    return NULL;
}

//TODO reimplement
alGoodsRecord * alGoodsRecord::internalNew(alDataGoods * data, alGoodsRecord * parent, bool isgroup)
{
//    QSqlRecord * rec = data->primeInsert();
//    alGoodsRecord * res = new alGoodsRecord(data, rec);
//    res->fParent = parent;
//    res->fId = data->uid();
//    res->fIsGroup = isgroup;
//    res->fIsNew = TRUE;
//    return res;
    return NULL;
}

alGoodsRecord * alGoodsRecord::newElement(alDataGoods * data, alGoodsRecord * parent)
{
    return internalNew(data, parent, false);
}

alGoodsRecord * alGoodsRecord::newGroup(alDataGoods * data, alGoodsRecord * parent)
{
    return internalNew(data, parent, true);
}

int alGoodsRecord::update()
{
    QPixmap pix = picture();    
    alDataPictures * pics = new alDataPictures(fData->engine());
    if(!fPictureId) fPictureRec = pics->newElement();
    else fPictureRec = pics->select(fPictureId);
    fPictureRec->setPicture(pix);
    int ok = fPictureRec->update();
    
    primeUpdateInsert();
    fRecord->setValue("parent", (!fParent ? 0 : fParent->id()));
    fRecord->setValue("isgroup", fIsGroup);
    fRecord->setValue("name", fName);
    fRecord->setValue("price", fPrice);
    fRecord->setValue("externalcode", fExternalCode);    
    fRecord->setValue("description", fDescription.toUtf8());
    fRecord->setValue("hydrocarbonat", fHydroCarbonat);
    fRecord->setValue("fat", fFat);    
    fRecord->setValue("protein", fProtein);
    fRecord->setValue("calories", fCalories);
    fRecord->setValue("outofstore", fOutOfStore ? "TRUE" : "FALSE");
    fRecord->setValue("eqexport", fEqExport ? "TRUE" : "FALSE");    
    fRecord->setValue("barcode", fBarcode);
    fRecord->setValue("maxdiscount", fMaxDiscount);       
    fRecord->setValue("id_pictures", fPictureRec ? fPictureRec->id() : 0);    
    ok &= alDataRecord::update();
//    qDebug(fData->lastQuery().utf8());
//    qDebug(fData->lastError().text().utf8());
    return ok;
}

void alGoodsRecord::load()
{
    alDataRecord::load();
    fIsNew = FALSE;    
    fIsGroup = fRecord->value("isgroup").toBool();
    fName = fRecord->value("name").toString();
    fParent = NULL;    
    if(fRecord->value("parent").toULongLong() && fRecord->value("parent").toULongLong()!=fId)
    {
        alDataGoods* goods = new alDataGoods(fData->engine());
        fParent = goods->select(fRecord->value("parent").toULongLong());
    }
    fPrice = fRecord->value("price").toDouble();
    fExternalCode = fRecord->value("externalcode").toString();
    fDescription = fRecord->value("description").toString();
    fPicture = QPixmap();
    fPictureId = fRecord->value("id_pictures").toULongLong();
    fHydroCarbonat = fRecord->value("hydrocarbonat").toDouble();
    fFat = fRecord->value("fat").toDouble();
    fProtein = fRecord->value("protein").toDouble();
    fCalories = fRecord->value("calories").toDouble();    
    fOutOfStore = fRecord->value("outofstore").toBool();    
    fEqExport = fRecord->value("eqexport").toBool();        
    fBarcode = fRecord->value("barcode").toString();    
    fMaxDiscount = fRecord->value("maxdiscount").toInt();
    fPictureRec = NULL;
}

QPixmap alGoodsRecord::picture() 
{  
    if(fPicture.isNull() && fPictureId)
    {
	fPictureRec = (new alDataPictures(fData->engine()))->select(fPictureId);
	if(fPictureRec) fPicture = fPictureRec->picture();
    }
    return fPicture;    
}
