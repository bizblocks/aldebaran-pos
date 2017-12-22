TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release
QT += widgets

DEFINES	+= DEBUG

INCLUDEPATH	+= .. ../../impexp ../../tradeequip/equip

HEADERS	+= datadiscount.h \
	dataeq.h \
	datagoods.h \
	data.h \
	dataorder.h \
	dataordert.h \
	datapictures.h \
	datarights.h \
	datausers.h \
	datawaiters.h \
	datasettings.h \
	queries.h

SOURCES	+= data.cpp \
	datadiscount.cpp \
	dataeq.cpp \
	datagoods.cpp \
	dataorder.cpp \
	dataordert.cpp \
	datapictures.cpp \
	datarights.cpp \
	datausers.cpp \
	datasettings.cpp \
	queries.cpp

FORMS	= dlgdiscount.ui \
	dlgdevice.ui \
	dlguser.ui \
	goodselement.ui \
	goodsgroup.ui

IMAGES	= images/ok.png \
	images/stop_cancel.png \
	images/select-file.png \
	images/save.png \
	images/delete.png

TRANSLATIONS = \
    ../../translations/aldebaran-data-en.ts \
    ../../translations/aldebaran-data-ru.ts

TARGET      = aldebarandata
DESTDIR     = ../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj  
  aldebarandata.path = $(LIBDIR)
  aldebarandata.files = libaldebaran.so.$$VERSION
  aldebarandata.extra = cp -df $(DESTDIR)/libaldebarandata.so* $(INSTALL_ROOT)$(LIBDIR)  
}

INSTALLS += aldebarandata

RESOURCES += \
    data.qrc

DISTFILES +=
