TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

win32:CONFIG	+= dll


DEFINES	+= TRBARCODE_BUILD

INCLUDEPATH	+= ../../../tradeequip-1.1.0/src/lib

HEADERS	+= tereaderbarcode.h

SOURCES	+= tereaderbarcode.cpp

include ( ../../config.pri )
TARGET      = tereader-barcode

TREQPATH = ../../../tradeequip-1.1.0

LIBS	+= -L$${TREQPATH}/lib -ltradeequip


DESTDIR     = ../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = $(LIBDIR)/tradeequip
  tereaderbarcode.path = $(LIBDIR)/tradeequip
  tereaderbarcode.extra = cd $(INSTALL_ROOT)$(LIBDIR) && ln -sf  tradeequip/libtereader-barcode.so* $(INSTALL_ROOT)$(LIBDIR)
}

INSTALLS += target
INSTALLS += tereaderbarcode

DEFINES += _CRT_SECURE_NO_DEPRECATE 
