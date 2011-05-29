TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

unix:LIBS	+= -L../tardeequip-1.1.0/lib -L../tradeequip-drv/lib -lteprinter-cts300 -ltecashregister-felix-rk -ltecashregister-shtrih-fr -ltereader-barcode

INCLUDEPATH	+= ../../aldebaran/data

unix:INCLUDEPATH	+= ../tradeequip-drv/printers/citizen-ct-s300/lib ../tradeequip-drv/printers/citizen-ct-s300/lib ../tradeequip-drv/cashregisters/felix-rk/lib ../tradeequip-drv/cashregisters/shtrih-fr/lib ../tradeequip-1.1.0/src/lib ../../impexp/ ../tradeequip-drv/readers/barcode

HEADERS	+= worker.h \
	driver.h \
	officeprinter.h \
	cts300printer.h \
	felixrk.h \
	siriusterminal.h \
	mscreader.h \
	barcodereader.h \
	virtualmart.h \
	fr.h \
	shtrihfr.h

SOURCES	+= worker.cpp \
	officeprinter.cpp \
	cts300printer.cpp \
	felixrk.cpp \
	siriusterminal.cpp \
	mscreader.cpp \
	barcodereader.cpp \
	virtualmart.cpp \
	fr.cpp \
	shtrihfr.cpp

FORMS	= dlgcts300settings.ui \
	dlgfelixsettings.ui \
	dlgsiriussettings.ui \
	dlgmscreader.ui \
	dlgvmsettings.ui \
	dlgshtrihsettings.ui

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