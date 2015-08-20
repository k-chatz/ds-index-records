/***********************************************************************
implementation file	: TSDDA.h
Purpose				: DDA Item Type
***********************************************************************/

#ifndef __TSDDA__
#define __TSDDA__

#include <stdio.h>

#include "IT_Finder.h"

typedef struct KeyIndex{
        keyType key;
        int arrayIndex;
} TStoixeiouDDA;

int TSDDA_setValue (TStoixeiouDDA *target, TStoixeiouDDA source);
int TSDDA_setKey(keyType * key, keyType Val);
int TSDDA_setIndex(int * index, int Val);

void TSDDA_writeValue(FILE * out, TStoixeiouDDA data);

/* basikes sygkriseis gia xrhsh sthn eisagcgh-diagarfh-anazhthsh se DDA */
int TSDDA_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_mikrotero(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_megalytero(TStoixeiouDDA, TStoixeiouDDA);

/* symplhrvmatikes sygkriseis */
int TSDDA_mikrotero_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_megalytero_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_diaforo(TStoixeiouDDA, TStoixeiouDDA);
#endif