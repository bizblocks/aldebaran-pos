#ifndef IMPSHTRIH_H
#define IMPSHTRIH_H

#include "impexp.h"

class QFile;

class impShtrihM : public importer
{
public:
    impShtrihM();
    ~impShtrihM();
    virtual bool open(QString filename);        
    virtual bool seek(int row);    
    virtual QVariant value(QString name);
    virtual map toMap();
    virtual bool close();
    
    virtual bool isOpened() { return true; };
    virtual int errorCode() {  return 0; };
    virtual QString errorMsg(int) { return ""; };
    
protected:
    QFile * sourceFile;
    int fIsGroup;
    QString fName;
    QString fCode;
    QString fParentCode;
    double fPrice;
};

class expShtrihM : public impShtrihM
{
public:
    expShtrihM();
    ~expShtrihM();    
    virtual bool open(QString filename);    
    virtual bool fromMap(map m);
protected:
    int count;
};


#endif
