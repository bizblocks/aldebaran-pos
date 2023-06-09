/****************************************************************************
**
** Main file of Aldebaran Applicaion
**
** Created : 20071122
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
#include "engine.h"

int main (int argc, char ** argv)
{
	alEngine engine(argc, argv);
	return engine.start();
}
