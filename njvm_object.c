/*
 * File:   njvm_object.c
 * Author: Stanislav Hannes, 5000458
 * Date:	12.06.2015
 * Describtion: Functions and Typedef for Objects
 */

#include <stdio.h>
#include <stdlib.h>

#include "njvm_object.h"

StackSlot *newStackSlot(ObjRef objRef){
	return newObjRef((int)(int *)objRef->data);
}

StackSlot *newObjRef(int value) {
	StackSlot *result;
	ObjRef objRef;

	objRef = *(ObjRef *)malloc(sizeof(unsigned int) + sizeof(int));
	if(objRef == NULL) {
		fputs("Error: cannot allocate memory for obiRef.\n", stderr);
	}

	result = (StackSlot *)malloc(sizeof(StackSlot));
	if(result == NULL) {
		fputs("Error: cannot allocate newObjRef memory.\n", stderr);
	}

	objRef->size = sizeof(int);
	*(int *)objRef->data = value;
	result->isObjRef = TRUE;
	result->u.objRef = objRef;

	return result;
}

StackSlot *newObjNum(int value) {
	StackSlot *result;
	result = (StackSlot *)malloc(sizeof(StackSlot));
	if(result == NULL) {
		fputs("Error: cannot allocate newObjNum memory.\n", stderr);
	}
	result->isObjRef = FALSE;
	result->u.number = value;
	return result;
}