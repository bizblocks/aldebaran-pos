#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include <qobject.h>
#include <qvariant.h>
#include <qmap.h>

class QFile;
class QTextStream;

//tags
#define SECTION "<SECTION"
#define ENDSECTION "<END"
#define VALUE "<VALUE"
#define RIGHTBRACKET ">"
#define ASTERIKS "*"

class alHTMLTemplate : public QObject
{
protected:
    alHTMLTemplate();    
public:
    ~alHTMLTemplate();
    static alHTMLTemplate * fromText(QString txt);
    static alHTMLTemplate * fromFile(QFile file);    
    static alHTMLTemplate * fromFile(QString file);
    void setValue(QString name, QVariant value);
    void addSection(QString name);
    QString result();
private:
    QMap<QString, QVariant> values;
    QString inText;
    QTextStream * outStream;
    QString outStr;
    alHTMLTemplate * root;
    int level;
};

#endif
