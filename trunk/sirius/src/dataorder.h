#ifndef DATAORDER_H
#define DATAORDER_H

#include <qobject.h>
#include <qmap.h>

class sirius;
class sDataCursor;

typedef QMap<QString, QVariant> sOrderLine;
typedef QValueList<sOrderLine> sOrderTable;

class sDataOrder : public QObject
{
	Q_OBJECT
public:
	sDataOrder(sirius * s);
	~sDataOrder();
public:
	void init();
	int select();
	void select(Q_UINT32 id);
//	bool first();
//	bool next();
//	int select(QString filter, QString sort);
	QVariant value(QString name);
	QVariant tableValue(int row, QString name);
	double total(QString field);	
	void newOrder();
	int addItem(sDataCursor * item);
	void selectRows();
	void save();
	void kill();
	Q_UINT32 date, time, status, id_client, guests;
	inline Q_UINT32 id() { return fId; };
	inline Q_UINT32 rowCount() { return buf.count(); };
public slots:
	void inc(int row);
	void dec(int row);
signals:
	void rowChanged(int r);
protected:
	void checkTable();
	void incdec(int row, int sign);
private:
	sirius * fSirius;
	sOrderTable buf;
	QStringList filter;
	QStringList sort;
	Q_UINT32 fId;
	bool saved;
};

#endif
