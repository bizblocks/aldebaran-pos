#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include "engine.h"
#include "ui_dlguser.h"

#define TNAME "users"

alDataUsers::alDataUsers(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    //alData::setName(TNAME, TRUE);
}

alDataUsers::~alDataUsers()
{
}

bool alDataUsers::checkTable()
{
    if(alData::checkTable(TNAME))
        return true;
#ifdef DEBUG    
    qDebug() << QObject::tr("creating table users").toUtf8();
#endif    
    QString query = Queries::tr("CREATE TABLE USERS ("
		    "id int8 NOT NULL, name varchar(30),"
		    "role int4, password varchar(15),"
		    "CONSTRAINT id_user PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
#ifdef DEBUG    
    qDebug() << QObject::tr("lastError was %1").arg(engine()->db().lastError().text()).toUtf8();
#endif        
    query = Queries::tr("CREATE INDEX idx_name ON users (name);"); 
    engine()->db().exec(query);
}

//TODO reimplement
QSqlIndex alDataUsers::defaultSort()
{
    //return QSqlIndex::fromStringList(QStringList::split(",", "name"), this);
}

alDataRecord * alDataUsers::current()
{
    return alUserRecord::current(this);    
}
    
alUserRecord * alDataUsers::select(ULLID uid)
{
    alData::select(Queries::tr("id=%1").arg(uid));
    if(first())
        return (alUserRecord*)current();
    return NULL;
}

alUserRecord * alDataUsers::addUser(QString name, int role)
{
    alUserRecord * user = alUserRecord::newElement(this);
    user->setName(name);
    user->setRole(role);
    user->setPassword(QString("%1%2").arg(name).arg(user->id()));
    user->update();
    return user;
}

void alDataUsers::checkUsers()
{
    alDataRights * rights = new alDataRights(engine());
    alData::select(Queries::tr("role=1"));
    if(!first())
    {
	alUserRecord * user = addUser(QObject::tr("Administrator"), 1);
	rights->createSetForUser(user);
    }
    alData::select(Queries::tr("role=3"));
    if(!first())
    {
	alUserRecord * user = addUser(QObject::tr("Service"), 3);
	rights->createSetForUser(user);	
    }
}

bool alDataUsers::delElement()
{
    ULLID id = value("id").toULongLong();
    QString query = Queries::tr("DELETE FROM users WHERE id=%1").arg(id);
    engine()->db().exec(query);
    query = Queries::tr("DELETE FROM rights WHERE id_owner=%1").arg(id);
    engine()->db().exec(query);
    return true;    
}

alUserRecord * alDataUsers::newElement()
{
    return alUserRecord::newElement(this);
}

alUserRecord::alUserRecord(alData * data) :
	alDataRecord(data)
{
    rights = NULL;
    fData = new alDataGoods(data->engine());
    fData->select(Queries::tr("id=%1").arg(fId));
    //fRecord = fData->primeUpdate();
    load();
}

alUserRecord::alUserRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    rights = NULL;    
    if(!fRecord)
        return;
    load();
}

//TODO reimplement
alUserRecord * alUserRecord::newElement(alDataUsers * data)
{
    if(!data)
        return NULL;
//    QSqlRecord * rec = data->primeInsert();
//    rec->setValue("id", data->uid());
//    alUserRecord * res = new alUserRecord(data, rec);
//    res->fIsNew = TRUE;
//    res->setRole(2);
//    return res;
    return NULL;
}

//TODO reimplement
alUserRecord * alUserRecord::current(alDataUsers * data)
{
    if(!data)
        return NULL;
    //return new alUserRecord(data, data->primeUpdate());
    return NULL;
}

void alUserRecord::load()
{
    fName = fRecord->value("name").toString();
    fRole = fRecord->value("role").toInt();
    fPass = fRecord->value("password").toString();
    rights = new alDataRights(fData->engine());
    rights->selectByOwner(this);
    for(int r=1;r<rEnd;r++)
	fRights[r] = NULL;
    if(rights->first()) do
    {
	alRightsRecord * r = (alRightsRecord *)rights->current();
	fRights[r->rule()] = r;
    } while(rights->next());
}

int alUserRecord::update() 
{
    primeUpdateInsert();
    fRecord->setValue("name", UTF8(fName));
    fRecord->setValue("role", fRole);
    fRecord->setValue("password", UTF8(fPass));
    return alDataRecord::update();
//    if(!success) return success;
//    for(int r=0;r<rEnd;r++)
//	if(fRights[r]) success+=fRights[r]->update();		
}

bool alUserRecord::right(alRights rule)
{
    if(!fRights[rule])
	return FALSE;
    return fRights[rule]->enabled();
}

bool alUserRecord::checkPassword(QString pass)
{
//TODO replace with more secure password-check, maybe assemble??
    if(pass==fPass) return true;
    return false;
}

//TODO reimplement
bool alUserRecord::dialog(QWidget * parent)
{
//    dlgUser * dlg = new dlgUser(parent);
//    dlg->setData(this);
//    if(dlg->exec())
//    {
//        update();
//        delete dlg;
//        return TRUE;
//    }
//    delete dlg;
    return FALSE;
}

void alUserRecord::setRight(alRights rule, bool enabled)
{
    if(!fRights[rule])
    {
	fRights[rule] = alRightsRecord::newElement(rights);
	fRights[rule]->setOwner(this);
	fRights[rule]->setRule(rule);
    }
    fRights[rule]->setEnabled(enabled);
    fRights[rule]->update();
}
