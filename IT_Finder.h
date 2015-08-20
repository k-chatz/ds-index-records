/***********************************************************************
implementation file	: IT_Finder.h
Author				: <Costas Chatzopoulos -1115201300202- 21/05/2015>
Purpose				: Finder Item Type
***********************************************************************/

#ifndef __ITFINDER__
#define __ITFINDER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*File fields positions*/

#define _BufferSize_ 200

typedef char keyType[5];

typedef struct data{
	keyType ICAO;
	char IATA[4];
	char * City;
	char * Name;
	char * Country;
} IT_Finder;

IT_Finder ITF_create();
void ITF_destroy(IT_Finder * target);
int ITF_setValue(IT_Finder * target, IT_Finder source);
int ITF_readValue(FILE * from,  IT_Finder * item);
int ITF_writeValue(FILE * to, IT_Finder item);

#endif
