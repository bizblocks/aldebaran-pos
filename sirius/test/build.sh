#!/bin/sh
gcc -lsqlite3 sqlite3test.c -o sqlite3test.x86
/usr/local/arm/4.1.1-920t/bin/arm-linux-gcc -DSQLITE_MAX_SQL_LENGTH=1000000000 -USQLITE_THREADSAFE -DSQLITE_THREADSAFE=0 -L./ -I../../../sqlite  sqlite3test.c sqlite3.c -o sqlite3test.arm -ldl
