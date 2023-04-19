#ifndef EQTABLE_H
#define EQTABLE_H

#include "datatable.h"

class alEqRecord;

class alEqTable : public alDataTable
{
    Q_OBJECT
public:
    alEqTable(QWidget * parent, alEngine * engine);
    virtual void init();    
    alEqRecord * current();
public slots:
    bool newElement();
    virtual bool editRowData();
    virtual bool deleteRowData();
protected slots:
    virtual void fillLine(int r);
protected:
    virtual QPixmap pixmap(int r);
    bool dialog(alEqRecord * user);
};

#endif
