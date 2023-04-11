TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

LIBS	+= -L../../../../tradeequip-1.1.0/lib -L../../../lib -ltradeequip -ltecashregister-felix-rk

DEFINES	+= _CRT_SECURE_NO_DEPRECATE

INCLUDEPATH	+= ../lib ../../../../tradeequip-1.1.0/src/lib

SOURCES	+= main.cpp

FORMS	= mainform.ui

include ( ../../../config.pri )
TARGET      = tecashregister-felix-rk-test
# -ltecashregister-felix-rk
INCLUDEPATH += ../../../../tradeequip/src/lib
DESTDIR     = ../../../bin

TRANSLATIONS = \
    ../../../translations/tecashregister-felix-rk-test-en.ts \
    ../../../translations/tecashregister-felix-rk-test-ru.ts 
