#!/bin/sh
spectool -g -C /usr/src/RPM/SOURCES/ aldebaran-pos/aldebaran-pos.spec
rpmbuild -bb aldebaran-pos/aldebaran-pos.spec &>buildlog
less buildlog

