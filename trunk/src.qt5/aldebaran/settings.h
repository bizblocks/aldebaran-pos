/****************************************************************************
**
** Framework for Aldebaran Application
**
** Created : 20070722
**
** Copyleft
** Author: Sokolov Anton (a.volokos on the gmail.com)
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
**
**********************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H

#include <qobject.h>
#include <qsettings.h>
#include "engine.h"

class alEngine;

class alSettings : public QObject
{
Q_OBJECT
public:
    alSettings(alEngine * e);
    ~alSettings();
public slots:
    virtual void init();
    virtual bool dbDialog();
    virtual bool dialog();	
    virtual QStringList dbSettings();
    virtual alValueList subSystemSettings(QString subSystem = QString::null);
    void addSubSystem(QString subs, QStringList k) { subSystems.append(subs); keys[subs] = k;}
    virtual void flush();
    QVariant parameter(QString sub, QString key);	
protected slots:
    virtual void flushqt();
    virtual void flushsql();	
private:
    alEngine * fEngine;
    QStringList dbParams;
    QMap<QString, alValueList> params;
    QStringList subSystems;
    QMap<QString, QStringList> keys;
};

#endif
