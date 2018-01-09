<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="ru_RU">
<context>
    <name>Queries</name>
    <message>
        <source>SELECT MAX(id) as max_id from %1</source>
        <translation>SELECT MAX(id) as max_id from %1</translation>
    </message>
    <message>
        <source>id=%1</source>
        <translation>id=%1</translation>
    </message>
    <message>
        <source>CREATE TABLE orders (id int8 NOT NULL, num int8, summtype int2 DEFAULT 1, orderdate timestamp, timeopen time, timeclose time, status int4,  id_user int8,  checknum int4, tablenum int4, guests int2, id_discount int8, comment varchar(255), externalcode varchar(50), CONSTRAINT id_orders PRIMARY KEY (id)) WITHOUT OIDS;</source>
        <translation>CREATE TABLE orders (id int8 NOT NULL, num int8, summtype int2 DEFAULT 1, orderdate timestamp, timeopen time, timeclose time, status int4,  id_user int8,  checknum int4, tablenum int4, guests int2, id_discount int8, comment varchar(255), externalcode varchar(50), CONSTRAINT id_orders PRIMARY KEY (id)) WITHOUT ROWID;</translation>
    </message>
    <message>
        <source>role=%1</source>
        <translation>role=%1</translation>
    </message>
    <message>
        <source>id_order=%1</source>
        <translation>id_order=%1</translation>
    </message>
    <message>
        <source>CREATE TABLE RIGHTS (id int8 NOT NULL, id_owner int8 NOT NULL,rule int4, enabled bool,CONSTRAINT id_rights PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation>CREATE TABLE RIGHTS (id int8 NOT NULL, id_owner int8 NOT NULL,rule int4, enabled bool,CONSTRAINT id_rights PRIMARY KEY (id))WITHOUT ROWID;</translation>
    </message>
    <message>
        <source>id_owner=%1</source>
        <translation>id_owner=%1</translation>
    </message>
    <message>
        <source>CREATE TABLE USERS (id int8 NOT NULL, name varchar(30),role int4, password varchar(15),CONSTRAINT id_user PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation>CREATE TABLE USERS (id int8 NOT NULL, name varchar(30),role int4, password varchar(15),CONSTRAINT id_user PRIMARY KEY (id))WITHOUT ROWID;</translation>
    </message>
    <message>
        <source>role=1</source>
        <translation>role=1</translation>
    </message>
    <message>
        <source>role=3</source>
        <translation>role=3</translation>
    </message>
    <message>
        <source>CREATE TABLE settings (id int8 NOT NULL, subsystem varchar(20), valkey varchar(20), value bytea,CONSTRAINT id_settings PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation>CREATE TABLE settings (id int8 NOT NULL, subsystem varchar(20), valkey varchar(20), value bytea,CONSTRAINT id_settings PRIMARY KEY (id))WITHOUT ROWID;</translation>
    </message>
</context>
</TS>
