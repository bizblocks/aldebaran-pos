#ifndef FELIX_H_
#define FELIX_H_

#include <tecashregisterbase.h>
#include "felix-config.h"

// Replace with actual function call
#define op_warning(a)

// Fiscal operation
#define FOP_SELL 1
#define FOP_SELLRET 2
#define FOP_STORNO 3

// Fiscal document type
#define FDT_SELL 1
#define FDT_SELLRET 2
#define FDT_ANNULATE 2

//const int R_OK=0;
//const int R_FMC12=0x01; // Неисправна ФП1, ФП2 или часы
//const int R_FM1=0x02; // Неисправна ФП1
//const int R_FM2=0x03; // Неисправна ФП2
//const int R_FM_Incorrect_Parm=0x04;
//const int R_NoData=0x05;
//const int R_FM_DataOut=0x06;
//const int R_Incorrect_Parm=0x07;
//const int R_Unsupported=0x08;
//const int R_Wrong_Length=0x09;
//const int R_NoLicense=0x11;
//const int R_SN_AlreadySet=0x12;

/*! /en	Result codes for sendCommand, readData, sendData etc /_en
	/ru Коды завершения функций sendCommand, readData, sendData и т.д. /_ru */
/*!	/en Operation was completed successfully. /_en
	/ru Операция завершена успешно /_ru */
#define RSP_OK 0

/*!	/en Transaction was completed successfully, but device returned command error code
	/ru Передача команды прошла успешно, но устройство вернуло код ошибки. Код ошибки можно получить функцией deviceError(). */
#define RSP_COMMANDERROR 1

/*!	/en	One of read/write operations was timed out. Detailed error info is in errorText(). /_en
	/ru Одна из операций ввода/вывода завершилась с ошибкой таймаута.
		Подробную информацию об ошибке можно получить вызвав функцию errorText(). /_ru */
#define RSP_TIMEOUT 2

/*!	/en Device is going to transmit data /_en
	/ru Устройство находится в режиме передачи данных. Получить данные можно функцией readData(). /_ru */
#define RSP_DATAPENDING 3

/*!	/en	COM port is closed /_en
	/ru COM-порт закрыт /_ru */
#define RSP_PORTCLOSED 4

/*!	/en Buffer size isn't big enough to contain device responce /_en
	/ru Размер предоставленного буфера недостаточен для сохранения
		ответа устройства. В остальном операция завершилась успешно. /_ru */
#define RSP_BUFFEROVERRUN 5

/*!	/en Responce checksum error /_en
	/ru Ошибка контрольной суммы ответа устройства /_ru */
#define RSP_CHECKSUMERROR 6

/*!	/en Responce too short. /_en
	/ru Длина ответа устройства меньше допустимой.
		Возможно аппаратная ошибка при передаче байта длины ответа. /_ru */
#define RSP_RESPONCETOOSHORT 7

/*!	/en	Function needs information of device setting (f.e. number of digits after dot). /_en */
#define RSP_NODEVICEINFO 8

/*!	/en	There was error during function execution. /_en */
#define RSP_INTERNALERROR 9

/*! /en	Driver cannot work with attached device. /_en */
#define RSP_DEVICEUNKNOWN 10

/*!	/en invalid function parameters /_en
	/ru В функцию переданы неверные параметры. Подробнее см. errorText() /_ru */
#define RSP_INVALIDPARAMETERS 100 /* invalid function parameters */

/*!	/en invalid function parameter 1 /_en
	/ru Ошибка в параметре №1. /_ru */
#define RSP_INVALIDPARAMETER1 101

/*!	/en invalid function parameter 2 /_en
	/ru Ошибка в параметре №2. /_ru */
#define RSP_INVALIDPARAMETER2 102

/*!	/en invalid function parameter 3 /_en
	/ru Ошибка в параметре №3. /_ru */
#define RSP_INVALIDPARAMETER3 103

/*!	/en invalid function parameter 4 /_en
	/ru Ошибка в параметре №4. /_ru */
#define RSP_INVALIDPARAMETER4 104

/*!	/en invalid function parameter 5 /_en
	/ru Ошибка в параметре №5. /_ru */
#define RSP_INVALIDPARAMETER5 105

/*!	/en invalid function parameter 6 /_en
	/ru Ошибка в параметре №6. /_ru */
#define RSP_INVALIDPARAMETER6 106

/*!	/en invalid function parameter 7 /_en
	/ru Ошибка в параметре №7. /_ru */
#define RSP_INVALIDPARAMETER7 107

/*!	/en invalid function parameter 8 /_en
	/ru Ошибка в параметре №8. /_ru */
#define RSP_INVALIDPARAMETER8 108

/*! /en Values for FR mode */
#define SHMODE_DATAOUT 			0x01
#define SHMODE_OPENSHIFT 			0x02
#define SHMODE_24HOURSHIFT 			0x03
#define SHMODE_CLOSEDSHIFT 			0x04
#define SHMODE_BADFISCALPASSWORD 		0x05
#define SHMODE_DATECONFIRM 			0x06
#define SHMODE_DOTPOSITION_CHANGEENABLED 	0x07
#define SHMODE_OPENDOC 			0x08
#define SHMODE_TECHRESET 			0x09
#define SHMODE_TESTRUN 			0x0A
#define SHMODE_FULLFISCALREPORT 		0x0B
#define SHMODE_MASK 				0x0F

#define MODE_SELECT		0x00
#define MODE_REGISTRATION	0x01
#define MODE_REPORTS		0x02
#define MODE_REPORTSCLEAN	0x03
#define MODE_PROGRAMMING	0x04
#define MODE_FM		0x05
#define MODE_ECRP		0x06

struct FRState;
struct FRShortState;

enum FRFlags
{
	FR_ControlTapeLoaded=1,
	FR_CheckTapeLoaded=2,
	FR_DocumentSet=4,
	FR_DocumentDetected=8,
	FR_TwoDigitsAfterDot=16,
	FR_ERPTLoaded=32, // Electronic registration protected tape (ERPT)
	FR_ControlTapeSet=64,
	FR_CheckTapeSet=128,
	FR_ControlTapePrintHeadSet=256,
	FR_CheckTapePrintHeadSet=512,
	FR_CoverIsOpened=1024,
	FR_LeftPrintSensorFail=2048,
	FR_RightPrintSensorFail=4096,
	FR_CashBoxIsOpened=8192
};

enum FMFlags
{
	FM_FM1Set=1,
	FM_FM2Set=2,
	FM_Licensed=4,
	FM_Overload=8,
	FM_BatteryLow=16
};

class FELIX_EXPORT FelixRK : public TECashRegisterBase
{
	Q_OBJECT

public:
	typedef TECashRegisterBase super;
	FelixRK(QString pname, Q_ULONG mn);
	FelixRK();
	~FelixRK();
	
	typedef int Result;
	typedef double Decimal;
	typedef unsigned char Byte;
	typedef unsigned short UShort;

//    virtual QString model() const;
//    virtual Caps modelCaps() const;
//    virtual QString softwareVersion() const;

	virtual bool openCheck();
	virtual bool sellAdd( const QString &name, int dep, double summa, double quantity, int qdec );
//    virtual Result buyAdd();
//    virtual Result closeCheck();
//    virtual Result resetCheck();
	virtual Q_ULONG readMachineNumber();

	virtual bool printCheck(bool returnFlag);
	virtual bool cancelPrint();
	virtual bool openCheck(int eDocumentType);
//    	virtual int bueAdd( const QString &name, int dep, double summa, double quantity, int qdec );

    	virtual int open();

    	virtual QCString utf8ToDevice( const QString &text );
    	virtual QString deviceToUtf8( const QCString &text );

	QString flagsStr(Byte flags);
protected:
	Result checkAnswer(Byte * pAnswer, int szAnswerSize);
	void setDeviceError(Byte bDeviceError)
	{
		m_bDeviceError=bDeviceError;
	}

/*
	/en
	sendData function SHOULD NOT be used directly, as it implements just a part of a connection protocol.

	pCommand - pointer to data to send
	szCmdSize - length of data in bytes.
	pszBytesWritten - pointer to variable, which receives number of written bytes. It CAN be NULL.

	Remarks: This function uses retryCount() to determine number of performed retries. /_en
	/ru Функция sendData предназначена для внутреннего использования в ф-ции sendCommand и НЕ ДОЛЖНА
		использоваться напрямую.
		pCommand - указатель на посылаемую команду
		szCmdSize - длина команды в байтах
		pszBytesWritten - Указатель на переменную, принимающую количество отправленных байт. Этот параметр может быть равен NULL.
		Примечание: Максимальное число попыток отправки команды определяется значением ф-ции retryCount().
		/_ru
*/
	Result sendData(Byte const * pCommand, int szCmdSize, int * pszBytesWritten);
public: 	
/*!
	/en sendCommand sends block of data pointed to by pCommand of szCmdSize size in bytes to device,
	then fills pResponce buffer with responce of device, numbers of written and read bytes
	are saved to *pszWrittenBytes and *pszReadBytes accordingly.
	Return value indicates status of transaction: success, failure, timeout, buffer overrun and so on.

	Remarks: This function tries to send command retryCount() times.

	NB: This function can block on up to reqTimeout() milliseconds. This is protocol requirement. /_en

	/ru sendCommand отправляет блок данных размером szCmdSize на устройство, записывает ответ устройства
	в буфер pResponse. Количество посланных и прочитанных байтов, исключая служебные, записывается
	по указателям pszWrittenBytes и pszReadBytes соответственно.
	Примечание: Максимальное число попыток отправки команды определяется значением ф-ции retryCount().
	ВНИМАНИЕ: Если устройство не отвечает, то время выполнения функции может составить reqTimeout() миллисекунд.
	/_ru
*/
	Result sendCommand(Byte const * pCommand, int szCmdSize,
		Byte * pResponce, int szRespBufSize, int *pszWrittenBytes=0,
		int *pszReadBytes=0, bool ignorePendingData=true);
    
/*
	/en
	readData reads device responce into pResponce pointed buffer.
	pResponce - pointer to receive buffer. It can be NULL in which case all received data is ignored.
	szRespBufSize - size of receive buffer in bytes.
	pszReadBytes - pointer to variable, which receives number of total number of read bytes minus STX byte,length byte and checksum byte, which
	can be greater then szRespBufSize.  It can be NULL.

	Remarks: readData can be used IF AND ONLY IF sendCommand(ignorePendingData==false) returns RSP_DATAPENDING,
	and immediately after sendCommand call. Such usage is excessive however, because there are commands in current protocol version,
	purposed for data querying.
	Function always read all available data, while saving maximum szRespBufSize bytes,
	excessive bytes are dropped, and function returns RSP_BUFFEROVERRUN.
	If pResponce is NULL, then RSP_BUFFEROVERRUN is replaced with RSP_OK.
	If device returns error code, then function returns RSP_COMMANDERROR and sets deviceError propetry. /_en
	/ru Ф-ция readData считывает ответ устройства в буфер, на который указывает pResponce.
		pResponce - указатель на буфер. Может быть равен NULL, в этом случае все полученные данные игнорируются.
		szRespBufSize - размер буфера в байтах.
		pszReadBytes  - указатель на переменную, принимающую количество полученных байт. Этот параметр может быть равен NULL.
		Примечание: Эта ф-ция может быть использована только в том случае, если ф-ция sendCommand с параметром ignorePendingData
		равным false вернула значение RSP_DATAPENDING, причем без промежуточных вызовов других ф-ций.
		Впрочем такое её использование в текущей версии протокола излишне, т.к. существуют команды для запроса
		следующей порции данных.
	/_ru
*/
	Result readData(Byte * pResponce, int szRespBufSize, int *pszReadBytes);

	// Types of decimal values (price, quantity, etc)
	enum DecType
	{
		DTPrice,
		DTQuantity,
		DTPercent,
		DTInteger
	};
	// This function converts from Decimal to internal device representation.
	// It uses decimal point position acquired from device.
	Result fromDecimal(Decimal dVal,Byte * pBuf,int szSize, DecType type);

	Result toDecimal(Byte const * const pBuf,int szSize, Decimal * pdVal, DecType type);

	Result stringToByteArray(const QString & text, Byte * pBuf, int szSize);

	Result internalEnterMode(int mode, int pt);

	Result internalExitMode();

	// Adds buy/sell position to check.
	Result internalAddOperation(int oOperation, Decimal dQuantity, Decimal dPrice, Byte Section);

	//
	Result internalCloseCheck(Decimal dCashsum, Decimal * pdChangeSum);

	Result internalAddDiscount(int range, int type, Decimal dSum);

	Result internalCancelCheck();

	Result internalCheckSubtotal(int iType, Decimal dSubtotal, Decimal * pdRest, Decimal * pdChangeSum);

	Result internalRing();

	Result internalReadState(FRState * pState);

	Result internalReadShortState(FRShortState * pState);

	Result internalCommandSumTaxText(Byte cmd, Decimal dSum,  Byte const * baTax /* Byte [4] */,
		const QString & sText, Byte & OpNum=m_bTmpOpNum);

	Result internalAddDiscountStorno();

	Result internalCancelDiscount();

	Result internalRepeatDocument();

/*! /en	Operator password required. /_en
	/ru /_ru */
    	Result internalPayingIn(Decimal dSum);

/*! /en	Operator password required. /_en
	/ru /_ru */
    	Result internalPayment(Decimal dSum);

	Result internalOpenCheck(int iType);
	//Result internalOpenCheck(Byte * const baOperpass, Byte DocType /* FDT_XXX constants */,
	//	Byte & OpNum=m_bTmpOpNum);

/*! /en	internalReadOptions reads device model and operation parameters.
		RSP_DEVICEUNKNOWN can be returned as well as other error codes./_en
	/ru Эта функция читает параметры устройства и сохраняет их с помощью функции setValue /_ru */
	Result internalReadOptions(int);


/*! /en	Prints one line of text (40 chars maximum)./_en
	/ru /_ru */
	Result internalPrintLine(const QString & line);

/*! /en	Prints one bold line of text (20 chars maximum)./_en
	/ru /_ru */
	Result internalPrintBoldLine(const QString & line, bool bOnCheckTape, bool bOnJournalTape, Byte & OpNum=m_bTmpOpNum);

/*! /en	/_en
	/ru /_ru */
	Result internalPrintHeader(const QString & header, int iDocNumber, int *piSeqDocNumber, Byte & OpNum=m_bTmpOpNum);

/*! /en	/_en
	/ru Получить значение денежного регистра № accumNum (0..255) /_ru */
	Result internalGetMoneyAccumValue(int accumNum, Decimal *pdValue, Byte & OpNum=m_bTmpOpNum);

/*! /en	/_en
	/ru Получить значение операционного регистра № regNum (0..255) /_ru */
	Result internalGetOperRegisterValue(int regNum, int parNum1, int parNum2, Byte *piValue, int * iSize);

/*! /en	Sysadmin password required. /_en
	/ru /_ru */
	Result internalWriteLicense(const Byte * pLic /* Byte [5] */);

/*! /en	Sysadmin password required. /_en
	/ru /_ru */
	Result internalReadLicense(Byte * pLic /* Byte [5] */);

/*! /en	Sysadmin password required. /_en
	/ru /_ru */
	Result internalSetTime(int hour, int min, int sec);

/*! /en	Sysadmin password required. Year must be in 0..255/2000..2255 range (2000..2255 year accordingly) /_en
	/ru /_ru */
	Result internalSetDate(int day, int month, int year);

/*! /en	Sysadmin password required. Year must be in 0..255/2000..2255 range (2000..2255 year accordingly) /_en
	/ru /_ru */
	Result internalCommitDate(int day, int month, int year);

	/*! /en	/_en */
	Result internalSetCommConfig(int portNumber, int baudRate, int timeOut);

	Result internalReadCommConfig(int portNumber, int *pBaudRate, int *pTimeOut);

	Result internalQueryTableInfo(int tableNum, QString & name, int *pRowCount, int *pColumnCount);

	Result internalQueryColumnInfo(int tableNum, int columnNum, QString & name, int *pType, int *pSize, void *pMin=0, void *pMax=0);

/*! /en pSize - in/out paramenter /_en */
	Result internalReadField(int tableNum, int rowNum, int columnNum, void *pValue, int *pSize);

	Result internalWriteField(int tableNum, int rowNum, int columnNum, void *pValue, int size);


/*! /en	Sysadmin password required. devNum: 1-FM1, 2-FM2, 3-clock, 4-EPROM, 5-processor, 6-programm memory, 7-RAM /_en
	/ru /_ru */
	Result internalBeginDump(int devNum, /*out*/ int *pBlockCount);

/*! /en	Sysadmin password required. pDevNum: 1-FM1, 2-FM2, 3-clock, 4-EPROM, 5-processor, 6-programm memory, 7-RAM /_en
	/ru /_ru */
	Result internalGetData(/*out*/int *pDevNum, /*out*/int *pBlockNum, /*out*/Byte * pData, /*in*/int szBufSize);

/*! /en	Sysadmin password required. /_en
	/ru /_ru */
	Result internalEndDump();

/*! /en	Sysadmin password required. /_en
	/ru /_ru */
	Result internalResetTables();

/*! /en	Sysadmin password required. fPos: 0 - after 0 digits, 1 - after 2 digits /_en
	/ru /_ru */
	Result internalSetDecimalPointPos(int iFlag);

/*! /en	Operator password required. iCutType: 0-full cut, 1-partial cut, other values - nothing /_en
	/ru /_ru */
	Result internalCutCheck(int iCutType);

/*! /en	Sysadmin password required. /_en
	/ru Общее гашение (!!!найти перевод на английский!!!) /_ru */
	Result internalTotalClear();

/*! /en	Sysadmin password required. /_en
	/ru Суточный отчет без гашения /_ru */
	Result internalDailyReport(Byte reportType = 1);

/*! /en	Sysadmin password required. /_en
	/ru Суточный отчет с гашением /_ru */
	Result internalDailyReportAndClear();

/*! /en	Operator password required. /_en
	/ru Открыть денежный ящик /_ru */
	Result internalOpenCashbox(int iCashboxNumber);

/*! /en	Operator password required. /_en
	/ru Протяжка фдаги 1 - контрольная лента, 2 - чековая лента, 4 - подкладной документ /_ru */
	Result internalTapeAdvance(int flags, int iLineCount);

/*! /en	Operator password required. /_en
	/ru Продолжить печать после сбоя. /_ru */
	Result internalContinuePrint();

/*! /en	Operator password required. /_en
	/ru Тестовый прогон. /_ru */
	Result internalTestRun(int iPeriodInMin);

/*! /en	Operator password required. /_en
	/ru Остановить тестовый прогон. /_ru */
	Result internalStopTestRun();
	
/*! /en 	device type /_en
	/ru Тип устройства /_ru */
	Result internalDeviceType(Byte * pProtocol, Byte * pType, Byte * pModel, Byte pMode[2], Byte pVersion[5], QString &name);
	
public:
	// Timeouts (in milliseconds)
	int T0() const { return 1000;}
	int T1() const { return 500;}
	int T2() const	{ return 2000;}
	int T3() const	{ return 500;}
	int T4() const	{ return 500;}
	int T5(Byte o);
	int T6() const	{ return 500;}
	int T7() const	{ return 500;}	
	int T8() const	{ return 1000;}
	
	// Number of retries for sendCommand and sendData, readData fails immediately.
	int retryCount() const { return 5; }

	bool optionsRead() const{return m_bOptionsRead;}
	void setOptionsRead(bool bRead){m_bOptionsRead=bRead;}
	Q_ULLONG quantityMultiplier() const{return m_ullQuantityMultiplier;}
	Q_ULLONG priceMultiplier() const{return m_ullPriceMultiplier;}
	Q_ULLONG percentMultiplier() const{return m_ullPercentMultiplier;}
	void setPriceMultiplier(Q_ULLONG ullPM){m_ullPriceMultiplier=ullPM;}

	enum PassType
	{
		PTAccess,
		PTOperator,
		PTAdmin,
		PTFiscal
	};


	virtual QValueList<int> supportedBaudRates()
	{
		QValueList<int> ret;
		ret<<9600<<14400<<19200<<38400<<57600<<115200;
		return ret;
	}

// --- Common driver functions ---
public slots:
	virtual int startDriver();
	virtual int stopDriver();
	virtual int setCaptureMode(int iMode);

	virtual int setPassword(int pt, const QString & pass);
	virtual int openCashbox(int n); // open cash box number n
	virtual int ZReport();
	virtual int XReport();

	virtual bool isCheckOpened();
	virtual bool onlinePrintMode();
	virtual void setOnlinePrintMode(bool bOnlinePM);
	virtual bool isOnlinePrintModeSupported();

	virtual int openCheck(int eDocumentType, int & piReserved);
	virtual int beginAdd(int iReserved);
	virtual int setDiscount(double dDiscount); // absolute value of a discount
	virtual int setDiscountPercent(double); // discount in 0.01% units
	virtual int setItemSection(int iSection);
	virtual int setOperation(int eOperationType);
	virtual int setUnit(const QString & sUnit);
	virtual int setComment(const QString & sComment);
	virtual int setItem(const QString & sName, double dPrice, double dQuantity);
	virtual int endAdd(int iReserved);
	virtual int cancelAdd(int iReserved);
	virtual int setPayment(double dSum, int iType=1);
	virtual int cancelCheck(int iReserved);
	virtual int closeCheck(double & dChange, int iReserved);
	virtual int curDocumentNumber(int & iDocNum);
	virtual int curChangeNumber(int & iChangeNum);
	virtual double summaTotal();
	virtual int printItemOut(const PurchaseInfo & item);
	
	int curDocumentNumber();
	int curChangeNumber();
	
	virtual int payingin(double);
	virtual int payment(double);

	virtual int checkDeviceReady();	

	int deviceError() const
	{
		int res = m_bDeviceError;
		return res;
	}

	QString devErrorText(int err);
	
	int getMaxPrint();
protected:
//ENQ=0x05 ACK=0x06 STX=0x02 ETX=0x03 EOT=0x04 NAK=0x15 DLE=0x10
	static const Byte ENQ=0x05;
	static const Byte STX=0x02;
	static const Byte ETX=0x03;	
	static const Byte DLE=0x10;
	static const Byte ACK=0x06;
	static const Byte NAK=0x15;
	static const Byte EOT=0x04;
	static Byte m_bTmpOpNum; // This member works as default parameter

private:
	Byte m_bDeviceError;
	Byte m_baAccessPass[2];
	Byte m_baOperPass[4];
	Byte m_baAdminPass[4];
	Byte m_baFiscalPass[4];
	int m_maxPrn;
	bool m_bOptionsRead; // device options were received from device.
	bool m_bCheckIsOpen;
	bool m_bOnlinePrintMode;
	Q_ULLONG m_ullQuantityMultiplier;
	Q_ULLONG m_ullPriceMultiplier;
	Q_ULLONG m_ullPercentMultiplier;
	PurchaseInfo m_CurrentItem;
	bool m_bCrItBAdd; // beginAdd was called.
	bool m_bCrItBAddImplicit; // beginAdd was called implicitly.
	bool m_bCrItProcessed; // m_CurrentItem is processed, item cannot be cancelled.
	bool m_bCrItCompleted; // m_CurrentItem was filled and is going to be processed, no more attributes can be added

	int checkForBeginAdd(); // checks if beginAdd was called and if it doesn't then calls it. Also it checks if we can add attribute and if don't then returns CERROR_INVALIDCALL.
	void explainCheckPrintError(); // Uses setErrorText() to give more precise check print error description.
		// Call this function if internalOpenCheck returned error code RSP_COMMANDERROR.

	void init(); // This initialization function incorporates common constructor code
};

// FR state structure
struct FRState
{
	FelixRK::Byte errorByte;
	FelixRK::Byte operatorNumber;
	FelixRK::Byte numberInRoom;	
	FelixRK::Byte date[3]; // dd-mm-yy
	FelixRK::Byte time[3]; // hh-mm-ss
	FelixRK::Byte frFlags;	
	FelixRK::Byte serialNumber[4];
	FelixRK::Byte frModel;	
	FelixRK::Byte frSoftwareVersion[2];
	FelixRK::Byte frMode;				
	FelixRK::Byte currentDocumentNumber[2];
	FelixRK::Byte currentChangeNumber[2];
	FelixRK::Byte documentState;
	FelixRK::Byte currentCheckSum[5];
	FelixRK::Byte dot;
	FelixRK::Byte frPort;
};

struct FRShortState
{
	FelixRK::Byte errorByte;
	FelixRK::Byte frMode;
	FelixRK::Byte frFlags;
};

#endif
