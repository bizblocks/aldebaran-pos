/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

class dlgLogin : public QDialog, Ui::dlgLogin
{
public:
    dlgLogin(QWidget * parent = 0) : QDialog(parent), Ui::dlgLogin() {}
public slots:
    void init(alEngine * e);
    void up();
    void down();
    void eqData(int, QVariant data);
    void login();
private:
    alEngine * fEngine;
    alUsersTable * userTab;
};

void dlgLogin::init(alEngine * e)
{
    fEngine = e;
    userTab = new alUsersTable(frmSelect, fEngine);
    userTab->init();
    userTab->setSelectable(TRUE);
    userTab->showVerticalHeader();
    userTab->adjustColumns();
    connect(userTab, SIGNAL(currentChanged(int, int)), editPassword, SLOT(setFocus()));
    editPassword->setFocus();
    connect(fEngine, SIGNAL(event(int, QVariant)), this, SLOT(eqData(int, QVariant)));
}

void dlgLogin::up()
{
    userTab->setCurrentRow(userTab->currentRow()-1);
    editPassword->setFocus();
}

void dlgLogin::down()
{
    userTab->setCurrentRow(userTab->currentRow()+1);
    editPassword->setFocus();
}

void dlgLogin::eqData(int, QVariant data)
{
    QMap<QString, QVariant> dataMap = data.toMap();
    editPassword->setText(dataMap["line"].toString());
    login();
}

void dlgLogin::login()
{  
    QString p = editPassword->text();
    editPassword->setText("");
    alUserRecord * user = userTab->current();
    if(user->checkPassword(p))
    {
        if(!user->right(rLogin))
        {
            QMessageBox::critical(this, "aldebaran", QObject::tr("You don't have rights to login"));
            return;
        }
        fEngine->setCurrentUser(user);
        accept();
        return;
    }
    QMessageBox::critical(this, "aldebaran", QObject::tr("Incorrect password!!"));
}
