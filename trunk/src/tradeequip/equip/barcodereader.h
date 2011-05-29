#ifndef BARCODEREADER_H
#define BARCOEREADER_H

#include <qpixmap.h>
#include "mscreader.h"

class TEReaderBarcode;
class eqJob;

class  eqBarcodeReader : public eqMSCReader
{
    Q_OBJECT
public:
    eqBarcodeReader(QString name);
    ~eqBarcodeReader();
signals:
    void data(QString);
public slots:
protected slots:
    virtual void onData(int);
private:
};

#endif
