TEMPLATE = subdirs
SUBDIRS  = aldebaran/data aldebaran

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/aldebaran/data/release/ -laldebarandata
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/aldebaran/data/debug/ -laldebarandata
else:unix: LIBS += -L$$OUT_PWD/aldebaran/data/ -laldebarandata

INCLUDEPATH += $$PWD/aldebaran/data
DEPENDPATH += $$PWD/aldebaran/data
