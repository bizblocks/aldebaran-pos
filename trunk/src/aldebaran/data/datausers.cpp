#include <qsqldatabase.h>
#include "engine.h"
#include "dlguser.h"

#define TNAME "users"

alDataUsers::alDataUsers(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    alData::setName(TNAME, TRUE);    
}

alDataUsers::~alDataUsers()
{
}

void alDataUsers::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME).size()>0) return;
#ifdef DEBUG    
    qDebug(QObject::tr("creating table users").utf8());
#endif    
    QString query = Queries::tr("CREATE TABLE USERS ("
		    "id int8 NOT NULL, name varchar(30),"
		    "role int4, password varchar(15),"
		    "CONSTRAINT id_user PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    fEngine->db()->exec(query);
#ifdef DEBUG    
    qDebug(QObject::tr("lastError was %1").arg(fEngine->db()->lastError().text()).utf8());
#endif        
    query = Queries::tr("CREATE INDEX idx_name ON users (name);"); 
    fEngine->db()->exec(query);
}

QSqlIndex alDataUsers::defaultSort()
{
    return QSqlIndex::fromStringList(QStringList::split(",", "name"), this);
}

alDataRecord * alDataUsers::current()
{
    return alUserRecord::current(this);    
}
    
alUserRecord * alDataUsers::select(Q_ULLONG uid)
{
    alData::select(Queries::tr("id=%1").arg(uid));
    if(first()) return (alUserRecord*)current();
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
    alDataRights * rights = new alDataRights(fEngine);
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
    Q_ULLONG id = value("id").toULongLong();
    QString query = Queries::tr("DELETE FROM users WHERE id=%1").arg(id);
    fEngine->db()->exec(query);
    query = Queries::tr("DELETE FROM rights WHERE id_owner=%1").arg(id);
    fEngine->db()->exec(query);    
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
    fRecord = fData->primeUpdate();    
    load();
}

alUserRecord::alUserRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    rights = NULL;    
    if(!fRecord) return;
    load();
}

alUserRecord * alUserRecord::newElement(alDataUsers * data)
{
    if(!data) return NULL;
    QSqlRecord * rec = data->primeInsert();
    rec->setValue("id", data->uid());
    alUserRecord * res = new alUserRecord(data, rec);
    res->fIsNew = TRUE;
    res->setRole(2);    
    return res;    
}

alUserRecord * alUserRecord::current(alDataUsers * data)
{
    if(!data) return NULL;    
    return new alUserRecord(data, data->primeUpdate());    
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

bool alUserRecord::dialog(QWidget * parent)
{
    dlgUser * dlg = new dlgUser(parent);
    dlg->setData(this);
    if(dlg->exec())
    {
	update();
	delete dlg;
	return TRUE;
    }
    delete dlg;
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
