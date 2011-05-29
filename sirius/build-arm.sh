#!/bin/sh
PATH=$PATH:/usr/local/arm/4.1.1-920t/bin
QTDIR=/usr/src/linux-crater_1-0-0/build/qt-2.3.10
make -C src -f Makefile.arm $1 || exit
cp dist/usr/bin/sirius dist-nosvn/usr/bin/sirius
rm sirius.tar.gz
tar --directory dist-nosvn/ --gzip -cvvf sirius.tar.gz ./

