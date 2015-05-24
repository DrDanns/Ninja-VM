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

extern int STACK[STACKSIZE];
extern int *StaticDataArea;
extern int stackPointer;
extern int framePointer;
extern int SDASize;
extern int retRegister;


void allocateSDA(int sdaSize);

#endif /*NJVM_MEMORY*/
