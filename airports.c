/***********************************************************************
implementation file	: airports.c
Author				: <Costas Chatzopoulos -1115201300202- 21/05/2015>
Purpose				: Client interface from 'finder'.
***********************************************************************/
#include <stdio.h>
#include <assert.h>		/*For checks*/
#include <math.h>		/*For pow at the end of the program.*/
#include "IT_Finder.h"
#include "Finder.h"

#define _MaxRecords_ 5000

#define OS 1 /*0 For linux, 1 for Windows*/

#if (OS)
#include <windows.h>
#else 
#include <sys/time.h>			/* for gettimeofday() */
#endif

double elapsedTime = 0.0;

#define F1 "Data Files/ICAO_Random_Input-Windows.txt"
#define F2 "Data Files/ICAO_Sorted_Input-Windows.txt"
#define F3 "Data Files/ICAO_FOUND_1.txt"
#define F4 "Data Files/AIRPORTS_1.txt"
#define F5 "Data Files/ICAO_SEARCH-Windows.txt"
#define F6 "Data Files/ICAO_FOUND_2.txt"
#define F7 "Data Files/AIRPORTS_2.txt"

void importRecords(finderPtr finder, FILE * in){
	printf("--Import records from %s..\n", (in == stdin) ? "stdin" : "file");

	int error = 0, rec = 0, recPos = 0;

#if (OS)
	LARGE_INTEGER frequency;		/* ticks per second */
	LARGE_INTEGER t1, t2;			/* ticks */

	/* get ticks per second */
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&t1); /*Start timer*/
#else
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL); /*Start timer */
#endif

	while (!feof(in) && rec < _MaxRecords_){

		/*Create a temporary record set type for save each data of the records*/
		IT_Finder dataSet = ITF_create();

		if (ITF_readValue(in, &dataSet)){
			rec++;
			if (fInsert(finder, dataSet)){
				printf("--Not imported dublicate record with key field: '%s'\n", dataSet.ICAO);
				//ITF_writeValue(stdout, dataSet);
			}
			ITF_destroy(&dataSet);
			switch (rec){
			case 511:
#if (OS)
				QueryPerformanceCounter(&t2); /*Stop timer */
#else
				gettimeofday(&t2, NULL); /* stop timer */
#endif
				recPos = rec;
				break;
			case 1023:
#if (OS)
				QueryPerformanceCounter(&t2); /* stop timer */
#else
				gettimeofday(&t2, NULL); /* stop timer */
#endif
				recPos = rec;
				break;
			case 2047:
#if (OS)
				QueryPerformanceCounter(&t2); /* stop timer */
#else
				gettimeofday(&t2, NULL); /* stop timer */
#endif
				recPos = rec;
				break;
			case 4095:
#if (OS)
				QueryPerformanceCounter(&t2); /* stop timer */
#else
				gettimeofday(&t2, NULL); /* stop timer */
#endif
				recPos = rec;
				break;
			default:
				recPos = 0;
			}
			if (recPos){
#if (OS)
				elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
#else
				/* compute the elapsed time in millisec */
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
#endif
				printf("--Record %d, elapsed time: %g msec\n", recPos, elapsedTime);
			}
		}
	}

#if (OS)
	QueryPerformanceCounter(&t2); /* stop timer */
	/* compute the elapsed time in millisec */
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
#else
	gettimeofday(&t2, NULL); /* stop timer */
	/* compute the elapsed time in millisec */
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
#endif
	if (rec)
		printf("--Average time for one record import: %g msec\n", elapsedTime / rec);
	printf("--Imported records: %d with elapsed time: %g msec\n", rec, elapsedTime);
}

void findRecords(finderPtr finder, FILE * in, FILE * out){
	printf("--Search records from %s..\n", (in == stdin) ? "stdin" : "file");
	int error = 0, found = 0, i = 0, j = 0;

	IT_Finder dataSet = ITF_create();

#if (OS)
	LARGE_INTEGER frequency;		/* ticks per second */
	LARGE_INTEGER t1, t2;			/* ticks */

	/* get ticks per second */
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&t1); /*Start timer*/
#else
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL); /*Start timer */
#endif

	while (!feof(in)){
		if (ITF_readValue(in, &dataSet)){
			error = fSearch(finder, dataSet.ICAO, &found);
			if (!error){
				if (found){
					if (out != NULL)
						ITF_writeValue(out, dataSet);
					i++;
				}
				else
					j++;
			}
			else
				fprintf(stderr, "--Error: fSearch\n");
		}
	}

#if (OS)
	/*Full elapsed time*/
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
#else
	gettimeofday(&t2, NULL); /* stop timer */
	/* compute the elapsed time in millisec */
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
#endif

	if (i || j)
		printf("--Average time for one record search: %g msec\n", (elapsedTime / (i + j)));
	printf("--Found %d of %d keys (%d Not found) in %g msec\n", i, i + j, j, elapsedTime);
}

void sortRecords(finderPtr finder, FILE * out){
	int error = 0;
	printf("--Sort records from finder and puts in %s..\n", (out == stdin) ? "stdin" : "file");
	int rec = 0;

#if (OS)
	LARGE_INTEGER frequency;		/* ticks per second */
	LARGE_INTEGER t1, t2;			/* ticks */

	/* get ticks per second */
	QueryPerformanceFrequency(&frequency);
	
	QueryPerformanceCounter(&t1); /*Start timer*/
#else
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL); /*Start timer */
#endif

	/*Print all sorted*/
	error = fPrintAll(finder, out, &rec);
	if (error)
		fprintf(stderr, "--Error: fPrintAll\n");

#if (OS)
	/*Full elapsed time*/
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
#else
	gettimeofday(&t2, NULL); /* stop timer */
	/* compute the elapsed time in millisec */
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
#endif
	printf("--Sorted records %d, elapsed time: %g msec\n", rec, elapsedTime);
}

int main(int argc, char * argv[]){

#if (OS)
	LARGE_INTEGER frequency;		/* ticks per second */
	LARGE_INTEGER t1, t2;			/* ticks */

	/* get ticks per second */
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&t1); /*Start timer*/
#else
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL); /*Start timer */
#endif

	FILE *in, *out;
	int i, found = 0, error = 0, rec = 0;

	for (i = 0; i < 2; i++){

		/*Question 1)*/
		printf("\nQuestion 1)\n");
		printf("-Create finder..\n");
		finderPtr f1 = fConstruct(_MaxRecords_);
		printf("\n");

		/*Question 2)*/
		printf("\nQuestion 2)\n");
		printf("-Open file %s for read..\n", (i == 0) ? F1 : F2);
		in = fopen((i == 0) ? F1 : F2, "r");
		if (in != NULL){
			/*Import records*/
			importRecords(f1, in);
			printf("-Close file %s..\n", (i == 0) ? F1 : F2);
			fclose(in);
		}
		else
			perror("-Error while opening the file");
		printf("\n");


		/*Question 3)*/
		printf("\nQuestion 3)\n");
		printf("-Open file %s for read..\n", F5);
		in = fopen(F5, "r");
		if (in != NULL){
			printf("-Open file %s for write..\n", (i == 0) ? F3 : F6);
			out = fopen((i == 0) ? F3 : F6, "w");
			if (out != NULL){
				/*Find records*/
				findRecords(f1, in, out);
				printf("-Close file %s..\n", (i == 0) ? F3 : F6);
				fclose(out);
			}
			else
				perror("-Error while opening the file");
			printf("-Close file %s..\n", F5);
			fclose(in);
		}
		else
			perror("-Error while opening the file");
		printf("\n");


		/*Question 4)*/
		printf("\nQuestion 4)\n");
		printf("-Open file %s for read & write..\n", (i == 0) ? F3 : F6);
		in = fopen((i == 0) ? F3 : F6, "r+");
		if (in != NULL){
			/*Find records*/
			findRecords(f1, in, NULL);
			printf("-Close file %s..\n", (i == 0) ? F3 : F6);
			fclose(in);
		}
		else
			perror("-Error while opening the file");
		printf("\n");


		/*Question 5)*/
		printf("\nQuestion 5)\n");
		printf("-Open file %s for write..\n", (i == 0) ? F4 : F7);
		out = fopen((i == 0) ? F4 : F7, "w");
		if (out != NULL){
			sortRecords(f1, out);
			printf("-Close file %s..\n", (i == 0) ? F4 : F7);
			fclose(out);
		}
		else
			perror("-Error while opening the file");
		printf("\n");


		/*Question 6)*/
		printf("\nQuestion 6)\n");
		printf("-Destroy finder..\n");
		fDestruct(&f1);

		printf("__________________________________________________________\n");
	}

#if (OS)
	QueryPerformanceCounter(&t2); /* stop timer */
	/* compute the elapsed time in millisec */
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
#else
	gettimeofday(&t2, NULL); /* stop timer */
	/* compute the elapsed time in millisec */
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
#endif
	printf("To complete the process required %4.2f second\n\n", elapsedTime * pow(10,-3));

	printf("Press enter to exit..\n");
	getchar();
	return 0;
}
