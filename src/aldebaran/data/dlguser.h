#ifndef DLGUSER_H
#define DLGUSER_H

#include <QDialog>
#include "ui_dlguser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class dlgUser; }
QT_END_NAMESPACE

class dlgUser : public QDialog
{
    Q_OBJECT
public:
    dlgUser(QWidget * parent = 0) : QDialog(parent), ui(new Ui::dlgUser) { ui->setupUi(this); init(); };
public slots:
    void setData(alUserRecord * data);
    void setItem(Q3ListBoxItem * item, bool checked);
    void refresh();
    void check(Q3ListBoxItem * item);
    void init();
    void passwordChanged( const QString & text );
    void ok();
private:
    Ui::dlgUser * ui;
    alUserRecord * fData;
    QString fPassword;
};

#endif // DLGUSER_H
