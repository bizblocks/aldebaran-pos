#include <stdio.h>
#include "ESCPOS.h"

int main(int, char **)
{
    ESCPOS * printer = new ESCPOS("ip192.168.1.2:9100");
    printer->setDebugLevel(1);
    qDebug(printer->codepages().join(" "));
    qDebug(QString("open res: %1").arg(printer->open()));
    printer->setCodepage("PC866");
    printer->print("------------------------------\n");
    printer->print("Тестовая строка\n");
    printer->printBoldLine("TEST BOLD LINE\n");
//    printer->printBarcode("1234567890123");
//    printer->print("----------------------------------------\n----------------------------------------\n"); //    printer->print("01234567890123456789012345678901234567890123456789\n");    
    printer->print("\n\n\n");
    printer->cut();
    printer->beep();
    printer->openCashbox(0);
}
