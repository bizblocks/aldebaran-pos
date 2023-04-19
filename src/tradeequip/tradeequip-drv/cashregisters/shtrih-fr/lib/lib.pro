TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on debug dll

LIBS	+= -L../../../../tradeequip-1.1.0/lib -ltradeequip

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

DEFINES	+= SHTRIH_BUILD

INCLUDEPATH	+= ../../../../tradeequip-1.1.0/src/lib

HEADERS	+= shtrih-fr.h

SOURCES	+= shtrih-fr.cpp

include ( ../../../config.pri )
TARGET      = tecashregister-shtrih-fr
DESTDIR     = ../../../lib
#DLLDESTDIR	= /lib

TRANSLATIONS = \
    ../../../translations/tecashregister-shtrih-fr-en.ts \
    ../../../translations/tecashregister-shtrih-fr-ru.ts 
    
DEFINES += _CRT_SECURE_NO_DEPRECATE 

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = $(LIBDIR)/tradeequip
  tecashregister-shtrih-fr.path = $(LIBDIR)/tradeequip
  tecashregister-shtrih-fr.extra = cd $(INSTALL_ROOT)$(LIBDIR) && ln -sf tradeequip/libtecashregister-shtrih-fr.so* $(INSTALL_ROOT)$(LIBDIR)
}

INSTALLS += target
INSTALLS += tecashregister-shtrih-fr
