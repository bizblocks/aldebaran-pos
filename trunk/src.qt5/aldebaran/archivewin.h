#ifndef ARCHIVEWIN_H
#define ARCHIVEWIN_H

#include <qwidget.h>
#include <qpixmap.h>

class QGridLayout;
class QDateEdit;
class alArchiveTable;
class alEngine;

class alArchiveWindow : public  QWidget
{
    Q_OBJECT
public:
    alArchiveWindow(alEngine * e, QWidget * parent=0, QString name=QString::null);
    void init();
public slots:
    void refresh();
    void close();
    void applyFilter();
signals:
    void exit();
private:
    alEngine * fEngine;
    QGridLayout * grid;
    alArchiveTable * arcTab;
    QDateEdit * dBegin, * dEnd;
};

#endif
