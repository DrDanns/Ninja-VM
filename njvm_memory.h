/*
 * File:	njvm_memory.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Header-File for njvm_memory.c
 */
#ifndef NJVM_MEMORY
#define NJVM_MEMORY

#include <stdlib.h>
#include <stdio.h>
#include "njvm.h"
#include "njvm_memory.h"
#include "njvm_object.h"

extern StackSlot* stack[STACKSIZE];
extern int stackByteSize;
extern ObjRef *staticData;
extern int sdaSize;
extern int stackPointer;
extern int framePointer;
extern ObjRef *retRegister;

void allocateSDA(int sdaSize);

#endif /*NJVM_MEMORY*/
