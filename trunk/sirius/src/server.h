#ifndef SERVER_H
#define SERVER_H

#include <qobject.h>
#include <qserversocket.h>
#include <qcstring.h>
#include <qvariant.h>

class QSocket;
class sirius;
class sServerSocket;

struct sImportValue
{
	QVariant asVariant;
	QByteArray asArray;
};

typedef QValueList<sImportValue> sImportLine;
typedef QValueList<sImportLine> sImportTable;

class sServer : public QObject
{
	Q_OBJECT
public:
	sServer(sirius * s);
	bool start();
	bool stop();
	bool abort();
	bool restart();
	bool isRunning() { return fIsRunning; };
protected slots:
	void readData(QSocket * s);
private:
	bool fIsRunning;
	sServerSocket * server;
	sirius * fSirius;
	Q_UINT32 cmd, fields, size;
	sImportTable tab;
	sImportLine line;
	bool badLine;
};

class sServerSocket : public QServerSocket
{
	Q_OBJECT
public:
	sServerSocket(QObject *);
	virtual void newConnection (int socket);
signals:
	void newConnect();
	void endConnect();
	void readClient(QSocket*);
private slots:
	void emitRead();
	void discardClient();
	void setError(int e);
};


typedef QValueList<QVariant> sExportLine;
#define SIRIUS_OK			100
#define SIRIUS_NOTOPENED		101

class exporter : public QObject
{
	Q_OBJECT
public:
	exporter();
	~exporter();
	bool open(QString host, int port);
	bool fromMap(sExportLine m);
//    bool writeValues();
	bool writeHeader(QString header);
	bool writeTailer(QString tailer);
	int errorCode();
	QString errorMsg(int e);
signals:
	void error();
	void start();
	void step(int);
	void finish();
protected slots:
	void setError(int e);
	void deviceConnected();	
private:
	bool headerWritten;
	QSocket * fSocket;
	int fError;
	struct queueElement
	{
		QString type;
		sExportLine data;
		QVariant varData;
	};
	QValueList<queueElement> queue;	
};

#endif
