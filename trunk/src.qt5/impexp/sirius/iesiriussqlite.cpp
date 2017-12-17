#include <qapplication.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qdir.h>
#include <qprocess.h>
#include "sirius/data.h"
#include "sirius/iesiriussqlite.h"
#include "sirius/iesirius.h"

expSiriusSQLite::expSiriusSQLite() :
	exporter()
{
    fDb = NULL;
}

expSiriusSQLite::~expSiriusSQLite()
{
    close();
}

bool expSiriusSQLite::open(QString path)
{
    fPath = path;
    if(fPath[fPath.length()-1] != '/') fPath += "/";
    fPath = QDir::convertSeparators(fPath);
    QFile(fPath+"sirius.db").remove();
    fDb = sData::openDataBase(fPath+"sirius.db");    
    QDir().mkdir(fPath+"images");
    if(!fDb) return FALSE;
    QString query = "CREATE TABLE IF NOT EXISTS goods("
			"id NUMERIC PRIMARY KEY, parent NUMERIC,"
			"isgroup NUMERIC, name TEXT, description TEXT,"
			"picture TEXT, price DOUBLE,"
			"hydrocarbonat DOUBLE, fat DOUBLE, protein DOUBLE, calories DOUBLE,"
			"inactive NUMERIC"
			")";	
    sDataCursor * cursor = fDb->exec(query);
    if(cursor)
    {
	cursor->step();
	delete cursor;
    }
    return TRUE;
}

bool expSiriusSQLite::close()
{
    if(!fDb) return false;
    delete fDb;
    fDb = NULL;
    return true;
}

QPixmap thumb(QPixmap pic)
{
	QImage img = pic.convertToImage();
	img = img.smoothScale(104, 62);
	pic.convertFromImage(img);
	return pic;
}

bool expSiriusSQLite::fromMap(map m)
{
    if(!fDb) return TRUE;
    sDataCursor * cursor = NULL;    
    QString query = QString("INSERT OR REPLACE INTO goods (id, parent, isgroup, name, description, picture, price, "
			    "hydrocarbonat, fat, protein, calories, inactive) "
			    "VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12)");
    if((cursor = fDb->exec(query)))
    {
	QString pictureName(QString(fPath+"images/%1.png").arg(m["01"].toString()));
	QString thumbPictureName(QString(fPath+"images/%1_thumb.png").arg(m["01"].toString()));
	QString remotePictureName(QString("/usr/share/sirius/data/images/%1.png").arg(m["01"].toString()));
	cursor->bindValue(1, m["01"].toString());
	cursor->bindValue(2, m["02"].toString());
	cursor->bindValue(3, m["03"].toString());
	cursor->bindValue(4, m["04"].toString());
	cursor->bindValue(5, m["05"].toString());
	cursor->bindValue(6, remotePictureName);
	cursor->bindValue(7, m["07"].toString());
	cursor->bindValue(8, m["08"].toString());
	cursor->bindValue(9, m["09"].toString());
	cursor->bindValue(10, m["10"].toString());
	cursor->bindValue(11, m["11"].toString());
	cursor->bindValue(12, m["12"].toString());
	cursor->step();
	delete cursor;
	QPixmap pixmap(m["06"].toByteArray());
	pixmap.save(pictureName, "PNG");
	pixmap = thumb(pixmap);
	pixmap.save(thumbPictureName, "PNG");
    }
    return TRUE;
}

int expSiriusSQLite::errorCode()
{
    if(!fDb) return SIRIUS_NOTOPENED;
    int fError = fDb->lastError();
    if(!fError) fError = SIRIUS_OK;
    return fError;
}

QString expSiriusSQLite::errorMsg(int)
{
    if(!fDb) return QObject::tr("Database not opened");
    return fDb->lastErrorText();
}

bool expSiriusSQLite::writeValues()
{
    return fromMap(values);
}

bool expSiriusSQLite::writeTailer(QString)
{
    QFile(QString("%1/sirius-data.tar.gz").arg(fPath)).remove();    
    QProcess process(QString("tar"));
    process.addArgument("-czf");
    process.addArgument(QString("%1/sirius-data.tar.gz").arg(fPath));
    process.addArgument("-C");      
    process.addArgument(fPath);
    process.addArgument("sirius.db");
    process.addArgument("images");    
    process.start();
    while(process.isRunning())
    {
	qApp->processEvents(100);
    }
    return TRUE;
}
