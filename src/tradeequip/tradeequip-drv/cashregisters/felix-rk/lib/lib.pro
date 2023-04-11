TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on dll

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

LIBS	+= -L../../../../tradeequip-1.1.0/lib -ltradeequip

DEFINES	+= FELIX_BUILD

INCLUDEPATH	+= ../../../../tradeequip-1.1.0/src/lib

HEADERS	+= felix-rk.h

SOURCES	+= felix-rk.cpp

include ( ../../../config.pri )
TARGET      = tecashregister-felix-rk
DESTDIR     = ../../../lib
#DLLDESTDIR	= /lib

TRANSLATIONS = \
    ../../../translations/tecashregister-felix-rk-en.ts \
    ../../../translations/tecashregister-felix-rk-ru.ts 
DEFINES += _CRT_SECURE_NO_DEPRECATE 

LIBDIR=/usr/lib

unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
    target.path = $(LIBDIR)/tradeequip
    tecashregister-felix-rk.path = $(LIBDIR)/tradeequip
    tecashregister-felix-rk.extra = cd $(INSTALL_ROOT)$(LIBDIR) && ln -sf tradeequip/libtecashregister-felix-rk.so* $(INSTALL_ROOT)$(LIBDIR)/
}

INSTALLS += target
INSTALLS += tecashregister-felix-rk
