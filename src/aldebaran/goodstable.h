#ifndef GOODSTABLE_H
#define GOODSTABLE_H

#include "datatable.h"
//#include "data/datagoods.h"

class alEngine;
class alGoodsRecord;

class alGoodsTable : public alDataTable
{
Q_OBJECT
public:
    alGoodsTable(QWidget * parent, alEngine * engine);
    virtual void init();
    virtual void load(alGoodsRecord * parent);
    virtual void load(QString filter) { currentGroup = 0; alDataTable::load(filter); };
public slots:
    virtual void editCell(int row, int col, bool replace = FALSE);
    virtual QPixmap pixmap(int r);    
    bool newElement();
    bool newGroup();
    virtual bool editRowData();
    virtual bool deleteRowData();
    bool levelUp();
    bool home();    
protected:
    bool internalNew(bool isgroup=false);
private:    
    alGoodsRecord * currentGroup;
};

#endif
