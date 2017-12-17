#include <felix-rk.h>
#include <qapplication.h>
#include <qobject.h>
#include <qmessagebox.h>

#define FR_NAME "TECashRegisterFelixRK"

FelixRK * m_Felix;

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	m_Felix = 0;
	if (te_driverExists( FR_NAME )) 
	{
	    m_Felix = ( FelixRK *) te_createDriverObject( FR_NAME );
	    printf("Driver Felix-RK loaded succesfully\n");
  	} else {
		printf("Driver Felix-RK not installed\n");
	    	return 100;
  	}

	m_Felix->setPortDevice("/dev/ttyS0");
	m_Felix->setDebugLevel(1);
	m_Felix->setPassword(FelixRK::PTAccess,QString("0000"));
	m_Felix->setPassword(FelixRK::PTOperator,QString("30"));
	m_Felix->setPassword(FelixRK::PTAdmin,QString("30"));
	m_Felix->setPortBaudRate(115200);
	m_Felix->setPortDataBits(DATA_8);
	m_Felix->setPortParity(PAR_NONE);
	m_Felix->setPortStopBits(STOP_1);
	m_Felix->setPortFlowControl(FLOW_OFF);		
	int res=m_Felix->open();	
	printf(QObject::tr("open() returns %1\n").arg(res));
	if(res!=1) return 100;

	FRShortState state;
	res = m_Felix->internalReadShortState(&state);
	if(res)
		printf("\nerror %i (%s) in internalReadState()\n", res, (const char*)m_Felix->errorText().utf8());
	else
		printf("\nstate=%X, flags=%X\n", state.frMode, state.frFlags);

	m_Felix->internalRing(); printf("\n");
/*	res = m_Felix->internalPrintLine("12345678901234567890"); 
	if(res)
		printf("\nerror %i (%s) in internalPrintLine()\n", res, (const char*)m_Felix->errorText().utf8());
	else
		printf("\nprinting is ok\n");
	m_Felix->internalPrintLine("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩьЫЪЭЮЯ"); printf("\n");*/
	
//	res = m_Felix->XReport(); 
//	if(res)
//		printf("\nerror %i (%s) in XReport()\n", res, (const char*)m_Felix->errorText().utf8());
//	else
//		printf("\nXReport is ok\n");
//	res = m_Felix->ZReport(); 
//	if(res)
//		printf("\nerror %i (%s) in XReport()\n", res, (const char*)m_Felix->errorText().utf8());
//	else
//		printf("\nXReport is ok\n");
		
	m_Felix->internalCancelCheck();

	int tmp;
	if(!m_Felix->openCheck(CRO_SELL, tmp))
	{
//		m_Felix->setDiscountPercent(5);
		m_Felix->setDiscount(5);
		m_Felix->setPayment(25.5, 1);
		m_Felix->setItem("Булка с маком", 12.1, 2);		
		FelixRK::Decimal change;
		res = m_Felix->closeCheck(change, 0);
		if(res)
			printf("\nerror %i (%s) in closeCheck()\n", res, (const char*)m_Felix->errorText().utf8());
		else
			printf("\ncheck is ok, change is %f\n", change);
	} else
		printf("\nerror (%s) in openCheck()\n", (const char*)m_Felix->errorText().utf8());
//	m_Felix->payingin(100.10);
//	m_Felix->payment(100.10);
	
	printf("\ncheck number=%i\n", m_Felix->curDocumentNumber());
	m_Felix->close();
	printf("\nthe end\n");
	return 0;
}

