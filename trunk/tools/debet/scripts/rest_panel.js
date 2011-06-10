include ("sys/DpBaseDlg.js")
function Load()
{
	Caption(ru("Ресторан", "Ресторан"));
	
	//FORM.setImage(rootDirectoryEx() +"/icons/billing.gif");

	loadCalcPanel();
}


function loadCalcPanel()
{
	
	this.selHandler = selHandler;
	this.selDocHandler = selDocHandler;
	this.settingsDocHandler = settingsHandler;
	pReport = PANELBAR.createPanel();
	pReport.setCaption(ru("Отчеты","Звіти"));
		
	pReport.addItem("VDOST", ru("Ведомость остатков","Відомість залишків"), true);	
	pReport.addItem("OBR", ru("Оборотная ведомость","Обігова відомість"), true);	
	pReport.addItem("VBRS", ru("Выборка по отпуску","Вибірка по відпуску"), true);	
	pReport.addItem("VBPM", ru("Выборка по перемещению","Вибірка по переміщенню"), true);	
	pReport.addItem("VBPR", ru("Выборка по приходу","Вибірка по приходу"), true);
	pReport.addItem("VBRS2", ru("Выборка по списанию","Вибірка по списанню"), true);
	pReport.addItem("VBGP5", ru("Приготовление блюд", "Приготування блюд"), true);
	pReport.addItem("VBGP7", ru("Расходы ингредиентов", "Витрати iнгредієнтiв"), true);
	
	
	pDoc = PANELBAR.createPanel();
	pDoc.setCaption(ru("Документы","Документи"));
		
	pDoc.addItem("TCS", UR("Чеки|Чеки"), true);	
	pDoc.addItem("TCSRET", UR("Чеки повернення|Чеки возвраты"), true);
	pDoc.addItem("TCSOTK", UR("Чеки вiдмова|Чеки отказы"), true);	
	pDoc.addItem("NK", UR("Реалiзацiя|Реализация"), true);	
	pDoc.addItem("GP", UR("Готова продукцiя|Готовая продукция"), true);
	pDoc.addItem("SM", UR("Перемiщення|Перемещение"), true);
	pDoc.addItem("PM", UR("Внутрішнє переміщення|Внутреннее перемещение"), true);
	pDoc.addItem("PN", UR("Прибуткування|Приход"), true);
	pDoc.addItem("PZ", UR("Списання|Списание"), true);
	pDoc.addItem("VR", UR("Повернення реалізації|Возврат реализации"), true);
	pDoc.addItem("IM", UR("Інвентаризація|Инвентаризация"), true);
	
	pCl = PANELBAR.createPanel();
	pCl.setCaption(ru("Справочники","Довiдники"));
		
	pCl.addItem("CLS.NMKL", "Номенклатура", true);	
	pCl.addItem("CLS.PODR", UR("Бари та кухнi|Кухни/Бары"), true);	
	pCl.addItem("CLS.MOL", UR("Касири|Кассиры"), true);
	pCl.addItem("CLS.REC", UR("Рецепти|Рецепты"), true);
	pCl.addItem("CLS.MENU", "Меню", true);
	
	
	pSyncro = PANELBAR.createPanel();
	pSyncro.setCaption(ru("Синхронизация","Синхронiзация"));
		
	pSyncro.addItem("SYNCRO", "Запуск", true);
//knorr
	pSyncro.addItem("ALDEBARAN", UR("Альдебаран|Альдебаран"), true);
//knorr
	pSyncro.addItem("SYNCSET", UR("Налаштування|Настройка"), true);
	/*
	pSettings = PANELBAR.createPanel();
	pSettings.setCaption(UR("Налаштування|Настройки"));
	pSettings.addItem("NMK_PROC", "% наценки для товаров", true);	
	*/
	
	/*
	pS
rvis.addItem("ITERATED", ru("Договора","Угоди"), true);	
	pServis.addItem("BU", 		ru("Начисления","Нарахування"), true);	
	pServis.addItem("BO", 		ru("Оплаты","Оплати"), true);	
	pServis.addItem("DEBTORS", 	ru("Долги","Борги"), true);	
	pServis.addItem("ORDERS", 	ru("Заявки","Заявки"), true);	
	*/
	
	pReport.setSelectHandler(this, "selHandler");
	pCl.setSelectHandler(this, "selHandler");
	pSyncro.setSelectHandler(this, "selHandler");
	pDoc.setSelectHandler(this, "selDocHandler");
	//pSettings.setSelectHandler(this, "settingsHandler");
	//PANELBAR.setHorizontal(true);
	var ctrl = PANELBAR.getCtrl();
	ctrl.setWeights([120,150,80,50])
	
}

function selHandler(sID, oPanel)
{
	switch(sID)
	{
		case "VDOST":
			showWindow("r_vdost.js")
			break;
		case "OBR": 
			showWindow("r_obr.js")
			break;
		case "VBPR":
			showWindow("r_vbpr.js");
			break;
		case "VBRS":
		case "VBRS2":
			WriteParameter("FDOC",(sID == "VBRS"?"NK":"PZ"),"r_vbrs")
			showWindow("r_vbrs.js");
			break;
		case "VBPM":
			showWindow("r_vbpm.js");
			break;
		case "VBGP5":
			showWindow("r_vbgp.js", SW_NOMODAL,{frtype:'5'})
			break;
		case "VBGP7":
			showWindow("r_vbgp.js", SW_NOMODAL,{frtype:'7'})
			break;
		case "CLS.NMKL":
			showWindow("l_clnmktree.xml");
			break;
		case "CLS.PODR":
			var par = new Object();			
			par.Fcl =  getPar("CODPODR");			
			showWindow("l_cl.xml", SW_NOMODAL, par);
			break
		case "CLS.MOL":
			var par = new Object();			
			par.Fcl =  getPar("CODMOL");			
			showWindow("l_cl.xml", SW_NOMODAL, par);
			break	
		case "CLS.REC":
			showWindow("l_cl_rec.js");
			break;
		case "CLS.MENU":
			showWindow("l_cl_pri.xml");
			break;
		case "SYNCRO":
			showWindow("restaurant:synchro.xml", SW_MODAL);
			break;
//knorr
		case "ALDEBARAN":
			showWindow("restaurant:aldebaran.xml", SW_NOMODAL);
			break;
//knorr
		case "SYNCSET":
			showWindow("e_param.xml", SW_MODAL, {sel:"RESTAURANT"});
			break;
	}
}

function selDocHandler(sID, oPanel)
{
	var par = new Object();
	if (sID == "TCSRET")
	{
		par.doc = "TCS";
		par.nop = 2;
	}
	else if (sID == "TCSOTK")
	{
		par.doc = "TCS";
		par.nop = 3;
	}
	else
	{
	par.doc = String(sID);
	par.nop = 1;
	}
	showWindow("l_docekz.xml", SW_NOMODAL, par);
	
}

function settingsHandler(sID, oPanel)
{
	if (sID == "NMK_PROC")
	{
		var nProc = input("% наценки для товаров", "Введите % наценки для товаров",	Number(getOrgVar("NMK_PROC")), 3, 3);
		if(nProc != null)
			ExecuteSQL("UPDATE ^ORGVARS SET FVAL = "+ sqlTo(String(nProc)) + " WHERE FVAR='NMK_PROC'");
	}
}
