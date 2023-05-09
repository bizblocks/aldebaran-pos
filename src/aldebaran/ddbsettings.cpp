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
#include <qsqldatabase.h>
#include <qmessagebox.h>
#include "engine.h"
#include "ddbsettings.h"

void ddbsettings::setData( QStringList data )
{
    ui->cmbDBType->clear();
    QStringList drivers = QSqlDatabase::drivers();
    ui->cmbDBType->insertStringList(drivers);
    alDBG(tr("available drivers: %1").arg(drivers.join(" ")));
    if(!data[0].isEmpty())
        ui->cmbDBType->setCurrentText(data[0]);
    ui->editDBName->setText(data[1]);
    ui->editAdress->setText(data[2]);
    ui->editPort->setText(data[3]);
    ui->editUser->setText(data[4]);
    ui->editPassword->setText(data[5]);
}

QStringList ddbsettings::getData()
{
    QStringList res;
    res.append(ui->cmbDBType->currentText());
    res.append(ui->editDBName->text());
    res.append(ui->editAdress->text());
    res.append(ui->editPort->text());
    res.append(ui->editUser->text());
    res.append(ui->editPassword->text());
    return res;
}

void ddbsettings::on_btnTest_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(ui->cmbDBType->currentText(), "testconnectiondb");
    db.setDatabaseName(ui->editDBName->text());
    db.setHostName(ui->editAdress->text());
    db.setPort(ui->editPort->text().toInt());
    bool res = db.open(ui->editUser->text(), ui->editPassword->text());
    if(res)
        QMessageBox::information(this, "aldebaran", tr("Successfully connected"));
    else
        QMessageBox::critical(this, "aldebaran", tr("Can't connect database:\n%1").arg(db.lastError().text()));
    QSqlDatabase::removeDatabase("testconnectiondb");
}

