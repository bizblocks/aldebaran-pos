TEMPLATE	= lib
LANGUAGE	= C++

VERSION = 1.1.1a

#CONFIG	+= qt warn_on release thread
CONFIG	+= qt warn_on debug thread

QT      += sql qt3support network

QMAKE_CXXFLAGS = -fpermissive -Wno-deprecated-copy

unix:LIBS	+= -L../tardeequip-1.1.0/lib -L../tradeequip-drv/lib -ltereader-barcode

unix:DEFINES	+= DEBUG

INCLUDEPATH	+= ../../aldebaran/data ../../aldebaran/

unix:INCLUDEPATH	+= ../tradeequip-drv/printers/citizen-ct-s300/lib ../tradeequip-drv/printers/citizen-ct-s300/lib ../tradeequip-drv/cashregisters/felix-rk/lib ../tradeequip-drv/cashregisters/shtrih-fr/lib ../tradeequip-1.1.0/src/lib ../../impexp/ ../tradeequip-drv/readers/barcode

HEADERS	+= worker.h \
	dlgvmsettings.ui.h \
	driver.h \
	officeprinter.h \
	siriusterminal.h \
	mscreader.h \
	barcodereader.h \
	virtualmart.h \
	fr.h

SOURCES	+= worker.cpp \
	officeprinter.cpp \
	siriusterminal.cpp \
	mscreader.cpp \
	barcodereader.cpp \
	virtualmart.cpp \
	fr.cpp

FORMS	= dlgsiriussettings.ui \
	dlgmscreader.ui \
	dlgvmsettings.ui \
	dlgecrsettings.ui

TRANSLATIONS = \
    ../../../translations/equip-en.ts \
    ../../../translations/equip-ru.ts 

TARGET      = equip
DESTDIR     = ../../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  equip.path = /usr/lib
  equip.file = libequip.so.$$VERSION
  equip.extra = cp -df $(DESTDIR)/libequip.so* $(INSTALL_ROOT)$(LIBDIR)  
}

INSTALLS += equip

QMAKE_CLEAN = libequip.so*
