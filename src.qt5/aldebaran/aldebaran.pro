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
    datatable.cpp

INCLUDEPATH += ../impexp \
    ../tradeequip/equip

HEADERS += \
    aldebaran.h \
    settings.h \
    engine.h \
    valuetable.h \
    ddbsettings.ui.h \
    dlglogin.ui.h \
    userstable.h \
    datatable.h

FORMS += \
    calculator.ui \
    dlglogin.ui \
    equipmentdialog.ui \
    ddbsettings.ui \
    settingsdialog.ui

DISTFILES +=

RESOURCES += \
    aldebaran.qrc

unix:!macx: LIBS += -L$$PWD/../../lib/ -laldebarandata

INCLUDEPATH += $$PWD/data
DEPENDPATH += $$PWD/data

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/release/ -laldebarandata
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/debug/ -laldebarandata
else:unix: LIBS += -L$$PWD/../../lib/ -laldebarandata

INCLUDEPATH += $$PWD/data
DEPENDPATH += $$PWD/data
