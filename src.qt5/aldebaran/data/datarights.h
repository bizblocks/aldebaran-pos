#ifndef DATARIGHTS_H
#define DATARIGHTS_H

#include "data.h"

class alRightsRecord;

class alDataRights : public alData
{
public:
    alDataRights(alEngine * e);
    ~alDataRights();
    virtual alDataRecord * current();
    virtual alRightsRecord * select(ULLID uid);
    virtual bool selectByOwner(alUserRecord * user);
    void createSetForUser(alUserRecord * r);
protected:
    virtual bool checkTable();
};

class alRightsRecord : public alDataRecord
{
public:
	Q_PROPERTY(alDataRecord * onwer READ owner WRITE setOwner)
	Q_PROPERTY(int  rule READ rule WRITE setRule)
	Q_PROPERTY(bool  enabled READ bool WRITE setEnabled)	
protected:
    alRightsRecord(alData * data);	
    alRightsRecord(alData * data, QSqlRecord * rec);    
    virtual void load();
public slots:
    static alRightsRecord * newElement(alDataRights * data);
    static alRightsRecord * current(alDataRights * data);    
    virtual int update ();    
    alDataRecord * owner();
    void setOwner(alDataRecord * o);
    int rule() { return fRule; };
    void setRule(int r) { fRule = r; };
    bool enabled() { return fEnabled; };
    void setEnabled(bool e) { fEnabled = e; };
private:
    alDataRecord * fOwner;
    ULLID fOwnerId;
    int fRule;
    bool fEnabled;
};

#endif
