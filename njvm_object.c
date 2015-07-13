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
	StackSlot *result;

	result = (StackSlot*)malloc(sizeof(StackSlot));
	if(result == NULL) {
		fatalError("cannot allocate memory in newStackSlot.\n");
	}

	result->isObjRef = TRUE;
	result->u.objRef = objRef;
	return result;
}

StackSlot *newObjRef(int value) {
	StackSlot *result;
	bigFromInt(value);

	result = (StackSlot *)malloc(sizeof(StackSlot));
	if(result == NULL) {
		fatalError("cannot allocate memory in newObjRef.\n");
	}

	result->isObjRef = TRUE;
	result->u.objRef = bip.res;

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
