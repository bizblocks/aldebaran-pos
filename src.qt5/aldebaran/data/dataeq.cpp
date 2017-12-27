#include <QtSql/QSqlDatabase>
#include <qbuffer.h>
#include <QDebug>
#include "dataeq.h"
#include "engine.h"
#include "ui_dlgdevice.h"

#define TNAME "equipment"

alDataEq::alDataEq(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    //alData::setName(TNAME, TRUE);
}

alDataEq::~alDataEq()
{
}

void alDataEq::checkTable()
{
    if(!engine()->db().isOpen())
        return;
    QStringList check = engine()->db().tables();
    if(check.contains(TNAME))
        return;
#ifdef DEBUG
    qDebug() << QObject::tr("creating table equipment").toUtf8();
#endif    
    QString query = Queries::tr("CREATE TABLE equipment ("
		    "id int8 NOT NULL, name varchar(20),"
		    "type varchar(20), enabled bool, options bytea,"
		    "CONSTRAINT id_eq PRIMARY KEY (id))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
#ifdef DEBUG    
    qDebug() << QObject::tr("lastError was %1").arg(engine()->db().lastError().text()).toUtf8();
#endif        
}

alDataRecord* alDataEq::current()
{
    return alEqRecord::current(this);
}

alEqRecord * alDataEq::newElement()
{
    return alEqRecord::newElement(this);
}

bool alDataEq::delElement()
{
    ULLID id = value("id").toULongLong();
    QString query = QString(Queries::tr("DELETE FROM equipment WHERE id=%1")).arg(id);
    engine()->db().exec(query);
    return true;
}

alEqRecord::alEqRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    if(!fRecord) return;
    load();
}

//TODO reimplement
alEqRecord * alEqRecord::current(alDataEq * data)
{
    if(!data)
        return NULL;
    //return new alEqRecord(data, data->primeUpdate());
    return NULL;
}

//TODO reimplement
alEqRecord * alEqRecord::newElement(alDataEq * data)
{
    if(!data)
        return NULL;
//    QSqlRecord * rec = data->primeInsert();
//    rec->setValue("id", data->uid());
//    alEqRecord * res = new alEqRecord(data, rec);
//    res->fIsNew = TRUE;
//    return res;
    return NULL;
}


void alEqRecord::load()
{
    fName = fRecord->value("name").toString();
    fType = fRecord->value("type").toString();
    fEnabled = fRecord->value("enabled").toBool();
    QByteArray bOpt = fRecord->value("options").toByteArray();
    QString sOpt(bOpt);
    QStringList slOpt = QString(sOpt).split("\n");
    fOptions.clear();
    for(int i=0;i<(int)slOpt.count();i++)
    {
        QStringList pair = QString(slOpt[i]).split("=");
//      qDebug(slOpt[i]);
//        pair[0] = QString::fromLocal8Bit(pair[0]);
        if(pair.count()==1)
            fOptions[pair[0]] = ""; //default
        else
            fOptions[pair[0]] = pair[1].replace('\r', '\n');
            //fOptions[pair[0]] = QString::fromLocal8Bit(pair[1]).replace('\r', '\n');
    }
}

int alEqRecord::update() 
{
    primeUpdateInsert();
    fRecord->setValue("name", fName);
    fRecord->setValue("type", fType);
    fRecord->setValue("enabled", fEnabled ? "TRUE" : "FALSE");
    QString sOpt = "";
    for(int i=0;i<(int)fOptions.keys().count();i++)
	sOpt += fOptions.keys()[i] + "=" + fOptions.values()[i].replace('\n', '\r') + "\n";
//    qDebug(sOpt.utf8());
    QByteArray a = QByteArray(sOpt.toLocal8Bit());
    fRecord->setValue("options", a);
    return alDataRecord::update();
}

//TODO reimplement
bool alEqRecord::dialog(QWidget * parent)
{
//    dlgDevice * dlg = new dlgDevice(parent);
//    dlg->init(fData->engine());
//    dlg->setData(this);
//    if(dlg->exec())
//    {
//        update();
//        delete dlg;
//        return TRUE;
//    }
//    delete dlg;
//    return FALSE;
}

QStringList alEqRecord::options()
{
    return fOptions.keys();
}

QString alEqRecord::option(QString optionName)
{
    return fOptions[optionName];
}

void alEqRecord::setOption(QString n, QString v)
{
    fOptions[n] = v;
}
