TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

unix:LIBS	+= -L../../../../tradeequip-1.1.0/lib -ltradeequip

unix:INCLUDEPATH	+= ../../../../tradeequip-1.1.0/src/lib

HEADERS	+= ESCPOS.h \
	ESCPOS-config.h

SOURCES	+= ESCPOS.cpp

TARGET      = teprinter-ESCPOS
DESTDIR     = ../../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = $(LIBDIR)/tradeequip
  teprinter-ESCPOS.path = $(LIBDIR)/tradeequip
  teprinter-ESCPOS.extra = cd $(INSTALL_ROOT)$(LIBDIR) && ln -sf  tradeequip/libteprinter-ESCPOS.so* $(INSTALL_ROOT)$(LIBDIR)
}

INSTALLS += target 
INSTALLS += teprinter-ESCPOS
