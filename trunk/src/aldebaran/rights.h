#ifndef RIGHTS_H
#define RIGHTS_H

#include <qobject.h>

enum alRights
{
    rStart = 0,
    rLogin,
    rZReport,
    rXReport,
    rPaying,
    rPayout,
    rEquipment,
    rImport,
    rExport,
    rSettings,
    rOrderEditStrangeLines,
    rArchive,
    rDiscount,
    rDiscountProtected,
    rAdvancedReport,
    rCard,
    rEnd
};

const bool rDefaultSets[3][rEnd] =
{
    {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE},
    {TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE},
    {TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,FALSE}
};

const QString alRightsStrings[] = {"", 
			     QObject::tr("System: Login"),
			     QObject::tr("System: Z-report"),
			     QObject::tr("System: X-Report"),
			     QObject::tr("System: Paying"),
			     QObject::tr("System: Payout"),
			     QObject::tr("System: Equipment"),
			     QObject::tr("System: Import goods"),				
			     QObject::tr("System: Export sales"),
			     QObject::tr("System: Settings"),
			     QObject::tr("Order: edit strange lines"),
			     QObject::tr("Order: Archive"),
			     QObject::tr("Discount: Manual"),
			     QObject::tr("Discount: Protected"),			     
			     QObject::tr("System: Advanced report"),
			     QObject::tr("Order: Card pay"),
			     ""}; 

#endif
