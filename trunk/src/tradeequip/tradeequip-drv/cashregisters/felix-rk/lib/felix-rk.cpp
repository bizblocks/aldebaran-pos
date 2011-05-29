#include <math.h>
#include "felix-rk.h"
#include <qdatetime.h>
#include <qtextcodec.h>

//using FelixRK::Result;

Q_ULONG from4Bytes(FelixRK::Byte *pBytes /* Byte[4] */)
{
	return ((Q_ULONG)pBytes[0])|(((Q_ULONG)pBytes[1])<<8)|(((Q_ULONG)pBytes[2])<<16)|(((Q_ULONG)pBytes[3])<<24);
}

FelixRK::Byte FelixRK::m_bTmpOpNum;

FelixRK::FelixRK() : TECashRegisterBase("/dev/ttyS0",0)
{
	init();
}

FelixRK::FelixRK(QString pname, Q_ULONG mn) : TECashRegisterBase(pname,mn)
{
	init();
	setPortDevice(pname);
	setMachineNumber(mn);
}

FelixRK::~FelixRK()
{
}

void FelixRK::init()
{
	setName("TECashRegisterFelixRK");
	m_ee.addFuncBinding(this,&FelixRK::readMachineNumber,"readMachineNumber");
	m_ee.addFuncBinding<FelixRK,int>(this,&FelixRK::open,"open");
	m_ee.addFuncBinding<FelixRK,int>(this,&FelixRK::close,"close");
	m_ee.addFuncBinding<FelixRK,int,int,int&>(this,&FelixRK::openCheck,"openCheck");
	m_ee.addFuncBinding(this,&FelixRK::cancelPrint,"cancelPrint");
	m_ee.addFuncBinding(this,&FelixRK::sellAdd,"addSell");
	m_ee.addFuncBinding(this,&FelixRK::printCheck,"printCheck");
	m_ee.addFuncBinding(this,&FelixRK::internalOpenCashbox,"openCashbox");
	m_ee.addFuncBinding<FelixRK,QString>(this,&FelixRK::errorText,"errorText");
	m_ee.addFuncBinding<FelixRK,int,int>(this,&FelixRK::setPortNumber,"setPortNumber");
	m_ee.addProcBinding1<FelixRK,int>(this,&FelixRK::setPortBaudRate,"setBaudRate");
	m_ee.addFuncBinding(this,&FelixRK::setPassword,"setPassword");
	m_ee.addFuncBinding(this,&FelixRK::internalReadOptions,"readOptions");
//	m_ee.addFuncBinding(this,&FelixRK::internalDailyReport,"dailyReport");
	m_ee.addFuncBinding(this,&FelixRK::internalDailyReportAndClear,"dailyReportAndClear");
	m_ee.addFuncBinding(this,&FelixRK::internalCancelCheck,"internalCancelCheck");
	m_ee.addFuncBinding<FelixRK,QVariant,const QString &>(this,&FelixRK::value,"value");
//	setCaptureMode(CM_NonExclusive);
	setDeviceError(0);
	setPortBaudRate(4800);
	setPortDataBits(DATA_8);
	setPortFlowControl(FLOW_OFF);
	setPortNumber(1);
	setPortParity(PAR_NONE);
	setPortStopBits(STOP_1);
	setTimeout(T1());
	m_bOptionsRead=false;
	m_bCheckIsOpen=false;
	m_bOnlinePrintMode=false;
	m_bCrItProcessed=false;
	m_bCrItBAdd=false;
	m_bCrItBAddImplicit=false;
	m_bCrItCompleted=false;
	m_ullQuantityMultiplier=1000;
	m_ullPriceMultiplier=100;
	m_ullPercentMultiplier=100;
	m_maxPrn = 0;
}



FelixRK::Result FelixRK::sendCommand(Byte const * pCommand,
	int szCmdSize, Byte * pResponce, int szRespBufSize,
	int *pszWrittenBytes, int *pszReadBytes, bool ignorePendingData)
{
	if (szCmdSize<=0)
	{
		setErrorText(tr("szCmdSize must be greater then zero."));
		return RSP_INVALIDPARAMETER2;
	}
	if (szCmdSize>255)
	{
		setErrorText(tr("szCmdSize must be less then 66."));
		return RSP_INVALIDPARAMETER2;
	}
	if (szCmdSize>0 && pCommand==0)
	{
		setErrorText(tr("pCommand must not be NULL, while szCmdSize>0."));
		return RSP_INVALIDPARAMETERS;
	}
	if (szRespBufSize<0)
	{
		setErrorText(tr("szRespBufSize<0"));
		return RSP_INVALIDPARAMETER4;
	}
	//defaulting read/write byte count to zero
	if (pszWrittenBytes) // pointer can be null
		*pszWrittenBytes=0;
	if (pszReadBytes)
		*pszReadBytes=0;
	if (!port()->isOpen())
	{
		setErrorText(tr("Port is closed."));
		return RSP_PORTCLOSED;
	}
	Result result=RSP_TIMEOUT;
	for(int j=0;j<retryCount();j++)
	{
		setTimeout(T0());	
		if (putch(ENQ)==-1)
		{	// Timeout or hardware error
			setErrorText(tr("Timeout while sending ENQ byte."));
			setOptionsRead(false); //Device is offline. We should read device setting next time.
			return RSP_TIMEOUT;
		}
		// We should wait for byte more then 10 seconds.
		int ichr;
		setTimeout(T1());
		ichr=getch();
		if (ichr==-1) // There's no response, exiting
			continue;
		if(((Byte)ichr)==NAK)
		{ // Device is sending some data, just ignore it.
		    Sleep(T1());
			continue;
		}
		else if(((Byte)ichr)==ENQ)
			Sleep(T7());
		else if(((Byte)ichr)!=ACK)
			continue;
		 		
		// Ok. We can finally send data to device.
		result=sendData(pCommand, szCmdSize, pszWrittenBytes);
		setTimeout(T4());
		putch(EOT);		
		if (result!=RSP_OK)
		{
			continue; // sendData failed, so we should repeat entire IO sequence, or fail if retry count is exceeded.
		}
		
		if(!ignorePendingData) return result;
		setTimeout(T5(m_bTmpOpNum));
		ichr=getch();
		if(ichr==ENQ)
			result=readData(pResponce,szRespBufSize,pszReadBytes);
		if (result==RSP_OK)
		{
			setErrorText(tr("No error"));
			return result;
		}
		else if (result==RSP_BUFFEROVERRUN)
			return result;
		else if (result==RSP_COMMANDERROR)
			return result;
		else if (result==RSP_RESPONCETOOSHORT)
			return result;
		// Otherwise we make another attempt.
	} /* End of retry cycle*/
	if (result==RSP_TIMEOUT)
	{
		setOptionsRead(false); //Device is offline. We should read device setting next time.
		setErrorText(tr("All retries failed. Device link is down."));
	}
	return result;
}


FelixRK::Result FelixRK::sendData(Byte const * pCommand, int szCmdSize, int * pszBytesWritten)
{
	for(int j=0;j<retryCount();j++)
	{
		Byte * maskCommand = new Byte[szCmdSize*2+1];
		Byte * start = maskCommand;
		for(int i=0;i<szCmdSize;i++)
		{			
			if(pCommand[i]==DLE || pCommand[i]==ETX)
			{
				(*maskCommand) = DLE;
				maskCommand++;
			}
			(*maskCommand) = pCommand[i];
			maskCommand++;
		}
		(*maskCommand) = ETX;
		int maskSize = maskCommand-start;
		maskCommand = start;
		Byte bCheckSum=maskCommand[0]; //checkSum

//		setTimeout(T5());
		putch(STX);
		putch(maskCommand[0]);
		for(int i=1;i<maskSize+1;i++)
		{
			putch(maskCommand[i]);
			bCheckSum=bCheckSum^maskCommand[i];
		}
		putch(bCheckSum);

		setTimeout(T3());
		int iResp=getch();
		if (((Byte)iResp)!=ACK)
			continue; // error occured, retrying.
		if (pszBytesWritten)
			*pszBytesWritten=szCmdSize;
		return RSP_OK;
	}
	if (pszBytesWritten)
		*pszBytesWritten=0;
	return RSP_TIMEOUT;
}

FelixRK::Result FelixRK::readData(Byte * pResponce, int szRespBufSize, int *pszReadBytes)
{
	FelixRK::Result result;
	for(int j=0;j<retryCount();j++)
	{
		if (pszReadBytes)
			*pszReadBytes=0;

		putch(ACK);
		
		int ichr;		
		for(int i=0;i<retryCount();i++)
		{
			setTimeout(T2());
			ichr = getch();
			if(ichr==-1)
				break;
			else if(((Byte)ichr)==STX)
				break;
			else if(((Byte)ichr)==ENQ)
				break;			
		}
		
		if(((Byte)ichr)==ENQ)
			continue;
			
		if(((Byte)ichr)!=STX)
		{
			setErrorText(tr("readData: Timeout while waiting for STX."));
			break;		
		}

		bool DLE_flag = false;
		Byte checkSum=0;
		int iLen = 0;
		for(int i=0;iLen<szRespBufSize;i++)
		{
			setTimeout(T6());		
			int iByte=getch();
			if (iByte==-1)
				break;
			checkSum = checkSum ? checkSum^(Byte)iByte : (Byte)iByte;
			if(((Byte)iByte)==ETX && !DLE_flag)
				break;
			DLE_flag=!DLE_flag && (((Byte)iByte)==DLE);
			if(DLE_flag)
				continue;
			if (pResponce && i<szRespBufSize)
				pResponce[iLen]=(Byte)iByte;
			iLen++;
		}
		
		if(iLen==szRespBufSize)
			continue;
		
		if (pszReadBytes)
			*pszReadBytes=iLen;

		setTimeout(T6());
		int iByte=getch();
		if (iByte==-1)
			continue;
		if(((Byte)iByte)!=checkSum)
		{
			putch(NAK);
			result = RSP_CHECKSUMERROR;
			continue;
		}
		
		putch(ACK);
		setTimeout(T4());
		iByte = getch();
		if(iByte==-1)
			break;
		if(((Byte)iByte)==EOT)
			break;
		if(((Byte)iByte)==STX)
			continue;
		setTimeout(T6());
		iByte = getch();
		if(iByte==-1)
			break;
	}
	return RSP_OK;	
}

FelixRK::Result FelixRK::checkAnswer(Byte * pAnswer, int szAnswerSize)
{
    if(szAnswerSize<2)
	return RSP_OK;
    if (pAnswer[0]!=0x55)
    {
	setErrorText(tr("Device returns error code 0x%1. %2").arg(pAnswer[0],0,16).arg(devErrorText(pAnswer[0])));
	setDeviceError(pAnswer[0]);
	return RSP_COMMANDERROR;
    } 
    else if (pAnswer[1])
    {
	setErrorText(tr("Device returns error code 0x%1. %2").arg(pAnswer[1],0,16).arg(devErrorText(pAnswer[1])));
	setDeviceError(pAnswer[1]);
	return RSP_COMMANDERROR;			
    }
    return RSP_OK;
}

FelixRK::Result FelixRK::internalEnterMode(int mode, int pt)
{
	if(mode<0 || mode>4)
	{
		setErrorText(tr("Invalid mode"));
		return CRERROR_INVALIDCALL;
	}
	Byte * pPass;
	switch(pt)
	{
	case PTOperator:
		pPass=m_baOperPass;
		break;
	case PTAdmin:
		pPass=m_baAdminPass;
		break;
	case PTFiscal:
		pPass=m_baFiscalPass;
		break;
	default:
		setErrorText(tr("Invalid password type."));
		return CRERROR_INVALIDCALL;
	}	

	FRShortState state;
	Result result = internalReadShortState(&state);
	if(result!=RSP_OK) return result;
	if(state.frMode==mode<<4) return RSP_OK;
	while(state.frMode!=0)
	{
		result = internalExitMode();
		if(result!=RSP_OK)
		{
			setErrorText(QString(tr("ECR can't exit from mode 0x%1")).arg(state.frMode, 0, 16));
			return result;
		}
		result = internalReadShortState(&state);
		if(result!=RSP_OK)
			return result;
	}

	m_bTmpOpNum 		= 0x56;
	Byte cmd[8]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, mode, pPass[0], pPass[1], pPass[2], pPass[3]};
	Byte answer[3];
	result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);
	if(result!=RSP_OK)
		return result;
	return checkAnswer(answer, sizeof(answer));
}

FelixRK::Result FelixRK::internalExitMode()
{
	m_bTmpOpNum = 0x48;
	Byte cmd[3]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
	Byte answer[3];
	Result result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);
	if(result!=RSP_OK)
		return result;
	return checkAnswer(answer, sizeof(answer));
}


FelixRK::Result FelixRK::internalAddOperation(int oOperation, Decimal dQuantity, Decimal dPrice, Byte Section)
{
	m_bTmpOpNum = 0x00;
	switch(oOperation)
	{
	case FOP_SELL:
		m_bTmpOpNum = 0x52;
		break;
	case FOP_SELLRET:
		m_bTmpOpNum = 0x57;
		break;
	case FOP_STORNO:
		m_bTmpOpNum = 0x4E;
		break;
	default:
		setErrorText(tr("Invalid operation number %1").arg(oOperation));
		return RSP_INVALIDPARAMETER1;
	}
	Result result;
	Byte qty[5];
	if ((result=fromDecimal(dQuantity, qty, sizeof(qty), DTQuantity))!=RSP_OK) // There can be overflow or something.
		return result;
	Byte price[5];
	if ((result=fromDecimal(dPrice, price, sizeof(price), DTPrice))!=RSP_OK)
		return result;
	Byte cmd[15]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Section};
	for(unsigned char i=0;i<5;i++)
		cmd[4+i] = price[i];
	for(unsigned char i=0;i<5;i++)
		cmd[9+i] = qty[i];	
	Byte answer[3];
	result = sendCommand(cmd, sizeof(cmd)-(m_bTmpOpNum==0x52 ? 0 : 1), answer, sizeof(answer)+1);
	if (result!=RSP_OK) return result;
	result = checkAnswer(answer, sizeof(answer));
	return result;
}

FelixRK::Result FelixRK::fromDecimal(Decimal dVal,Byte * pBuf,int szSize, DecType type)
{ // Sanity checking
	if (dVal<0)
	{
		setErrorText(tr("fromDecimal: Conversion of negative values isn't supported."));
		return RSP_INVALIDPARAMETER1;
	}
	if (pBuf==0)
	{
		setErrorText(tr("fromDecimal: pBuf is NULL."));
		return RSP_INVALIDPARAMETER2;
	}
	Q_ULLONG ulVal = 0;
	if(type==DTPrice)
		ulVal = (Q_ULLONG)round(dVal*100.);
	else if(type==DTQuantity)
		ulVal = (Q_ULLONG)round(dVal*1000.);
	else
		ulVal = (Q_ULLONG)round(dVal);

	QString sNum = QString("%1").arg(ulVal);
	sNum = sNum.rightJustify(szSize*2, '0');
	if (sNum.length()>(uint)szSize*2)
	{
		setErrorText(tr("fromDecimal: Overflow. Supplied buffer size is too small."));
		return RSP_INVALIDPARAMETER3;
	}

	for(char i=0;i<szSize;i++)
	{
		QString sPart = QString("%1").arg(sNum.mid(i*2,2));
		pBuf[i]=(Byte)(sPart.toInt(0, 16));
	}
	return RSP_OK;
}

FelixRK::Result FelixRK::toDecimal(Byte const * const pBuf,int szSize, Decimal * pdVal, DecType type)
{ // Sanity checking
	if (pdVal==0)
	{
		setErrorText(tr("toDecimal: pdVal==0"));
		return RSP_INVALIDPARAMETER3;
	}
	if (pBuf==0)
	{
		setErrorText(tr("toDecimal: pBuf is NULL."));
		return RSP_INVALIDPARAMETER1;
	}
	if (szSize<=0)
	{
		setErrorText(tr("toDecimal: szSize should be greater than zero"));
		return RSP_INVALIDPARAMETER1;
	}
	QString sNum("");
	for(unsigned char i=0;i<szSize;i++)
	{
		sNum+=QString("%1").arg(pBuf[i], 0, 16).rightJustify(2, '0');
	}
	bool ok;
	if(type==DTPrice) *pdVal = sNum.toInt(&ok)/100.;
	else if(type==DTQuantity) 	*pdVal = sNum.toInt(&ok)/1000.;
	else *pdVal = sNum.toInt(&ok);		
	return RSP_OK;
}

QCString FelixRK::utf8ToDevice( const QString &text )
{
	QTextCodec * utf8=QTextCodec::codecForName("UTF-8");
	QString unicodetext = utf8->toUnicode(text);
	QTextCodec * ibm866=QTextCodec::codecForName("IBM 866");
	return ibm866->fromUnicode(unicodetext);
}

QString FelixRK::deviceToUtf8( const QCString &text )
{
	QTextCodec * ibm866=QTextCodec::codecForName("IBM 866");
	QString unicodetext = ibm866->toUnicode(text);
	QTextCodec * utf8=QTextCodec::codecForName("UTF-8");
	return utf8->fromUnicode(unicodetext);
}

FelixRK::Result FelixRK::internalReadOptions(int /*reserved*/)
{
	// Clear all values
	setValue("Model",QVariant());
	setValue("SoftVersion",QVariant());
	setValue("SoftBuild",QVariant());
	setValue("SoftBuildDate",QVariant());
	setValue("CurrentDocumentNumber",QVariant());
	setValue("DateTime",QVariant());
	setValue("Mode",QVariant());
	setValue("Submode",QVariant());
	setValue("FiscalizationsCount",QVariant());
	setValue("FiscalizationsRemaining",QVariant());
	setValue("FRFlags",QVariant());
	setValue("FMFlags",QVariant());
	setValue("SerialNumber",QVariant());
	setValue("LastClosedChangeNumber",QVariant());
	setValue("FreeFMRecordCount",QVariant());
	setValue("INN",QVariant());

/*		if (szModLen<=0)
			setValue("Model","Unknown");
		else
		{
			QCString csModStr((char*)(resp.la.deviceName),szModLen+1); // +1 for null byte
			setValue("Model",deviceToUtf8(csModStr));
		}
		if (resp.la.deviceType==0 && resp.la.deviceSubtype==0)
		{ // It's a fiscal register.
//knorr!!		
//			FRState frs;
//			if (internalReadState(&frs)==RSP_OK)
//			{
//				ushort frflags=frs.frFlags[0]|(frs.frFlags[1]<<8);
//				setPriceMultiplier((frflags&FR_TwoDigitsAfterDot)?100:1);
//				setValue("SoftVersion",QString("%1.%2").arg((int)frs.fmSoftwareVersion[0]).arg((int)frs.fmSoftwareVersion[1]));
//				setValue("SoftBuild",(uint)(frs.fmBuildNumber[0]+(uint)frs.fmBuildNumber[1]*256));
//				setValue("SoftBuildDate",QDateTime(QDate(frs.frBuildDate[2]+2000,frs.frBuildDate[1],frs.frBuildDate[0])));
//				setValue("CurrentDocumentNumber",(uint)(frs.currentDocumentNumber[0]+(uint)frs.currentDocumentNumber[1]*256));
//				setValue("DateTime",QDateTime(QDate(frs.date[2]+2000,frs.date[1],frs.date[0]),QTime(frs.time[0],frs.time[1],frs.time[2])));
//				setValue("Mode",(uint)frs.frMode);
//				setValue("Submode",(uint)frs.frSubmode);
//				setValue("FiscalizationsCount",(uint)frs.fiscalizationsCount);
//				setValue("FiscalizationsRemaining",(uint)frs.fiscalizationsRemaining);
//				setValue("FRFlags",(uint)(frs.frFlags[0]+(uint)frs.frFlags[1]*256));
//				setValue("FMFlags",(uint)(frs.fmFlags));
//				setValue("SerialNumber",((uint)(frs.serialNumber[0]))+(((uint)(frs.serialNumber[1]))<<8)+
//					(((uint)(frs.serialNumber[2]))<<16)+(((uint)(frs.serialNumber[3]))<<24));
//				setValue("LastClosedChangeNumber",(uint)(frs.lastClosedChangeNumber[0]+(uint)frs.lastClosedChangeNumber[1]*256));
//				setValue("FreeFMRecordCount",(uint)(frs.freeFMRecordsCount[0]+(uint)frs.freeFMRecordsCount[1]*256));
//				char innbuf[13];
//				sprintf(innbuf,"%02x%02x%02x%02x%02x%02x",frs.INN[0],frs.INN[1],frs.INN[2],frs.INN[3],frs.INN[4],frs.INN[5]);
//				setValue("INN",QString(innbuf));
//				setOptionsRead(true);
//				return RSP_OK;
//			}
//			else
//			    setErrorText(tr(""));
//knorr
		}
	}
	else if (res==RSP_COMMANDERROR)
	{ // Device doesn't support this command. Let's try another variant.
		setValue("Model","Unknown");
	}
	setOptionsRead(false);
*/
	return RSP_NODEVICEINFO;
}

FelixRK::Result FelixRK::internalReadState(FRState * pState)
{
	m_bTmpOpNum = 0x3F;
	Byte cmd[3]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
	Result result = sendCommand(cmd, sizeof(cmd), (Byte*)pState, sizeof(*pState)+1);
	if(result!=RSP_OK)
		return result;
	if(pState->errorByte!=0x44)
	{
		setDeviceError(pState->frMode);
		return RSP_COMMANDERROR;		
	}	
	return RSP_OK;	
}

FelixRK::Result FelixRK::internalReadShortState(FRShortState * pState)
{
	m_bTmpOpNum = 0x45;
	Byte cmd[3]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
	Result result = sendCommand(cmd, sizeof(cmd), (Byte*)pState, sizeof(*pState)+1);
	if(result!=RSP_OK)
		return result;
	if(pState->errorByte!=0x55)
	{
		setDeviceError(pState->errorByte);
		return RSP_COMMANDERROR;		
	}	
	return RSP_OK;	
}

FelixRK::Result FelixRK::setPassword(int pt,const QString & pass)
{
	bool ok;
	pass.toULong(&ok);	
	if (!ok)
	{
		setErrorText(tr("Invalid password format. Enter digits only, please."));
		return CRERROR_INVALIDCALL;
	}
	char passLen = 8;
	Byte * pPass;
	switch(pt)
	{
	case PTAccess:
		passLen = 4;
		pPass=m_baAccessPass;
		break;
	case PTOperator:
		pPass=m_baOperPass;
		break;
	case PTAdmin:
		pPass=m_baAdminPass;
		break;
	case PTFiscal:
		pPass=m_baFiscalPass;
		break;
	default:
		setErrorText(tr("Invalid password type."));
		return CRERROR_INVALIDCALL;
	}
	QString string = pass.rightJustify(passLen, '0', true);
	for(char i=0;i<passLen/2;i++)
	{
		QString part = QString("%1").arg(string.mid(i*2,2));
		pPass[i]=(Byte)(part.toInt(0, 16));
	}
	return CRERROR_OK;
}

FelixRK::Result FelixRK::internalSetCommConfig(int portNumber, int baudRate, int timeOut)
{
	Q_UNUSED(portNumber);
	Q_UNUSED(timeOut);	
	switch(baudRate)
	{
	case 2400:
//		lCmd.baudRateCode=0;
		break;
	case 4800:
//		lCmd.baudRateCode=1;
		break;
	case 9600:
//		lCmd.baudRateCode=2;
		break;
	case 19200:
//		lCmd.baudRateCode=3;
		break;
	case 38400:
//		lCmd.baudRateCode=4;
		break;
	case 57600:
//		lCmd.baudRateCode=5;
		break;
	case 115200:
//		lCmd.baudRateCode=6;
		break;
	default:
//		setErrorText(tr("Unsupported baud rate %1").arg(baudRate));
		return RSP_INVALIDPARAMETER2;
	}
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalReadCommConfig(int portNumber, int *pBaudRate, int *pTimeOut)
{
	Q_UNUSED(portNumber);
	Q_UNUSED(pBaudRate);
	Q_UNUSED(pTimeOut);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalQueryTableInfo(int tableNum, QString & name, int *pRowCount, int *pColumnCount)
{
	Q_UNUSED(tableNum);
	Q_UNUSED(name);	
	Q_UNUSED(pRowCount);
	Q_UNUSED(pColumnCount);	
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalQueryColumnInfo(int tableNum, int columnNum, QString & name, int *pType, int *pSize, void *pMin, void *pMax)
{
	Q_UNUSED(tableNum);
	Q_UNUSED(name);
	Q_UNUSED(columnNum);
	Q_UNUSED(pType);
	Q_UNUSED(pSize);
	Q_UNUSED(pMin);
	Q_UNUSED(pMax);		
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalReadField(int tableNum, int rowNum, int columnNum, void *pValue, int *pSize)
{
	Q_UNUSED(tableNum);
	Q_UNUSED(rowNum);	
	Q_UNUSED(columnNum);	
	Q_UNUSED(pValue);
	Q_UNUSED(pSize);		
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalWriteField(int tableNum, int rowNum, int columnNum, void *pValue, int size)
{
	Q_UNUSED(tableNum);
	Q_UNUSED(rowNum);	
	Q_UNUSED(columnNum);
	Q_UNUSED(pValue);
	Q_UNUSED(size);	
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalCloseCheck(Decimal dCashsum, Decimal * pdChangeSum)
{
	if(pdChangeSum) *pdChangeSum = 0;

	Result result;
	Byte sum[5];
	if ((result=fromDecimal(dCashsum, sum, sizeof(sum), DTPrice))!=RSP_OK) // There can be overflow or something.
		return result;
	Byte bType = 0x00;
	FRShortState state;
	result = internalReadShortState(&state);
	if(result!=RSP_OK)
		return result;
	if(state.frMode==0x01 && dCashsum>0) 
		bType = 0x01;
	m_bTmpOpNum = 0x4A;
	Byte cmd[10] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0, bType, 0, 0, 0, 0, 0};
	if(state.frMode==0x01 && dCashsum>0) 
		for(unsigned char i=0;i<5;i++)
			cmd[5+i] = sum[i];
	Byte answer[3];
	result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);

	if(result!=RSP_OK)
		return result;
	result = checkAnswer(answer, sizeof(answer));
	if(result!=RSP_OK)
		return result;
	return result;
}

FelixRK::Result FelixRK::internalAddDiscount(int iRange, int iType, Decimal dSum)
{
	m_bTmpOpNum = 0x43;
	Result result;
	Byte bRange = 0x00;
	if(iRange==1) bRange = 0x01;
	int iSize = 3;
	Byte bType = 0x00;
	if(iType==1)
	{
		iSize = 5;
		bType = 0x01;
	}
	Byte bSign = 0x00;
	if(dSum<0)
	{
		bSign = 0x01;
		dSum = -dSum;
	}
	Byte val[iSize];
	if ((result=fromDecimal(dSum, val, iSize, DTPrice))!=RSP_OK) // There can be overflow or something.
		return result;
	Byte cmd[12]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0, bRange, bType, bSign, 0, 0, 0, 0, 0};
	for(unsigned char i=0;i<iSize;i++)
		cmd[7+i] = val[i];
	Byte answer[3];
	result=sendCommand(cmd, 7+iSize, answer, sizeof(answer)+1);
	if (result!=RSP_OK) return result;
	return checkAnswer(answer, sizeof(answer));	
}

FelixRK::Result FelixRK::internalCancelCheck()
{
	m_bTmpOpNum = 0x59;
	Byte cmd[3] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
	Byte answer[3];
	Result result = sendCommand(cmd,sizeof(cmd),answer,sizeof(answer)+1);
	if (result!=RSP_OK)
		return result;
	return checkAnswer(answer, sizeof(answer));	
}

FelixRK::Result FelixRK::internalCheckSubtotal(int iType, Decimal dSum, Decimal * pdRest, Decimal * pdChangeSum)
{
	if(iType<1 || iType>4)
	{
		setErrorText(tr("Wrong payment"));
		return RSP_INVALIDPARAMETER1;
	}

	m_bTmpOpNum = 0x99;
	if(pdRest)
		*pdRest = 0;
	if(pdChangeSum)
		*pdChangeSum = 0;

	Result result;
	Byte sum[5];
	if ((result=fromDecimal(dSum, sum, sizeof(sum), DTPrice))!=RSP_OK) // There can be overflow or something.
		return result;
	Byte cmd[10] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0, iType};
	for(unsigned char i=0;i<5;i++)
		cmd[5+i] = sum[i];
	Byte answer[12];
	result = sendCommand(cmd,sizeof(cmd), answer, sizeof(answer)+1);

	if(result!=RSP_OK) return result;
	result = checkAnswer(answer, sizeof(answer));
	if(result!=RSP_OK) return result;

	Byte pBuf[5];
	for(unsigned char i=0;i<5;i++)
		pBuf[i] = answer[2+i];
	if (pdRest) result=toDecimal(pBuf, 5, pdRest, DTPrice);
	for(unsigned char i=0;i<5;i++)
		pBuf[i] = answer[7+i];
	if (pdChangeSum) result=toDecimal(pBuf, 5, pdChangeSum, DTPrice);
	return result;
}

FelixRK::Result FelixRK::internalPayingIn(Decimal dSum)
{
	Result result;
	Byte sum[5];
	if ((result=fromDecimal(dSum, sum, sizeof(sum), DTPrice))!=RSP_OK) // There can be overflow or something.
		return result;
	m_bTmpOpNum = 0x49;
	Byte cmd[9] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0};
	for(unsigned char i=0;i<5;i++)
		cmd[4+i] = sum[i];
	Byte answer[3];
	result = sendCommand(cmd,sizeof(cmd), answer, sizeof(answer)+1);
	if(result!=RSP_OK)
		return result;
	return checkAnswer(answer, sizeof(answer));
}

FelixRK::Result FelixRK::internalPayment(Decimal dSum)
{
	Result result;
	Byte sum[5];
	if ((result=fromDecimal(dSum, sum, sizeof(sum), DTPrice))!=RSP_OK) // There can be overflow or something.
		return result;
	m_bTmpOpNum = 0x4F;
	Byte cmd[9] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0};
	for(unsigned char i=0;i<5;i++)
		cmd[4+i] = sum[i];
	Byte answer[3];
	result = sendCommand(cmd,sizeof(cmd), answer, sizeof(answer)+1);
	if(result!=RSP_OK)
		return result;
	return checkAnswer(answer, sizeof(answer));
}


FelixRK::Result FelixRK::internalAddDiscountStorno()
{
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalRing()
{
	m_bTmpOpNum = 0x47;
	Byte cmd[3]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
	return sendCommand(cmd, sizeof(cmd), 0, 0, 0, 0, false);
}

FelixRK::Result FelixRK::internalRepeatDocument()
{
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalOpenCheck(int iType)
{
	setDeviceError(0);
	if(iType<0 || iType>3)
	{
		setErrorText(tr("Wrong check type"));
		return CRERROR_INVALIDCALL;
	}

	m_bTmpOpNum = 0x92;
	Byte cmd[5]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, 0, iType};
	Byte answer[3];
	Result result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);
	if(result!=RSP_OK) return result;
	return checkAnswer(answer, sizeof(answer));	
}

int FelixRK::getMaxPrint()
{
/*
ККМ Триум-Ф: X = 0..40;
ККМ ФЕЛИКС-Р Ф: X =0..20;
ККМ ФЕЛИКС-02К: X =0..20;
ККМ «Меркурий-140Ф» АТОЛ: X =0..24;
ККМ ТОРНАДО: X =0..48;
ККМ Меркурий MS-K: X =0..39;
ККМ ФЕЛИКС-Р К: X =0..38;
ККМ ФЕЛИКС-3СК: X =0..38.  
  */    
    if(m_maxPrn!=0) return m_maxPrn;
    Result result;    
    Byte model;
    QString name;
    result = internalDeviceType(NULL, NULL, &model, NULL, NULL, name);
    if(result!=RSP_OK) return result;
    switch(model)
    {
    case 13: m_maxPrn = 40; break;
    case 14: m_maxPrn = 20; break;
    case 15: m_maxPrn = 20; break;
    case 16: m_maxPrn = 24; break;
    case 20: m_maxPrn = 48; break;
    case 23: m_maxPrn = 39; break;
    case 24: m_maxPrn = 32; break;
    case 27: m_maxPrn = 38; break;
    default: m_maxPrn = 20; break;
    }    
    return m_maxPrn;
}

FelixRK::Result FelixRK::internalDeviceType(Byte * pProtocol, Byte * pType, Byte * pModel, Byte pMode[2], Byte pVersion[5], QString &name)
{
    m_bTmpOpNum = 0xA5;
    Byte cmd[3]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
    Byte answer[255];
    memset((void*)answer, 0, 255);
    Result result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);
    if(result!=RSP_OK && result!=RSP_TIMEOUT) return result;
    if(answer[0]!=0) return RSP_TIMEOUT;
    if(pProtocol) *pProtocol = answer[1];
    if(pType) *pType = answer[2];
    if(pModel) *pModel = answer[3];
    if(pMode) { pMode[0] = answer[4]; pMode[1] = answer[5]; }
    if(pVersion) memcpy(pVersion, answer+6, 5);
    char model[255];
    memcpy(model, answer+9, 246);
    if(name) name.fromUtf8(deviceToUtf8(QCString((const char *)model, 246)));
    return RSP_OK;
}

FelixRK::Result FelixRK::internalPrintLine(const QString & line)
{    
    int maxPrn = getMaxPrint();
    m_bTmpOpNum = 0x4C;
    struct
    {
	Byte accessPass[2];
	Byte cmd;
	Byte line[40]; 
    }lCmd;
    memcpy((void*)lCmd.accessPass,(void*)m_baAccessPass,sizeof(lCmd.accessPass));	
    lCmd.cmd = m_bTmpOpNum;
    Byte result = stringToByteArray(line, lCmd.line, maxPrn);
    if(result!=RSP_OK) return result;
    Byte answer[3];
    result=sendCommand((Byte*)&lCmd,3+maxPrn,answer,sizeof(answer)+1);
    if(result!=RSP_OK) return result;
    return checkAnswer(answer, sizeof(answer));	
}

FelixRK::Result FelixRK::internalPrintBoldLine(const QString & line, bool bOnCheckTape, bool bOnJournalTape, Byte & OpNum)
{
	Q_UNUSED(line);
	Q_UNUSED(bOnCheckTape);
	Q_UNUSED(bOnJournalTape);
	Q_UNUSED(OpNum);	
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalPrintHeader(const QString & header, int iDocNumber, int *piSeqDocNumber, Byte & OpNum)
{
	Q_UNUSED(header);
	Q_UNUSED(iDocNumber);
	Q_UNUSED(piSeqDocNumber);
	Q_UNUSED(OpNum);	
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalGetMoneyAccumValue(int accumNum, Decimal *pdValue, Byte & OpNum)
{
	Q_UNUSED(accumNum);
	Q_UNUSED(pdValue);
	Q_UNUSED(OpNum);	
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalGetOperRegisterValue(int regNum, int parNum1, int parNum2, Byte * pValue, int * iSize)
{
// Sanity checks
	if (regNum<1 || regNum>23)
	{
		setErrorText(tr("Register number is out of range (1..23)."));
		return RSP_INVALIDPARAMETER1;
	}

	if (parNum1<0 || parNum1>255)
	{
		setErrorText(tr("Parameter 1  of register is out of range (0..255)."));
		return RSP_INVALIDPARAMETER2;
	}

	if (parNum2<0 || parNum2>255)
	{
		setErrorText(tr("Parameter 2 of register is out of range (0..255)."));
		return RSP_INVALIDPARAMETER3;
	}

	m_bTmpOpNum = 0x91;
	Byte cmd[6]={m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, regNum, parNum1, parNum2};
	Result result = RSP_INVALIDPARAMETER4;
	if(pValue) result = sendCommand(cmd, sizeof(cmd), pValue, 11, 0, iSize);
	if(result!=RSP_OK) return result;
	return checkAnswer(pValue, *iSize);	
}

FelixRK::Result FelixRK::internalWriteLicense(const Byte * pLic /* Byte [5] */)
{
	Q_UNUSED(pLic);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalReadLicense(Byte * pLic /* Byte [5] */)
{
	Q_UNUSED(pLic);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalSetTime(int hour, int min, int sec)
{
	Q_UNUSED(hour);
	Q_UNUSED(min);
	Q_UNUSED(sec);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalSetDate(int day, int month, int year)
{
	Q_UNUSED(day);
	Q_UNUSED(month);
	Q_UNUSED(year);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalCommitDate(int day, int month, int year)
{
	Q_UNUSED(day);
	Q_UNUSED(month);
	Q_UNUSED(year);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalBeginDump(int devNum, int * pBlockCount)
{
	Q_UNUSED(devNum);
	Q_UNUSED(pBlockCount);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalGetData(int *pDevNum, int *pBlockNum, Byte * pData, int szBufSize)
{
	Q_UNUSED(pDevNum);
	Q_UNUSED(pBlockNum);
	Q_UNUSED(pData);
	Q_UNUSED(szBufSize);	
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalEndDump()
{
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalDailyReport(Byte reportType)
{
	m_bTmpOpNum = 0x67;
	Byte cmd[4] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum, reportType};
	Byte answer[3];
	Result result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);
	if(result==RSP_OK)
	{
		result = checkAnswer(answer, sizeof(answer));
		if(result!=RSP_OK)
			return result;
	}

	FRShortState state;
	do{
		result = internalReadShortState(&state);
		Sleep(500);
	} while(state.frMode==0x22);
	
	if(state.frMode==0x02)
	{
		setErrorText(tr("Printing X-Report error %1").arg(flagsStr(state.frFlags)));
		return RSP_INTERNALERROR;
	}

//	m_bTmpOpNum = 0x73;
//	Byte cmd_end[3] =  {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
//	result = sendCommand(cmd_end, sizeof(cmd_end), answer, sizeof(answer)+1);
//	if(result==RSP_OK)
//		return checkAnswer(answer, sizeof(answer));
	return result;
}

FelixRK::Result FelixRK::internalDailyReportAndClear()
{
	m_bTmpOpNum = 0x5A;
	Byte cmd[3] = {m_baAccessPass[0], m_baAccessPass[1], m_bTmpOpNum};
	Byte answer[3];
	Result result = sendCommand(cmd, sizeof(cmd), answer, sizeof(answer)+1);
	if(result==RSP_OK)
	{
		result = checkAnswer(answer, sizeof(answer));
		if(result!=RSP_OK)
			return result;
	}

	FRShortState state;
	do{
		result = internalReadShortState(&state);
		Sleep(500);
	} while(state.frMode==0x23);
	if(state.frMode!=0x17)
	{
		setErrorText(tr("Printing Z-Report error %1").arg(flagsStr(state.frFlags)));
		return RSP_INTERNALERROR;
	}

	do{
		result = internalReadShortState(&state);
		Sleep(500);
	} while(state.frMode==0x17);
	
	return RSP_OK;
}

FelixRK::Result FelixRK::internalSetDecimalPointPos(int iFlag)
{
	Q_UNUSED(iFlag);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalResetTables()
{
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalCutCheck(int iCutType)
{
	Q_UNUSED(iCutType);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalTotalClear()
{
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalOpenCashbox(int iCashboxNumber)
{
	Q_UNUSED(iCashboxNumber);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalContinuePrint()
{
	return CRERROR_NOTSUPPORTED;
}

/*! /en	Operator password required. /_en
	/ru Тестовый прогон. /_ru */
FelixRK::Result FelixRK::internalTestRun(int iPeriodInMin)
{
	Q_UNUSED(iPeriodInMin);
	return CRERROR_NOTSUPPORTED;
}

/*! /en	Operator password required. /_en
	/ru Остановить тестовый прогон. /_ru */
FelixRK::Result FelixRK::internalStopTestRun()
{
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::internalTapeAdvance(int flags, int iLineCount)
{
	Q_UNUSED(flags);
	Q_UNUSED(iLineCount);
	return CRERROR_NOTSUPPORTED;
}

FelixRK::Result FelixRK::stringToByteArray(const QString & text, Byte * pBuf, int szSize)
{
	if (pBuf==0)
	{
		setErrorText(tr("stringToByteArray: pBuf==0"));
		return RSP_INVALIDPARAMETER2;
	}
	if (szSize<=0)
	{
		setErrorText(tr("stringToByteArray: szSize<=0"));
		return RSP_INVALIDPARAMETER3;
	}
	QCString devStr=utf8ToDevice(text);
	memset((void*)pBuf,0,szSize);
	memcpy((void*)pBuf,(const void*)((const char*)devStr),min((uint)szSize,devStr.length()));
	return RSP_OK;
}

QString FelixRK::devErrorText(int err)
{
	QString et=tr("Unknown error 0x%1").arg((int)err,0,16);;
	switch(err)
	{
	case 0x00:	et=trUtf8("Ошибок нет"); break;
	case 0x01:	et=trUtf8("Контрольная лента обработана без ошибок"); break;
	case 0x08:	et=trUtf8("Неверная цена (сумма)"); break;
	case 0x09:	et=trUtf8("Некорректная длина команды"); break;
	case 0x0A:	et=trUtf8("Неверное количество"); break;
	case 0x0B:	et=trUtf8("Переполнение счетчика наличности"); break;
	case 0x0C:	et=trUtf8("Невозможно сторно последней операции"); break;
	case 0x0D:	et=trUtf8("Сторно по коду невозможно (в чеке зарегистрировано меньшее количество товаров с указанным кодом)"); break;
	case 0x0E:	et=trUtf8("Невозможен повтор последней операции"); break;
	case 0x0F:	et=trUtf8("Повторная скидка на операцию невозможна"); break;
	case 0x10:	et=trUtf8("Скидка/надбавка на предыдущую операцию невозможна"); break;
	case 0x11:	et=trUtf8("Неверный код товара"); break;
	case 0x12:	et=trUtf8("Неверный штрих-код товара");	break;
	case 0x13:	et=trUtf8("Неверный формат"); break;
	case 0x14:	et=trUtf8("Неверная длина"); break;
	case 0x15:	et=trUtf8("ККМ заблокирована в режиме ввода даты"); break;
	case 0x16:	et=trUtf8("Требуется подтверждение ввода даты"); break;
	case 0x18:	et=trUtf8("Нет больше данных для передачи ПО ККМ"); break;
	case 0x19:	et=trUtf8("Нет подтверждения или отмены продажи"); break;
	case 0x1A:	et=trUtf8("Отчет с гашением прерван. Вход в режим невозможен."); break;
	case 0x1B:	et=trUtf8("Отключение контроля наличности невозможно (не настроены необходимые типы оплаты)."); break;
	case 0x1E:	et=trUtf8("Вход в режим заблокирован"); break;
	case 0x1F:	et=trUtf8("Проверьте дату и время"); break;
	case 0x20:	et=trUtf8("Дата и время в ККМ меньше чем в ЭКЛЗ"); break;
	case 0x21:	et=trUtf8("Невозможно закрыть архив"); break;
	case 0x3D:	et=trUtf8("Товар не найден"); break;
	case 0x3E:	et=trUtf8("Весовой штрих-код с количеством <>1.000"); break;
	case 0x3F:	et=trUtf8("Переполнение буфера чека"); break;
	case 0x40:	et=trUtf8("Недостаточное количество товара"); break;
	case 0x41:	et=trUtf8("Сторнируемое количество больше проданного"); break;
	case 0x42:	et=trUtf8("Заблокированный товар не найден в буфере чека"); break;
	case 0x43:	et=trUtf8("Данный товар не продавался в чеке, сторно невозможно "); break;
	case 0x44:	et=trUtf8("Memo PlusTM 3TM заблокировано с ПК"); break;
	case 0x45:	et=trUtf8("Ошибка контрольной суммы таблицы настроек Memo PlusTM 3TM"); break;
	case 0x46:	et=trUtf8("Неверная команда от ККМ"); break;
	case 0x66:	et=trUtf8("Команда не реализуется в данном режиме ККМ"); break;
	case 0x67:	et=trUtf8("Нет бумаги"); break;
	case 0x68:	et=trUtf8("Нет связи с принтером чеков"); break;
	case 0x69:	et=trUtf8("Механическая ошибка печатающего устройства"); break;
	case 0x6A:	et=trUtf8("Неверный тип чека"); break;
	case 0x6B:	et=trUtf8("Нет больше строк картинки"); break;
	case 0x6C:	et=trUtf8("Неверный номер регистра"); break;
	case 0x6D:	et=trUtf8("Недопустимое целевое устройство"); break;
	case 0x6E:	et=trUtf8("Нет места в массиве картинок"); break;
	case 0x6F:	et=trUtf8("Неверный номер картинки / картинка отсутствует"); break;
	case 0x70:	et=trUtf8("Сумма сторно больше, чем было получено данным типом оплаты"); break;
	case 0x71:	et=trUtf8("Сумма не наличных платежей превышает сумму чека"); break;
	case 0x72:	et=trUtf8("Сумма платежей меньше суммы чека"); break;
	case 0x73:	et=trUtf8("Накопление меньше суммы возврата или аннулирования"); break;
	case 0x75:	et=trUtf8("Переполнение суммы платежей"); break;
	case 0x76:	et=trUtf8("(зарезервировано)"); break;
	case 0x7A:	et=trUtf8("Данная модель ККМ не может выполнить команду"); break;
	case 0x7B:	et=trUtf8("Неверная величина скидки / надбавки"); break;
	case 0x7C:	et=trUtf8("Операция после скидки / надбавки невозможна"); break;
	case 0x7D:	et=trUtf8("Неверная секция"); break;
	case 0x7E:	et=trUtf8("Неверный вид оплаты"); break;
	case 0x7F:	et=trUtf8("Переполнение при умножении"); break;
	case 0x80:	et=trUtf8("Операция запрещена в таблице настроек"); break;
	case 0x81:	et=trUtf8("Переполнение итога чека"); break;
	case 0x82:	et=trUtf8("Открыт чек аннулирования – операция невозможна"); break;
	case 0x84:	et=trUtf8("Переполнение буфера контрольной ленты"); break;
	case 0x86:	et=trUtf8("Вносимая клиентом сумма меньше суммы чека"); break;
	case 0x87:	et=trUtf8("Открыт чек возврата – операция невозможна"); break;
	case 0x88:	et=trUtf8("Смена превысила 24 часа"); break;
	case 0x89:	et=trUtf8("Открыт чек продажи – операция невозможна"); break;
	case 0x8A:	et=trUtf8("Переполнение ФП"); break;
	case 0x8C:	et=trUtf8("Неверный пароль"); break;
	case 0x8D:	et=trUtf8("Буфер контрольной ленты не переполнен"); break;
	case 0x8E:	et=trUtf8("Идет обработка контрольной ленты"); break;
	case 0x8F:	et=trUtf8("Обнуленная касса (повторное гашение невозможно)"); break;
	case 0x91:	et=trUtf8("Неверный номер таблицы"); break;
	case 0x92:	et=trUtf8("Неверный номер ряда"); break;
	case 0x93:	et=trUtf8("Неверный номер поля"); break;
	case 0x94:	et=trUtf8("Неверная дата"); break;
	case 0x95:	et=trUtf8("Неверное время"); break;
	case 0x96:	et=trUtf8("Сумма чека по секции меньше суммы сторно"); break;
	case 0x97:	et=trUtf8("Подсчет суммы сдачи невозможен"); break;
	case 0x98:	et=trUtf8("В ККМ нет денег для выплаты"); break;
	case 0x9A:	et=trUtf8("Чек закрыт – операция невозможна"); break;
	case 0x9B:	et=trUtf8("Чек открыт – операция невозможна"); break;
	case 0x9C:	et=trUtf8("Смена открыта, операция невозможна"); break;
	case 0x9D:	et=trUtf8("ККМ заблокирована, ждет ввода пароля доступа к ФП"); break;
	case 0x9E:	et=trUtf8("Заводской номер уже задан"); break;
	case 0x9F:	et=trUtf8("Количество перерегистраций не может быть более 4"); break;
	case 0xA0:	et=trUtf8("Ошибка Ф.П."); break;
	case 0xA2:	et=trUtf8("Неверная смена"); break;
	case 0xA3:	et=trUtf8("Неверный тип отчета"); break;
	case 0xA4:	et=trUtf8("Недопустимый пароль"); break;
	case 0xA5:	et=trUtf8("Недопустимый заводской номер ККМ"); break;
	case 0xA6:	et=trUtf8("Недопустимый РНМ"); break;
	case 0xA7:	et=trUtf8("Недопустимый ИНН"); break;
	case 0xA8:	et=trUtf8("ККМ не фискализирована"); break;
	case 0xA9:	et=trUtf8("Не задан заводской номер"); break;
	case 0xAA:	et=trUtf8("Нет отчетов"); break;
	case 0xAB:	et=trUtf8("Режим не активизирован"); break;
	case 0xAC:	et=trUtf8("Нет указанного чека в КЛ"); break;
	case 0xAD:	et=trUtf8("Нет больше записей КЛ"); break;
	case 0xAE:	et=trUtf8("Некорректный код или номер кода защиты ККМ"); break;
	case 0xB0:	et=trUtf8("Требуется выполнение общего гашения"); break;
	case 0xB1:	et=trUtf8("Команда не разрешена введенными кодами защиты ККМ"); break;
	case 0xB2:	et=trUtf8("Невозможна отмена скидки/надбавки"); break;
	case 0xB3:	et=trUtf8("Невозможно закрыть чек данным типом оплаты (в чеке присутствуют  операции без контроля наличных)"); break;
	case 0xBA:	et=trUtf8("Ошибка обмена с фискальным модулем"); break;
	case 0xBe:	et=trUtf8("Необходимо провести профилактические работы"); break;
	case 0xC8:	et=trUtf8("Нет устройства, обрабатывающего данную команду"); break;
	case 0xC9:	et=trUtf8("Нет связи с внешним устройством"); break;
	case 0xCA:	et=trUtf8("Ошибочное состояние ТРК"); break;
	case 0xCB:	et=trUtf8("Больше одной регистрации в чеке"); break;
	case 0xCC:	et=trUtf8("Ошибочный номер ТРК"); break;
	case 0xCD:	et=trUtf8("Неверный делитель"); break;
	case 0xCF:	et=trUtf8("В ККМ произведено 20 активизаций"); break;
	case 0xD0:	et=trUtf8("Активизация данной ЭКЛЗ в составе данной ККМ невозможна"); break;
	case 0xD1:	et=trUtf8("Перегрев головки принтера"); break;
	case 0xD2:	et=trUtf8("Ошибка обмена с ЭКЛЗ на уровне интерфейса I2C"); break;
	case 0xD3:	et=trUtf8("Ошибка формата передачи ЭКЛЗ"); break;
	case 0xD4:	et=trUtf8("Неверное состояние ЭКЛЗ"); break;
	case 0xD5:	et=trUtf8("Неисправимая ошибка ЭКЛЗ"); break;
	case 0xD6:	et=trUtf8("Авария крипто-процессора ЭКЛЗ"); break;
	case 0xD7:	et=trUtf8("Исчерпан временной ресурс ЭКЛЗ"); break;
	case 0xD8:	et=trUtf8("ЭКЛЗ переполнена"); break;
	case 0xD9:	et=trUtf8("В ЭКЛЗ переданы неверная дата или время"); break;
	case 0xDA:	et=trUtf8("В ЭКЛЗ нет запрошенных данных"); break;
	case 0xDB:	et=trUtf8("Переполнение ЭКЛЗ (итог чека)"); break;
	}
	return et;
}

bool FelixRK::openCheck()
{
	return openCheck(CRO_SELL);
}

bool FelixRK::openCheck(int eDocumentType)
{
	if (m_vCheckBuffer.size()==0)
	{
		if ((eDocumentType & ~CRO_OPMASK)!=0)
		{
			setErrorText(tr("Unsupported document type."));
			return CRERROR_INVALIDCALL;
		}
		int fdt=0;
		switch(eDocumentType)
		{
		case CRO_SELL:
			fdt=FDT_SELL;
			break;
		case CRO_SELLRET:
			fdt=FDT_SELLRET;
			break;
		default:
			setErrorText(tr("Unsupported document type."));
			return CRERROR_INVALIDCALL;
		}
		m_bCheckIsOpen=true;		
		m_CheckInfo.m_CheckOperation = fdt;
		m_CheckInfo.m_DefaultOperation = fdt;
		setDeviceError(0);
		return true;
	}
	else
	{
		setErrorText("Current check isn't empty.");
		return false;
	}
}

bool FelixRK::cancelPrint()
{
	
	if (m_vCheckBuffer.size()==0)
	{
		setErrorText("Current check is empty.");
		return false;
	}
	m_vCheckBuffer.clear();
	return true;
}

bool FelixRK::sellAdd( const QString &name, int dep, Decimal summa, Decimal quantity, int qdec )
{
	PurchaseInfo pi(name,dep,summa,quantity,qdec);
	m_vCheckBuffer.push_back(pi);
	return 1;
}

bool FelixRK::printCheck(bool bRet)
{
	if (m_vCheckBuffer.size()==0)
	{
		setErrorText("Current check is empty.");
		return false;
	}
	if (internalEnterMode(MODE_REGISTRATION, PTOperator)!=RSP_OK)
		goto errorexit;
	if (internalOpenCheck(bRet?FDT_SELLRET:FDT_SELL)!=RSP_OK)
		goto errorexit;
	for(uint i=0;i<m_vCheckBuffer.size();++i)
	{
		if(internalPrintLine(m_vCheckBuffer[i].m_name)!=RSP_OK)
			goto errorexit;
		if(internalAddOperation(bRet?FOP_SELLRET:FOP_SELL, (Decimal)m_vCheckBuffer[i].m_quantity,(Decimal)m_vCheckBuffer[i].m_price,(Byte)m_vCheckBuffer[i].m_dep)!=RSP_OK)
			goto errorexit;
	}
	Decimal change, rest;
	if (internalCheckSubtotal(1, 25, &rest, &change)!=RSP_OK)
		goto errorexit;
	if (internalCloseCheck(0, &change)!=RSP_OK)
		goto errorexit;
	m_vCheckBuffer.clear();
	return true;
errorexit:
	internalExitMode();
	m_vCheckBuffer.clear();
	return false;
}



Q_ULONG FelixRK::readMachineNumber()
{
	FRState st;
	if (internalReadState(&st)==RSP_OK) 
		setMachineNumber(from4Bytes(st.serialNumber));
	else 
		setMachineNumber(0);
	return machineNumber();
}



bool FelixRK::isCheckOpened()
{
	return m_bCheckIsOpen;
}

bool FelixRK::onlinePrintMode()
{
	return m_bOnlinePrintMode;
}

void FelixRK::setOnlinePrintMode(bool bOnlinePM)
{
	if(!isCheckOpened())
		m_bOnlinePrintMode = bOnlinePM;
}

bool FelixRK::isOnlinePrintModeSupported()
{
	return true;
}

int FelixRK::openCheck(int eDocumentType, int & /*iReserved*/)
{
	int paymenttype=eDocumentType & CRO_OPMASK;
	if ((eDocumentType & ~CRO_OPMASK)!=0 || paymenttype==CRO_BUY || paymenttype==CRO_BUYSTORNO || paymenttype==CRO_CASHIN || paymenttype==CRO_CASHOUT || paymenttype==CRO_SELLSTORNO)
	{
		setErrorText(tr("Unsupported document type."));
		return CRERROR_INVALIDCALL;
	}
	int fdt=0;
	int fop=0;
	switch(eDocumentType)
	{
	case CRO_SELL:
		fdt=FDT_SELL;
		fop=FOP_SELL;
		break;
	case CRO_SELLRET:
		fdt=FDT_SELLRET;
		fop=FOP_SELLRET;
		break;
	default:
		setErrorText(tr("Unsupported document type."));
		return CRERROR_INVALIDCALL;
	}
	m_CheckInfo.m_CheckOperation=fdt;
	m_CheckInfo.m_DefaultOperation=fop;
	if (onlinePrintMode())
	{
		int res=internalOpenCheck(fdt);
		if (res==RSP_OK)
		{
			m_bCheckIsOpen=true;
			return CRERROR_OK;
		}
		else
			return CRERROR_DEVICEERROR;
	}
	else
	{
		m_bCheckIsOpen=true;
		return CRERROR_OK;
	}
}

int FelixRK::beginAdd(int /*iReserved*/)
{
   // This macro incorporates OClHelper, which automagically opens/closes port as needed.
	if (!isCheckOpened())
	{
		setErrorText(tr("Check isn't opened. I cannot beginAdd()."));
		return CRERROR_INVALIDCALL;
	}
	if (m_bCrItBAdd)
	{
		setErrorText(tr("Previous call to beginAdd() was not matched with endAdd()."));
		return CRERROR_INVALIDCALL;
	}
	m_CurrentItem.clear();
	m_bCrItCompleted=false;
	m_bCrItProcessed=false;
	m_bCrItBAdd=true;
	m_bCrItBAddImplicit=false;
	return CRERROR_OK;
}

int FelixRK::setDiscount(Decimal dDiscount)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	m_CurrentItem.m_dDiscount=dDiscount;
	m_CurrentItem.m_isDiscountInPercent=false;
	m_CurrentItem.m_isEmpty=false;
	return CRERROR_OK;
}

int FelixRK::setDiscountPercent(Decimal dDisPer)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	m_CurrentItem.m_dDiscount=dDisPer;
	m_CurrentItem.m_isDiscountInPercent=true;
	m_CurrentItem.m_isEmpty=false;
	return CRERROR_OK;
}

int FelixRK::setItemSection(int iSection)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	m_CurrentItem.m_dep=iSection;
	m_CurrentItem.m_isEmpty=false;
	return CRERROR_OK;
}

int FelixRK::setOperation(int eOperationType)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	int fdt=0;	
	switch(eOperationType)
	{
	case CRO_SELL:
		fdt=FDT_SELL;
		break;
	case CRO_SELLRET:
		fdt=FDT_SELLRET;
		break;
	default:
		setErrorText(tr("Unsupported operation type."));
		return CRERROR_INVALIDCALL;
	}
	m_CurrentItem.m_iOperation=fdt;
	m_CurrentItem.m_isEmpty=false;
	return CRERROR_OK;
}

int FelixRK::setUnit(const QString & sUnit)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	m_CurrentItem.m_sUnit=sUnit;
	m_CurrentItem.m_isEmpty=false;
	return CRERROR_OK;
}

int FelixRK::setComment(const QString & sComment)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	m_CurrentItem.m_sUnit=sComment;
	m_CurrentItem.m_isEmpty=false;
	return CRERROR_OK;
}

int FelixRK::setItem(const QString & sName, Decimal dPrice, Decimal dQuantity)
{
	int ret=checkForBeginAdd();
	if (ret) return ret;// CRERROR_OK == 0, so...
	m_CurrentItem.m_name=sName;
	m_CurrentItem.m_price=dPrice;
	m_CurrentItem.m_quantity=dQuantity;
	m_CurrentItem.m_isEmpty=false;
	m_bCrItCompleted=true; //Disable attributes addition
	if (m_bCrItBAddImplicit)
		return endAdd(0);
	return CRERROR_OK;
}

int FelixRK::endAdd(int /*iReserved*/)
{
	int ret=CRERROR_OK;
	if (!m_bCrItBAdd)
	{
		setErrorText(tr("There was no matching beginAdd() call."));
		return CRERROR_INVALIDCALL;
	}
	if (!m_bCrItCompleted)
	{
		setErrorText(tr("There was no setItem() call. Item isn't complete."));
		return CRERROR_INVALIDCALL;
	}
	if (m_bOnlinePrintMode)
	{
		ret=printItemOut(m_CurrentItem);
	}
	else
		m_vCheckBuffer.push_back(m_CurrentItem);
	m_bCrItBAdd=false;
	m_bCrItProcessed=true;
	m_bCrItCompleted=false;
	m_CurrentItem.clear();
	return ret;
}

/*! \fn int TECashRegisterFelixRK::printItemOut(PurchaseInfo &item)
/ru Посылает позицию item на ККМ
	\return Ф-ция возвращает CRERROR_OK при успешном выполнении, или один из кодов ошибки CRERROR_XXX.
 /_ru
/en
 /_en
 */
int FelixRK::printItemOut(const PurchaseInfo & item)
{
	int result = internalPrintLine(item.m_name);
	if(result!=RSP_OK)
		return CRERROR_DEVICEERROR;
	result = internalAddOperation(item.m_iOperation, item.m_quantity, item.m_price, item.m_dep);
	if(result!=RSP_OK)
		return CRERROR_DEVICEERROR;
	if(item.m_dDiscount!=0)
	{
		if(item.m_isDiscountInPercent)
			result = internalAddDiscount(1, 0, item.m_dDiscount);
		else
			result = internalAddDiscount(1, 1, item.m_dDiscount);		
		if(result!=RSP_OK)
			return CRERROR_DEVICEERROR;
	}
	
	return CRERROR_OK;
}

int FelixRK::cancelAdd(int /*iReserved*/)
{
	if (m_bCrItBAdd)
	{
		setErrorText(tr("There was no matching beginAdd() call."));
		return CRERROR_INVALIDCALL;
	}
	if (m_bCrItProcessed)
	{
		if (!m_bOnlinePrintMode)
		{
			setErrorText(tr("This item was processed already. I cannot cancel it."));
			return CRERROR_INVALIDCALL;
		} else 
		{
			if(!m_vCheckBuffer.empty())
			{
				PurchaseInfo item = m_vCheckBuffer.last();
				Result result = internalAddOperation(FOP_STORNO, item.m_quantity, item.m_price, item.m_dep);
				if(result!=RSP_OK)
					return CRERROR_DEVICEERROR;
			}
		}
	}
	m_bCrItBAdd=false;
	m_bCrItProcessed=false;
	m_bCrItCompleted=false;
	m_CurrentItem.clear();
	return CRERROR_OK;
}

int FelixRK::setPayment(Decimal dSum, int iType)
{
 	if (!m_bCheckIsOpen)
	{
		setErrorText(tr("Check isn't open. I cannot setPayment(%1,%2).").arg(dSum).arg(iType));
		return CRERROR_INVALIDCALL;
	}
	if (iType<1 || iType>4)
	{
		setErrorText(tr("Unsupported payment type %1. Valid range 1..4.").arg(iType));
		return CRERROR_INVALIDCALL;
	}
	qDebug(QString("setPayment sum %1 type %2").arg(dSum).arg(iType));
	m_CheckInfo.m_mPayment[iType]=dSum;
	return CRERROR_OK;
}

int FelixRK::cancelCheck(int /*iReserved*/)
{
 	if (!m_bCheckIsOpen)
	{
		setErrorText(tr("Check isn't open. I cannot cancelCheck()."));
		return CRERROR_INVALIDCALL;
	}
	if (m_bCrItBAdd)
	{
		int ret=cancelAdd(0); // Открыта позиция, отменяем её.
		if (ret) return ret;
	}
	clearCheckInfo();
	setDeviceError(0);
	Byte ret = internalCancelCheck();
	if(ret!=RSP_OK)
		return CRERROR_DEVICEERROR;
	m_bCheckIsOpen=false;
	return CRERROR_OK;
}

int FelixRK::closeCheck(Decimal &dChange, int /*iReserved*/)
{
	int res;
	if (m_bCrItBAdd)
	{
		setErrorText(tr("There's currently open check position, endAdd() or setItem() wasn't called. I cannot close check."));
		return CRERROR_INVALIDCALL;
	}
	if (onlinePrintMode())
	{ 
		Decimal tChange = 0;
		for(unsigned char i=1;i<5;i++)
		{
			Decimal dSum = m_CheckInfo.m_mPayment[i];
			Decimal tRest;
			if(dSum>0)
				internalCheckSubtotal(i, dSum, &tRest, &tChange);
			dChange+=tChange;
		}
		res = internalCloseCheck(0, &tChange);
		m_bCheckIsOpen=false;
		return CRERROR_OK;
	}
	else
	{
		FRShortState state;
		res=internalReadShortState(&state);
		//trying enter mode withot check error
		internalEnterMode(MODE_REGISTRATION, PTOperator);		
		if ((res=internalOpenCheck(m_CheckInfo.m_CheckOperation))==RSP_COMMANDERROR)
			return CRERROR_DEVICEERROR;
		else if (res)
			return CRERROR_DEVICEERROR;
		
		for(uint i=0;i<m_vCheckBuffer.size();++i)
		{		
			PurchaseInfo & ci=m_vCheckBuffer[i];
			if(internalPrintLine(ci.m_name)!=RSP_OK) return CRERROR_DEVICEERROR;
//			goto checkerror;
			int op=(ci.m_iOperation==-1)?m_CheckInfo.m_DefaultOperation:ci.m_iOperation;				
			if(internalAddOperation(op, (Decimal)ci.m_quantity,(Decimal)ci.m_price,(Byte) ci.m_dep)!=RSP_OK) return CRERROR_DEVICEERROR;
//				goto checkerror;
			if (ci.m_dDiscount!=0)
			{
				if(ci.m_isDiscountInPercent)
					res = internalAddDiscount(1, 0, ci.m_dDiscount);
				else
					res = internalAddDiscount(1, 1, ci.m_dDiscount);		
				if(res!=RSP_OK) return CRERROR_DEVICEERROR;
//					goto checkerror;
			}
		}
		
		dChange = 0;
		Decimal tChange = 0;
		for(unsigned char i=1;i<5;i++)
		{			
			Decimal dSum = m_CheckInfo.m_mPayment[i];
			Decimal tRest;
			tChange = 0;
			if(dSum>0 || i==1) internalCheckSubtotal(i, dSum, &tRest, &tChange);
			dChange+=tChange;
		}
		res = internalCloseCheck(0, &tChange);
		if (res) return CRERROR_DEVICEERROR;
//			goto checkerror;
	}
	clearCheckInfo();
	m_bCheckIsOpen=false;
	setDeviceError(0);
	setErrorText("");
	return CRERROR_OK;
//checkerror:
//	QString error=errorText();
//	clearCheckInfo();
//	m_bCheckIsOpen=false;
//	res = internalCancelCheck();
//	if (res)
//	{
//		setErrorText(tr("!!!There was error while adding check positions: %1. And I cannot cancel check due to error: %1.").arg(error).arg(errorText()));
//		return CRERROR_FATALDEVICEERROR;
//	}
//	else
//		setErrorText(error);
//	return CRERROR_DEVICEERROR;
}

void FelixRK::explainCheckPrintError()
{
	Result res=0;
	FRState fs;
	res = internalReadState(&fs);
	if (res==RSP_OK)
	{
		if (fs.frFlags & 0x80)
			setErrorText(tr("Cash register is out of paper.\nPlease, insert tape and try again."));
		else if (fs.frFlags & 0x40)
			setErrorText(tr("Printer connection error.\nPlease, contact support center."));
		else if (fs.frFlags & 0x20)
			setErrorText(tr("Mechanical printer error.\nPlease, contact support center."));
	}
	else if(res==RSP_COMMANDERROR)
		setErrorText(devErrorText(deviceError()));
	else if(res==RSP_TIMEOUT)
		setErrorText(tr("Device access timeout"));
}

int FelixRK::checkForBeginAdd()
{
   // This macro incorporates OClHelper, which automagically opens/closes port as needed.
	if (m_bCrItCompleted)
	{
		setErrorText(tr("Item was closed by setItem(). Cannot add attribute"));
		return CRERROR_INVALIDCALL;
	}
	if (!m_bCrItBAdd) // beginAdd() wasn't called we should call it implicitly
	{
		int ret=beginAdd(0);
		if (ret)
			return ret;
	}
	m_bCrItBAddImplicit=true;
	return CRERROR_OK;
}

int FelixRK::open()
{
    return super::open();
}

/*! \fn int FelixRK::payment(Decimal dSum)
/ru Выплата денег из кассы.
	Драйвер устройства должен переопределить эту функцию.
	\return Ф-ция возвращает CRERROR_OK при успешном выполнении, или один из кодов ошибки CRERROR_XXX.
 /_ru
/en
 /_en
 */
int FelixRK::payment(Decimal dSum)
{
	if (dSum<=0)
	{
		setErrorText(tr("payment(): Sum must be positive."));
		return CRERROR_INVALIDCALL;
	}
	if(internalEnterMode(MODE_REGISTRATION, PTOperator)!=RSP_OK)
		return CRERROR_DEVICEERROR;
	if (internalPayment(dSum)!=RSP_OK)
		return CRERROR_DEVICEERROR;
	else
		return CRERROR_OK;
}

/*! \fn int FelixRK::payingin(Decimal dSum)
/ru Внесение денег в кассу.
	Драйвер устройства должен переопределить эту функцию.
	\return Ф-ция возвращает CRERROR_OK при успешном выполнении, или один из кодов ошибки CRERROR_XXX.
 /_ru
/en
 /_en
 */
int FelixRK::payingin(Decimal dSum)
{
	if (dSum<=0)
	{
		setErrorText(tr("payingin(): Sum must be positive."));
		return CRERROR_INVALIDCALL;
	}
	if(internalEnterMode(MODE_REGISTRATION, PTOperator)!=RSP_OK)
		return CRERROR_DEVICEERROR;	
	if (internalPayingIn(dSum)!=RSP_OK)
		return CRERROR_DEVICEERROR;
	else
		return CRERROR_OK;
}

int FelixRK::curDocumentNumber(int & iDocNum)
{
	int res=0;
	FRState fs;
	res=internalReadState(&fs);
	if (res!=RSP_OK)
		return CRERROR_DEVICEERROR;

	Decimal dDocNum;
	if(toDecimal(fs.currentDocumentNumber, 2, &dDocNum, DTInteger))
		return CRERROR_DEVICEERROR;
	iDocNum = (int)round(dDocNum);
	return CRERROR_OK;
}

int FelixRK::curChangeNumber(int & iDocNum)
{
	int res=0;
	FRState fs;
	res = internalReadState(&fs);
	if (res!=RSP_OK)
		return CRERROR_DEVICEERROR;

	Decimal dDocNum;
	if(toDecimal(fs.currentChangeNumber, 2, &dDocNum, DTInteger))
		return CRERROR_DEVICEERROR;
	iDocNum = (int)round(dDocNum);
	return CRERROR_OK;
}

int FelixRK::curDocumentNumber()
{
	FRState fs;
	int res = internalReadState(&fs);
	if (res!=RSP_OK)
		return 0;

	Decimal dDocNum;
	toDecimal(fs.currentDocumentNumber, 2, &dDocNum, DTInteger);
	return (int)round(dDocNum);
}

int FelixRK::curChangeNumber()
{
	FRState fs;
	int res = internalReadState(&fs);
	if (res!=RSP_OK)
		return 0;

	Decimal dDocNum;
	toDecimal(fs.currentChangeNumber, 2, &dDocNum, DTInteger);
	return (int)round(dDocNum);
}


int FelixRK::checkDeviceReady()
{
	int ret=CRERROR_OK;
	FRState fs;
	ret = internalReadState(&fs);
	if (ret==RSP_OK)
	{
		if (fs.frFlags & 0x80)
		{ // Device is out of paper.
			setErrorText(tr("Cash register is out of paper.\nPlease, insert tape and try again.\nPlease, contact support center."));
			ret = CRERROR_DEVICEERROR;
		}
		else if (fs.frFlags & 0x40)
		{
			setErrorText(tr("Printer connection error.\nPlease, contact support center."));
			ret = CRERROR_DEVICEERROR;		
		}
		else if (fs.frFlags & 0x20)
		{
			setErrorText(tr("Mechanical printer error.\nPlease, contact support center."));
			ret = CRERROR_DEVICEERROR;		
		}
	} else if(ret==RSP_COMMANDERROR){
		setErrorText(devErrorText(deviceError()));
		return CRERROR_DEVICEERROR;
	}
	return ret;
}

int FelixRK::startDriver()
{
	return open();
}

int FelixRK::stopDriver()
{
	return close();
}

int FelixRK::setCaptureMode(int iMode)
{
	Q_UNUSED(iMode);
	return CRERROR_OK;
}

/*! \fn int FelixRK::openCashbox(int n)
/ru Открыть денежный ящик номер n, нумерация ящиков начинается с 1.
  При исполнении этой функции возможно обращение к устройству.
	\param n - номер денежного ящика (начиная с 1)
	\return Ф-ция возвращает CRERROR_OK при успешном выполнении, или один из кодов ошибки CRERROR_XXX.
 /_ru
/en
 /_en
 */
int FelixRK::openCashbox(int n)
{  
	Result res=internalOpenCashbox(n-1);
	return res==RSP_OK?CRERROR_OK:CRERROR_DEVICEERROR;
}

/*! \fn int FelixRK::ZReport()
/ru Запускает вывод Z-отчёта на устройстве.
  При исполнении этой функции возможно обращение к устройству.
	\return Ф-ция возвращает CRERROR_OK при успешном выполнении, или один из кодов ошибки CRERROR_XXX.
 /_ru
/en
 /_en
 */
int FelixRK::ZReport()
{
	Result res = internalEnterMode(MODE_REPORTSCLEAN, PTAdmin);
	if(res!=RSP_OK)
		return CRERROR_DEVICEERROR;
	res = internalDailyReportAndClear();
	if(res!=RSP_OK)
		return CRERROR_DEVICEERROR;
	return CRERROR_OK;
}

/*! \fn int FelixRK::XReport()
/ru Запускает вывод X-отчёта на устройстве.
  При исполнении этой функции возможно обращение к устройству.
	\return Ф-ция возвращает CRERROR_OK при успешном выполнении, или один из кодов ошибки CRERROR_XXX.
 /_ru
/en
 /_en
 */
int FelixRK::XReport()
{ 
	Result res = internalEnterMode(MODE_REPORTS, PTAdmin);
	if(res!=RSP_OK)
		return CRERROR_DEVICEERROR;
	res = internalDailyReport();
	if(res!=RSP_OK)
		return CRERROR_DEVICEERROR;
	return CRERROR_OK;
}



double FelixRK::summaTotal()
{
	Decimal sum = 0.0;
	return sum;
}

int FelixRK::T5(FelixRK::Byte o)
{
	switch(o)
	{
		case 0x4A: case 0x62: case 0xA7: case 0xA6: case 0x8D: case 0x8E:
			return 20000;
		case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD:
			return 120000;
		case 0x91:
			return 45000;
		default:
			return 1000;
	}
	return 1000;
}

QString FelixRK::flagsStr(Byte flags)
{
	QString bin = QString("%1").arg(flags, 0, 2);
	if(bin.mid(1,1)=="1")
		return tr("Printer communication error");
	if(bin.mid(0,1)=="1")
		return tr("No paper");
	if(bin.mid(2,1)=="1")
		return tr("Printer mechanical error");
	return tr("No error");
}

#include "teplugin.h"
//template TEPlugin<FelixRK>;
typedef TEPlugin<FelixRK> TECashRegisterFelixRKPlugin;
TE_EXPORT_PLUGIN( TECashRegisterFelixRKPlugin )


