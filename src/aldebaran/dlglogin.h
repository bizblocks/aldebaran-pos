#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include "ui_dlglogin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class dlgLogin; }
QT_END_NAMESPACE

class dlgLogin : public QDialog
{
    Q_OBJECT
public:
    dlgLogin(QWidget * parent = 0) : QDialog(parent), ui(new Ui::dlgLogin) { ui->setupUi(this); };
public slots:
    void init(alEngine * e);
    void up();
    void down();
    void eqData(int, QVariant data);
    void login();
private:
    alEngine * fEngine;
    alUsersTable * userTab;
    Ui::dlgLogin * ui;
};


#endif // DLGLOGIN_H
