#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T16:07:49
#
#-------------------------------------------------

QT       += core gui sql network
CONFIG   += c++11

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
    data/alsqltablemodel.cpp \
    mainwin.cpp \
    aclock.cpp \
    dclock.cpp \
    whall.cpp \
    wtable.cpp \
    goodstable.cpp \
    data/goodselement.cpp

INCLUDEPATH += ../impexp \
    ../tradeequip/equip

HEADERS += \
    aldebaran.h \
    settings.h \
    engine.h \
    valuetable.h \
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
    data/goodsgroup.ui.h \
    data/queries.h \
    data/alsqltablemodel.h \
    mainwin.h \
    aclock.h \
    dclock.h \
    whall.h \
    wtable.h \
    settingsdialog.ui.h \
    goodstable.h \
    data/goodselement.h

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
    data/goodsgroup.ui \
    dlgexportsales.ui \
    dlgadvreport.ui

DISTFILES +=

RESOURCES += \
    aldebaran.qrc


INCLUDEPATH += $$PWD/data
DEPENDPATH += $$PWD/data
