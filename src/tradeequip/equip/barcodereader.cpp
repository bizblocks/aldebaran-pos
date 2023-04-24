#include "barcodereader.h"
#include "tereaderbarcode.h"
#include "ui_dlgmscreader.h"

eqBarcodeReader::eqBarcodeReader(QString name) :
    eqMSCReader(name)
{
    reader = NULL;
    fPortDevice = "/dev/null";
    fPortBaudRate = 9600;
    fPortDataBits = DATA_8;
    fPortParity = PAR_NONE;
    fPortStopBits = STOP_1;
    fPortFlowControl = FLOW_OFF;
    fHeader = 0;
    fTrailer = 0;
}


eqBarcodeReader::~eqBarcodeReader()
{
    if(reader)
    {
        reader->close();
        delete reader;
        reader = NULL;
    }
}

void eqBarcodeReader::onData(int ev)
{
    //    if (ev==EVENT_READER_DATAARRIVED)
    {
        QString text = "";
        if(reader)
        {
            text = reader->text();
            //	    qDebug(QString("EVENT_READER_DATAARRIVED: %1").arg(text));
            //	    qDebug(QString("header is %1, trailer is %2, first char is %3").arg(fHeader).arg(fTrailer).arg(text[0]));
            emit data(text); //TODO replace with truck no
        }
        reader->next();
    }
}
