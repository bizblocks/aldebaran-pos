#include <qdir.h>
#include <qtextstream.h>
#include <qtimer.h>
#include "log.h"

QTextStream * logFile = NULL;
QTimer * timer = NULL;
fileHelper * file = NULL;
char logLevel = 3;

void alLog::init(char level, QString logname)
{
    logLevel = level;
    QString filename = QString(QDir::homeDirPath())+QString("/.aldebaran/%1.log").arg(logname);
    file = new fileHelper(filename);
    logFile = new QTextStream();
    logFile->setDevice(file->file());
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), file, SLOT(flush()));
    timer->start(10000);
    ALLOG(QObject::tr("log started"));
}

void alLog::log(QString msg)
{
    if(logLevel>0) message(msg);
}

void alLog::error(QString msg)
{
    if(logLevel>1) message(msg);
}

void alLog::debug(QString msg)
{
    if(logLevel>2) message(msg);
}

void alLog::message(QString msg)
{
    if(logFile) (*logFile) << msg << endl;
}

void alLog::done()
{
    ALLOG(QObject::tr("log finished"));    
    file->flush();
    if(logFile) logFile->unsetDevice();
    if(timer) delete timer;    
    if(file) delete file;
    if(logFile) delete logFile;
}

void fileHelper::flush() 
{
    ffile->flush(); 
}
