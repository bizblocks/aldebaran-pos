#include <sys/types.h>
#include <sys/stat.h>
#include <qtextcodec.h>
#include <QTextStream>
#include <qfile.h>
#include "ieshtrih.h"

impShtrihM::impShtrihM() :
    importer()
{
    sourceFile = new QFile();
    values.clear();
    values["externalcode"] = "";
    values["name"] = "";
    values["isgroup"] = FALSE;
    values["parentcode"] = "";
    values["barcode"] = "";
    values["price"] = "";
    values["hydrocarbonat"] = "";
    values["fat"] = "";
    values["protein"] = "";
    values["calories"] = "";
    values["maxdiscount"] = "";
    //
    values["cardcode"] = "";
    values["cardname"] = "";
    values["cardpercent"] = "";
    fields.clear();
    fields = values.keys();
}

impShtrihM::~impShtrihM()
{
    if(sourceFile)
    {
        sourceFile->flush();
        sourceFile->close();
        delete sourceFile;
    }
}

bool impShtrihM::open(QString fileName)
{
    sourceFile->setName(fileName);
    if(!sourceFile->exists()) return FALSE;
    if(!sourceFile->open(IO_ReadOnly)) return FALSE;
    lines.clear();
    QString str;
    //skip first 2 lines
    Q_ULLONG max = 1024;
    //TODO check if this works
    if((str=sourceFile->readLine(max)).isEmpty())
        return FALSE;
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

bool impShtrihM::close()
{
    if(sourceFile)
    {
        sourceFile->flush();
        sourceFile->close();
        delete sourceFile;
        sourceFile = NULL;
        return TRUE;
    }
    return FALSE;
}

bool impShtrihM::seek(int row)
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
        values["externalcode"] = fCodec->toUnicode(lst[0]);
        values["barcode"] = fCodec->toUnicode(lst[1]);
        values["name"] = fCodec->toUnicode(lst[2]);
        values["price"] = lst[4].toDouble();
        values["parentcode"] = fCodec->toUnicode(lst[15]);
        values["isgroup"] = !lst[16].toInt();
        values["maxdiscount"] = lst[9].toInt();
        if(lst.count()>20)
        {
            values["hydrocarbonat"] = lst[19].toDouble();
            values["fat"] = lst[20].toDouble();
            values["protein"] = lst[21].toDouble();
            values["calories"] = lst[22].toDouble();
        }
        break;
    }
    return TRUE;
}

QVariant impShtrihM::value(QString name)
{
    QVariant res;
    return values[name];
}

map impShtrihM::toMap()
{
    return values;
}

expShtrihM::expShtrihM() :
    impShtrihM()
{
    sourceFile = new QFile();
    values.clear();
    values["code"] = "";
    values["name"] = "";
    values["isgroup"] = FALSE;
    values["parentcode"] = "";
    values["price"] = "";
    values["hydrocarbonat"] = "";
    values["fat"] = "";
    values["protein"] = "";
    values["calories"] = "";
    fields.clear();
    fields = values.keys();
}

expShtrihM::~expShtrihM()
{
    sourceFile->open(IO_WriteOnly);
    QTextStream ts(sourceFile);
    ts << "#\r\n";
    ts << "1\r\n";
    ts << "1\r\n";
    for(uint i=0;i<lines.count();i++)
    {
        ts << lines[i];
    }
    sourceFile->flush();
    //    system(QString("chmod 666 %1").arg(sourceFile->name()));
    chmod(sourceFile->name(), 0666);
}

bool expShtrihM::open(QString fileName)
{
    QString header="";
    count = 0;
    QFile file;
    sourceFile->setName(fileName);
    lines.clear();
    if(!sourceFile->exists())
    {
        if(!sourceFile->open(IO_WriteOnly)) return FALSE;
    }
    else
    {
        if(!sourceFile->open(IO_ReadWrite)) return FALSE;
    }
    Q_ULLONG max = 1024;
    QString str;
    //TODO check
    while(!(str=sourceFile->readLine(max)).isEmpty())
    {
        if(str.isEmpty()) continue;
        lines << str;
    }
    
    if(lines[0][0]=='@')
    {
        sourceFile->close();
        sourceFile->remove();
        return open(fileName);
    }
    else
    {
        sourceFile->close();
        sourceFile->remove();
        if(lines.count()>2)
        {
            lines.remove(lines.at(0));
            lines.remove(lines.at(0));
            lines.remove(lines.at(0));
        }
    }
    return TRUE;
}

bool expShtrihM::fromMap(map m)
{
    if(!sourceFile) return FALSE;
    QString str;
    for(uint i=0;i<m.count();i++)
    {
        str  += m[m.keys()[i]].toString() + ";";
    }
    lines << str << "\r\n";
    return TRUE;
}
