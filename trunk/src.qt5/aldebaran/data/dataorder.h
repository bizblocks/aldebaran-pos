
#ifndef DATAORDER_H
#define DATAORDER_H

#include <qpixmap.h>
#include <qdatetime.h>
#include "data.h"

class alOrderRecord;
class alDataOrderTable;
class alUserRecord;
class alDiscountRecord;
class importer;

//can use that class as prototype for Document in feature
class alDataOrder : public alData
{
public:
    alDataOrder(alEngine * e);
//	virtual bool select ( const QString & filter, const QSqlIndex & sort = QSqlIndex ( ) );	
    enum Status
    {
	New,
	Saved,
	Closed,
	Canceled,
	Exported
    };
    virtual alOrderRecord * select(int uid);
    virtual bool select(QString filter) { return alData::select(filter); };
    alOrderRecord * selectByNumber(int num);        
    ULLID unum();
    alOrderRecord * newDocument();
    bool delDocument();
    virtual alDataRecord * current();
    alOrderRecord * import(importer * imp);
protected:
    virtual bool checkTable();
    virtual QSqlIndex defaultSort();    
};

typedef alDataOrder::Status alStatus;

class alOrderRecord : public alDataRecord
{
    Q_OBJECT
    Q_PROPERTY(int num READ num WRITE setNum);
    Q_PROPERTY(alStatus status READ status WRITE setStatus);
protected:    
    alOrderRecord(alData * data);
    alOrderRecord(alData * data, QSqlRecord * rec);
    virtual void load();    
public slots:
    virtual alDataOrderTable * getDocumentTable();
    static alOrderRecord * newDocument(alDataOrder * data);
    static alOrderRecord * current(alData * data);
    int num() const { return fNum; };
    void setNum(int n) { fNum = n; };
    int checkNum() { return fCheckNum; };
    void setCheckNum(int n) { fCheckNum = n; };
    alStatus status() const {return fStatus; };
    void setStatus(alStatus  p);    
    int table() { return fTableNum; };
    void setTable(int t) { fTableNum = t; };
    int summType() { return fSummType; };
    void setSummType(int st) { fSummType = st; };
    QDate date() { return fDate; };
    void setDate(QDate d) { fDate = d; };
    QTime timeOpen() { return fTimeOpen; };
    void setTimeOpen(QTime t) { fTimeOpen = t; };
    QTime timeClose() { return fTimeClose; };
    void setTimeClose(QTime t) { fTimeClose = t; };
    void setUser(alUserRecord * u) { fUser = u; };
    alUserRecord * user() { return fUser; };
    int guests() { return fGuests; };
    void setGuests(int g) { fGuests = g; };
    alDiscountRecord * discount() { return fDiscount; };
    void  setDiscount(alDiscountRecord * d);
    QString comment() { return fComment;};
    void setComment(QString c) { fComment = c; };    
    QString externalCode() { return fExternalCode; };
    void setExternalCode(QString e) { fExternalCode =  e; };    
    int update();
    double total(QString attr);
    void printOrder(QString device="");    
    void printBill(QString device="");
    QString info();
private:
    alDataOrderTable * fDataTable;
    int fNum, fCheckNum, fTableNum, fGuests, fSummType;
    alDataOrder::Status fStatus;
    QDate fDate;
    QTime fTimeOpen, fTimeClose;
    alUserRecord * fUser;
    alDiscountRecord * fDiscount;
    QString fComment, fExternalCode;
    friend class alDataOrder;
};

#endif
