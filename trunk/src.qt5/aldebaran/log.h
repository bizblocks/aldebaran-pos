#ifndef ALLOG_H
#define ALLOG_H

#include <qobject.h>
#include <qstring.h>
#include <qfile.h>

#define ALLOG(msg) alLog::log("L:"+QString(__FILE__) + ":" + QString("%1").arg(__LINE__) + ":"+msg);
#define ALDEBUG(msg) alLog::debug("D:"+QString(__FILE__) + ":" + QString("%1").arg(__LINE__) + ":"+msg);
#define ALERROR(msg) alLog::error("E:"+QString(__FILE__) + ":" + QString("%1").arg(__LINE__) + ":"+msg);

class alLog
{
public:    
    static void init(char level=1, QString logname="aldebaran");
    static void log(QString);
    static void debug(QString);
    static void error(QString);
    static void done();
private:    
    static void message(QString); 
};

class fileHelper : public QObject
{
Q_OBJECT    
public:    
    fileHelper(QString filename) : QObject() { ffile = new QFile(filename); ffile->open(IO_WriteOnly | IO_Append); };
    ~fileHelper() { delete ffile; };
    QFile * file() { return ffile; }
public slots:    
    void flush();
private:    
    QFile * ffile;
};

#endif
