#include <QtSql/QSqlDatabase>
#include <qbuffer.h>
#include <qdebug.h>
#include "engine.h"
#include "ui_dlgdiscount.h"

#define TNAME "discount"

alDataDiscount::alDataDiscount(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    //alData::setName(TNAME, TRUE);
}

alDataDiscount::~alDataDiscount()
{
}

bool alDataDiscount::checkTable()
{
    if(alData::checkTable(TNAME))
        return true;
#ifdef DEBUG    
    qDebug() << QObject::tr("creating table discount").toUtf8();
#endif    
    QString query = Queries::tr("CREATE TABLE discount ("
		    "id int8 NOT NULL, name varchar(50),"
		    "type int2, value int2, protect bool, code varchar(255),"
		    "CONSTRAINT id_discount PRIMARY KEY (id), "
		    "CONSTRAINT code UNIQUE(code))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
#ifdef DEBUG    
    qDebug() << QObject::tr("lastError was %1").arg(engine()->db().lastError().text()).toUtf8();
#endif        
    query = Queries::tr("CREATE INDEX idx_discount_code ON discount (code);"); 
    engine()->db().exec(query);
}

alDataRecord* alDataDiscount::current()
{
    return alDiscountRecord::current(this);
}

alDiscountRecord * alDataDiscount::newElement()
{
    return alDiscountRecord::newElement(this);
}

alDiscountRecord *alDataDiscount:: select(ULLID uid)
{
    alData::select(QString("id=%1").arg(uid));
    if(first())
        return (alDiscountRecord*)current();
    return NULL;    
}

bool alDataDiscount::select(const QString filter)
{
    return alData::select(filter);
}

bool alDataDiscount::delElement()
{
    ULLID id = value("id").toULongLong();
    QString query = QString(Queries::tr("DELETE FROM discount WHERE id=%1")).arg(id);
    engine()->db().exec(query);
    return true;
}

void alDataDiscount::import(importer * imp)
{	
    impValues values;
    for(int lineNum=0;lineNum<imp->count();lineNum++)
    {
	imp->seek(lineNum);
	if(imp->value("cardcode").toString()[0]!='%') continue;	
	values[imp->value("cardcode").toString().mid(1)] = imp->toMap();
    }
    update(&values);
}

//TODO uncomment
void alDataDiscount::update(impValues * values)
{
//    alDiscountRecord * rec;
//    impValues::iterator it;
//    map map;
    
//    select("");
//    engine()->startTransaction();
//    if(first()) do
//    {
//        if(value("code").toString().isEmpty()) continue;
//        it = values->find(value("code").toString());
//        if(it==values->end()) continue;
//        rec = (alDiscountRecord*)current();
//        map = *it;
//        rec->engine()(map["cardcode"].toString().mid(1));
//        rec->setName(map["cardname"].toString());
//        rec->setValue((int)map["cardpercent"].toDouble());
//        rec->update();
//        values->remove(it);
//    }while(next());
//    fEngine->commitTransaction();
    
//    fEngine->startTransaction();
//    for(it=values->begin();it!=values->end();++it)
//    {
//	map = *it;
//	if(map["cardcode"].toString()[0]!='%') continue;
//	rec = newElement();
//	rec->engine()(map["cardcode"].toString().mid(1));
//	rec->setName(map["cardname"].toString());
//	rec->setValue((int)map["cardpercent"].toDouble());
//	rec->setType(0);
//	rec->setProtect(TRUE);
//	rec->update();
//    }
//    fEngine->commitTransaction();
////second variant low-level
}

alDiscountRecord::alDiscountRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    if(!fRecord) return;
    load();
}

//TODO implement
alDiscountRecord * alDiscountRecord::current(alDataDiscount * data)
{
    if(!data)
        return NULL;
    //return new alDiscountRecord(data, data->primeUpdate());
    return NULL;
}

//TODO implement
alDiscountRecord * alDiscountRecord::newElement(alDataDiscount * data)
{
    if(!data)
        return NULL;
//    QSqlRecord * rec = data->primeInsert();
//    rec->setValue("id", data->uid());
//    alDiscountRecord * res = new alDiscountRecord(data, rec);
//    res->fIsNew = TRUE;
//    return res;
    return NULL;
}

void alDiscountRecord::load()
{
    alDataRecord::load();
    fName = fRecord->value("name").toString();
    fType = fRecord->value("type").toInt();
    fValue = fRecord->value("value").toInt();
    fProtect = fRecord->value("protect").toBool();
    fCode = fRecord->value("code").toString();
}

int alDiscountRecord::update() 
{
    primeUpdateInsert();
    fRecord->setValue("name", fName);
    fRecord->setValue("type", fType);
    fRecord->setValue("value", fValue);
    fRecord->setValue("protect", fProtect ? "TRUE" : "FALSE");
    fRecord->setValue("code", fCode);    
    alDataRecord::update();    
    qDebug() << fData->lastError().text();
    return TRUE;
}

//TODO uncomment
bool alDiscountRecord::dialog(QWidget * parent)
{   
//    dlgDiscount * dlg = new dlgDiscount(parent);
//    dlg->init(fData->engine());
//    dlg->setData(this);
//    if(dlg->exec())
//    {
//    	update();
//        delete dlg;
//        return TRUE;
//    }
//    delete dlg;
//    return FALSE;
}
