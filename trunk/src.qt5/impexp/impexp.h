#ifndef IMPEXP_H
#define IMPEXP_H

#include <qobject.h>
#include <qstringlist.h>
#include <qmap.h>
#include <qvariant.h>
#include <qiodevice.h>

class QTextCodec;

typedef QMap<QString, QVariant> map;
typedef QMap<QString, map> impValues;

class importer : public QObject
{
    Q_OBJECT
public:  
    static importer * createImporter(QString name);
    virtual ~importer() {};
    static QStringList importersList();
    virtual int count() { return lines.count(); };
    virtual bool seek(int row) { if(row<count()) fCurrent = row;  return row<count(); };
    virtual int current() { return fCurrent; };
    virtual bool open(QString filename) = 0;
//    virtual bool open(QIODevice * device) = 0;
    virtual bool close() = 0;
    virtual QVariant value(QString name) = 0;
    void setCodepage(QString cp);
    virtual map toMap() = 0;
    int cmd() { return fCmd; };
    void setCmd(int cmd) { fCmd = cmd; };
    void setData(impValues data) { fData = data; };
    
    virtual int errorCode() = 0;
    virtual QString errorMsg(int e) = 0;
    virtual bool isOpened() = 0;
    
protected:
    QString fCodepage;
    QTextCodec * fCodec;
    int fCurrent;
    QStringList lines;
    QStringList fields;
    map values;
    int fCmd;
    impValues fData;    
    importer();
};

class exporter : public importer
{
    Q_OBJECT
public:
    static exporter * createExporter(QString name);
    virtual ~exporter();
    static QStringList exportersList();    
    virtual bool fromMap(map) = 0;
    virtual bool setValue(QString name, QVariant value);
    virtual bool writeValues() = 0;
    virtual bool writeHeader(QString) = 0;
    virtual bool writeTailer(QString) = 0;
    virtual bool close() = 0;    
protected:
    exporter();
    bool headerWritten;    
};

class ieServer : public QObject
{
    Q_OBJECT
public:
    ieServer(QObject * p);
    ~ieServer();
    virtual bool start();
    virtual bool stop();
    virtual bool abort();
    virtual bool restart();
    virtual bool isRunning() { return fIsRunning; };
signals:
    void hasData(importer *);
protected:
    bool fIsRunning;
    int cmd, fields;
    AUINT32 size;
    impValues tab;
    map line;
    importer* fImporter;
};

typedef exporter ieImpExp;

#endif
