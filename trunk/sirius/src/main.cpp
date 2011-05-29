/****************************************************************************
This file is part of Sirius Embedded Application written by Artel-GNU.
Author: Anton Sokolov
Created: 15.01.2008
See LICENSE.GPL for more information
Copyleft
*****************************************************************************/
#include <stdio.h>
#include "sirius.h"


/*
  The program starts here. It parses the command line and builds a message
  string to be displayed by the Hello widget.
*/

int main( int argc, char ** argv)
{
	sirius * aSirius = new sirius(argc, argv);
	int res = aSirius->init();
	delete aSirius;
	printf("result code %i\n", res);
	return res;
}
