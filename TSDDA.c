/***********************************************************************
implementation file	: TSDDA.c
Author				: <Costas Chatzopoulos -1115201300202- 21/05/2015>
Purpose				: Item Type for DDA
***********************************************************************/

#include <string.h>

#include "TSDDA.h"

int success = 0;

int TSDDA_setValue(TStoixeiouDDA * target, TStoixeiouDDA source){
	target->arrayIndex = source.arrayIndex;
	strcpy(target->key, source.key);
	return 0;
}

int TSDDA_setKey(keyType * key, keyType Val){
	return strcpy(*key, Val) == NULL;
}

int TSDDA_setIndex(int * index, int Val){
	success = *index = Val;
	return !success;
}

void TSDDA_writeValue(FILE * out, TStoixeiouDDA data){
	fprintf(out, "[%d %s]\t", data.arrayIndex, data.key);
}

int TSDDA_iso(TStoixeiouDDA s1, TStoixeiouDDA s2){
	return strcmp(s1.key, s2.key) == 0;
}

int TSDDA_mikrotero(TStoixeiouDDA s1, TStoixeiouDDA s2){
	return strcmp(s1.key, s2.key) < 0;
}

int TSDDA_megalytero(TStoixeiouDDA s1, TStoixeiouDDA s2){
	return strcmp(s1.key, s2.key) > 0;
}

int TSDDA_mikrotero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return TSDDA_mikrotero(s1, s2) || TSDDA_iso(s1, s2);
}

int TSDDA_megalytero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return TSDDA_megalytero(s1, s2) || TSDDA_iso(s1, s2);
}

int TSDDA_diaforo(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return !TSDDA_iso(s1, s2);
}