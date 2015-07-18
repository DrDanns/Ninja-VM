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
		fatalError("cannot allocate memory for a newStackSlot.\n");
	}

	result->isObjRef = TRUE;
	result->u.objRef = objRef;
	return result;
}

StackSlot *newObjRef(int value) {
	bigFromInt(value);
  return newStackSlot(bip.res);
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

ObjRef newEmptyObjRef(){
    ObjRef objRef = NULL;
    return objRef;
}

StackSlot *newRecordsObject(int size){
    ObjRef record;
		ObjRef *objRef;
    int i;

    record = (ObjRef)malloc(sizeof(unsigned int) + (size * sizeof(objRef)));
    record->size = size | MSB;

    for(i = 0;i < size;i++) {
		*(GET_REFS(record)+i) = newEmptyObjRef();
	}

    return newStackSlot(record);
}
