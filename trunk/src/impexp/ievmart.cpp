#include <qtimer.h>
#include <qsqldatabase.h>
#include <qsqlcursor.h>
#include <qsqlselectcursor.h>
#include <qtextcodec.h>
#include "ievmart.h"

expVMart::expVMart() :
	exporter()
{
    setName("VMart");
    fTable = 0;    
    fDb = NULL;
    setError(VMART_OK);
}

expVMart::~expVMart()
{    
    fDb = NULL;
}

bool expVMart::open(QString host, int port, QString db, QString user, QString pass, QString prefix)
{
    bool fConnected = FALSE;
    if(!QSqlDatabase::isDriverAvailable("QMYSQL3") || db.isEmpty())
    {
	setError(VMART_SQLDRIVERNOTAVAILABLE);
	emit error();
	return FALSE;    
    }
    setError(VMART_OK);
    fPrefix = prefix;
    fDbName = QString("%1.%2").arg(host).arg(db);
    fDb = QSqlDatabase::addDatabase("QMYSQL3", fDbName);
    if(!fDb)
    {
	setError(VMART_NOTOPENED);
	emit error();
	return FALSE;
    }
    fDb->setDatabaseName(db);
    fDb->setHostName(host);
    fDb->setPort(port);
    if(!fDb->open(user, pass))
    {
	setError(VMART_NOTOPENED);	
	fConnected = FALSE;
	emit error();	
    }
    else
    {
	setError(VMART_OK);	
	fConnected = TRUE;
	emit connected();
    }
    return fConnected;
}

bool expVMart::isOpened()
{
    fDb = QSqlDatabase::database(fDbName);
    if(!fDb || !fDb->isOpen()) 
    {
	setError(VMART_NOTOPENED);
	emit error();
	return FALSE;
    }
    return TRUE;
}

bool expVMart::writeHeader(QVariant header)
{
   headerWritten = FALSE;       
   if(!isOpened()) return FALSE;

   int status = header.toMap()["3"].toInt();
   char statusc = 'C';
   if(status==2)  statusc = 'R';
   else if(status==3) statusc = 'X';
   
   QSqlQuery q(fDb);       
   QString updateQuery = QString("UPDATE %1orders SET order_status='%2' WHERE order_id=%3")
			 .arg(fPrefix).arg(statusc).arg(header.toMap()["2"].toULongLong());       
   if(!q.exec(updateQuery)) return FALSE;
   updateQuery = QString("UPDATE %1order_item SET order_status='%2' WHERE order_id=%3")
		 .arg(fPrefix).arg(statusc).arg(header.toMap()["2"].toULongLong());
   
   headerWritten = q.exec(updateQuery);

   return headerWritten;   
}

bool expVMart::writeTailer(QString)
{
    return isOpened();
}

int expVMart::errorCode()
{
    if(!fDb) return VMART_NOTOPENED;
    int e = fError;
    setError(VMART_OK);
    return e;
}

QString expVMart::errorMsg(int e)
{
    QString res = "";
    switch(e)
    {
    case VMART_OK: res = QObject::tr("No Error"); break;
    case VMART_NOTOPENED: res = QObject::tr("Connection isn't opened"); break;
    case VMART_SQLDRIVERNOTAVAILABLE: res = QObject::tr("Database driver isn't loaded"); break;
    default: res = fDb ? fDb->lastError().text() : tr("Unknown error"); break;
    };
    return res;
}

void expVMart::setError(int e)
{
    fError = e;
    if(e!=VMART_OK) emit(error());
}

bool expVMart::writeValues()
{
    return !isOpened() && headerWritten;
}

QString expVMart::host()
{
    if(!fDb) return "127.0.0.1";
    return fDb->hostName();
}

int expVMart::port()
{
    if(!fDb) return 3306;
    return fDb->port();
}

impVMart::impVMart() :
	expVMart()
{
    fCurrent = -1;
    timer = NULL;
    connect(this, SIGNAL(error()), this, SLOT(close()));
}

bool impVMart::open(QString host, int port, QString db, QString user, QString pass, QString prefix)
{
    if(!expVMart::open(host, port, db, user, pass, prefix))
    {
	setError(VMART_NOTOPENED);	
	emit error();
	return FALSE;
    }
    if(timer) delete timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkNewOrder()));
//to options    
    timer->start(10000);
    return TRUE;
}

bool impVMart::close()
{
    if(timer)
    {
	delete timer;
	timer = NULL;
    }
    if(fDb)
    {
	QSqlDatabase::removeDatabase(fDb);
	fDb = NULL;
	return TRUE;
    }
    return FALSE;
}

void impVMart::checkNewOrder()
{
    if(!isOpened()) return;
    QString orders_users_query = QString("SELECT * FROM %1orders "
					 "LEFT JOIN %1user_info ON %1orders.user_id = %1user_info.user_id "
					 "WHERE %1orders.order_status='P' "
					 "ORDER BY %1orders.order_id");
    orders_users_query = orders_users_query.replace("%1", fPrefix);
    QSqlSelectCursor orders(orders_users_query, fDb);
    if(orders.first())
    {
	qDebug(QString("new order on table %1").arg(fTable));
	setCmd('O');
	values.clear();
	fData.clear();
	values["0"] = orders.value("order_id");
	values["1"] = QVariant(0);
	values["2"] = QVariant(fTable);
	QString comment = QString("%1 %2 %3, %4, %5, %6, %7 %8")
			  .arg(orders.value("last_name").toString())
			  .arg(orders.value("first_name").toString())
			  .arg(orders.value("middle_name").toString())
			  .arg(orders.value("city").toString())
			  .arg(orders.value("address_2").toString())
			  .arg(orders.value("address_1").toString())
			  .arg(orders.value("phone_1").toString())
			  .arg(orders.value("phone_2").toString());
	values["3"] = QVariant(0);
//to options	
	values["4"] = QTextCodec::codecForName("CP-1251")->toUnicode(comment);
	fData["0"] = values;
	QSqlCursor items(QString("%1order_item").arg(fPrefix), TRUE, fDb);
	QSqlIndex id = items.index("order_item_id");
	items.select(QString("order_id=%1").arg(values["0"].toInt()), id);
	if(items.first()) do
	{
	    values.clear();
	    values["0"] = items.value("order_item_sku");
	    values["1"] = items.value("product_quantity");
	    values["2"] = items.value("product_final_price");
	    values["3"] = values["1"].toDouble() * values["2"].toDouble();
	    values["4"] = QVariant(0);
	    values["5"] = items.value("order_item_sku");
	    fData[QString("%1").arg(fData.count())] = values;
	} while(items.next());	
	emit hasData();
    };
}

bool impVMart::seek(int row)
{
    if(row<0 || (uint)row>=fData.count()) return FALSE;
    fields.clear();
    if(fCmd=='O')
    {	
	if(!row) fields << "id"  << "status" << "table" << "client_id" << "comment";
	else fields << "id_goods" << "amount" << "price" << "sum" << "printed" << "sku_goods";
    }
    fCurrent = row;
    return TRUE;
}

QVariant impVMart::value(QString name)
{
    if(fCurrent<0 || (uint)fCurrent>=fData.count()) return QVariant();
    int index = fields.findIndex(name);
    if(index<0) return QVariant();
//    qDebug(QString("%1=%2").arg(name).arg(fData[QString("%1").arg(fCurrent)][QString("%2").arg(index)].toString()));
    return fData[QString("%1").arg(fCurrent)][QString("%2").arg(index)];
}

map impVMart::toMap()
{
    map res;
    if(fCurrent<0 || (uint)fCurrent>=fData.count()) return res;
    for(uint index=0;index<fields.count();index++)
	res[fields[index]] = fData[fData.keys()[fCurrent]][QString("%1").arg(index)];
    return res;
}
