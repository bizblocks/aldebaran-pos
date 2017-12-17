<!DOCTYPE TS><TS>
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
        <source>CREATE TABLE discount (id int8 NOT NULL, name varchar(50),type int2, value int2, protect bool, code varchar(255),CONSTRAINT id_discount PRIMARY KEY (id), CONSTRAINT code UNIQUE(code))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_discount_code ON discount (code);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM discount WHERE id=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE equipment (id int8 NOT NULL, name varchar(20),type varchar(20), bool enabled, options bytea,CONSTRAINT id_eq PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM equipment WHERE id=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE goods (id int8 NOT NULL, parent int8, isgroup bool DEFAULT false,name varchar(200), price numeric(12,2), maxdiscount int2 DEFAULT 100, description bytea,externalcode varchar(15), barcode varchar(13), id_pictures int8,hydrocarbonat numeric(6,3), fat numeric(6,3), protein numeric(6,3), calories numeric(7,3),outofstore bool DEFAULT false,eqexport bool DEFAULT true,CONSTRAINT id_goods PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_parent ON goods (parent);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_name ON goods (name);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_extcode ON goods (extrnalcode);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_barcode ON goods USING btree (barcode);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>isgroup=&apos;f&apos;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM goods WHERE parent=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM goods WHERE id=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>isgroup=true</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE orders (id int8 NOT NULL, num int8, orderdate timestamp, timeopen time, timeclose time, status int4,  id_user int8,  checknum int4, tablenum int4, guests int2, id_discount int8, comment varchar(255), externalcode varchar(50), CONSTRAINT id_orders PRIMARY KEY (id)) WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_num ON orders (num);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>SELECT MAX(num) AS max_num FROM orders</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>num=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM orders WHERE id=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>role=%1</source>
        <translation>role=%1</translation>
    </message>
    <message>
        <source>externalcode=&apos;%1&apos;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>SELECT SUM(%1) FROM order_table WHERE id_order=%2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE order_table (id_order int8 NOT NULL, ln int8 NOT NULL,id_goods int8, amount numeric(8,3),price numeric(12,2), summ numeric(15,2), id_user int8,printed bool,CONSTRAINT id_ordertable PRIMARY KEY (id_order,ln))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>id_order=%1</source>
        <translation>id_order=%1</translation>
    </message>
    <message>
        <source>DELETE FROM order_table WHERE id_order=%1;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>INSERT INTO order_table VALUES (%1, %2, %3, %4, %5, %6, %7, %8);
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE pictures (id int8 NOT NULL, picture bytea,CONSTRAINT id_pictures PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM pictures WHERE id=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE RIGHTS (id int8 NOT NULL, id_owner int8 NOT NULL,rule int4, enabled bool,CONSTRAINT id_rights PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation>CREATE TABLE rights (id NUMERIC PRIMARY KEY, id_ownerNUMERIC, rule NUMERIC, enabled BOOL);</translation>
    </message>
    <message>
        <source>CREATE INDEX idx_owner ON RIGHTS (id_onwer);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>id_owner=%1</source>
        <translation>id_owner=%1</translation>
    </message>
    <message>
        <source>CREATE TABLE USERS (id int8 NOT NULL, name varchar(30),role int4, password varchar(15),CONSTRAINT id_user PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation>CREATE TABLE users (id NUMERIC PRIMARY KEY, name TEXT, role NUMERIC, password TEXT);</translation>
    </message>
    <message>
        <source>CREATE INDEX idx_name ON users (name);</source>
        <translation type="unfinished"></translation>
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
        <source>DELETE FROM users WHERE id=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM rights WHERE id_owner=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE settings (id int8 NOT NULL, subsystem varchar(20), valkey varchar(20), value bytea,CONSTRAINT id_settings PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation>CREATE TABLE settings (id NUMERIC PRIMARY KEY, subsytem TEXT, valkey TEXT, value TEXT);</translation>
    </message>
    <message>
        <source>CREATE INDEX idx_subsys ON settings (subsystem);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_name ON settings (valkey);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_setting ON settings (subsystem, valkey);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>subsystem=&apos;%1&apos; AND valkey=&apos;%2&apos;</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
