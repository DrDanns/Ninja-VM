/*
 * File:	njvm_memory.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Header-File for njvm_memory.c
 */
#ifndef NJVM_MEMORY
#define NJVM_MEMORY

#include <stdlib.h>
#include "njvm.h"

int STACK[STACKSIZE];
int *StaticDataArea;
int stackPointer;
int framePointer;

void allocateSDA(int sdaSize);

#endif /*NJVM_MEMORY*/
