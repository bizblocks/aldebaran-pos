#ifndef ARCHIVETABLE_H
#define ARCHIVETABLE_H

#include "datatable.h"

class alEngine;
class alOrderWindow;

class alArchiveTable : public alDataTable
{
    Q_OBJECT
public:
    alArchiveTable(QWidget * parent, alEngine * engine);
    virtual void init();
public slots:
    virtual QPixmap pixmap(int r);
    virtual bool editRowData();
    virtual bool deleteRowData();
    void closeOrder();
protected slots:
    virtual void fillLine(int r);
signals:
    void exitOrder();
private:
    alOrderWindow * orderWin;
    int orderRow;
};

#endif
