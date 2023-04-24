TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

QT      += qt3support sql

LIBS	+= -lsqlite3

HEADERS	+= impexp.h \
	ieshtrih.h \
	iecsv.h \
	ievmart.h \
	sirius/data.h \
	sirius/iesirius.h \
	sirius/iesiriussqlite.h

SOURCES	+= impexp.cpp \
	ieshtrih.cpp \
	iecsv.cpp \
	ievmart.cpp \
	sirius/data.cpp \
	sirius/iesirius.cpp \
	sirius/iesiriussqlite.cpp

TRANSLATIONS = \
    ../../translations/impexp-en.ts \
    ../../translations/impexp-ru.ts 

TARGET      = impexp
DESTDIR     = ../../lib

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = $(LIBDIR)
  impexp.path = $(LIBDIR)
  impexp.files = libimpexp.so.$$VERSION
}

INSTALLS += target 
INSTALLS += impexp

QMAKE_CLEAN = libimpexp.so*

QMAKE_CXXFLAGS_RELEASE = -fpermissive -Wno-deprecated-copy
