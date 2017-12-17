include ( ../../config.pri )
TEMPLATE    = lib
LANGUAGE    = C++
TARGET      = tereader-card

CONFIG      += qt warn_on
win32:CONFIG	+= dll

HEADERS     = tereadercard.h

SOURCES     = tereadercard.cpp

TREQPATH = ../../../tradeequip

INCLUDEPATH += $${TREQPATH}/src/lib
LIBS += -L$${TREQPATH}/lib -ltradeequip

DEFINES += TRCARD_BUILD

DESTDIR     = ../../lib
DLLDESTDIR	= /lib
DEFINES += _CRT_SECURE_NO_DEPRECATE 

unix {
  tereadercard.path = $(LIBDIR)/tradeequip
  tereadercard.files = libimpexp.so.$$VERSION
  tereadercard.extra = \
    cp -df $(DESTDIR)/libtereadercard.so* $(INSTALL_ROOT)$(LIBDIR)/tradeequip && \
    ln -s -t $(INSTALL_ROOT)$(LIBDIR) tradeequip/libtereadercard.so*
}

INSTALLS += tereadercard
