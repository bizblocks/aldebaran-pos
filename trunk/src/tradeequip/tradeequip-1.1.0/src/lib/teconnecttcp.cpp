/****************************************************************************
** $Id: teconnecttcp.cpp,v 1.1 2006/07/12 09:12:32 leader Exp $
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
    Serial connect to trade equipment object.
   (c) V.Grazdankin, 1999-2005
*/
#ifndef TECONNECTTCP_CPP
#define TECONNECTTCP_CPP
#include "teconnecttcp.h"
#include <stdarg.h>

/*!
    \class TEConnectTCP teconnecttcp.h
    \brief The TEConnectTCP is TCP/IP connection class to connect with trade equipment.

    trade equipment TCP/IP connection object.
    Object have internal text command interpreter
    that give access to object functions.
    \param cmd (in) command text. Command format: <function> '(' <parm1> ',' <parm2> ',' ... <parmN> ')'
    \return - command execution result.
*/


/*!
 * Serial connection object fot trade equipment object.
 * Object have internal text command interpreter
 * that give access to object functions.
 * \param cmd (in) command text. Command format: <function> '(' <parm1> ',' <parm2> ',' ... <parmN> ')'
 * \return - command execution result.
 */
TEConnectTCP::TEConnectTCP( int pn ) : TEConnect( pn )
{
}

/*!
*/
TEConnectTCP::~TEConnectTCP()
{
}



#endif // TECONNECTSERIAL_CPP
