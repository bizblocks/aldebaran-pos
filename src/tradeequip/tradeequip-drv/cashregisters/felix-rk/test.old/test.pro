TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on

LIBS	+= -L../../../../tradeequip/lib -L../../../lib -ltradeequip -ltecashregister-felix-rk

DEFINES	+= _CRT_SECURE_NO_DEPRECATE

INCLUDEPATH	+= ../lib

SOURCES	+= main.cpp

#FORMS	= mainform.ui

include ( ../../../config.pri )
TARGET      = tecashregister-felix-fr-test
# -ltecashregister-felix-fr
INCLUDEPATH += ../../../../tradeequip/src/lib
DESTDIR     = ../../../bin

TRANSLATIONS = \
    ../../../translations/tecashregister-felix-rk-test-en.ts \
    ../../../translations/tecashregister-felix-rk-test-ru.ts 
