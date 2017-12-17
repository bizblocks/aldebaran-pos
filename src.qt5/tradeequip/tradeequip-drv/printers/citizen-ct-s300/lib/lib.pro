TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

unix:LIBS	+= -L../../../../tradeequip-1.1.0/lib -ltradeequip

unix:INCLUDEPATH	+= ../../../../tradeequip-1.1.0/src/lib

HEADERS	+= cts300.h \
	cts300-config.h

SOURCES	+= cts300.cpp

TARGET      = teprinter-cts300
DESTDIR     = ../../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = $(LIBDIR)/tradeequip
  teprinter-cts300.path = $(LIBDIR)/tradeequip
  teprinter-cts300.extra = cd $(INSTALL_ROOT)$(LIBDIR) && ln -sf  tradeequip/libteprinter-cts300.so* $(INSTALL_ROOT)$(LIBDIR)
}

INSTALLS += target 
INSTALLS += teprinter-cts300
