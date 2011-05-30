#include <stdio.h>
#include "ESCPOS.h"

int main(int, char **)
{
    ESCPOS * printer = new ESCPOS("ip192.168.0.192:9100");
    printer->setDebugLevel(1);
    qDebug(printer->getCodepages().join(" "));
    qDebug(QString("open res: %1").arg(printer->open()));
    printer->setCodepage("PC866");
    printer->print("------------------------------\n");
    printer->print("Тестовая строка\n");
    printer->printBoldLine("TEST BOLD LINE\n");
    printer->printBarcode("1234567890123");
    printer->print("------------------------------\n");    
    printer->print("\n\n\n");
    printer->cut();
}
