/***********************************************************************
implementation file	: Finder.h
Author				: <Costas Chatzopoulos -1115201300202- 21/05/2015>
Purpose				: Client interface from 'finder'.
***********************************************************************/

#ifndef __Finder__
#define __Finder__

#include <stdlib.h>
#include <stdio.h>
#include "IT_Finder.h"

typedef struct finder * finderPtr;

finderPtr fConstruct(int maxSize);
int fDestruct(finderPtr * f);
int fInsert(finderPtr f, IT_Finder Data);
int fSearch(finderPtr f, keyType key, int * found);
int fPrintAll(finderPtr f, FILE * out, int * counter);
int printData(finderPtr f);

#endif