<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1">
<context>
    <name>GoodsElement</name>
    <message>
        <source>Element</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Name:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Barcode:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>1234567890123</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Ext.code:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Proteins:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hydrocarbonates:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Calories:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fat:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Price:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Out of store</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Export to equipment</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Max discount:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Picture</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>GoodsGroup</name>
    <message>
        <source>Group</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Name:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Picture</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Export to equipment</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <source>creating table discount</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>lastError was %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>creating table equipment</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>creating table goods</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>creating table orders</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>creating table pictures</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>creating table rights</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>creating table users</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Administrator</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Service</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>lastError was: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Queries</name>
    <message>
        <source>SELECT MAX(id) as max_id from %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>id=%1</source>
        <translation type="unfinished"></translation>
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
        <source>CREATE TABLE equipment (id int8 NOT NULL, name varchar(20),type varchar(20), enabled bool, options bytea,CONSTRAINT id_eq PRIMARY KEY (id))WITHOUT OIDS;</source>
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
        <translation type="unfinished"></translation>
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
        <source>id_order=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DELETE FROM order_table WHERE id_order=%1;
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
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>id_owner=%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE USERS (id int8 NOT NULL, name varchar(30),role int4, password varchar(15),CONSTRAINT id_user PRIMARY KEY (id))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_name ON users (name);</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>role=1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>role=3</source>
        <translation type="unfinished"></translation>
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
        <translation type="unfinished"></translation>
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
    <message>
        <source>CREATE TABLE orders (id int8 NOT NULL, num int8, summtype int2 DEFAULT 1, orderdate timestamp, timeopen time, timeclose time, status int4,  id_user int8,  checknum int4, tablenum int4, guests int2, id_discount int8, comment varchar(255), externalcode varchar(50), CONSTRAINT id_orders PRIMARY KEY (id)) WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE TABLE order_table (id_order int8 NOT NULL, ln int8 NOT NULL,id_goods int8, externalcode varchar(15), amount numeric(8,3),price numeric(12,2), summ numeric(15,2), id_user int8,printed bool,CONSTRAINT id_ordertable PRIMARY KEY (id_order,ln))WITHOUT OIDS;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>INSERT INTO order_table VALUES (%1, %2, %3, &apos;%4&apos;, %5, %6, %7, %8, %9);
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>CREATE INDEX idx_owner ON RIGHTS (id_owner);</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>alDataRecord</name>
    <message>
        <source>Abstract data record dialog</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>alOrderRecord</name>
    <message>
        <source>Can&apos;t print order</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Order #%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Can&apos;t print bill</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Bill #%1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Total:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Calories: %1
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hydrocarbonates: %1
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Fat: %1
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Protein: %1
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>not speciefed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Discount: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Table #%1 Guests: %2 %3
Opened: %4 %5 Summ: %6</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>dlgDevice</name>
    <message>
        <source>Device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>name:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>type:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Enabled</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>dlgDiscount</name>
    <message>
        <source>discount</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>name:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>type:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>value</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>protect</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>code:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>dlgUser</name>
    <message>
        <source>User</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;OK</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Cancel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Name:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Password:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
