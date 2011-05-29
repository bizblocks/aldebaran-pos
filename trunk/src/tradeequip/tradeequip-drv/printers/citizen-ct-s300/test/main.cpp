#include <stdio.h>
#include "cts300.h"

int main(int, char **)
{
    CTS300 * printer = new CTS300("/dev/lp0");
    qDebug(printer->getCodepages().join(" "));
    printer->open();
    printer->setCodepage("PC866");
    printer->printLine("------------------------------\n");
    printer->printLine("Тестовая строка\n");
    printer->printBoldLine("TEST BOLD LINE\n");
    printer->printBarcode("123456789012");
    printer->printLine("\n\n\n");
    printer->cut();
}
