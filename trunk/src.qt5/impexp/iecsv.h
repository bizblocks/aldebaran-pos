#ifndef IMPCSV_H
#define IMPCSV_H

#include "ieshtrih.h"

class QFile;

class impCSV : public impShtrihM
{
public:
    impCSV();
    ~impCSV();
    virtual bool open(QString filename);        
    virtual bool seek(int row);    
    enum eKind
    {
	csvGoods
    };
    eKind kind();
protected:    
    QString noQuotes(QString str);
private:
    eKind fKind;
};


#endif
