#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T16:07:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aldebaran
TEMPLATE = app


SOURCES += main.cpp \
    engine.cpp \
    settings.cpp \
    valuetable.cpp \
    userstable.cpp \
    datatable.cpp \
    data/data.cpp \
    data/datadiscount.cpp \
    data/dataeq.cpp \
    data/datagoods.cpp \
    data/dataorder.cpp \
    data/dataordert.cpp \
    data/datapictures.cpp \
    data/datarights.cpp \
    data/datasettings.cpp \
    data/datausers.cpp \
    data/queries.cpp \
    data/alsqltablemodel.cpp

INCLUDEPATH += ../impexp \
    ../tradeequip/equip

HEADERS += \
    aldebaran.h \
    settings.h \
    engine.h \
    valuetable.h \
    ddbsettings.ui.h \
    userstable.h \
    datatable.h \
    data/data.h \
    data/datadiscount.h \
    data/dataeq.h \
    data/datagoods.h \
    data/dataorder.h \
    data/dataordert.h \
    data/datapictures.h \
    data/datarights.h \
    data/datasettings.h \
    data/datausers.h \
    data/datawaiters.h \
    data/dlgdevice.ui.h \
    data/dlgdiscount.ui.h \
    data/dlguser.ui.h \
    data/goodselement.ui.h \
    data/goodsgroup.ui.h \
    data/queries.h \
    data/alsqltablemodel.h

FORMS += \
    calculator.ui \
    dlglogin.ui \
    equipmentdialog.ui \
    ddbsettings.ui \
    settingsdialog.ui \
    data/dlgdiscount.ui \
    data/dlgdevice.ui \
    data/dlguser.ui \
    data/goodselement.ui \
    data/goodsgroup.ui

DISTFILES +=

RESOURCES += \
    aldebaran.qrc


INCLUDEPATH += $$PWD/data
DEPENDPATH += $$PWD/data
