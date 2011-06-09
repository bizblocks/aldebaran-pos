include("sys/mask.js");
include("Objects/DpClEx.js");
include("doc/DpDoc.js");
var arrNmklID = new Array();
var arrKassID = new Array();
var arrNmklFWID = new Array();
var arrEdi = new Array();
var arrEdiExt = new Array();
var conn;
var syncPeriod = null;
var importCheck = false;
var isDeleteMenu = false;

include("sys/DpBaseDlg.js");
function Load()
{
	TCNUM.mask = "########";
	Caption("Синхронизация с Front Office");
	
	var hostName = getPar("REST_SYNC_HOST");
	if (!hostName)
		hostName = "localhost";	
	HOST.value = hostName;
	HOST.readOnly = true;
	
	
	var dbName = getPar("REST_SYNC_DBNAME");
	if (!dbName)
		dbName = "db_server";	
	DBNAME.value = dbName;
	DBNAME.readOnly = true;;
	
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
	btnCancel.setText(UR("Зачинити|Закрыть"));
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
	
	//ExecSQL(conn, "delete  from t_article ", true);
	//ExecSQL(conn, "delete  from t_article_group ", true);
	
	syncPeriod = getSyncPeriod();
	importCheck = IMPBILL.checked;
	isDeleteMenu = DELMENU.checked;
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
	
//	if (isDeleteMenu)
//		deleteMenu();
	synchMenu();

//	if (importCheck)
//	{
//		importBill(6, false);
//		importBill(6, true);
//		importBill(8);
//	}
	
	progressReset();
		
}

function synchroEdi()
{
	arrEdi = new Array();
	arrEdiExt = new Array();
	var tbl = OpenTable("select fcod, ftxts, ftxtf from ^cl_edi order by fcod");
	while(!tbl.isEOF())
	{
		var innerCod = Number(tbl.getValue("fcod"));
		var extCod = getExtEdiCod(tbl.getValue("ftxts"), tbl.getValue("ftxtf"), innerCod);		
		arrEdi[innerCod] =  extCod;
		arrEdiExt[extCod] =  innerCod;
		tbl.moveNext();
	}
	
	tbl.close();
	
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

function getExtEdiCod(txt, txtf, cod)
{
	var extTbl = OpenExtTable(conn, 
			"select id_measure, name, sname from t_measure where sname = " 
				+ sqlToEx(POSTGRE, txt));
	if (extTbl.isEmpty())
	{
		var sSQL = "insert into t_measure (name, sname, digits, amount) values ("
			+ sqlToEx(POSTGRE, txtf) +", " + sqlToEx(POSTGRE, txt) + ", 3, 1)"
		var bRet = ExecSQL(conn, sSQL, true);
		
		extTbl.close();
		if(bRet)
			return getExtEdiCod(txt);
		else
			return null;
	}
	else
	{
		var ret = Number(extTbl.getValue("id_measure"));
		if (cod)
		{
			var sql = "select count(*) as cnt from ^cl_nmk where fcedib = " + cod + " and fvid = 'S'";
			var oSnap = getSnap(sql)
			if (oSnap && oSnap[0] && oSnap[0] > 0)
			{
				var sSQL = "update t_measure set amount = 0 where id_measure = " + ret;			
				var bRet = ExecSQL(conn, sSQL, true)
			}
		}
		extTbl.close();
		return ret;
	}
}

function importMol()
{
	var codmol = getPar("CODMOL", "MTR");
	var extTbl = OpenExtTable(conn,	"select id_kassir, name from t_kassir order by id_kassir");
	initProgressBar(0, extTbl.recordCount);
	var nRow = 0;
	while(!extTbl.isEOF())
	{
		nRow++;
		var name = String(extTbl.getValue("name"));
		var outid = String(Number(extTbl.getValue("id_kassir")));		
		var oSnap = getSnap("select fwid, foutid from ^listcl where fcl = " + codmol + " and ftxt = " + sqlTo(name));
		if(oSnap)
		{
			if(oSnap[1] != outid)
			{
				ExecuteSQL("update ^cl set foutid = " + sqlTo(outid) + " where fwid = " + oSnap[0]);
			}
		}
		else
		{
			var oCL = new DpClEx("CL1", codmol);
			oCL.setVar("HTXT", name);
			oCL.setVar("HCL", codmol);
			
			var nCod = 1;
			var sSQL = "select max(fcod) as cod from ^listcl where fcl = " + codmol;
			oSnapCod = getSnap(sSQL);
			if(oSnapCod && oSnapCod[0])
				nCod = oSnapCod[0] + 1;			
			oCL.setVar("HCOD", nCod);
			oCL.setVar("HOUTID", outid);
			Put_Log_Message("Добавлен МОЛ: " + name)
			
			oCL.save();
		}
		
		progressWorked(1, "Импорт МОЛ");
			
		extTbl.moveNext();
	}
	
	extTbl.close();
}

function synchPodr()
{
	include("Objects/DpExtentionBuilder.js");
	var sprPodr = getPar("CODPODR", "MTR");
	var extBuilder = new DpExtentionBuilder("CL", String(sprPodr));
	if (!extBuilder.exist())
		return
	var tblExt = extBuilder.getValueTableName(); 
	
	if (!hasField(tblExt, "FPLACE") && !hasField("FKITCHEN"))
		return;
	
	
	//Кухни
	var sSQL = "select cl.fcod as fcod, cl.ftxt as ftxt from ^listcl cl inner join " + tblExt + " e on cl.fwid = e.fmainwid "
		+ " where e.fmainwid != 0 and cl.fcl = " + sprPodr + " and fkitchen =  " +sqlTrue;
	
	var tbl = OpenTable(sSQL);
	initProgressBar(0, tbl.recordCount);
	while (!tbl.isEOF())
	{
		var m = new Object();
		m.name = String(tbl.getValue("ftxt"));
		m.id_kitchen = Number(tbl.getValue("fcod"));
		
		var extTbl = OpenExtTable(conn,	
				"select id_kitchen from t_kitchen where id_kitchen = " 
					+ m.id_kitchen);
		
		var sSQL = "";
		if (extTbl.isEmpty())
		{
			sSQL = createPGInsertQuery("t_kitchen" , m);
			Put_Log_Message("Добавленна Кухня: " + m.name)
			
		}
		else
		{
			sSQL = createPGUpdateQuery("t_kitchen" , m, " id_kitchen = " + m.id_kitchen );
		}
		
		ExecSQL(conn, sSQL, true);
		progressWorked(1, "Экспорт Кухон");
		tbl.moveNext();
		extTbl.close();
	}
	tbl.close();
	
	//Залы
	sSQL = "select cl.fcod as fcod, cl.ftxt as ftxt from ^listcl cl inner join " + tblExt + " e on cl.fwid = e.fmainwid "
		+ " where e.fmainwid != 0 and cl.fcl = " + sprPodr + " and fplace =  " +sqlTrue;
	
	tbl = OpenTable(sSQL);
	initProgressBar(0, tbl.recordCount);
	while (!tbl.isEOF())
	{
		var m = new Object();
		m.name = String(tbl.getValue("ftxt"));
		m.id_place = Number(tbl.getValue("fcod"));
		
		var extTbl = OpenExtTable(conn,	
				"select id_place from t_place where id_place = " 
					+ m.id_place);
		
		var sSQL = "";
		if (extTbl.isEmpty())
		{
			sSQL = createPGInsertQuery("t_place" , m);			
			Put_Log_Message("Добавлен Зал: " + m.name);
			
		}
		else
		{
			sSQL = createPGUpdateQuery("t_place" , m, " id_place = " + m.id_place );
		}
		
		ExecSQL(conn, sSQL, true);
		
		tbl.moveNext();
		progressWorked(1, "Экспорт Залов");
		extTbl.close();
	}
	tbl.close();
	

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

function deleteMenu()
{
	var extTbl = OpenExtTable(conn,	"select * from t_menu ");
	while (!extTbl.isEOF())
	{
		var id_menu = Number(extTbl.getValue("id_menu"));
		var menuName = String(extTbl.getValue("name"))
		var oSnap = getSnap("select fwid from ^cl_pri where fwid = " + id_menu);
		if (oSnap == null)
		{
			ExecSQL(conn, "delete from t_menu_article_group where id_menu = " + id_menu, true);
			ExecSQL(conn, "delete from t_article_menu where id_menu = " + id_menu, true);
			ExecSQL(conn, "delete from t_menu where id_menu = " + id_menu, true);
			Put_Log_Message("Удалено меню " + menuName);			
		}
		
		extTbl.moveNext();
	}
	
	extTbl.close();
}

function syncNmklGrp()
{
	var tmpFunc = "CREATE OR REPLACE FUNCTION upsert (sql_update TEXT, sql_insert TEXT) RETURNS VOID LANGUAGE plpgsql
AS $$
BEGIN
    LOOP
        -- first try to update
        EXECUTE sql_update;
        -- check if the row is found
        IF FOUND THEN
            RETURN;
        END IF;
        -- not found so insert the row
        BEGIN
            EXECUTE sql_insert;
            RETURN;
            EXCEPTION WHEN unique_violation THEN
                -- do nothing and loop
        END;
    END LOOP;
END;
$$;";

	var sql = "select fwid, ftxt, fcod, fpodr, max(fdat) from ^cl_pri where fisgrp = 0 order by fcod";
	var tblGroups = OpenTable("m", sql);	
	while(!tblGroups.isEOF())
	{
		var updQuery = "UPDATE";
		var insQuery = "INSERT";
		ExecSQL(conn, "select upsert('"+updQuery+"', '"+insQuery+"')");
		Put_Log_Message("Добавлена группа: "+"");
	}

}

function synchMenu()
{
	syncNmklGrp();
//	var sql = "select fwid, ftxt, fcod, fpodr, fdat from ^cl_pri where fisgrp = 0";
//	if (syncPeriod.bdate)
//		sql += " and fdat >= " + sqlTo(syncPeriod.bdate);
//	if (syncPeriod.edate)
//		sql += " and fdat <= " + sqlTo(syncPeriod.edate);
//	sql += " order by fcod";
	
	var tblMenu = OpenTable("m", sql);
	
	while (!tblMenu.isEOF())
	{
		var m = new Object();
		m.id_menu = Number(tblMenu.getValue("FWID"));
		m.id_place = Number(tblMenu.getValue("FPODR"));
		m.name = String(tblMenu.getValue("FTXT"));
		
		ExecSQL(conn, "delete from t_menu_article_group where id_menu = " + m.id_menu, true);
		ExecSQL(conn, "delete from t_article_menu where id_menu = " + m.id_menu, true);
		
		var extTbl = OpenExtTable(conn,	
				"select id_menu from t_menu where id_menu = " + m.id_menu);
		var sSQL = "";
		if (extTbl.isEmpty())
		{
			m.dtime_created = new Date().getTime();
			m.dtime_created = Math.round(m.dtime_created/1000);
			sSQL = createPGInsertQuery("t_menu" , m);
			Put_Log_Message("Добавлено меню: " + m.name)
			
		}
		else
		{
			sSQL = createPGUpdateQuery("t_menu" , m, " id_menu = " + m.id_menu);
			Put_Log_Message("Изменено меню: " + m.name)
			
		}
		
		var bRet = ExecSQL(conn, sSQL, true);
		
	
		
		var  priceTblName = String(pName(String(tblMenu.getValue("FCOD")), today, tblMenu.getValue("FWID")));

		
		DropTable("TMP_PRICE")
		ExecuteSQL("select p.fcena as fcena, p.fpodr as fpodr, n.fcod as fnmklcod, n.fleftkey as flkey, n.fpodr as fnmklpodr " 
				+ " into TMP_PRICE from " + priceTblName + " p inner join ^cl_nmk n on p.fnmkl = n.fwid")
		var priceTbl = OpenTable("TMP_PRICE");		
		initProgressBar(0, priceTbl.recordCount);
		while (!priceTbl.isEOF())
		{
			var nmk = new Object();
			nmk.id_menu = m.id_menu;
			nmk.id_kitchen = Number(priceTbl.getValue("fpodr"))?Number(priceTbl.getValue("fpodr")):Number(priceTbl.getValue("fnmklpodr"));			
			nmk.id_article = getFONmklID(String(priceTbl.getValue("fnmklcod")));
			nmk.price = Number(priceTbl.getValue("fcena"));
			
			if (nmk.id_article != null)
			{
				sSQL = createPGInsertQuery("t_article_menu" , nmk);
				ExecSQL(conn, sSQL, true);
			}
			
			progressWorked(1, "Экспорт меню " + m.name );
			priceTbl.moveNext();
		}
				
		priceTbl.close();
		
		var sqlGroup = "select fwid, fcod, ftxt0 from ^cl_nmk where fwid != 0 and fisgrp = " + sqlTrue
				+ " and exists (select flkey from tmp_price where flkey between fleftkey and frightkey)";
		
		//browse(sqlGroup);
		
		var groupTbl = OpenTable(sqlGroup);		
		while (!groupTbl.isEOF())
		{
			var group = new Object();
			group.id_menu = m.id_menu;
			group.id_article_group = Number(groupTbl.getValue("fwid"));			
			
			var sqlInsGrp = createPGInsertQuery("t_menu_article_group" , group);
			ExecSQL(conn, sqlInsGrp, true);
			
			groupTbl.moveNext();
		}
		
		groupTbl.close();
		tblMenu.moveNext();
		
		extTbl.close();
		
	}
	
	tblMenu.close();
		
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
	var nCodOrg = getOrgVar("ORGROZN");
	if (!nCodOrg)
		nCodOrg = 0;
	else
		nCodOrg = Number(nCodOrg); 
	
	var sql = "select * from t_bill where state = " + type;
		
	
	if(syncPeriod.tcnum)
	{
		sql += " and id_bill > " + syncPeriod.tcnum; 
	}
	else
	{
		if (syncPeriod.bdate)
			sql += " and dtime_open >= " + Math.round(syncPeriod.bdate.getTime()/1000);
		
		if (syncPeriod.edate)
			sql += " and dtime_open <= " + Math.round(goDay(syncPeriod.edate, 1).getTime()/1000);
	}
	//alert(sql);
	var extTbl = OpenExtTable(conn, sql);
	progressReset();
	initProgressBar(0, extTbl.recordCount);
	var nCount = 0;
	while (!extTbl.isEOF())
	{
		var nID = Number(extTbl.getValue("id_bill")); 
		
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
		if (type == 8)
			nNop = 2;
		if (isOtkaz)
			nNop = 3;
		var oDoc = new DpDoc("TCS", nNop);
		oDoc.setVar("HNOM", String(nID));
		oDoc.setVar("HOUTID", String(nID));
		var date = Number(extTbl.getValue("dtime_open")) * 1000;
		date = new Date(date).getVarDate();
		oDoc.setVar("HDAT", date);
		var nMol = getKassirID(extTbl.getValue("id_kassir"));
		oDoc.setVar("HMOL", nMol);		
		oDoc.setVar("HPLCH", nCodOrg);		
		
		
		var extTblPay = OpenExtTable(conn, "select summa, cardnumber, \"type\" from t_bill_pay where id_bill = " + nID
				+ " ORDER BY \"type\" ");
		var sum = 0;
		var n = 1;
		while(!extTblPay.isEOF() && n <=2)
		{
			var nSum = Number(extTblPay.getValue("summa"));
			sum += nSum;
			
			oDoc.setVar("HSUM" + n, nSum);
			oDoc.setVar("HTYPE_OPL", n == 2 ? 3 : Number(extTblPay.getValue("type")));
			extTblPay.moveNext();
			n++;			
		}
		extTblPay.close();
		oDoc.setVar("HSUM", sum);		
		
		var extTblCont = OpenExtTable(conn, "select * from t_bill_cont where id_bill = " + nID
				+ " and " + (isOtkaz?"state = 2":"state <> 2") + " order by article_pos");
		
		
		n = 0;
		while(!extTblCont.isEOF())
		{
			var oRow = oDoc.createRow("ROW");
			n++;
			oRow.setVar("RNOM", n);
			oRow.setVar("RTNMK", getNmklFWID(extTblCont.getValue("article")));
			oRow.setVar("ROCENA", Number(extTblCont.getValue("price")));
			oRow.setVar("RKOL", Number(extTblCont.getValue("amount")));
			oRow.setVar("RDISCOUNT", (-1) * Number(extTblCont.getValue("discount")));
			var edi = arrEdiExt[Number(extTblCont.getValue("id_measure"))];
			if (edi)
				oRow.setVar("REDI", edi);
			//oRow.setVar("RPNDS", null);
			oRow.setVar("RISWHITE", Number(extTblCont.getValue("white")) == 1);
			oRow.setVar("RPODR", Number(extTblCont.getValue("id_kitchen")));
			//oRow.setVar("RPODR", Number(extTblCont.getValue("id_kitchen")));
			oRow.setVar("RMOL", getKassirID(Number(extTblCont.getValue("id_kassir"))));			
			oDoc.appendRow("ROW", oRow);
			extTblCont.moveNext();
			
						
		}
		oDoc.setVar("HNR" , n);
		extTblCont.close();
		
		if (n != 0)
		{
		
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
			
			oDoc.save(true, "ADD", true, true);	
			nCount++;
		}
		progressWorked(1, "Импорт " + (type == 6 ? "чеков":"возвратов"));
		
		extTbl.moveNext();
	}
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

