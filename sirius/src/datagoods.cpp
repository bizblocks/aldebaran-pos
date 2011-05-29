#include <qpixmap.h>
#include "sirius.h"
#include "datagoods.h"

sDataGoods::sDataGoods(sirius * s) : 
	QObject(s, "sDataGoods")
{
	fSirius = s;
	checkTable();
	init();
}

void sDataGoods::checkTable()
{
	if(!fSirius) return;
	QString query = "CREATE TABLE IF NOT EXISTS goods("
			"id NUMERIC PRIMARY KEY, parent NUMERIC,"
			"isgroup NUMERIC, name TEXT, description TEXT,"
			"picture TEXT, price DOUBLE,"
			"hydrocarbonat DOUBLE, fat DOUBLE, protein DOUBLE, calories DOUBLE,"
			"inactive NUMERIC"
			")";	
	sDataCursor * cursor = fSirius->db()->exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
	else qDebug(fSirius->db()->lastErrorText());
}

void sDataGoods::init()
{
	filter.clear();
	filter << "parent = 0";
	sort.clear();
	sort << "isgroup DESC";
	sort << "name ASC";
}

sDataGoods::~sDataGoods()
{

}

sDataCursor * sDataGoods::select()
{
	if(!fSirius) return NULL;
	return fSirius->db()->select("goods", filter.join(","), sort.join(","));
}

sDataCursor * sDataGoods::select(QString filter, QString sort)
{
	if(!fSirius) return NULL;
	return fSirius->db()->select("goods", filter, sort);
}

sDataCursor * sDataGoods::select(Q_UINT32 id)
{
	if(!fSirius) return NULL;
	QString filter = QString("id = %1").arg(id);
	return fSirius->db()->select("goods", filter, sort.join(","));
}

void sDataGoods::useParent(Q_UINT32 parent)
{
	filter[0] = QString("parent = %1").arg(parent);
}

/*QVariant sDataGoods::value(QString name)
{
	if(!cursor) return 0;
	return cursor->value(name);
}*/

QPixmap sDataGoods::picture(sDataCursor * cursor)
{
	if(!cursor) return 0;
	QPixmap pic;	
	pic.load(cursor->value("picture").toString(), "PNG");
//	int depth = pic.depth();
//	if(depth) qDebug(QString("picture depth is %1bpp").arg(depth));
	return pic;
}

