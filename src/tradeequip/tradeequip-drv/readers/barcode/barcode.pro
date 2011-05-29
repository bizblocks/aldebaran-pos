include ( ../../config.pri )
TEMPLATE    = lib
LANGUAGE    = C++
TARGET      = tereader-barcode

CONFIG      += qt warn_on
win32:CONFIG	+= dll

HEADERS     = tereaderbarcode.h

SOURCES     = tereaderbarcode.cpp

TREQPATH = ../../../tradeequip-1.1.0

INCLUDEPATH += $${TREQPATH}/src/lib
LIBS += -L$${TREQPATH}/lib -ltradeequip

DEFINES += TRBARCODE_BUILD

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
