#ifndef DATAGOODS_H
#define DATAGOODS_H

#include <qobject.h>
#include <qstringlist.h>
#include <qvariant.h>

class sirius;
class sDataCursor;
class sGoodsRecord;

class sDataGoods : public QObject
{
	Q_OBJECT
public:
	sDataGoods(sirius * s);
	~sDataGoods();
public slots:
	void init();
	void useParent(Q_UINT32 parent);
	sDataCursor * select();
	sDataCursor * select(QString filter, QString sort);
	sDataCursor * select(Q_UINT32 id);
//	bool first();
//	bool next();
//	QVariant value(QString name);
	static QPixmap picture(sDataCursor *);
//	QPixmap preview();	
protected:
	void checkTable();
private:
	sirius * fSirius;
//	sDataCursor * cursor;
	QStringList filter;
	QStringList sort;
};

class sGoodsRecord : public QObject
{
	Q_OBJECT
protected:
	sGoodsRecord(sDataGoods * data);	
public:
	static sGoodsRecord * current();
public slots:
	ulong id() { return fId; };	
	bool isGroup() { return fIsGroup; };
private:
	ulong fId;
	bool fIsGroup;
};

#endif
