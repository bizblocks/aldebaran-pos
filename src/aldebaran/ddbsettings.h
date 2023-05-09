#ifndef DDBSETTINGS_H
#define DDBSETTINGS_H

#include <QDialog>
#include "ui_ddbsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ddbsettings; }
QT_END_NAMESPACE


class ddbsettings : public QDialog
{
    Q_OBJECT
public:
    ddbsettings(QWidget * parent) : QDialog(parent), ui(new Ui::ddbsettings) { ui->setupUi(this); };
    ddbsettings(QWidget * parent = 0, const char * name = 0, bool modal = FALSE) :
        QDialog(parent, name, modal), ui(new Ui::ddbsettings) { ui->setupUi(this); };
public slots:
    void setData( QStringList data );
    QStringList getData();
private slots:
    void on_btnTest_clicked();
private:
    Ui::ddbsettings * ui;
};


#endif // DDBSETTINGS_H
