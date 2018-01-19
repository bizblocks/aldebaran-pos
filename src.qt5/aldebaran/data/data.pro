TEMPLATE	= lib

QT += core gui sql widgets

DEFINES	+= DEBUG

INCLUDEPATH	+= .. ../../impexp ../../tradeequip/equip

HEADERS	+= $$PWD/datadiscount.h \
        $$PWD/dataeq.h \
        $$PWD/datagoods.h \
        $$PWD/data.h \
        $$PWD/dataorder.h \
        $$PWD/dataordert.h \
        $$PWD/datapictures.h \
        $$PWD/datarights.h \
        $$PWD/datausers.h \
        $$PWD/datawaiters.h \
        $$PWD/datasettings.h \
        $$PWD/queries.h

SOURCES	+= $$PWD/data.cpp \
        $$PWD/datadiscount.cpp \
        $$PWD/dataeq.cpp \
        $$PWD/datagoods.cpp \
        $$PWD/dataorder.cpp \
        $$PWD/dataordert.cpp \
        $$PWD/datapictures.cpp \
        $$PWD/datarights.cpp \
        $$PWD/datausers.cpp \
        $$PWD/datasettings.cpp \
        $$PWD/queries.cpp

FORMS	= $$PWD/dlgdiscount.ui \
        $$PWD/dlgdevice.ui \
        $$PWD/dlguser.ui \
        $$PWD/goodselement.ui \
        $$PWD/goodsgroup.ui

TRANSLATIONS = \
    ../../../translations/aldebaran-data-en.ts \
    ../../../translations/aldebaran-data-ru.ts

TARGET      = aldebarandata
DESTDIR     = ../../../lib

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
    $$PWD/data.qrc

DISTFILES +=
