#include <qtextcodec.h>
#include <qfile.h>
#include "iecsv.h"

impCSV::impCSV() :
    impShtrihM()
{
    sourceFile = new QFile();
    values.clear();
    values["externalcode"] = "";
    values["barcode"] = "";
    values["name"] = "";
    values["isgroup"] = FALSE;
    values["parentcode"] = "";
    values["price"] = "";
    values["hydrocarbonat"] = "";
    values["fat"] = "";
    values["protein"] = "";
    values["calories"] = "";
    values["description"] = "";
    values["picturename"] = "";
    values["maxdiscount"] = 0;
    //
    values["cardcode"] = "";
    values["cardname"] = "";
    values["cardpercent"] = "";
    fields.clear();
    fields = values.keys();
}

impCSV::~impCSV()
{
    if(sourceFile)
    {
        sourceFile->flush();
        sourceFile->close();
        delete sourceFile;
    }
}

bool impCSV::open(QString fileName)
{
    sourceFile->setName(fileName);
    if(!sourceFile->exists()) return FALSE;
    if(!sourceFile->open(IO_ReadOnly)) return FALSE;
    lines.clear();
    QString str;
    //skip first 2 lines
    Q_ULLONG max = 1024;
    if((str=sourceFile->readLine(max)).isEmpty())
        return FALSE;

    while(!(str=sourceFile->readLine(max)).isEmpty())
    {
        if(str.isEmpty()) continue;
        if(str.find(";")<0) continue;
        lines << str;
    }
    seek(0);
    return TRUE;
}

bool impCSV::seek(int row)
{
    if(!importer::seek(row)) return FALSE;
    QStringList lst = QStringList::split(";", lines[row], TRUE);
    values.clear();
    char firstchar = 0;
    if(lst[0].length()) firstchar = lst[0].ascii()[0];
    switch(firstchar)
    {
    case '%':
        values["cardcode"] = fCodec->toUnicode(lst[0]);
        values["cardname"] = fCodec->toUnicode(lst[1]);
        values["cardpercent"] = lst[3].toDouble();
        break;
    default:
        values["externalcode"] = noQuotes(fCodec->toUnicode(lst[3]));
        values["barcode"] = noQuotes(fCodec->toUnicode(lst[1]));
        values["name"] = noQuotes(fCodec->toUnicode(lst[2]));
        values["price"] = noQuotes(lst[8]).toDouble();
        values["parentcode"] = noQuotes(fCodec->toUnicode(lst[1]));
        values["isgroup"] = noQuotes(lst[0]).toInt();
        values["calories"] = noQuotes(lst[4]).toDouble();
        values["fat"] = noQuotes(lst[5]).toDouble();
        values["protein"] = noQuotes(lst[6]).toDouble();
        values["hydrocarbonat"] = noQuotes(lst[7]).toDouble();
        values["description"] = noQuotes(fCodec->toUnicode(lst[9]));
        values["picturename"] = noQuotes(lst[10]);
        values["maxdiscount"] = 100;
        break;
    }
    return TRUE;
}

QString impCSV::noQuotes(QString str)
{
    str = str.stripWhiteSpace();
    if(str[0]=='\"') str = str.mid(1);
    if(str[str.length()-1]=='\"') str = str.left(str.length()-1);
    return str;
}
