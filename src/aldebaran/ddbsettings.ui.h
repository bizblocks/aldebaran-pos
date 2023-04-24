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

class ddbsettings : public QDialog, Ui::ddbsettings
{
public:
    ddbsettings(QWidget * parent) : QDialog(parent), Ui::ddbsettings() {};
    ddbsettings(QWidget * parent = 0, const char * name = 0, bool modal = FALSE) :
        QDialog(parent, name, modal), Ui::ddbsettings() {};
public slots:
    void setData( QStringList data );
    QStringList getData();
    void testConnection();
};

void ddbsettings::setData( QStringList data )
{
    cmbDBType->clear();
    QStringList drivers = QSqlDatabase::drivers();
    cmbDBType->insertStringList(drivers);
#ifdef DEBUG
    qDebug(tr("available drivers: %s").utf8(), drivers.join(" ").ascii());
#endif
    
    if(!data[0].isEmpty())
        cmbDBType->setCurrentText(data[0]);
    editDBName->setText(data[1]);
    editAdress->setText(data[2]);
    editPort->setText(data[3]);
    editUser->setText(data[4]);
    editPassword->setText(data[5]);
}

QStringList ddbsettings::getData()
{
    QStringList res;
    res.append(cmbDBType->currentText());
    res.append(editDBName->text());
    res.append(editAdress->text());
    res.append(editPort->text());
    res.append(editUser->text());
    res.append(editPassword->text());
    return res;
}

void ddbsettings::testConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(cmbDBType->currentText(), "testconnectiondb");
    db.setDatabaseName(editDBName->text());
    db.setHostName(editAdress->text());
    db.setPort(editPort->text().toInt());
    bool res = db.open(editUser->text(), editPassword->text());
    if(res)
        QMessageBox::information(this, "aldebaran", tr("Successfully connected"));
    else
        QMessageBox::critical(this, "aldebaran", tr("Can't connect database:\n%1").arg(db.lastError().text()));
    QSqlDatabase::removeDatabase("testconnectiondb");
}

