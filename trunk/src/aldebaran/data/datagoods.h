#ifndef DATAGOODS_H
#define DATAGOODS_H

#include <qpixmap.h>
#include "data.h"
#include "impexp.h"

class alGoodsRecord;
class alPictureRecord;
class importer;

//can use that class as prototype for Catalogues in feature
class alDataGoods : public alData
{
public:
    alDataGoods(alEngine * e);
    virtual bool select ( const QString & filter, const QSqlIndex & sort = QSqlIndex ( ) );	
    virtual alDataRecord* current();    
    virtual alGoodsRecord * select(int uid);
    alGoodsRecord * newElement(alGoodsRecord * parent = NULL);
    alGoodsRecord * newGroup(alGoodsRecord * parent = NULL);
    bool delElement();
    bool delGroup();
    void import(importer * imp);
    void exportpictures();
protected:
    virtual void checkTable();    
    virtual QSqlIndex defaultSort();
private:
    alGoodsRecord * internalNew(alGoodsRecord * parent = NULL, bool group = FALSE);
    void update(impValues * values);
    void update(map map, alGoodsRecord * cr);
};

class alGoodsRecord : public alDataRecord
{
	Q_PROPERTY(int id READ id)
	Q_PROPERTY(bool isGroup read isGroup)
	Q_PROPERTY(int parent READ parent WRITE setParent)
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(double price READ price WRITE setPrice)
	Q_PROPERTY(QString description READE description WRITE setDescription)
	Q_PROPERTY(QString externalCode READE externalCode WRITE setExternalCode)
	Q_PROPERTY(QPixmap picture READE picture WRITE setPicture)	    
protected:
    alGoodsRecord(alData * data);
    alGoodsRecord(alData * data, QSqlRecord * rec);    
    static alGoodsRecord * internalNew(alDataGoods * data,  alGoodsRecord * parent = NULL, bool isgroup=false);    
    virtual void load();
public slots:
    static alGoodsRecord * newElement(alDataGoods * data, alGoodsRecord * parent = NULL);
    static alGoodsRecord * newGroup(alDataGoods * data, alGoodsRecord * parent = NULL);
    static alGoodsRecord * current(alDataGoods * data);    
    virtual int update ();    
    bool isGroup() { return fIsGroup; };
    alGoodsRecord * parent() { return fParent; };
    void setParent(alGoodsRecord  * p) { fParent = p; };
    QString name() { return fName; };
    void setName(QString n) { fName = n; };
    double price() { return fPrice; };
    void setPrice(double p) { fPrice = p; };
    QString description() { return fDescription; };
    void setDescription(QString d) { fDescription = d; };
    QString externalCode() { return fExternalCode; };
    void setExternalCode(QString e) { fExternalCode =  e; };
    QPixmap picture();
    void setPicture(QPixmap p) { fPicture = p; };    
    double hydroCarbonat() { return fHydroCarbonat;};
    void setHydroCarbonat(double d) { fHydroCarbonat =d; };
    double fat() { return fFat; };
    void setFat(double d) { fFat = d; };
    double protein() { return fProtein; }; 
    void setProtein(double d) { fProtein = d; };
    double calories() {return fCalories; };
    void setCalories(double d) { fCalories = d; };
    bool outOfStore() {  return fOutOfStore; };
    void setOutOfStore(bool o) { fOutOfStore = o; };
    bool eqExport() {  return fEqExport; };
    void setEqExport(bool o) { fEqExport = o; };    
    QString barcode() { return fBarcode; };
    void setBarcode(QString b) { fBarcode = b; };
    int maxDiscount() { return fMaxDiscount; };
    void setMaxDiscount(int m) { fMaxDiscount = m; };
private:
    bool fIsGroup;
    alGoodsRecord * fParent;
    QString fName;
    double fPrice;
    QString fDescription, fExternalCode, fBarcode;
    QPixmap fPicture;    
    QByteArray fbaPicture;
    alPictureRecord * fPictureRec;
    Q_ULLONG fPictureId;
    double fHydroCarbonat, fFat, fProtein, fCalories;
    bool fOutOfStore, fEqExport;
    int fMaxDiscount;
};

#endif
