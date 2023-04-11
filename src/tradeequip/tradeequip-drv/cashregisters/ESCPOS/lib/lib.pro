TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

unix:LIBS	+= -L../../../../tradeequip-1.1.0/lib -ltradeequip

unix:INCLUDEPATH	+= ../../../../tradeequip-1.1.0/src/lib

HEADERS	+= ESCPOS.h \
	ESCPOS-config.h

SOURCES	+= ESCPOS.cpp

TARGET      = tecashregister-ESCPOS
DESTDIR     = ../../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = $(LIBDIR)/tradeequip
  tecashregister-ESCPOS.path = $(LIBDIR)/tradeequip
  tecashregister-ESCPOS.extra = cd $(INSTALL_ROOT)$(LIBDIR) && ln -sf  tradeequip/libtecashregister-ESCPOS.so* $(INSTALL_ROOT)$(LIBDIR)
}

INSTALLS += target 
INSTALLS += tecashregister-ESCPOS

