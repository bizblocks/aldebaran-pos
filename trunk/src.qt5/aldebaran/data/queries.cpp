#include <QDebug>
#include <QTranslator>
#include "queries.h"

Queries * Queries::instance = NULL;

Queries::Queries(QString d)
{
    trans = NULL;
    fDialect = d;
    loaded = false;
}

void Queries::init()
{
    if(trans)
        delete trans;
    trans = new QTranslator(0);
    loaded = trans->load("queries-"+fDialect.toLower(), "/usr/share/aldebaran");
}

Queries * Queries::getQueries()
{
    if(!Queries::instance) 
        Queries::instance = new Queries();
    return Queries::instance;
}

void Queries::setDialect(QString d)
{
    Queries::getQueries()->fDialect = d;
    Queries::getQueries()->init();
}

QString Queries::tr(QString query)
{
//    qDebug() << QString("source query: %1").arg(query);
    Queries * that = getQueries();
    QString trquery = that->trans->translate("Queries", query.toUtf8());
    if(trquery.isEmpty())
        trquery = query;
//    qDebug() << QString("result query: %1").arg(query);
    return trquery;
}
