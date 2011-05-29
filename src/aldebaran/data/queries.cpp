#include <qtranslator.h>
#include "queries.h"

Queries * Queries::instance = NULL;

Queries::Queries(QString d)
{
    trans = NULL;
    fDialect = d;
    init();
}

void Queries::init()
{
    if(trans)
	delete trans;
    trans = new QTranslator(0);
    trans->load("queries-"+fDialect.lower(), "/usr/share/aldebaran");
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
    qDebug(QString("source query: %1").arg(query));
    Queries * that = getQueries();
    QTranslatorMessage msg = that->trans->findMessage("Queries", query);
    query = msg.translation();
    qDebug(QString("result query: %1").arg(query));
    return query; 
}
