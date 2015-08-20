/***********************************************************************
implementation file	: IT_Finder.c
Author				: <Costas Chatzopoulos -1115201300202- 21/05/2015>
Purpose				: Item Type for Finder
***********************************************************************/

#include "IT_Finder.h"
#include <string.h>

/*fields*/
#define _ICAO_ 0
#define _IATA_ 1
#define _City_ 2
#define _Name_ 3
#define _Country_ 4

IT_Finder ITF_create(){
	IT_Finder dataSet;
	strcpy(dataSet.ICAO, "");
	strcpy(dataSet.IATA, "");
	dataSet.City = NULL;
	dataSet.Name = NULL;
	dataSet.Country = NULL;
	return dataSet;
}

void ITF_destroy(IT_Finder * target){
	if ((*target).City != NULL){
		free((*target).City);
		(*target).City = NULL;
	}

	if ((*target).Name != NULL){
		free((*target).Name);
		(*target).Name = NULL;
	}

	if ((*target).Country != NULL){
		free((*target).Country);
		(*target).Country = NULL;
	}
}

int ITF_setValue(IT_Finder * target, IT_Finder source){
	strcpy(target->ICAO, source.ICAO);

	strcpy(target->IATA, source.IATA);

	if (source.City != NULL){
		target->City = malloc(sizeof(char)* strlen(source.City) + 1);
		strcpy(target->City, source.City);
	}

	if (source.Name != NULL){
		target->Name = malloc(sizeof(char)* strlen(source.Name) + 1);
		strcpy(target->Name, source.Name);
	}

	if (source.Country != NULL){
		target->Country = malloc(sizeof(char)* strlen(source.Country) + 1);
		strcpy(target->Country, source.Country);
	}

	return 1;
}

int ITF_readValue(FILE * from, IT_Finder * item){
	char buffer[_BufferSize_];
	char * split;
	if (fgets(buffer, _BufferSize_, from) != NULL){
		int field = 0;
		split = strtok(buffer, "%\n");
		while (split != NULL && field < 5){
			switch (field){
			case _ICAO_:
				strcpy(item->ICAO, split);
				break;
			case _IATA_:
				strcpy(item->IATA, split);
				break;
			case _City_:
				item->City = malloc(sizeof(char)*strlen(split) + 1);
				strcpy(item->City, split);
				break;
			case _Name_:
				item->Name = malloc(sizeof(char)*strlen(split) + 1);
				strcpy(item->Name, split);
				break;
			case _Country_:
				item->Country = malloc(sizeof(char)*strlen(split) + 1);
				strcpy(item->Country, split);
				break;
			}
			split = strtok(NULL, "%\n");
			field++;
		}
		return 1;
	}
	else
		return 0;
}

int ITF_writeValue(FILE * to, IT_Finder item){
	int ICAO, IATA, City, Name, Country;

	ICAO = (strcmp(item.ICAO, "") == 0);
	IATA = (strcmp(item.IATA, "") == 0);
	City = (item.City == NULL);
	Name = (item.Name == NULL);
	Country = (item.Country == NULL);

	return fprintf(to, (to == stdout) ? "[%s] [%s] [%s] [%s] [%s]\n" :			/*For debuging*/
		(IATA && City && Name && Country) ? "%s\n" : "%s%%%s%%%s%%%s%%%s%%\n",	/*For Search or PrintAll*/
		ICAO ? "NULL" : item.ICAO, IATA ? "NULL" : item.IATA, City ? "NULL" : item.City,
		Name ? "NULL" : item.Name, Country ? "NULL" : item.Country);
}