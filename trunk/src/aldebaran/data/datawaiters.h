#ifndef DATAWAITERS_H
#define DATAWAITERS_H

#include "data.h"
#include "rights.h"

class alWaiterRecord;

class alDataWaiters : public alData
{
public:
    alDataWaiters(alEngine * e);
    ~alDataWaiters();
public slots:    
    virtual alDataRecord * current();
    virtual alWaiterRecord * select(Q_ULLONG uid);
    alWaiterRecord * newElement();
    bool delElement();
protected:
    virtual void checkTable();    
    virtual QSqlIndex defaultSort();
};

class alWaiterRecord : public alDataRecord
{
public:
	Q_PROPERTY(int id READ id)
	Q_PROPERTY(QString name READ name WRITE setName)
protected:
    alWaiterRecord(alData * data);	
    alWaiterRecord(alData * data, QSqlRecord * rec);    
    virtual void load();
public:
    inline bool operator==(alWaiterRecord * u1 ) 
    {
	if(!u1) return FALSE;
	return fId == u1->id();
    };
public slots:
    static alWaiterRecord * newElement(alDataWaiters * data);
    static alWaiterRecord * current(alDataWaiters * data);    
    virtual int update ();    
    QString name() { return fName; };
    void setName(QString n) { fName = n; };
    virtual bool dialog(QWidget * parent);    
private:
    QString fName;
};

#endif
