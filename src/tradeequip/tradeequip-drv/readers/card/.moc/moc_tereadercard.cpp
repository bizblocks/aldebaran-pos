/****************************************************************************
** TEReaderCard meta object code from reading C++ file 'tereadercard.h'
**
** Created: Fri Oct 26 06:49:33 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../tereadercard.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TEReaderCard::className() const
{
    return "TEReaderCard";
}

QMetaObject *TEReaderCard::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TEReaderCard( "TEReaderCard", &TEReaderCard::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString TEReaderCard::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TEReaderCard", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TEReaderCard::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TEReaderCard", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TEReaderCard::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = TEReaderBase::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"TEReaderCard", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TEReaderCard.setMetaObject( metaObj );
    return metaObj;
}

void* TEReaderCard::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TEReaderCard" ) )
	return this;
    return TEReaderBase::qt_cast( clname );
}

bool TEReaderCard::qt_invoke( int _id, QUObject* _o )
{
    return TEReaderBase::qt_invoke(_id,_o);
}

bool TEReaderCard::qt_emit( int _id, QUObject* _o )
{
    return TEReaderBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool TEReaderCard::qt_property( int id, int f, QVariant* v)
{
    return TEReaderBase::qt_property( id, f, v);
}

bool TEReaderCard::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
