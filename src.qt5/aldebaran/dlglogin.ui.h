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

#include "engine.h"

void alEngine::dlgLoginInit()
{
    dlgLogin->userTab = new alUsersTable(dlgLogin->frmSelect, this);
    dlgLogin->userTab->init();
    dlgLogin->userTab->setSelectable(TRUE);
    dlgLogin->userTab->showVerticalHeader();
    dlgLogin->userTab->adjustColumns();
    connect(dlgLogin->userTab, SIGNAL(currentChanged(int, int)), dlgLogin->editPassword, SLOT(setFocus()));
    dlgLogin->editPassword->setFocus();
    connect(this, SIGNAL(event(int, QVariant)), this, SLOT(eqData(int, QVariant)));
}

void alEngine::dlgLoginUp()
{
    dlgLogin->userTab->setCurrentRow(dlgLogin->userTab->currentRow()-1);
    dlgLogin->editPassword->setFocus();
}

void alEngine::dlgLoginDown()
{
    dlgLogin->userTab->setCurrentRow(dlgLogin->userTab->currentRow()+1);
    dlgLogin->editPassword->setFocus();
}

void alEngine::dlgLoginEqData(int, QVariant data)
{
    QMap<QString, QVariant> dataMap = data.toMap();
    dlgLogin->editPassword->setText(dataMap["line"].toString());
    dlgLoginLogin();
}

void alEngine::dlgLoginLogin()
{
    QDialog * dlg = (QDialog*)dlgLogin->userTab->parent();
    QString p = dlgLogin->editPassword->text();
    dlgLogin->editPassword->setText("");
    alUserRecord * user = dlgLogin->userTab->current();
    if(user->checkPassword(p))
    {
        if(!user->right(rLogin))
        {
            QMessageBox::critical(dlg, "aldebaran", tr("You don't have rights to login"));
            return;
        }
        setCurrentUser(user);
        dlg->accept();
        return;
    }
    QMessageBox::critical(dlg, "aldebaran", tr("Incorrect password!!"));
}

