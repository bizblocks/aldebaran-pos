/****************************************************************************
** $Id: tescalesbase.h,v 1.3 2006/03/25 11:32:22 leader Exp $
**
** Trade equipment common portable library project
**
** Copyright (C) 1999-2006 Leader InfoTech.  All rights reserved.
**
** This file is part of the Library of the Ananas
** automation accounting system.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.leaderit.ru/ or email sales@leaderit.ru
**
** Contact org@leaderit.ru if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

/*
   Abstract Scales interface object
   (c) V.Grazdankin, 1999-2005
*/
#ifndef TESCALES_H
#define TESCALES_H
#include <tebase.h>

#define EVENT_SCALES_WEIGHT_READ 1
#define EVENT_SCALES_COMM_ERROR 100
#define EVENT_SCALES_QUERY_INFO 2

struct PLUInfo {
    unsigned int  PLU,
         ICode;
    char Name[56];
    int  Price,
         SLife,
         Tare,
         GCode,
         MsgNo;
};

//---------------------------------------------------------------------------
class LIB_EXPORT TEScalesBase : public TEBase
{
    Q_OBJECT
    
public:
    TEScalesBase( int pn );
    ~TEScalesBase();

    QString productCode() const; // Can be used after EVENT_SCALES_QUERY_INFO. 
                                 //Returns product code for which information was requested.
    
    
    
public:
	double price() const {return m_dPrice;}
	virtual void setPrice( double Price );
	
	double tareWeight() const {return m_dTareWeight;}
	virtual void setTareWeight( double dTareWeight ) {m_dTareWeight=dTareWeight;}

	unsigned int PLU() const {return m_uiPLU;}
	virtual void setPLU(unsigned int uiPLU) {m_uiPLU=uiPLU;}

	QString prodCode() const {return m_sProdCode;}
	virtual void setProdCode(const QString & sProdCode) {m_sProdCode=sProdCode;}

	QString groupCode() const {return m_sGroupCode;}
	virtual void setGroupCode(const QString & sGroupCode) {m_sGroupCode=sGroupCode;}

	QString prodName() const {return m_sProdName;}
	virtual void setProdName(const QString & sProdName) {m_sProdName=sProdName;}

	QDateTime useByDate() const {return m_dUseByDate;}
	virtual void setUseByDate(const QDateTime & dUseByDate) {m_dUseByDate=dUseByDate;}
	
	double weight() const {return 0;}
	double summa() const {return 0;}

public slots:
	virtual int readDisplay();

protected:
	void setSumma(double dSum){ Q_UNUSED( dSum );};
	void setWeight(double dWeight){ Q_UNUSED( dWeight ); };

//    virtual void processEvent( int Code );
//    int poll();
private:
	unsigned int m_uiPLU;
	QString m_sProdCode;
	QString m_sGroupCode;
	double m_dPrice;
	double m_dTareWeight;
	QString m_sProdName;
	QDateTime m_dUseByDate;
};
//---------------------------------------------------------------------------

#endif


