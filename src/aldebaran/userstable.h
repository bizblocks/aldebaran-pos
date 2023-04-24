#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <qwidget.h>
#include "datatable.h"

class alEngine;
class alUserRecord;

class alUsersTable : public alDataTable
{
    Q_OBJECT
public:
    alUsersTable(QWidget * parent, alEngine * engine);
    virtual void init();    
    alUserRecord * current();
public slots:
    bool newElement();
    virtual bool editRowData();
    virtual bool deleteRowData();
protected:
    virtual QIcon icon(int r);
    bool dialog(alUserRecord * user);
};

#endif
