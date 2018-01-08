#ifndef DATAUSERS_H
#define DATAUSERS_H

#include "data.h"
#include "rights.h"

class alDataRights;
class alRightsRecord;
class alUserRecord;

class alDataUsers : public alData
{
public:
    alDataUsers(alEngine * e);
    ~alDataUsers();
    void checkUsers();    
    virtual QPixmap pixmap(int) const;
public slots:    
    virtual alDataRecord * current();
    virtual alUserRecord * select(ULLID uid);
    alUserRecord * newElement();
    bool delElement();
protected:
    virtual bool checkTable();
    virtual QSqlIndex defaultSort();
private:
    alUserRecord * addUser(QString name, int role);
};

class alUserRecord : public alDataRecord
{
public:
	Q_PROPERTY(int id READ id)
	Q_PROPERTY(QString name READ name WRITE setName)
protected:
    alUserRecord(alData * data);	
    alUserRecord(alData * data, QSqlRecord * rec);    
    virtual void load();
public:
    inline bool operator==(alUserRecord * u1 ) 
    {
        if(!u1) return FALSE;
        return fId == u1->id();
    }
public slots:
    static alUserRecord * newElement(alDataUsers * data);
    static alUserRecord * current(alDataUsers * data);    
    virtual int update ();    
    QString name() { return fName; }
    void setName(QString n) { fName = n; }
    int role() { return fRole; }
    void setRole(int r) { fRole = r; }
    bool right(alRights rule);
    void setRight(alRights tule, bool enabled);
    void setPassword(QString p) {fPass = p; }
    bool checkPassword(QString p);
    virtual bool dialog(QWidget * parent);    
private:
    friend class alDataUsers;    
    QString fName;
    int fRole;
    QString fPass;
    alDataRights * rights;
    alRightsRecord * fRights[rEnd];
};

#endif
