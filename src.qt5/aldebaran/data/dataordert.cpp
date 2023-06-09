#include <math.h>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include "engine.h"

#define TNAME "order_table"

alDataOrderTable::alDataOrderTable(alEngine  * engine, alOrderRecord * order) :
	alData(engine, TNAME)
{
    fOrder = order;
    checkTable();
    //alData::setName(TNAME, TRUE);
    lines.clear();
}

bool alDataOrderTable::checkTable()
{
    if(alData::checkTable(TNAME))
        return true;
#ifdef DEBUG    
    qDebug() << QObject::tr("creating table orders").toUtf8();
#endif    
    QString query = Queries::tr("CREATE TABLE order_table ("
		    "id_order int8 NOT NULL, ln int8 NOT NULL,"
		    "id_goods int8, externalcode varchar(15), amount numeric(8,3),"
		    "price numeric(12,2), summ numeric(15,2), id_user int8,"
		    "printed bool,"		    
		    "CONSTRAINT id_ordertable PRIMARY KEY (id_order,ln))"
		    "WITHOUT OIDS;");
    engine()->db().exec(query);
#ifdef DEBUG
    qDebug() << query;
    qDebug() << QObject::tr("lastError was %1").arg(engine()->db().lastError().text()).toUtf8();
#endif        
//    query = "CREATE INDEX idx_num ON orders (num);"; 
//    engine()->db()->exec(query);
    return true;
}

bool alDataOrderTable::select()
{
    lines.clear();
    alData::select(Queries::tr("id_order=%1").arg(fOrder->id()));
    if(first()) do
    {
	alOrderLine * rec = new alOrderLine(this);
	lines.append(rec);
    }while(next());
    else return FALSE;
    return TRUE;
}

//TODO reimplement
QSqlIndex alDataOrderTable::defaultSort()
{
    //return QSqlIndex::fromStringList(QStringList::split(",", "ln"), this);
}

alOrderLine * alDataOrderTable::getLine(int row)
{
    seek(row);
    return lines[row];
}

alOrderLine * alDataOrderTable::newLine()
{
    alOrderLine * rec = alOrderLine::newLine(this);
    lines.append(rec);
    return rec;
}

QString alDataOrderTable::updateQuery()
{
    QString query = Queries::tr("DELETE FROM order_table WHERE id_order=%1;\n").arg(fOrder->id());
    for(int r=0;r<(int)lines.count();r++)
    {
	alOrderLine * line = getLine(r);
	query+=Queries::tr("INSERT INTO order_table VALUES (%1, %2, %3, '%4', %5, %6, %7, %8, %9);\n")
	       .arg(fOrder->id())
	       .arg(r+1)
	       .arg(line->item() ? line->item()->id() : 0)
	       .arg(line->externalCode())
	       .arg(line->amount())
	       .arg(line->price())
	       .arg(line->summ())
	       .arg(line->user() ? line->user()->id() : 0)
	       .arg(line->printed() ? "TRUE" : "FALSE");
    }	
    return query;
}

bool alDataOrderTable::delLine(int r)
{
    if(r>(int)lines.count()-1 ||  r<0)
        return FALSE;
    lines.removeAt(r);
    return TRUE;
}

int alDataOrderTable::count()
{
    return lines.count();
}

double alDataOrderTable::total(QString attr)
{
    double res = 0;
    for(int r=0;r<count();r++)
    {
	alOrderLine * line = lines[r];
	line->recalc();
	res+=line->value(attr).toDouble();
    }
    return res;
}

alOrderLine::alOrderLine(alDataOrderTable * data)
{
    fData = data;
    fOrderID = data->orderId();
    fLineNum = data->count()+1;
    setUser((new alDataUsers(data->engine()))->select(data->value("id_user").toULongLong()));    
    setItem((new alDataGoods(data->engine()))->select(data->value("id_goods").toULongLong()));
    setExternalCode(data->value("externalcode").toString());
    setAmount(data->value("amount").toDouble());
    setPrice(data->value("price").toDouble());
    setSumm(data->value("summ").toDouble());
    setPrinted(data->value("printed").toBool());
}

alOrderLine * alOrderLine::newLine(alDataOrderTable * data)
{
    alOrderLine * line = new alOrderLine(data);
    line->fOrderID = data->orderId();
    line->fLineNum = data->count()+1;
    line->setUser(NULL);
    line->setExternalCode("");
    line->setItem(0);
    line->setAmount(0);
    line->setPrice(0);
    line->setSumm(0);
    line->setPrinted(FALSE);
    return line;    
}

void alOrderLine::setItem(alGoodsRecord * item) 
{ 
    fItem = item;
    if(fItem)
    {
	fItemText = fItem->name();
	fExternalCode = fItem->externalCode();
	if(fPrice==0.) fPrice = fItem->price();
    }
    else
    {
	fExternalCode = "";
	fItemText = "<...>";
	fPrice = 0;
    }
    fAmount++;
    recalc();
}

void alOrderLine::recalc()
{
    fSumm = fAmount * fPrice;
    alDiscountRecord * discount = NULL;
    if(fData && fData->order() && (discount = fData->order()->discount()))
    {
	if(discount->type()==0)
	{
	    double value =discount->value();
        if(fItem)
            value = fItem->maxDiscount()<value ? fItem->maxDiscount() : value;
	    fSumm *= 1. - value/100.;
        qDebug() << QString("before floor %1").arg(fSumm, 7, 'f', 2);
	    if(floor(fSumm)<fSumm)
	    {
            fSumm = floor(fSumm)+1;
	    }
	}
	else
	{
	    //TODO handy discounts ??
//	    fSumm -= fSumm * (1 - discount->value()/100);	
	}
    } else return;
}
