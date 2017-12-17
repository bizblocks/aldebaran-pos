#include <unistd.h>
#include <sqlite3.h>
#include <qvariant.h>
#include "data.h"

static sqlite3 * fDb = NULL;

sqlite3 * sData::dbf()
{
	return fDb;
}

sData * sData::openDataBase(QString filename)
{
	if(fDb) return NULL;
	return new sData(filename);
}

sData::sData(QString filename) :
	QObject(NULL, QString("db%1").arg(filename))
{
	fDb = NULL;	
	sqlite3_open((const char*)filename.utf8(), &fDb);
	if(sDataCursor * cursor = exec("VACUUM"))
	{
		cursor->step();
		delete cursor;
	};
}

sData::sData() :
 	QObject(NULL, QString("NODATABASE"))
{
	fDb = NULL;
}

sData::~sData()
{
    if(fDb) sqlite3_close(fDb);
    fDb = NULL;
}

sDataCursor * sData::exec(QString query)
{
    if(!fDb) return NULL;
    const char * pszTail = NULL;
    sDataCursor * cursor = new sDataCursor(fDb);
    int res = sqlite3_prepare_v2(fDb, query.utf8(), -1, &cursor->fStmt, &pszTail);
    fLastQuery = query;
    if(res == SQLITE_OK) return cursor; 
    return NULL;
}

sDataCursor * sData::select(QString table, QString filter, QString sort)
{
    if(!fDb) return NULL;
    QString query = QString("SELECT * FROM %1").arg(table);
    if(!filter.isEmpty()) query += QString(" WHERE %1").arg(filter);
    if(!sort.isEmpty()) query += QString(" ORDER BY %1").arg(sort);
    return exec(query);
}

QString sData::lastErrorText()
{
    if(!fDb) return "База данных не открыта.";
    QString res = sqlite3_errmsg(fDb);
    return res;
}

int sData::lastError()
{
	if(!fDb) return -1;
	return sqlite3_errcode(fDb);
}

Q_UINT32 sData::uid(QString table)
{
	Q_UINT32 res = 0;
	QString query = QString("SELECT MAX(id) AS max_id FROM %1").arg(table);
	sDataCursor * cursor = exec(query);
	if(cursor)
	{
		cursor->step();
		res = sqlite3_column_int64(cursor->fStmt, 0);
		delete cursor;
	}
	return res+1;
}

int sData::sleep(int msecs)
{
	return sqlite3_sleep(msecs);
}

bool sData::beginTransaction()
{
	QString query = "BEGIN TRANSACTION";
	sDataCursor * cursor = exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
	else return FALSE;
	return TRUE;
}

bool sData::commitTransaction()
{
	QString query = "COMMIT TRANSACTION";
	sDataCursor * cursor = exec(query);
	if(cursor)
	{
		cursor->step();
		delete cursor;
	}
	else return FALSE;
	return TRUE;
}

sDataCursor::sDataCursor(sqlite3 * db) : 
	QObject(NULL, "dataCursor"),
	fSqlite3(db),
	fStmt(NULL)
{
	fSize = 0;
	fPos = -1;
	rows.clear();
	row.clear();
}

sDataCursor::~sDataCursor()
{
//	qDebug(QString("%1").arg(sqlite3_errmsg(fSqlite3)));
	finalize();
}

sDataCursor * sDataCursor::createCursor(sqlite3 * db, sqlite3_stmt * stmt)
{
	if(!db) return NULL;
	if(!stmt) return NULL;
	sDataCursor * cursor = new sDataCursor(db);
	cursor->fStmt = stmt;
	return cursor;
}

bool sDataCursor::first()
{
	if(!rows.count()) return init();
	if(!fPos) return TRUE;
	fPos = 0;
	row = rows[fPos];
	return TRUE;
}

bool sDataCursor::next()
{
	if(!rows.count()) return FALSE;
	fPos++;
	if(fPos+1>=rows.count())
	{
		int res = sqlite3_step(fStmt);
		if(res==SQLITE_ROW) fillRow();
		else return FALSE;
	}
	else row = rows[fPos];
	return TRUE;
}

bool sDataCursor::prev()
{
	if(!rows.count()) return FALSE;
	if(!fPos) return FALSE;
	fPos--;
	row = rows[fPos];
	return TRUE;
}

bool sDataCursor::last()
{
	if(!rows.count()) return FALSE;
	if(fPos==fSize-1) return TRUE;
	if(rows.count()==fSize)
	{
		fPos = fSize-1;
		row = rows[fPos];
		return TRUE;
	}
	int res = sqlite3_step(fStmt);
	if(res==SQLITE_ROW) do
	{
		fillRow();
		res = sqlite3_step(fStmt);
	}while(res==SQLITE_ROW);
	fPos = fSize-1;
	return TRUE;
}

void sDataCursor::fillRow()
{
	names.clear();
	row.clear();
	int colCount = sqlite3_column_count(fStmt);
	for(int i=0;i<colCount;i++)
	{
		QString colName(sqlite3_column_name(fStmt, i));
//		qDebug(QString("|%1|").arg(colName));
		int type = sqlite3_column_type(fStmt, i);
		QVariant val;
		uint n, len;
		double d;
		QString str;
		QByteArray ba;
		const unsigned char * buf;
		
		switch(type)
		{
			case SQLITE_INTEGER:
				n = sqlite3_column_int64(fStmt, i);
				val = QVariant(n);
				break;
			case SQLITE_FLOAT:
				d = sqlite3_column_double(fStmt, i);
				val = QVariant(d);
				break;
			case SQLITE_TEXT:
				buf = sqlite3_column_text(fStmt, i);
				len = sqlite3_column_bytes(fStmt, i);
				str = QString((const char*)buf);
				val = QVariant(str);
				break;
			case SQLITE_BLOB:
				buf = (unsigned char*)sqlite3_column_blob(fStmt, i);			
				len = sqlite3_column_bytes(fStmt, i);
//				if(len>1000) qDebug(QString("blob len is %1, 1000th element is %2").arg(len).arg((int)buf[1000]));
				ba.duplicate((const char*)buf, len);
				val = QVariant(ba.data(), len);
				break;
			case SQLITE_NULL:
				val = QVariant(0);
				break;
			default:
				buf = sqlite3_column_text(fStmt, i);			
				len = sqlite3_column_bytes(fStmt, i);
				ba.duplicate((const char*)buf, len);
				val = QVariant(ba.data(), len);
				break;
		}
		row[colName].asVariant = val;
		row[colName].asArray = ba;
		names << colName;
//		qDebug(colName+" = "+val.toString());
	}
	rows.append(row);
}

bool sDataCursor::init()
{
	int res = SQLITE_OK;
	for(int i=0;i<MAX_RETRY_COUNT;i++)
	{
		res = sqlite3_step(fStmt);
		if(res==SQLITE_DONE)
		{
			break;
		}
		else if(res==SQLITE_ROW)
		{
//			qDebug("sDataCursor::init before fill row");
			fillRow();
//			qDebug("sDataCursor::init after fill row");			
			break;
		}
		else if(res==SQLITE_BUSY)
		{
			sqlite3_busy_timeout(fSqlite3, 1000);
			continue;
		}
		else
		{
			qDebug(QString(sqlite3_errmsg(fSqlite3)));
			break;
		}
	}
	return res==SQLITE_ROW;
}

QVariant sDataCursor::value(QString name)
{
//	qDebug(QString("%1=%2").arg(name).arg(row[name].toString()));
	return row[name].asVariant;
}

QByteArray sDataCursor::byteValue(QString name)
{
	return row[name].asArray;
}

QStringList sDataCursor::columns()
{
	return names;
}

void sDataCursor::bindValue(int index, QString val)
{
	if(!fStmt) return;
	sqlite3_bind_text(fStmt, index, (const char*)val.utf8(), -1, SQLITE_TRANSIENT);
}

void sDataCursor::bindValue(int index, ulong val)
{
	if(!fStmt) return;
	sqlite3_bind_int(fStmt, index, val);
}

void sDataCursor::bindValue(int index, double val)
{
	if(!fStmt) return;
	sqlite3_bind_double(fStmt, index, val);
}

void sDataCursor::bindValue(int index, bool val)
{
	if(!fStmt) return;
	sqlite3_bind_int(fStmt, index, val);
}

void sDataCursor::bindValue(int index, QByteArray val)
{
	if(!fStmt) return;
	sqlite3_bind_blob(fStmt, index, val.data(), val.size(), SQLITE_TRANSIENT);
}

bool sDataCursor::step()
{
	if(!fStmt) return FALSE;
	int res = sqlite3_step(fStmt);
	return res==SQLITE_DONE || res==SQLITE_ROW;
}

bool sDataCursor::finalize()
{
	if(!fStmt) return FALSE;	
	sqlite3_clear_bindings(fStmt);	
	int res = sqlite3_finalize(fStmt);
	fStmt = NULL;
	return res==SQLITE_OK;
}

