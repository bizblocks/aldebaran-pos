TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on

QT      += qt3support sql xml

win32 {
    CONFIG	+= dll
    SOURCES	+= win_qextserialport.cpp
    HEADERS	+= win_qextserialport.h
}

DEFINES	+= TRADEEQUIP_EXPORT DEBUG

unix {
    SOURCES	+= posix_qextserialport.cpp
    HEADERS	+= posix_qextserialport.h
}

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

HEADERS	+= md5.h \
	qextserialbase.h \
	qextserialport.h \
	tserialport.h \
	qgetopt.h \
	preferences.h \
	teinifile.h \
	cmdparser.h \
	conv.h \
	estring.h \
	teglobal.h \
	tebase.h \
	tecashregisterbase.h \
	tescalesbase.h \
	tedisplaybase.h \
	tereaderbase.h \
	teplugin.h \
	tefactory.h \
	teconnect.h \
	teconnectserial.h \
	teconnecttcp.h \
	teconnectkeyboard.h \
	teconnectteserver.h

SOURCES	+= md5.c \
	qextserialbase.cpp \
	qextserialport.cpp \
	tserialport.cpp \
	qgetopt.cpp \
	preferences.cpp \
	teinifile.cpp \
	cmdparser.cpp \
	conv.cpp \
	estring.cpp \
	teglobal.cpp \
	tebase.cpp \
	tecashregisterbase.cpp \
	tescalesbase.cpp \
	tedisplaybase.cpp \
	tereaderbase.cpp \
	teplugin.cpp \
	tefactory.cpp \
	teconnect.cpp \
	teconnectserial.cpp \
	teconnecttcp.cpp \
	teconnectkeyboard.cpp \
	teconnectteserver.cpp

include ( ../config.pri )
TARGET      = tradeequip
#DEFINES += LIB_NO_DLL

TRANSLATIONS = \
    ../../translations/tradeequip-en.ts \
    ../../translations/tradeequip-ru.ts 

    

#Following statement duplicates config.h macro
#unix:DEFINES    = _TTY_POSIX_

#Following statement duplicates config.h macro
#win32:DEFINES   = _TTY_WIN_ _TTY_NOWARN_
        
DESTDIR     = ../../lib
#win32:DLLDESTDIR	= /lib
DEFINES	+= TRADEEQUIP_EXPORT 
DEFINES	+= NOQFILE
DEFINES += _CRT_SECURE_NO_DEPRECATE 

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  target.path = /usr/lib
  lib.path = $(DESTDIR)
  lib.files = libtradeequip.so.$$VERSION
  lib.extra = cp -df $(DESTDIR)/libtradeequip.so* $(INSTALL_ROOT)$(LIBDIR)/tradeequip
}

INSTALLS += target
