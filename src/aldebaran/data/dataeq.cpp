#include <qsqldatabase.h>
#include <qbuffer.h>
#include "dataeq.h"
#include "engine.h"
#include "dlgdevice.h"

#define TNAME "equipment"

alDataEq::alDataEq(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    alData::setName(TNAME, TRUE);    
}

alDataEq::~alDataEq()
{
}

void alDataEq::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME).size()>0) return;
    alDBG(QObject::tr("creating table equipment").utf8());
    QString query = Queries::tr("create_equipment");
    fEngine->db()->exec(query);
    alDBG(QObject::tr("lastError was %1").arg(fEngine->db()->lastError().text()).utf8());
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
    Q_ULLONG id = value("id").toULongLong();
    QString query = QString(Queries::tr("DELETE FROM equipment WHERE id=%1")).arg(id);
    fEngine->db()->exec(query);
    return true;
}

alEqRecord::alEqRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    if(!fRecord) return;
    load();
}

alEqRecord * alEqRecord::current(alDataEq * data)
{
    if(!data) return NULL;    
    return new alEqRecord(data, data->primeUpdate());    
}

alEqRecord * alEqRecord::newElement(alDataEq * data)
{
    if(!data) return NULL;
    QSqlRecord * rec = data->primeInsert();
    rec->setValue("id", data->uid());
    alEqRecord * res = new alEqRecord(data, rec);
    res->fIsNew = TRUE;
    return res;        
}

void alEqRecord::load()
{
    fName = fRecord->value("name").toString();
    fType = fRecord->value("type").toString();
    fEnabled = fRecord->value("enabled").toBool();
    QByteArray bOpt = fRecord->value("options").toByteArray();
    QString sOpt(bOpt);
    QStringList slOpt = QStringList::split("\n", sOpt);
    fOptions.clear();
    for(int i=0;i<(int)slOpt.count();i++)
    {
	QStringList pair = QStringList::split("=", slOpt[i]);
//	qDebug(slOpt[i]);
	pair[0] = QString::fromLocal8Bit(pair[0]);
	if(pair.count()==1) fOptions[pair[0]] = ""; //default
	else fOptions[pair[0]] = QString::fromLocal8Bit(pair[1]).replace('\r', '\n');
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
    QByteArray a = QByteArray(sOpt.local8Bit());
    fRecord->setValue("options", a);
    return alDataRecord::update();
}

bool alEqRecord::dialog(QWidget * parent)
{
    dlgDevice * dlg = new dlgDevice(parent);
    dlg->init(fData->engine());
    dlg->setData(this);
    if(dlg->exec())
    {
	update();
	delete dlg;
	return TRUE;
    }
    delete dlg;
    return FALSE;
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
