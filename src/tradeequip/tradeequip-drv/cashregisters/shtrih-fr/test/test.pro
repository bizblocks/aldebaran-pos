TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on

QT      += qt3support sql

LIBS	+= -L../../../../tradeequip-1.1.0/lib -L../../../lib -ltradeequip -ltecashregister-shtrih-fr

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

DEFINES	+= _CRT_SECURE_NO_DEPRECATE

INCLUDEPATH	+= ../lib ../../../../tradeequip-1.1.0/src/lib

SOURCES	+= main.cpp

FORMS	= mainform.ui

include ( ../../../config.pri )
TARGET      = tecashregister-shtrih-fr-test
# -ltecashregister-shtrih-fr
INCLUDEPATH += ../../../../tradeequip/src/lib
DESTDIR     = ../../../bin

TRANSLATIONS = \
    ../../../translations/tecashregister-shtrih-fr-test-en.ts \
    ../../../translations/tecashregister-shtrih-fr-test-ru.ts 
