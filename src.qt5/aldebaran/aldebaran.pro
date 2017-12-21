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
    settings.cpp

INCLUDEPATH += ../impexp \
    ../tradeequip/equip

HEADERS += \
    aldebaran.h \
    settings.h

FORMS += \
    calculator.ui \
    dlglogin.ui \
    equipmentdialog.ui \
    ddbsettings.ui \
    settingsdialog.ui

DISTFILES +=

RESOURCES += \
    aldebaran.qrc
