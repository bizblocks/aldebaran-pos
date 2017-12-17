#include <qobject.h>
#include <qsqldatabase.h>
#include "dataorder.h"
#include "dataordert.h"
#include "engine.h"
#include "worker.h"

#define TNAME "orders"

alDataOrder::alDataOrder(alEngine * e) :
	alData(e, TNAME)
{
    checkTable();
    alData::setName(TNAME, TRUE);    
}

void alDataOrder::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME).size()>0) return;
#ifdef DEBUG    
    qDebug(QObject::tr("creating table orders").utf8());
#endif    
    QString query = Queries::tr("CREATE TABLE orders ("
		    "id int8 NOT NULL, num int8, summtype int2 DEFAULT 1, "
		    "orderdate timestamp, timeopen time, timeclose time, "
		    "status int4,  id_user int8,  checknum int4, "
		    "tablenum int4, guests int2, id_discount int8, "
		    "comment varchar(255), externalcode varchar(50), "
		    "CONSTRAINT id_orders PRIMARY KEY (id)) "
		    "WITHOUT OIDS;");
    fEngine->db()->exec(query);
#ifdef DEBUG
    qDebug(query);
    qDebug(QObject::tr("lastError was %1").arg(fEngine->db()->lastError().text()).utf8());
#endif        
    query = Queries::tr("CREATE INDEX idx_num ON orders (num);"); 
    fEngine->db()->exec(query);
}

QSqlIndex alDataOrder::defaultSort()
{
    return QSqlIndex::fromStringList(QStringList::split(",", "orderdate, num"), this);    
}

Q_ULLONG alDataOrder::unum()
{
    Q_ULLONG unum = 1;
    QString query = Queries::tr("SELECT MAX(num) AS max_num FROM orders");
    QSqlQuery res = fEngine->db()->exec(query);
    if(res.first()) return res.value(0).toULongLong()+1;
    return unum;
}

alOrderRecord * alDataOrder::newDocument()
{
    return alOrderRecord::newDocument(this);
}

alOrderRecord * alDataOrder::select(int uid)
{
    alData::select(Queries::tr("id=%1").arg(uid));
    if(first()) return (alOrderRecord*)current();
    return NULL;
}

alOrderRecord * alDataOrder::selectByNumber(int num)
{
    alData::select(Queries::tr("num=%1").arg(num));
    if(first()) return (alOrderRecord*)current();
    return NULL;    
}

bool alDataOrder::delDocument()
{
    Q_ULLONG id = value("id").toULongLong();
    QString query = Queries::tr("DELETE FROM orders WHERE id=%1").arg(id);
    fEngine->db()->exec(query);    
    return true;        
}

alDataRecord* alDataOrder::current()
{
    return alOrderRecord::current(this);
}

alOrderRecord * alDataOrder::import(importer * imp)
{
    alDataUsers * users = new alDataUsers(fEngine);
    ((alData*)users)->select(Queries::tr("role=%1").arg(3));
    users->first();
    alUserRecord * userService = (alUserRecord*) users->current();    
    impValues values;
    imp->seek(0);
    QString extnum  = imp->value("id").toString();
    int status = imp->value("status").toInt();    
    alOrderRecord * order = NULL;
    if(status && select(Queries::tr("externalcode='%1'").arg(extnum)) && first())  order = (alOrderRecord*)current();
    else order = newDocument();
    order->setExternalCode(extnum);
    order->setStatus(Saved);    
    order->setTable(imp->value("table").toULongLong());
//    int intDT = imp->value("date").toUInt();
    order->setDate(QDate::currentDate());
//    intDT = imp->value("time").toUInt();
    order->setTimeOpen(QTime::currentTime());
    order->setUser(userService);
    order->setGuests(imp->value("guests").toUInt());
    order->setComment(imp->value("comment").toString());
//    order->setUser(userService);
//TODO set client
    order->update();
    alDataOrderTable * table = order->getDocumentTable();
    for(int lineNum=1;lineNum<imp->count();lineNum++)
    {
	imp->seek(lineNum);
	alOrderLine * line = table->newLine();
	alDataGoods * goods = new alDataGoods(engine());
	alGoodsRecord * item = goods->select(imp->value("id_goods").toULongLong());
	if(!item && goods->select(Queries::tr("externalcode='%1'").arg(imp->value("sku_goods").toString().utf8())) && goods->first())
	{
	    item = (alGoodsRecord*)goods->current();
	}
	line->setItem(item);
	line->setAmount(imp->value("amount").toUInt());	
	line->setPrice(imp->value("price").toString().toDouble());		
	line->setSumm(imp->value("sum").toString().toDouble());
	line->setUser(userService);
	line->setPrinted(imp->value("printed").toBool());
    }
    order->update();
    return order;
}

alOrderRecord::alOrderRecord(alData * data) :
	alDataRecord(data)
{
    fDiscount = NULL;
    fData = new alDataOrder(data->engine());
    fData->select(Queries::tr("id=%1").arg(fId));
    if(!fData->first()) fRecord = fData->primeInsert();   
    else fRecord = fData->primeUpdate();
    fDataTable = new alDataOrderTable(fData->engine(), this);
    load();    
}
	
alOrderRecord::alOrderRecord(alData * data, QSqlRecord * rec) :
	alDataRecord(data, rec)
{
    fDiscount = NULL;    
    if(!fRecord) return;
    fDataTable = new alDataOrderTable(fData->engine(), this);
    load();
}

alDataOrderTable * alOrderRecord::getDocumentTable()
{
    return fDataTable;
}

alOrderRecord * alOrderRecord::newDocument(alDataOrder * data)
{
    QSqlRecord * rec = data->primeInsert();
    rec->setValue("id", data->uid());
    alOrderRecord * res = new alOrderRecord(data, rec);
    res->setNum(data->unum());
    res->setDate(QDate::currentDate());
    res->setTimeOpen(QTime::currentTime());
    res->fIsNew = TRUE;
    res->	fUser = data->engine()->currentUser();    
    return res;    
}

int alOrderRecord::update()
{
    int res = 0;
    primeUpdateInsert();
    fRecord->setValue("num", fNum);
    fRecord->setValue("summtype", fSummType);
    fRecord->setValue("status", fStatus);
    fRecord->setValue("orderdate", fDate);
    fRecord->setValue("timeopen", fTimeOpen);    
    fRecord->setValue("timeclose", fTimeClose);
    fRecord->setValue("checknum", fCheckNum);
    fRecord->setValue("tablenum", fTableNum);    
    fRecord->setValue("id_user", fUser->id());
    fRecord->setValue("guests", fGuests);
    fRecord->setValue("comment", fComment);
    fRecord->setValue("externalcode", fExternalCode);    
    if(fDiscount) fRecord->setValue("id_discount", fDiscount->id());
    res = alDataRecord::update();
    if(!res) return res;
    QSqlQuery query(fDataTable->updateQuery(), fData->engine()->db());
//    qDebug(query.lastError().text().utf8());
    return res;
}


void alOrderRecord::load()
{
    fNum = fRecord->value("num").toULongLong();
    fSummType = fRecord->value("summtype").toInt();
    fStatus = (alDataOrder::Status)fRecord->value("status").toInt();
    fDate = fRecord->value("orderdate").toDate();
    fTimeOpen = fRecord->value("timeopen").toTime();
    fTimeClose = fRecord->value("timeclose").toTime();
    fCheckNum = fRecord->value("checknum").toULongLong();
    fTableNum = fRecord->value("tablenum").toInt();
    alDataUsers * users = new alDataUsers(fData->engine());
    fUser = users->select(fRecord->value("id_user").toULongLong());
    alDataDiscount * discount = new alDataDiscount(fData->engine());
    fDiscount = discount->select(fRecord->value("id_discount").toULongLong());
    fGuests = fRecord->value("guests").toUInt();
    fComment = fRecord->value("comment").toString();
    fExternalCode = fRecord->value("externalcode").toString();    
}

double alOrderRecord::total(QString attr)
{
    if(fDataTable)
    {
	QString query = Queries::tr("SELECT SUM(%1) FROM order_table WHERE id_order=%2").arg(attr).arg(id());
	QSqlQuery * sqlQuery = new QSqlQuery(fData->engine()->db());
	if(sqlQuery->exec(query))
	{
	    sqlQuery->first();
	    return sqlQuery->value(0).toDouble();
	}
    }
    return 0;
}

alOrderRecord * alOrderRecord::current(alData * data)
{
    if(!data) return NULL;
    alOrderRecord * res = new alOrderRecord(data);
    return res;
}

void alOrderRecord::printOrder(QString device)
{
    QStringList lst;
    QValueList<int> tabs;    
    alEngine * fEngine = fData->engine();
    alDataOrderTable * orderTab = getDocumentTable();
    
    eqJob * job = fEngine->createPrinterJob(device, "print");
    if(!job)
    {
	fEngine->error(tr("Can't print order"));
	return;
    }
    
    int pw = fEngine->printWidth();
    QString tmp = QString(tr("Order #%1")).arg(num());
    QString str = fEngine->centerString(tmp, pw)+QString("\n");
    str += info() + QString("\n");
    str += QString("").rightJustify(pw, '-') + QString("\n");
    for(int r=0;r<orderTab->count();r++)
    {
	alOrderLine * line = orderTab->getLine(r);
	if(!line->item()) continue;
	if(line->printed()) continue;
	lst << line->itemText();
	lst << QString("%1").arg(line->amount(), 0, 'f', 3);
	tabs << 0 << 5;
	str +=  fEngine->alignStrings(lst, tabs, pw) + QString("\n");
//	qDebug(fEngine->alignStrings(lst, tabs, pw) + QString("\n"));
	lst.clear();
	tabs.clear();
	line->setPrinted(TRUE);
	update();
    }
    str += QString("").rightJustify(pw, '-') + QString("\n");    
    str += "\n\n\n";
    str = str.utf8();    
    job->setData(str);
//    qDebug(str);
    fEngine->processJob(job);
    job = fEngine->createPrinterJob(device, "cut");
    fEngine->processJob(job);    
    job = fEngine->createPrinterJob(device, "beep");
    fEngine->processJob(job);    
}

void alOrderRecord::printBill(QString device)
{
    QValueList<int> tabs;
    QStringList lst;
    alEngine * fEngine = fData->engine();
    alDataOrderTable * orderTab = getDocumentTable();
    
    eqJob * job = fEngine->createPrinterJob(device, "print");
    if(!job)
    {
	fEngine->error(tr("Can't print bill"));
	return;
    }
    int pw = fEngine->printWidth();
    QString str = fEngine->centerString(QString(tr("Bill #%1")).arg(num()), pw)+QString("\n");
    str += info() + QString("\n");
    str += comment() + QString("\n");
    str += QString("").rightJustify(pw, '-') + QString("\n");
    double cal = 0., protein = 0., fat = 0., hc = 0.;
    for(int r=0;r<orderTab->count();r++)
    {
	alOrderLine * line = orderTab->getLine(r);
	if(!line->item()) continue;	
	lst << line->itemText();
	lst << QString("%1").arg(line->amount(), 0, 'f', 3);
	lst << QString("%1").arg(line->price(), 0, 'f', 2);
	lst << QString("%1").arg(line->summ(), 0, 'f', 2);
	tabs << 0 << 5 << 6 << 7;
	str +=  fEngine->alignStrings(lst, tabs, pw) + QString("\n");
	lst.clear();
	tabs.clear();
	if(line->item())
	{
	    hc += line->item()->hydroCarbonat();
	    fat += line->item()->fat();
	    protein += line->item()->protein();
	    cal += line->item()->calories();
	}
    }
    str += QString("").rightJustify(pw, '-') + QString("\n");
    double t = orderTab->total("summ");    
    lst << tr("Total:") << QString("%1").arg(t, 0, 'f', 2);    
    tabs << 0 << 5;
    str += fEngine->alignStrings(lst, tabs, pw) + QString("\n");
    str += QString(tr("Calories: %1\n").arg(cal, 0, 'f', 2));
    str += QString(tr("Hydrocarbonates: %1\n").arg(hc, 0, 'f', 2));    
    str += QString(tr("Fat: %1\n").arg(fat, 0, 'f', 2));        
    str += QString(tr("Protein: %1\n").arg(protein, 0, 'f', 2));            
    str += "\n\n\n";
    str = str.utf8();    
    job->setData(str);
    fEngine->processJob(job);
    job = fEngine->createPrinterJob(device, "cut");
    fEngine->processJob(job);    
}

QString alOrderRecord::info()
{
    QString sGuests = fGuests ? QString("%1").arg(fGuests) : tr("not speciefed");
    return QString(tr("Table #%1 Guests: %2 %3\nOpened: %4 %5 Summ: %6"))
	    .arg(table())
	    .arg(sGuests)
	    .arg(fDiscount ?  QString(tr("Discount: %1")).arg(fDiscount->name()) : QString(""))
	    .arg(date().toString())
	    .arg(timeOpen().toString())
	    .arg(getDocumentTable()->total("summ"), 8, 'F', 2);
}

void  alOrderRecord::setDiscount(alDiscountRecord * d)
{
    if(!d) return;    
    fDiscount = d;    
    if(getDocumentTable()) getDocumentTable()->total("summ");
}

void alOrderRecord::setStatus(alStatus p)
{
    fStatus = p;
    if(fStatus == alDataOrder::Closed) setTimeClose(QTime::currentTime());
}
