#include <math.h>
#include <qsqldatabase.h>
#include "engine.h"

#define TNAME "order_table"

alDataOrderTable::alDataOrderTable(alEngine  * engine, alOrderRecord * order) :
	alData(engine, TNAME)
{
    fOrder = order;
    checkTable();
    alData::setName(TNAME, TRUE);    
    lines.clear();
}

void alDataOrderTable::checkTable()
{
    if(!fEngine->db()) return;
    QStringList check = fEngine->db()->tables();
    if(check.grep(TNAME).size()>0) return;
#ifdef DEBUG    
    qDebug(QObject::tr("creating table orders").utf8());
#endif    
    QString query = Queries::tr("CREATE TABLE order_table ("
		    "id_order int8 NOT NULL, ln int8 NOT NULL,"
		    "id_goods int8, amount numeric(8,3),"
		    "price numeric(12,2), summ numeric(15,2), id_user int8,"
		    "printed bool,"		    
		    "CONSTRAINT id_ordertable PRIMARY KEY (id_order,ln))"
		    "WITHOUT OIDS;");
    fEngine->db()->exec(query);
#ifdef DEBUG
    qDebug(query);
    qDebug(QObject::tr("lastError was %1").arg(fEngine->db()->lastError().text()).utf8());
#endif        
//    query = "CREATE INDEX idx_num ON orders (num);"; 
//    fEngine->db()->exec(query);    
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

QSqlIndex alDataOrderTable::defaultSort()
{
    return QSqlIndex::fromStringList(QStringList::split(",", "ln"), this);
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
	query+=Queries::tr("INSERT INTO order_table VALUES (%1, %2, %3, %4, %5, %6, %7, %8);\n")
	       .arg(fOrder->id())
	       .arg(r+1)
	       .arg(line->item() ? line->item()->id() : 0)
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
    lines.remove(lines.at(r));
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
	if(fPrice==0.) fPrice = fItem->price();
    }
    else
    {
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
	    if(fItem) value = fItem->maxDiscount()<value ? fItem->maxDiscount() : value;
	    fSumm *= 1. - value/100.;
	    qDebug(QString("before floor %1").arg(fSumm, 7, 'f', 2));
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
