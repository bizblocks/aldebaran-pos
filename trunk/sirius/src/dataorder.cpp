#include "sirius.h"

sDataOrder::sDataOrder(sirius * s) : 
	QObject(s, "sDataOrder")
{
	fId = date = time = status = id_client = guests = 0;
	fSirius = s;
	saved = FALSE;
	checkTable();
	init();
}

sDataOrder::~sDataOrder()
{
}

void sDataOrder::checkTable()
{
	if(!fSirius) return;
	QString query = "CREATE TABLE IF NOT EXISTS horders("
			"id NUMERIC PRIMARY KEY, date NUMERIC, time NUMERIC, "
			"status NUMERIC, id_client NUMERIC, guests NUMERIC"
			")";	
	sDataCursor * cursor = fSirius->db()->exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
	query = "CREATE TABLE IF NOT EXISTS torders("
			"id_horders NUMERIC, rowid NUMERIC, "
			"id_goods NUMERIC, amount NUMERIC, price REAL, sum REAL"
			")";
	cursor = fSirius->db()->exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
}

void sDataOrder::init()
{
	buf.clear();
	filter.clear();
	filter << "";
	sort.clear();
	sort << "date ASC";
	sort << "time ASC";
}

void sDataOrder::select(Q_UINT32 id)
{
	if(!fSirius) return;
	sDataCursor * cursor = fSirius->db()->select("horders", QString("id=%1").arg(id), "");
	if(cursor)
	{
		cursor->first();
		fId = cursor->value("id").toUInt();
		date = cursor->value("date").toUInt();
		time = cursor->value("time").toUInt();
		status = cursor->value("status").toUInt();
		id_client = cursor->value("id_client").toUInt();
		guests = cursor->value("guests").toUInt();
		saved = TRUE;
		delete cursor;		
	}
}

void sDataOrder::newOrder()
{
	if(!fSirius) return;
	fId = fSirius->db()->uid("horders");
	QString query = QString("INSERT OR REPLACE INTO horders (id, date, time, status, id_client, guests) "
			"VALUES(?1, ?2, ?3, ?4, ?5, ?6)");
		
	sDataCursor * cursor = fSirius->db()->exec(query);	
	if(cursor)
	{
		cursor->bindValue(1, (ulong)fId);
		cursor->bindValue(2, (ulong)date2int(QDate::currentDate()));
		cursor->bindValue(3, (ulong)time2int(QTime::currentTime()));
		cursor->bindValue(4, (ulong)0);
		cursor->bindValue(5, (ulong)0);
		cursor->bindValue(6, (ulong)1);
		cursor->step();
		delete cursor;
		select(fId);		
	}
	else
	{
		fId = 0;	
		qDebug(fSirius->db()->lastErrorText());
	}
	saved = FALSE;
}

int sDataOrder::addItem(sDataCursor * item)
{
	if(saved)
	{
		fSirius->information(_u("Новый заказ возможен после оплаты текущего!!"));		
		return -1;
	}
	int amount = 1;
	int row = -1;
	for(uint r=0;r<buf.count();r++)
	{
		if(buf[r]["id_goods"].toUInt()==item->value("id").toUInt() && buf[r]["saved"].toUInt()!=1)
		{
			row = r;
			amount = buf[r]["amount"].toUInt() + 1;
			break;
		}
	}
	sOrderLine line;
	line["id_goods"] = item->value("id").toUInt();
	line["amount"] = amount;
	line["price"] = item->value("price").toDouble();
	line["sum"] = amount * line["price"].toDouble();
	line["saved"] = 0;
	line["hydrocarbonat"] = amount * item->value("hydrocarbonat").toDouble();
	line["fat"] = amount * item->value("fat").toDouble();
	line["protein"] = amount * item->value("protein").toDouble();
	line["calories"] = amount * item->value("calories").toDouble();
	if(row!=-1) buf[row] = line;
	else
	{
		buf.append(line);
		row = buf.count()-1;
	}
	emit rowChanged(row);
	return row;
}

void sDataOrder::selectRows()
{	
	buf.clear();
	sDataCursor * table = fSirius->db()->select("torders", QString("id_horders=%1").arg(fId), "rowid ASC");
	if(table)
	{
		if(table->first())do
		{
			QStringList columns(table->columns());			
			int line = -1;
			sDataCursor * goods = fSirius->dataGoods()->select(table->value("id_goods").toUInt());
			if(saved)
			{
				saved = FALSE;
				if(goods->first()) line = addItem(goods);
				saved = TRUE;
			}
			else if(goods->first()) line = addItem(goods);
			if(goods) delete goods;
			if(line==-1) return;
			for(uint c=0;c<columns.count();c++) buf[line][columns[c]] = table->value(columns[c]);
			buf[line]["saved"] = 1;
			emit rowChanged(buf.count()-1);
		}while(table->next());
		delete table;
	}
}

QVariant sDataOrder::tableValue(int row, QString name)
{
	if((uint)row>=buf.count()) return QVariant();
	if(name=="rowid") return row;
	return buf[row][name];
}

double sDataOrder::total(QString field)
{
	double res = 0.0;
	for(uint row=0;row<buf.count();row++)
	{
		res+=buf[row][field].toDouble();
	}
	return res;
}

void sDataOrder::save()
{	
	QString query = QString("DELETE FROM torders WHERE id_horders=%1").arg(fId);
	sDataCursor * cursor = fSirius->db()->exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
	
	for(uint row=0;row<buf.count();row++)
	{
		query = QString("INSERT OR REPLACE INTO torders (id_horders, rowid, id_goods, amount, price, sum) "
				"VALUES(?1, ?2, ?3, ?4, ?5, ?6)");
		cursor = fSirius->db()->exec(query);
		if(cursor)
		{
			cursor->bindValue(1, (ulong)fId);
			cursor->bindValue(2, (ulong)row);
			cursor->bindValue(3, (ulong)buf[row]["id_goods"].toUInt());
			cursor->bindValue(4, (ulong)buf[row]["amount"].toUInt());
			cursor->bindValue(5, buf[row]["price"].toDouble());
			cursor->bindValue(6, buf[row]["sum"].toDouble());
			cursor->step();
			delete cursor;
		}
	}
}

void sDataOrder::kill()
{
	QString query = QString("DELETE FROM torders WHERE id_horders=%1").arg(fId);
	sDataCursor * cursor = fSirius->db()->exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
	query = QString("DELETE FROM horders WHERE id=%1").arg(fId);
	cursor = fSirius->db()->exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}	
}

void sDataOrder::incdec(int row, int sign)
{
	if((uint)row>=buf.count()) return;
	if(buf[row]["saved"].toUInt()==1)
	{
		fSirius->information(_u("Извините, данная позиция сохранена и не может быть изменена!!"));
		return;
	}
	double oAmount = buf[row]["amount"].toUInt();
	buf[row]["amount"] = buf[row]["amount"].toUInt() + sign;
	buf[row]["sum"] = buf[row]["amount"].toUInt() * buf[row]["price"].toDouble();
	if(oAmount)
	{
		buf[row]["hydrocarbonat"] = buf[row]["amount"].toUInt() * buf[row]["hydrocarbonat"].toDouble()/oAmount;
		buf[row]["fat"] = buf[row]["amount"].toUInt() * buf[row]["fat"].toDouble()/oAmount;
		buf[row]["protein"] = buf[row]["amount"].toUInt() * buf[row]["protein"].toDouble()/oAmount;
		buf[row]["calories"] = buf[row]["amount"].toUInt() * buf[row]["calories"].toDouble()/oAmount;
	}
	if(!buf[row]["amount"].toUInt())
	{
		emit rowChanged(row);	
		buf.remove(buf.at(row));
	}
	else emit rowChanged(row);	
}

void sDataOrder::inc(int row)
{
	incdec(row, +1);
}

void sDataOrder::dec(int row)
{
	incdec(row, -1);
}

