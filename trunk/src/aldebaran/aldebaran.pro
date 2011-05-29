TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

LIBS	+= -L$(QTDIR)/lib -L../../lib -lequip -limpexp -laldebarandata -L../tradeequip/tradeequip-1.1.0/lib -L../tradeequip/tradeequip-drv/lib -ltradeequip -ltereader-barcode -lteprinter-cts300 -ltecashregister-felix-rk -ltecashregister-shtrih-fr -ltereader-barcode

DEFINES	+= DEBUG

INCLUDEPATH	+= ../tradeequip/equip ../impexp

HEADERS	+= engine.h \
	settings.h \
	mainwin.h \
	whall.h \
	wtable.h \
	goodstable.h \
	datatable.h \
	orderwin.h \
	ordertable.h \
	htmltemplate.h \
	userstable.h \
	rights.h \
	archivetable.h \
	archivewin.h \
	eqtable.h \
	discounttable.h \
	aclock.h \
	dclock.h \
	valuetable.h \
	errors.h

SOURCES	+= engine.cpp \
	settings.cpp \
	mainwin.cpp \
	main.cpp \
	whall.cpp \
	wtable.cpp \
	datatable.cpp \
	goodstable.cpp \
	orderwin.cpp \
	ordertable.cpp \
	htmltemplate.cpp \
	userstable.cpp \
	archivetable.cpp \
	archivewin.cpp \
	eqtable.cpp \
	discounttable.cpp \
	aclock.cpp \
	dclock.cpp \
	valuetable.cpp

FORMS	= ddbsettings.ui \
	settingsdialog.ui \
	calculator.ui \
	dlglogin.ui \
	equipmentdialog.ui \
	dlgselectdiscount.ui \
	dlgexportsales.ui \
	dlgadvreport.ui

IMAGES	= images/ok.png \
	images/stop_cancel.png \
	images/lock.png \
	images/exit.png \
	images/settings.png \
	images/select-file.png \
	images/element.png \
	images/group.png \
	images/delete.png \
	images/up.png \
	images/home.png \
	images/edit.png \
	images/printorder.png \
	images/save.png \
	images/printbill.png \
	images/geld.png \
	images/plus.png \
	images/minus.png \
	images/peoples.png \
	images/down.png \
	images/people.png \
	images/checked.png \
	images/unchecked.png \
	images/document-cancelled.png \
	images/document-closed.png \
	images/document.png \
	images/device.png \
	images/right.png \
	images/checkall.png \
	images/uncheckall.png \
	images/textdraw/editcopy.png \
	images/textdraw/editcut.png \
	images/textdraw/editdelete.png \
	images/textdraw/editlower.png \
	images/textdraw/editpaste.png \
	images/textdraw/editraise.png \
	images/textdraw/fileopen.png \
	images/textdraw/filesave.png \
	images/textdraw/redo.png \
	images/textdraw/textbold.png \
	images/textdraw/textcenter.png \
	images/textdraw/textitalic.png \
	images/textdraw/textjustify.png \
	images/textdraw/textleft.png \
	images/textdraw/textright.png \
	images/textdraw/textunderline.png \
	images/textdraw/undo.png \
	images/calc.png

SUBDIRS		= data

			
TRANSLATIONS = \
    ../../translations/aldebaran-en.ts \
    ../../translations/aldebaran-ru.ts 

TARGET      = aldebaran

DESTDIR	= ../../bin

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  aldebaran.path = $(BINDIR)
  aldebaran.files = aldebaran
  aldebaran.extra = cp -df $(DESTDIR)/aldebaran $(INSTALL_ROOT)$(BINDIR)
}

INSTALLS += aldebaran

QMAKE_CLEAN = libimpexp.so*
