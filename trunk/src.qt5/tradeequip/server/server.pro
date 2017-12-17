TEMPLATE	= lib
LANGUAGE	= C++

CONFIG	+= qt warn_on release

HEADERS	+= server.h \
	errors.h \
	driver.h

SOURCES	+= server.cpp

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}



