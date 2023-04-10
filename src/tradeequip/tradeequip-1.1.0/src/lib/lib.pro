TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on

win32:CONFIG	+= dll

DEFINES	+= TRADEEQUIP_EXPORT DEBUG

win32:SOURCES	+= win_qextserialport.cpp

unix:SOURCES	+= posix_qextserialport.cpp

win32:HEADERS	+= win_qextserialport.h

unix:HEADERS	+= posix_qextserialport.h

QMAKE_CXXFLAGS	+= -Wno-return-type

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
  lib.path = $(LIBDIR)
  lib.files = libtradeequip.so.$$VERSION
  lib.extra = cp -df $(DESTDIR)/libtradeequip.so* $(INSTALL_ROOT)$(LIBDIR)
}

INSTALLS += lib
