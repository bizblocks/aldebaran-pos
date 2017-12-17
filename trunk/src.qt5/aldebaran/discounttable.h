#ifndef DISCOUNTTABLE_H
#define DISCOUNTTABLE_H

#include <qvariant.h>
#include "datatable.h"

class alDiscountRecord;

class alDiscountTable : public alDataTable
{
    Q_OBJECT
public:
    alDiscountTable(QWidget * parent, alEngine * engine);
    virtual void init();
    alDiscountRecord * current();
public slots:
    bool newElement();
    virtual bool editRowData();
    virtual bool deleteRowData();
    virtual QVariant displayValue(QString attr, QVariant val);    
protected:
    virtual QPixmap pixmap(int r);
    bool dialog(alDiscountRecord * user);
};

#endif
