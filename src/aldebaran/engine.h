/****************************************************************************
**
** Framework for Aldebaran Application
**
** Created : 20070722
**
** Copyleft
** Author: Sokolov Anton (a.sokolov at artel-gnu.org)
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
**
**********************************************************************/
#ifndef ENGINE_H
#define ENGINE_H

#include <qobject.h>
#include <qvariant.h>
#include <qmap.h>
#include <qintdict.h>

#include "errors.h"
#include "data/dataordert.h"
#include "data/dataorder.h"
#include "data/datagoods.h"
#include "data/datausers.h"
#include "data/datarights.h"
#include "data/dataeq.h"
#include "data/datadiscount.h"
#include "data/datapictures.h"
#include "data/queries.h"
#include "datatable.h"
#include "htmltemplate.h"
#include "rights.h"
#include "valuetable.h"

class QApplication;
class QStringList;
class QSqlDatabase;
class QFtp;
class alMainWindow;
class alSettings;
class eqWorker;
class eqJob;
class alGoodsRec;
class sServer;

typedef QMap<QString, QVariant> alValueList;

// settings section defines
#define GENERAL "general"
#define EQUIPMENT "equipment"

// GENERAL settings
#define TABLENUM "tablenum"
#define SHEMA "shema"
#define USESHEMA "useshema"
#define IMPEXPCP "impexpcp"
#define IMPEXPFMT "impexpformat"
#define IMPEXPPATH "impexppath"
#define IMPEXPIMPORT "impexpimport"
#define IMPEXPEXPORT "impexpexport"
#define TPLORDER "ordertemplate"
#define TPLBILL "billtemplate"
#define IMPEXPFTP "useftp"
#define IMPEXPFTPHOST "ftphost"
#define IMPEXPFTPPORT "ftpport"
#define IMPEXPFTPLOGIN "ftplogin"
#define IMPEXPFTPPASSWORD "ftppassword"
#define IMPEXPFTPRDIR "ftprdir"
//EQUIPMENT settings
#define PRINTER "defaultprinter"
#define ECR "defaultecr"

#define YES QMessageBox::Yes
#define NO QMessageBox::No
#define RETRY QMessageBox::Retry
#define IGNORE QMessageBox::Ignore
#define ABORT QMessageBox::Abort
#define AL_NOT_IMPLEMENTED QMessageBox::information(0, "aldebaran", tr("not implemented"));

#define EVENT_MSCREADER		1
#define EVENT_BARCODEREADER		2

class alEngine : public QObject
{
Q_OBJECT
public:
    alEngine(int argc, char ** argv);
    ~alEngine();
    virtual int start();
    bool startTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    alUserRecord * currentUser() { return fCurrentUser; };
    void setCurrentUser(alUserRecord* u);
    QStringList driverList();
    eqJob * createPrinterJob(QString device, QString action);
    eqJob * createECRJob(QString device, QString action);    
    int printWidth();
    QString centerString(QString str, int iWidth);
    QString alignStrings(QStringList lst, QValueList<int> tabs, int iWidth);
    QFtp * ftpput(QString host, int port, QString login, QString password, const QFile& local, QString remotefile);
    QFtp * ftpget(QString host, int port, QString login, QString password, QString remote, const QFile& local);
protected:
    virtual void init();
public slots: 
    virtual QSqlDatabase * db();
    alValueList settingsFor(QString subSystem);
    QVariant parameter(QString sub, QString key);
    void settingsDialog();
    void eqDialog();
    void openOrder(int num);
    double calculator(double initVal=0.);
    alOrderRecord * tableOrder(int num);
    bool loginLock();
    void startImport();
    void import(bool stop=FALSE);
    void exportSales(int type, QDateTime begin, QDateTime end);
    void error(QString err);
    void exportOrder(alOrderRecord * order);
    bool exportGoods(QString device);
    bool prepareGoods(QString deviceType);
    void sendElement(alGoodsRecord * rec);
    bool resetDevice(QString device);
    bool updateDevice(QString device);
    bool shutdownDevice(QString device);
    bool connectDevice(QString device);
    void importData(importer * imp);
    void zReport();
    void xReport();
    void payin();
    void payout();
    void onError(int errorCode);
    alValueList processJob(eqJob *);
    void cancelCheque(QString devName);    
    alValueList cheque(QString devName, alValueTable, alValueTable);
    void advancedReport(int period, int type, QDateTime begin, QDateTime end);
//    QString errMsg(int err);
protected slots:
    void initTables();        
    void initUsers();
    void initEquipment();
    virtual void exitApp();
    void readerData(int, QString);
    void barcodeReaderData(QString);
    void endFTPExport(int id, bool error);
    QStringList advReportGoods(int period, QDateTime begin, QDateTime end);
    QStringList advReportHourly(int period, QDateTime begin, QDateTime end);
    QStringList advReportCheques(int period, QDateTime begin, QDateTime end);
    QStringList advReportDiscounts(int period, QDateTime begin, QDateTime end);
signals:
    void initialized();
    void settingsChanged();
    void event(int type, QVariant data);
private:
    QApplication * app;
    alMainWindow * mainWindow;
    alSettings * settings;
    QSqlDatabase * fDB;
    bool dbInited;
    alUserRecord * fCurrentUser;
    alDataOrder * fOrders;
    eqWorker * fWorker;
    sServer * server;
};    

QByteArray pixmap2bytearray(QPixmap);
QPixmap bytearray2pixmap(QByteArray);

QDate int2date(int days);
QTime int2time(int secs);
int date2int(QDate);
int time2int(QTime);

#endif
