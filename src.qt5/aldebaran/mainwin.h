/****************************************************************************
**
** UI part of Aldebaran Application
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
#ifndef MAINWIN_H
#define MAINWIN_H

#include <qmainwindow.h>
#include "engine.h"

class alEngine;
class alWHall;
class alOrderWindow;
class alArchiveWindow;
class alOrderRecord;
class QFrame;
class QWidget;
	
class alMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    alMainWindow(alEngine * engine);
    ~alMainWindow();
    alWHall * getHall() {return hall;}
    enum actions
    {
        XReport,
        ZReport,
        Paying,
        Payout,
        Archive,
        Equipment,
        Import,
        Export,
        Settings,
        AdvancedReport
    };
public slots:
    virtual void init();

    virtual void settings();

    virtual void rebuild();
    virtual void openOrder(ULLID orderId, int tableNum);
    virtual void openArchive();
    virtual alOrderRecord * currentOrder();
protected:
    virtual void showEvent(QShowEvent * e);
    void closeEvent(QCloseEvent * e);
    void createWidgets();
    void checkWidgets();
    void setWidgetGeometry(QWidget * w);
signals:
    void closed();
private:
    alEngine * fEngine;	
    alWHall * hall;
    alOrderWindow * orderWin;
    alArchiveWindow * arcWin;
    QWidget * currentWin;
    QFrame * serviceFrame;
};

#endif
