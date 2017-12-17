#include <qfile.h>
#include <qtextstream.h>
#include <qregexp.h>
#include "htmltemplate.h"

alHTMLTemplate::alHTMLTemplate() :
	QObject(NULL, "htmlTemplate")
{    
    outStream = new QTextStream(&outStr, IO_WriteOnly);
}

alHTMLTemplate::~alHTMLTemplate()
{
    if(outStream) delete outStream;
}

alHTMLTemplate * alHTMLTemplate::fromText(QString text)
{
    alHTMLTemplate * tpl = new alHTMLTemplate();
    tpl->inText =  text;
    return tpl;
}

alHTMLTemplate * alHTMLTemplate::fromFile(QString filename)
{
    alHTMLTemplate * tpl = new alHTMLTemplate();    
    QFile file(filename);
    file.open(IO_ReadOnly);
    QByteArray array = file.readAll();
    array.resize( array.size() +1 );
    array[ (int)array.size() - 1 ] = '\0';
    tpl->inText = QString::fromUtf8(array);
    return tpl;
}

void alHTMLTemplate::setValue(QString name, QVariant val)
{
    values[name] = val;
}

void alHTMLTemplate::addSection(QString name)
{
    QString sectionStart = QString("%1%2%3%4").arg(SECTION).arg(ASTERIKS)
		      .arg(name).arg(RIGHTBRACKET);
    QString sectionEnd = QString("%1%2%3%4").arg(ENDSECTION).arg(ASTERIKS)
			 .arg(name).arg(RIGHTBRACKET);
    QString section = sectionStart + QString(ASTERIKS) + sectionEnd;
    QRegExp rx(section, FALSE, TRUE);
    rx.setMinimal(TRUE);
    int pos;
    if((pos=rx.search(inText))<0) return;
    QString content = inText.mid(pos, rx.matchedLength());
    
    rx = QRegExp(sectionStart, FALSE, TRUE);
    rx.setMinimal(TRUE);
    pos = rx.search(content);
    sectionStart = content.mid(pos, rx.matchedLength()+1);
    content.replace(sectionStart, "");
    rx = QRegExp(sectionEnd, FALSE, TRUE);
    rx.setMinimal(TRUE);
    pos = rx.search(content);
    sectionEnd = content.mid(pos, rx.matchedLength()+1);
    content.replace(sectionEnd, "");
    
    for(uint i=0;i<values.count();i++)
    {
	QString valname = values.keys()[i];
	QString value = QString("%1 %2%3").arg(VALUE)
			.arg(valname).arg(RIGHTBRACKET);
	QRegExp valx(value, FALSE, TRUE);
	valx.setMinimal(TRUE);
	while(valx.search(content)>-1)
	    content = content.replace(valx, values[valname].toString());
    }
    (*outStream) << content;
}

QString alHTMLTemplate::result()
{
    QString res = outStr;
    return res;
}

