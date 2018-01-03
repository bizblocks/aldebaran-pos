#ifndef QUERIES_H
#define QUERIES_H

#include <qstring.h>

class QTranslator;

class Queries
{
public:
    static void setDialect(QString dialect);
    static QString tr(QString query);
    static Queries * getQueries();
protected:
    Queries(QString dialect="qpsql7");
    void init();
    static Queries* instance;
    QString fDialect;
    QTranslator * trans;
    bool loaded;
};

#endif
