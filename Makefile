NAME    =aldebaran
VERSION = $(shell cat VERSION)
NAMEV  = $(NAME)-$(VERSION)
MAKE = make
QMAKE = qmake
MAKEFILE = Makefile
LIBDIR = /usr/lib
BINDIR = /usr/bin
DOCDIR = /usr/share/doc/$(NAMEV)
INCLUDEDIR = /usr/include/aldebaran

log =
#BINDIR =	/usr/bin
#MANDIR =	/usr/man/man8
#VARDIR =	/usr/share/$(NAME)
TAR    =  	$(HOME)/tmp/$(NAMEV)
TARGET =	i586


first: all

all: tr Makefile
	$(QMAKE) src/src.pro -o src/$(MAKEFILE) && cd src && $(MAKE)
clean:
	rm -fr rpm
	rm -f $(NAME).spec
	rm -fr *~
	rm -f translations/*.qm
	cd src && $(QMAKE) && $(MAKE) clean

tr:
	lrelease translations/*.ts
	
install:
#	find src doc -name Makefile -delete
	$(QMAKE) src/src.pro -o src/$(MAKEFILE)
	cd src && $(MAKE) install LIBDIR=$(LIBDIR) BINDIR=$(BINDIR) INCLUDEDIR=$(INCLUDEDIR) && cd ../doc && $(QMAKE) doc.pro -o $(MAKEFILE) && $(MAKE) install DOCDIR=$(DOCDIR)
	
uninstall:
	cd src && $(MAKE) uninstall

tgz:	dummy
	mkdir -p rpm
	mkdir -p $(TAR)
	cp -r -f * $(TAR)
#	cd $(TAR) && make clean
#	cd $(TAR) && find src doc -name Makefile -delete
	cd $(HOME)/tmp && tar cf - "$(NAMEV)/" | bzip2 -f9 > "$(HOME)/RPM/SOURCES/$(NAMEV).tar.bz2"	
	rm -f -r $(TAR)
#srpm:	tgz
#	if [ -e /etc/altlinux-release ] ; then\
#	    iconv -f UTF-8 -t KOI8-R $(NAME).spec.in |\
#	    sed s/ru_RU.UTF8/ru_RU.KOI8-R/>$(NAME).spec;\
#	else \
#	    cp $(NAME).spec.in $(NAME).spec; \
#	fi
#	rpmbuild --target=$(TARGET) -bs $(NAME).spec
#	mv -f $(HOME)/RPM/SRPMS/$(NAME)* rpm
#rpm:	srpm
#	rpmbuild --target=$(TARGET) -bb $(NAME).spec
#	mv -f $(HOME)/RPM/RPMS/$(TARGET)/$(NAME)* rpm
	
tests: all
	./tests.begin -log=$(log)

dummy:
