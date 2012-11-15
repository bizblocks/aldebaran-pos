include("sys/mask.js");
include("Objects/DpClEx.js");
include("doc/DpDoc.js");
var arrNmklID = new Array();
var arrKassID = new Array();
var arrNmklFWID = new Array();
var arrKitchenID = new Array();
var arrEdi = new Array();
var arrEdiExt = new Array();
var conn;
var syncPeriod = null;
var importCheck = false;
var isDeleteMenu = false;
var oPodr, fpodr;

include("sys/DpBaseDlg.js");
function Load()
{
	TCNUM.mask = "########";
	Caption("Синхронизация с Альдебаран POS");
	
	var hostName = getPar("REST_SYNC_HOST");
	if (!hostName)
		hostName = "localhost";	
	HOST.value = hostName;
	HOST.readOnly = true;
	
	
	var dbName = getPar("REST_SYNC_DBNAME");
	if (!dbName)
		dbName = "db_server";	
	DBNAME.value = dbName;
	DBNAME.readOnly = true;
	
	var login = getPar("REST_SYNC_LOGIN");
	if (!login)
		login = "postgres";
	LOGIN.value = login;
	LOGIN.readOnly = true;
	
	var pass = getPar("REST_SYNC_PASS");
	if (!login)
		login = "";
	PASSWORD.value = login;
	PASSWORD.readOnly = true;
	
	oPodr = new DpCl();
	oPodr.setClcl(getPar("CODPODR"));
	oPodr.linkSmartCtrl(FPODR);
	var podr = ReadParEx("REST_SYNC_PODR");
	oPodr.setCod(!podr ? 1 : podr);
	
	var sSQL = "select max(" + Convert("foutid", "INT") + ") from ^htcs where foutid is not null and foutid != ''";
	var oSnap = getSnap(sSQL, false);
	if (oSnap && oSnap[0])
		TCNUM.value = oSnap[0]; 
	
	
	var typePer =  ReadParEx("REST_SYNC_TYPEPER");	
	
	if (typePer == "2")
		TYPEPER.value = "2";
	var sBDate = String(ReadParEx("REST_SYNC_BDATE"));
	if (sBDate)
	{
		BDATE.value = sBDate;
	}
	
	var sEDate = String(ReadParEx("REST_SYNC_EDATE"));
	if (sEDate)
	{
		EDATE.value = sEDate;
	}
	
	
	status.setEnabled(false);
	btnOK.setText("Запуск");
	btnCancel.setText("Закрыть");
	//alert(typeOf(retValue = new java.text.SimpleDateFormat().parse(retValue);("REST_SYNC_BDATE")));
	//Writec
	//WriteParEx("REST_SYNC_EDATE", EDATE.value);		
}

function onSave()
{
	var strConn = "jdbc:postgresql://" + HOST.value + "/"  + DBNAME.value;
	var ex;
	try
	{
		conn = getDBConnection(strConn, LOGIN.value, PASSWORD.value)
	}
	catch(ex)
	{
		var sMSG = ex.javaException.getLocalizedMessage();
		alert(sMSG);
		return false;
	}
		
	fpodr = oPodr.getCod();
	syncPeriod = getSyncPeriod();
	importCheck = IMPBILL.checked;
	var thr = new java.lang.Thread(
			function run()
			{
				display.syncExec
				(
					function stopFnk()
					{
						btnOK.setEnabled(false);
						btnCancel.setEnabled(false);	
					}
				)
								
				runSyncro();
				
				display.syncExec
				(
					function stopFnk()
					{
						status.setValue("Завершено");
						btnOK.setEnabled(true);		
						btnCancel.setEnabled(true);	
					}
				)
			}
		);
	thr.start();
	
	WriteParEx("REST_SYNC_PODR", fpodr);
	WriteParEx("REST_SYNC_TYPEPER", TYPEPER.value);
	if (TYPEPER.value == "1")
	{
		WriteParEx("REST_SYNC_BDATE", format("dd.mm.yyyy", BDATE.value));
		WriteParEx("REST_SYNC_EDATE", format("dd.mm.yyyy", EDATE.value));		
	}
	return false;

}

function runSyncro()
{
//	synchroEdi();
//	importMol();
//	syncNmklGrp();
//	syncNmkl();	
	
	
//	syncRec();	
//	synchPodr();
	
	exportGoods();
	exportClients();

	if (importCheck)
	{
		importBill(6, false);
		importBill(6, true);
		importBill(8);
	}
	
	progressReset();
		
}

function getSyncPeriod()
{
	var p = new Object();
	p.bdate = null; 
	p.edate = null;
	if (TYPEPER.value == "1")
	{
		p.bdate =  differ(BDATE.value, d00) < 0 ? BDATE.value : null; 
		p.edate =  differ(EDATE.value, d00) < 0 ? EDATE.value : null;
	}
	else 
	{
		var tcnum = String(TCNUM.value);
		if (tcnum)
		{
			var oSnap = getSnap("select fdoc_dat from ^htcs where foutid = "
					+ sqlTo(tcnum));
			if (oSnap)
				p.bdate = oSnap[0];
		}
		p.tcnum = tcnum;		
			
	}
	return p;
}

/*
function syncNmklGrp()
{
//	var tbl = OpenTable("select fcod, ftxts, fwid, fgrpid, fgrpdeep, fimage from ^cl_nmk " +
//			"where fisgrp = 1 and fgrpid >= 0 order by fleftkey");
	var tbl = OpenTable("select fcod, ftxts, fwid, fgrpid, fgrpdeep, fimage from ^cl_nmk " +
			"where fisgrp = 1 and fgrpid >= 0 order by fleftkey");
	include("sub/mtr.js");
	
	progressReset();
	initProgressBar(0, tbl.recordCount);
	while (!tbl.isEOF())
	{
		
		var m = new Object();
		m.name = String(tbl.getValue("ftxts"));
		if(m.name.length > 128)
			m.name = m.name.substring(0, 128);
		
		m.sname = m.name;
		if(m.sname.length > 32)
			m.sname = m.sname.substring(0, 32)
		
		m.level = Number(tbl.getValue("fgrpdeep")) - 1;
		m.id_article_group = Number(tbl.getValue("fwid"));
		
		var id_parent_group = Number(tbl.getValue("fgrpid"));		
		if(id_parent_group)
			m.id_parent_group = id_parent_group;
		
		var extTbl = OpenExtTable(conn,	
				"select id_article_group from t_article_group where id_article_group = " 
					+ m.id_article_group);
		
		
		var sSQL = "";		
		var img = tbl.getValue("fimage");
		if (img)
			m.image = String(img);	
		
		if (extTbl.isEmpty())
		{	
			sSQL = createPGInsertQuery("t_article_group" , m);
			Put_Log_Message("Добавленна Группа номенклатуры: " + m.name)
			
		}
		else
		{
			sSQL = createPGUpdateQuery("t_article_group" , m, " id_article_group = " + m.id_article_group );
		}
		
		ExecSQL(conn, sSQL, true);
		progressWorked(1, "Экспорт груп номенклатуры");
		tbl.moveNext();
		extTbl.close();
	}
	
	tbl.close();
}
*/

function syncNmkl()
{
	include("Objects/DpExtentionBuilder.js");
	var extBuilder = new DpExtentionBuilder("CL_NMK");
	var extTableName = extBuilder.getValueTableName();
	
	
	var sql = "select n.*, e.fnodisc as fnodisc,  e.fnofiscal as fnofiscal  from ^cl_nmk n left join " + extTableName + " e on n.fwid = e.fmainwid where n.fisgrp = 0 and n.fwid > 0 ";
	
	if (syncPeriod.bdate || syncPeriod.edate)
	{
		var subSql = " select fwid from ^archive where n.fwid = fid_doc " 
		if (syncPeriod.bdate)
			subSql += " and fmdate >= " + sqlTo(syncPeriod.bdate);
	
		if (syncPeriod.edate)
			subSql += " and fmdate <= " + sqlTo(goDay(syncPeriod.edate, 1));
		
		sql += " and exists ( " + subSql + ") ";
	}
	
		
	sql += "order by n.fleftkey ";
	
	var tbl = OpenTable(sql);
	progressReset();
	initProgressBar(0, tbl.recordCount);
	while (!tbl.isEOF())
	{
		
		var m = new Object();
		m.name = String(tbl.getValue("ftxts"));
		if(m.name.length > 128)
			m.name = m.name.substring(0, 128);
		
		m.sname = m.name;
		if(m.sname.length > 32)
			m.sname = m.sname.substring(0, 32)
		
		m.article = String(tbl.getValue("fcod"));
		if(m.article.length > 32)
			m.article = m.article.substring(0, 32)
			
		
		
		if (!m.id_measure)
			m.id_measure = 0;
		
		var id_article_group = Number(tbl.getValue("fgrpid"));		
		if(id_article_group)
			m.id_article_group = id_article_group;
		
		
		var nds = Number(tbl.getValue("fnds"));
		
		
		m.taxgroup = nds == 0? 1: 0;
		if (toScrObj(tbl.getValue("fnofiscal")))
		{
			m.taxgroup = null;
		}
		
		
		m.type = String(tbl.getValue("fvid")).trim() == "" ? 0 : 1;
		var edi = Number(tbl.getValue("FCEDIB"));
		m.id_measure = arrEdi[edi];			
		
		m.output = m.type == 0? 1: 0; //TODO:
		
		m.calculation = 0; 
		m.r_type = 0;
		m.price = Number(tbl.getValue("f1cena"));
		if (!m.price)
			m.price = 0;
		
		m.without_discount = toScrObj(tbl.getValue("fnodisc"))?"1":"0"; //TODO:
		m.normal = 0; //TODO:
		
		var extTbl = OpenExtTable(conn,	
				"select id_article from t_article where article = " 
					+ sqlToEx(POSTGRE, m.article));
		var sSQL = "";
		var img = tbl.getValue("fimage");
		if (img)
			m.picture = String(img);	
		if (extTbl.isEmpty())
		{
			m.dtime_created = new Date().getTime();
			m.dtime_created = Math.round(m.dtime_created/1000);			
			
			sSQL = createPGInsertQuery("t_article" , m);
			Put_Log_Message("Добавленна номенклатура: " + m.name)
			
		}
		else
		{
			sSQL = createPGUpdateQuery("t_article" , m, " article = " + sqlToEx(POSTGRE, m.article) );
			Put_Log_Message("Изменена номенклатура: " + m.name)
		}
		
		var bRet = ExecSQL(conn, sSQL, true);
		tbl.moveNext();
		progressWorked(1, "Экспорт номенклатуры");
		extTbl.close();
	}
	
	tbl.close();
}

function syncRec()
{
	ExecuteSQL("UPDATE ^cl_rec set fmdate = " + sqlTo(d00) + " where fmdate is null");
	
	var sql = "select fno, fbdat, fedat from ^cl_rec where fisreplacemap = 0"
	
	
	if (syncPeriod.bdate)
		sql += " and fmdate >= " + sqlTo(syncPeriod.bdate);
	
	if (syncPeriod.edate)
		sql += " and fmdate <= " + sqlTo(syncPeriod.edate);
	
	
	
	//sql += " and rownum < 200 ";
	
	sql += " order by fno";
	
	var tblRec = OpenTable("m", sql);
	progressReset();
	initProgressBar(0, tblRec.recordCount);
	while (!tblRec.isEOF())
	{
		var bdat = tblRec.getValue("fbdat");
		bdat = differ(bdat,d00) == 0 ? d00min : bdat;
		var edat = tblRec.getValue("fedat");
		trace(bdat);
		trace(edat);	
		trace(today.between(bdat, edat));
		if (!today.between(bdat, edat))
		{
			tblRec.MoveNext();
			continue;
		}
		
		var noRec = Number(tblRec.getValue("FNO"));
		sql = "select n.fcod as fnmkcod "
				+ "from ^cl_rrec r inner join ^cl_nmk n on r.fnmkl = n.fwid  "
				+ "where r.fhno = " + noRec + " and r.fmain = 1 and r.frtype = '5' and r.fwid is not null ";
		var oSnap = getSnap(sql);
		
		if (!oSnap || !oSnap[0])
		{
			tblRec.MoveNext();
			continue;
		}
			
		var m = new Object();
		m.id_article = getFONmklID(oSnap[0]);
		
		if (!m.id_article)
		{
			tblRec.MoveNext();
			continue;
		}
			
		ExecSQL(conn, "delete  from t_article_cont where id_article = " + m.id_article, true);
		ExecSQL(conn, "update t_article set calculation = 1 where id_article = " + m.id_article, true);
		
		sql = "select n.fcod as fnmkcod, r.fkol as fkol "
			+ "from ^cl_rrec r inner join ^cl_nmk n on r.fnmkl = n.fwid "
			+ "where r.fhno = " + noRec + " and r.fmain = 0 and r.frtype = '7' ";
		
		var tblRow = OpenTable(sql);
		while (!tblRow.isEOF())
		{
			m.id_article_cont = getFONmklID(tblRow.getValue("fnmkcod"));
			if(m.id_article_cont)
			{
				m.normal = Number(tblRow.getValue("fkol")); 
				sSQL = createPGInsertQuery("t_article_cont" , m);
				var bRet = ExecSQL(conn, sSQL, false);
			}
			
			tblRow.moveNext();
		}
		
		tblRow.close();
		progressWorked(1, "Экспорт рецептов");		
		tblRec.moveNext();
		
	}
	
	tblRec.close();
}

/*
	var tmpFunc = "CREATE OR REPLACE FUNCTION upsert (sql_update TEXT, sql_insert TEXT) RETURNS VOID LANGUAGE plpgsql " +
			"AS $$ " +
			"BEGIN " +
		      "LOOP " +
			    "EXECUTE sql_update; " +
			    "IF FOUND THEN " +
			      "RETURN; " +
			    "END IF; "
			    "BEGIN "
				  "EXECUTE sql_insert; " +
				  "RETURN; "+
				  "EXCEPTION WHEN unique_violation THEN " +
			      "END; " +
			"END LOOP;" +
			"END;" +
			"$$;" ;
*/

function delGoodsGrp(codes)
{
	Put_Log_Message("Удаление неиспользуемых групп");	
	var sql = "UPDATE goods SET parent=-1 WHERE (parent<>0) " 
		+ "AND ((parent IN (SELECT id FROM goods WHERE externalcode NOT IN ('"+codes.join("','")+"'))) "
		+ "OR (parent NOT IN (SELECT id FROM goods WHERE isgroup=true)))";	
	ExecSQL(conn, sql);
	sql = "DELETE FROM goods WHERE (isgroup=true) AND (parent IN (SELECT id FROM goods WHERE externalcode NOT IN ('"+codes.join("','")+"')))";
	ExecSQL(conn, sql);
	Put_Log_Message("Неиспользуемые группы удалены");
}

function exportGoodsGrp()
{
	Put_Log_Message("Экспорт групп товаров");	
	var sql = "select ftxt, fcod, max(fdat) from ^cl_pri where fisgrp = 0 group by ftxt, fcod";
	var tblGroups = OpenTable("m", sql);
	
	initProgressBar(0, tblGroups.recordCount);
	
	var codes = new Array();
	while(!tblGroups.isEOF())
	{
		var code = tblGroups.getValue("FCOD");
		codes[codes.length] = code;
		var query = "SELECT id FROM goods WHERE externalcode='"+code+"' AND isgroup=TRUE;";
		var res = OpenExtTable(conn, query);
		if(res.isEmpty())
			query = "INSERT INTO goods SELECT COALESCE(MAX(id), 0)+1, 0, true, '"+tblGroups.getValue("FTXT")+"', 0, 0, '','"+code+"', "
				+ " '', 0, 0, 0, 0, 0, FALSE, FALSE from goods;";
		else
			query = "UPDATE goods SET name='"+tblGroups.getValue("FTXT")+"' WHERE externalcode='"+code+"'";
		res.close();
		ExecSQL(conn, query);
		progressWorked(1, "Выгружена группа " +tblGroups.getValue("FTXT"));		
		tblGroups.moveNext();
	}
	tblGroups.close();
	delGoodsGrp(codes);
	Put_Log_Message("Экспорт групп завершён");
}

function exportGoods()
{
	Put_Log_Message("Экспорт товаров");
	exportGoodsGrp();	
	var sql = "select ftxt, fcod, max(fdat) from ^cl_pri where fisgrp = 0 group by ftxt, fcod";	
	var tblMenu = OpenTable("m", sql);
	
	while (!tblMenu.isEOF())
	{								
		var menucode = tblMenu.getValue("FCOD");
		var priceTblName = String(pName(String(menucode), today, tblMenu.getValue("FWID")));
		
		DropTable("TMP_PRICE")
		ExecuteSQL("select p.fcena as fcena, n.fcod as fnmklcod, n.ftxt0 as fnmkltxt " 
				+ " into TMP_PRICE from " + priceTblName + " p inner join ^cl_nmk n on p.fnmkl = n.fwid")
		var priceTbl = OpenTable("TMP_PRICE");		
		initProgressBar(0, priceTbl.recordCount);		
		while (!priceTbl.isEOF())
		{
			var code = priceTbl.getValue("fnmklcod");
			var query = "SELECT id FROM goods WHERE externalcode='"+code+"'";
			var res = OpenExtTable(conn, query);
			if(res.isEmpty())
				query = "INSERT INTO goods SELECT COALESCE(MAX(id), 0)+1, " +
					"(SELECT id FROM goods WHERE externalcode='"+menucode+"' LIMIT 1), " +
					"false, '"+priceTbl.getValue("FNMKLTXT")+"', "+priceTbl.getValue("FCENA")+", 0, '','"+code+"', " +
					"'', 0, 0, 0, 0, 0, FALSE, FALSE FROM goods;";
			else
				query = "UPDATE goods SET " +
					"name='"+priceTbl.getValue("FNMKLTXT") + "', " +
					"parent=(SELECT id FROM goods WHERE externalcode='"+menucode+"' LIMIT 1), " +
					"price="+priceTbl.getValue("FCENA")+ " " +
					"WHERE externalcode='"+code+"'";
			ExecSQL(conn, query);
			res.close();
			progressWorked(1, "Выгружен товар " +priceTbl.getValue("FNMKLTXT"));
			priceTbl.moveNext();
		}				
		priceTbl.close();				
		tblMenu.moveNext();		
	}	
	tblMenu.close();
	Put_Log_Message("Экспорт товаров завершён");
}


function exportClients()
{
	Put_Log_Message("Экспорт клиентов");
	var sql="select c.fwid, c.ftxt, fcod, fskidka  from ^com_cl as c left join ^com_clrelclcl as r on " +
		"c.fwid=r.fwid_cl right join dpbase.cl_12 on c.fwid=cl_12.fmainwid where fcl=12;";
	var tblClients = OpenTable("m", sql);
	while(!tblClients.isEOF())
	{
		var code = tblClients.getValue("FCOD");
		var query = "SELECT id FROM discount WHERE code='"+code+"'";
		var res = OpenExtTable(conn, query);
		if(res.isEmpty())
			query = "INSERT INTO discount SELECT COALESCE(MAX(id), 0)+1, " +
				"'"+tblClients.getValue("FTXT")+"', 0, "+tblClients.getValue("FSKIDKA")+", FALSE,'"+code+"' FROM discount;";
		else
			query = "UPDATE discount SET " +
				"name='"+tblClients.getValue("FTXT") + "', " +
				"value="+tblClients.getValue("FSKIDKA")+ " " +
				"WHERE code='"+code+"'";
		ExecSQL(conn, query);
		res.close();
		progressWorked(1, "Выгружен клиент " +tblClients.getValue("FTXT"));
		tblClients.moveNext();	
	}
	tblClients.close();
	Put_Log_Message("Экспорт клиентов завершён");
}

function getFONmklID(article)
{
	article = String(article);
	var ret = arrNmklID[article];
	if (ret)
		return ret;
	
	var extTbl = OpenExtTable(conn,	
			"select id_article from t_article where article = " 
				+ sqlToEx(POSTGRE, article));
	
	if (extTbl.isEmpty())
	{
		extTbl.close();
		return null;
	}
	
	ret = Number(extTbl.getValue("id_article"))	
	arrNmklID[article] = ret;
	extTbl.close();
	return ret;
}

function temp_importNmkl()
{
	
	include ("Objects/DpClEx.js")
	var dbname = "l_db_test";
	var strConn = "jdbc:postgresql://localhost/"  + dbname;
	
	conn = getDBConnection(strConn, "postgres", "");
	
	var extTbl = OpenExtTable(conn, "select * from t_article");
	while (!extTbl.isEOF())
	{
		var oNmkl = new DpClEx("nmkl", 0);
		oNmkl.setVar("HCOD", extTbl.getValue("article") );
		oNmkl.setVar("HTXT0", extTbl.getValue("name") );
		oNmkl.setVar("HTXTS", extTbl.getValue("name") );
		oNmkl.setVar("HNDS", 20);
		oNmkl.save("ADD", true);
		
		extTbl.moveNext();
	}
	
}

function importBill(type, isOtkaz)
{
	if(isOtkaz)
		return;
	Put_Log_Message("Импорт " + (type == 6 ? "чеков":"возвратов"));
	var nCodOrg = CURRENT_ORG;//getOrgVar("ORGROZN");
	if (!nCodOrg)
		nCodOrg = 0;
	else
		nCodOrg = Number(nCodOrg); 
	var sql = "SELECT * FROM orders LEFT JOIN discount ON orders.id_discount=discount.id WHERE status=2";	
	var extTbl = OpenExtTable(conn, sql);	
	progressReset();
	initProgressBar(0, extTbl.recordCount);
	var nCount = 0;
	while (!extTbl.isEOF())
	{
		var id_order = Number(extTbl.getValue("id")); 
		var nID = Number(extTbl.getValue("num")); 
		var sSQL = "select fwid from ^htcs where foutid = " + sqlTo(String(nID));
		if (type == 6)
			sSQL += " and FISRET = " + (isOtkaz? sqlTrue : sqlFalse);  		
		var oSnap = getSnap(sSQL);	
		if (oSnap && oSnap[0])
		{
			extTbl.moveNext();
			progressWorked(1, "Импорт " + (type == 6 ? (isOtkaz?"отказов":"чеков"):"возвратов"));
			continue;
		}
		var nNop = 1; //TODO:
//		if (type == 8)
//			nNop = 2;
//		if (isOtkaz)
//			nNop = 3;
		var oDoc = new DpDoc("TCS", nNop);
		oDoc.setVar("HNOM", String(nID));
		oDoc.setVar("HOUTID", String(nID));		
		var date = String(String(extTbl.getValue("orderdate")).left(10)+" "+extTbl.getValue("timeopen")).replace(/-/g, "/");
		date = new Date(date).getVarDate();
		oDoc.setVar("HDAT", date);
		var nMol = getKassirID(extTbl.getValue("id_user"));
		oDoc.setVar("HMOL", nMol);
		oDoc.setVar("HPLCH", extTbl.getValue("code"));		
		oDoc.setVar("HPODR", fpodr);
		
		var sum = 0;
		sql = "SELECT * FROM order_table WHERE id_order = " + id_order;
		var extTblCont = OpenExtTable(conn, sql);		
		var n = 0;
		while(!extTblCont.isEOF())
		{
			var oRow = oDoc.createRow("ROW");
			n++;
			oRow.setVar("RNOM", n);
			var nmkl_id = getNmklFWID(extTblCont.getValue("externalcode"));
			oRow.setVar("RTNMK", nmkl_id);
			var price = Number(extTblCont.getValue("price"));
			oRow.setVar("ROCENA", price);
			var amount = Number(extTblCont.getValue("amount"));
			oRow.setVar("RKOL", amount);
			oRow.setVar("RISWHITE", true);
			var discount = price*amount - Number(extTblCont.getValue("summ"));
			oRow.setVar("RDISCOUNT", discount);
			sum+=Number(extTblCont.getValue("summ"));
			
//			var edi = arrEdiExt[Number(extTblCont.getValue("id_measure"))];
//			if (edi)
//				oRow.setVar("REDI", edi);
//			oRow.setVar("RPNDS", null);
			oRow.setVar("RPODR", getNmklKitchenID(nmkl_id));
			oRow.setVar("RMOL", getKassirID(Number(extTblCont.getValue("id_user"))));
			oDoc.appendRow("ROW", oRow);
			extTblCont.moveNext();
		}
		
		var summtype = Number(extTbl.getValue("summtype"));
		summtype = summtype==1 ? 0 : (summtype==4 ? 2 : 1);		
		oDoc.setVar("HTYPE_OPL", summtype);
		oDoc.setVar("HSUM", sum);
		oDoc.setVar("HSUM1", sum);	
		oDoc.setVar("HNR" , n);		
		extTblCont.close();		
		
		if (n != 0)
		{
/*		
			if (type == 8)
			{
				var nIDRet = Number(extTbl.getValue("id_bill_return")); 
				oDoc.setVar("HISRET" , true);
				oSnap = getSnap("select fwid from ^htcs where foutid = " + sqlTo(String(nIDRet)));
				if (oSnap && oSnap[0])
				{
					oDoc.setVar("HIDRET" , oSnap[0]);				
				}
				var extTblPay = OpenExtTable(conn, "select summa, cardnumber, \"type\" from t_bill_pay where id_bill = " + nIDRet
						+ " ORDER BY \"type\" ");
				if (!extTblPay.isEOF())
				{
					oDoc.setVar("HTYPE_OPL", Number(extTblPay.recordCount) == 2 ? 3 : Number(extTblPay.getValue("type")));
				}
				extTblPay.close();
			}
			else if (isOtkaz)
			{
				oDoc.setVar("HISRET" , true);
			}
*/			
			oDoc.save(true, "ADD", true, true);	
			nCount++;
		}

		progressWorked(1, "Импорт " + (type == 6 ? "чеков":"возвратов"));
		extTbl.moveNext();
	}
	sql = "UPDATE orders SET status=4 WHERE status=2";
	ExecSQL(conn, sql);
	Put_Log_Message("Импортировано " + nCount + " " + (type == 6 ? (isOtkaz?"отказов":"чеков"):"возвратов"));
	//browse(extTbl);
}

function getKassirID(extID)
{
	extID = String(extID);
	var ret = arrKassID[extID];
	if (ret)
		return ret;
	
	var codMol = getPar("CODMOL");
	var oSnap = getSnap("select fcod from ^listcl where fcl = " 
			+ codMol + " and foutid = " + sqlTo(extID));
	
	if (oSnap && oSnap[0])
	{
		arrKassID[extID] = oSnap[0]; 
		return oSnap[0];
	}
	
	return null;
}

function getNmklFWID(articul)
{
	articul = String(articul);
	var ret = arrNmklFWID[articul];
	if (ret)
		return ret;
	
	var oSnap = getSnap("select fwid from ^cl_nmk where fcod = " + sqlTo(articul));
	
	if (oSnap && oSnap[0])
	{
		arrNmklFWID[articul] = oSnap[0]; 
		return oSnap[0];
	}
	
	return null;
}

function getNmklKitchenID(nmkl_id)
{
	nmkl_id = Number(nmkl_id);
	var ret = arrKitchenID[nmkl_id];
	if(ret)
		return ret;
	
	var oSnap = getSnap("select fpodr from ^cl_nmk where fwid = " + sqlTo(nmkl_id));
	
	if (oSnap && oSnap[0])
	{
		arrKitchenID[nmkl_id] = oSnap[0]; 
		return oSnap[0];
	}
	
	return null;	
}

function Put_Log_Message(msg)
{
	msg = String(msg);
	display.syncExec
	(
		function logFnk()
		{
/*		
			LOG.getCtrl().setText(LOG.getCtrl().getText() + "\r\n" + msg);
			var lc = LOG.getCtrl().getLineCount();
			if (lc > 10)
				LOG.getCtrl().setTopIndex(lc - 10);
*/
			LOG.appendText("\r\n" + msg);
		}
	);
}


function initProgressBar(nMin,nMax)
{
	display.syncExec
	(
		function init()
		{
			progress.setMinimum(nMin);
			progress.setMaximum(nMax);
		}
	);
}

function progressWorked(nWorked,sText)
{
	display.syncExec
	(
		function worked()
		{
			progress.setSelection(progress.getSelection() + nWorked);
			progress.setToolTipText(String(nWorked));
			if (sText)
				status.setValue(sText);
		}
	);
	java.lang.Thread.sleep(1);
}

function progressReset()
{
	display.syncExec
	(
		function worked()
		{
			progress.setSelection(0);
			
		}
	);
	java.lang.Thread.sleep(1);
}

function createPGUpdateQuery(tblName, m, where)
{
	sSQL = "UPDATE " + tblName;
	var sUpd = "";
	var bFirst = true;

	for (var fld in m)
	{			
		var fldName = fld;
		if(fldName == "level")
			fldName = "\"level\"";
		
		if(fldName == "type")
			fldName = "\"type\"";
		
		if (typeof(toScrObj(m[fld])) == "string")
		{
			
			m[fld] = String(java.lang.String(m[fld]).replace("№","#"));
		}
		
		
		try
		{
			if (!sWhere && fld.equalsIgnoreCase("fwid"))
				continue;
		}
		catch(x){}			
		if (bFirst)
		{
			sUpd += " SET " + fldName + " = " + sqlToEx(POSTGRE, m[fld]);
			bFirst = false;
		}
		else
			sUpd +=", " + fldName + " = " + sqlToEx(POSTGRE, m[fld]);
	}
	
	sSQL+=sUpd + " WHERE " + where;
	
	return sSQL;
	
}

function createPGInsertQuery(tblName, m)
{
	var sSQL = "insert into "+ tblName;		
	var sField = "";
	var sValue = "";
	
	for(var fld in m)
	{
		var fldName = fld;
		if(fldName == "level")
			fldName = "\"level\"";
		
		sField += ","+fldName;
		if (typeof(toScrObj(m[fld])) == "string")
		{
			m[fld] = String(java.lang.String(m[fld]).replace("№","#"));
		}
		
		sValue += ","+sqlToEx(POSTGRE, m[fld]);
	}
	
	sSQL +="("+sField.substr(1)+") values ("+ sValue.substr(1)+")";
	
	return sSQL;
}
