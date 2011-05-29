#ifndef DATAPICTURES_H
#define DATAPICTURES_H

#include <qpixmap.h>
#include "data.h"

class alPictureRecord;

class alDataPictures : public alData
{
public:
    alDataPictures(alEngine * e);
//    ~alDataPictures();
public slots:    
    virtual alDataRecord * current();
    alPictureRecord * newElement();
    virtual alPictureRecord * select(Q_ULLONG uid);
    virtual bool select(const QString filter = "");
    bool delElement();    
protected:
    virtual void checkTable();
};

class alPictureRecord : public alDataRecord
{
public:
	Q_PROPERTY(QString type READ type WRITE setType)
protected:
    alPictureRecord(alData * data);
    alPictureRecord(alData * data, QSqlRecord * rec);    
    virtual void load();
public slots:
    static alPictureRecord * newElement(alDataPictures * data);
    static alPictureRecord * current(alDataPictures* data);    
    virtual int update();
    QPixmap picture() { return fPicture; };
    void setPicture(QPixmap p) { fPicture = p; };    
private:
    int fType;
    alDataRecord * fObject;
    QPixmap fPicture;
};

#endif
