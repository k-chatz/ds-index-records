/***********************************************************************
implementation file	: finder.c
Author				: <Costas Chatzopoulos -1115201300202- 22/05/2015>
Purpose				: Client interface from 'finder'.
***********************************************************************/

#include <assert.h>
#include "Finder.h"
#include "TSDDA.h"

#define Simple 1 /* 0 for AVL - any Evr integer for Simple  */

#if (Simple)
#include "BST/ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
#include "AVL/ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif

/*Finder node*/
struct finder{
	IT_Finder * data;		/* array of size maxSize */
	int index;				/* index of first available element in array */
	typos_deikti treeRoot;	/* Root of DDA */
} finder;

/*Private functions*/

int _recAccess(finderPtr f, typos_deikti root, FILE * out){

	static int rec = 0;
#if (Simple)
	if (!Tree_keno(root)){
		TStoixeiouDDA x;
		_recAccess(f, Tree_apaidi(root), out);
		Tree_periexomeno(root, &x);
		rec++;
		//printf("[%d]",rec);
		ITF_writeValue(out, f->data[x.arrayIndex]);
		_recAccess(f, Tree_dpaidi(root), out);
#else   
	if (!AVLTree_keno(root)){
		TStoixeiouDDA x;
		_recAccess(f, AVLTree_apaidi(root), out);
		AVLTree_periexomeno(root, &x);
		rec++;
		//printf("[%d]",rec);
		ITF_writeValue(out, f->data[x.arrayIndex]);
		_recAccess(f, AVLTree_dpaidi(root), out);
#endif
	}
	return rec;
}

/*Public functions*/

finderPtr fConstruct(int maxSize){
	if (maxSize > 0){
		finderPtr f = (finderPtr)malloc(sizeof(finder));
		assert(f != NULL);
		if (f != NULL){
			f->data = (IT_Finder *)malloc(sizeof(IT_Finder)* maxSize);
			assert(f->data != NULL);
			f->index = 0;
#if(Simple)
			printf("-Use simple BST\n");
			Tree_dimiourgia(&(f->treeRoot));
#else
			printf("-Use AVL BST\n");
			AVLTree_dimiourgia(&(f->treeRoot));
#endif
		}
		return f;
	}
	return NULL;
}

int fInsert(finderPtr f, IT_Finder Data){
	int error = 0;
	if (f != NULL){
		TStoixeiouDDA x;
		TSDDA_setKey(&(x.key), Data.ICAO);
		TSDDA_setIndex(&(x.arrayIndex), f->index);
		//TSDDA_writeValue(stdout, x);
#if (Simple)
		Tree_eisagogi(&(f->treeRoot), x, &error);
#else
		int top;
		AVLTree_eisagogi(&(f->treeRoot), x, &top, &error);
#endif
		if (!error){
			ITF_setValue(&(f->data[f->index]), Data);
			//ITF_writeValue(stdout, f->data[f->index]);
			f->index++;
		}
		return error;
	}
	return 1;
}

int fSearch(finderPtr f, keyType key, int * found){
	int error = 0;
	TStoixeiouDDA item;
	typos_deikti target;

	error = TSDDA_setKey(&(item.key), key);
	if (!error){
#if (Simple)
		Tree_anazitisi(f->treeRoot, item, &target, found);
		Tree_periexomeno(target, &item);

#else
		AVLTree_anazitisi(f->treeRoot, item, &target, found);
		AVLTree_periexomeno(target, &item);
#endif
		if (*found){
			*found = item.arrayIndex;
		}

		return 0;
	}
	return error;
}

int fPrintAll(finderPtr f, FILE * out, int * counter){
	if (f != NULL){
		*counter = _recAccess(f, f->treeRoot, out);
		return 0;
	}
	else
		return 1;
}

int fDestruct(finderPtr * f){
	assert(f != NULL);
	if (*f != NULL){
		int i;
#if(Simple)
		Tree_katastrofi(&((*f)->treeRoot));
#else
		AVLTree_katastrofi(&((*f)->treeRoot));
#endif
		for (i = 0; i < (*f)->index; i++){
			//ITF_writeValue(stdout, (*f)->data[i]);
			ITF_destroy(&((*f)->data[i]));
		}
		free((*f)->data);
		(*f)->index = 0;
		free(*f);
		*f = NULL;
	}
	return 0;
}
