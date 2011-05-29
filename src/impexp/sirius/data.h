#ifndef DATA_H
#define DATA_H

#include <qobject.h>
#include <qvariant.h>
#include <qmap.h>

#define MAX_RETRY_COUNT	10

struct sqlite3;
struct sqlite3_stmt;
class sirius;
class sDataCursor;

struct sValue
{
	QVariant asVariant;
	QByteArray asArray;
};

typedef QMap<QString, sValue> sDataRow;

class sData : public QObject
{
	Q_OBJECT
public:
	sData();
	static sData * openDataBase(QString filename);
	~sData();
	virtual sDataCursor * exec(QString query);
	sDataCursor * select(QString table, QString filter, QString sort);
	Q_UINT32 uid(QString table);
	sqlite3 * dbf();
	int sleep(int msces);
	bool beginTransaction();
	bool commitTransaction();
protected:
	sData(QString filename);
public slots:
	QString lastQuery() { return fLastQuery; };
	QString lastErrorText();
	int lastError();
private:
	QString fLastQuery;
	QStringList columns;
};

class sDataCursor : public QObject
{
	Q_OBJECT
private:
	sDataCursor(sqlite3 * db);
	bool init();
public:
	~sDataCursor();
	static sDataCursor * createCursor(sqlite3 * db, sqlite3_stmt * stmt);
	bool first();
	bool next();
	bool prev();
	bool last();
	ulong size() { return fSize; };
	ulong pos() { return fPos; };
	QVariant value(QString name);
	QByteArray byteValue(QString name);
	QStringList columns();
	void bindValue(int index, QString val);
	void bindValue(int index, ulong val);
	void bindValue(int index, double val);
	void bindValue(int index, bool val);			
	void bindValue(int index, QByteArray val);
	bool step();
protected:
	bool finalize();
	void fillRow();
private:
	sqlite3 * fSqlite3;
	sDataRow row;
	QValueList<sDataRow> rows;
	ulong fSize;
	ulong fPos;
	QStringList names;
	friend class sData;
	sqlite3_stmt * fStmt;	
};

#endif
