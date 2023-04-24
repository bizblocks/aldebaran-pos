TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

QT      += qt3support

QMAKE_CXXFLAGS	+= -Wno-return-type -fpermissive -Wno-deprecated-copy -Wno-literal-suffix

unix:LIBS	+= -L../../../../tradeequip-1.1.0/lib -L../../../lib -ltecashregister-ESCPOS -ltradeequip

INCLUDEPATH	+= ../lib

unix:INCLUDEPATH	+= ../../../../tradeequip-1.1.0/src/lib

SOURCES	+= main.cpp

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


