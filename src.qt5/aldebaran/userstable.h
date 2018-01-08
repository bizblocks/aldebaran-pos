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
    alUsersTable(QWidget * parent, alEngine * engine = NULL);
    virtual void init(alEngine * e=NULL);
    alUserRecord * current();
public slots:
    bool newElement();
    virtual bool editRowData();
    virtual bool deleteRowData();
protected:
    bool dialog(alUserRecord * user);
};

#endif
