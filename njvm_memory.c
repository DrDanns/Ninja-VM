/*
 * File:	njvm_memory.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	includes all variables and functions for simulating
 * the Stack and the Static Data Area
 */

#include "njvm_memory.h"

StackSlot* stack[STACKSIZE];  /* Stack Array */
int stackByteSize = STACKSIZE * sizeof(StackSlot);
ObjRef *staticData;    /* Static Data Area (Array) */
int sdaSize;          /* Size of the SDA. Calculatet from the Input-File */
int stackPointer;
int framePointer;
ObjRef *retRegister;    /* Return Value */

void allocateSDA(int sdaSize)
{
    staticData = (ObjRef*) malloc (sdaSize * sizeof(ObjRef));
    sdaSize = sdaSize;
    if (staticData == NULL)
      fputs("Error: cannot allocate memory for the Static Data Area.\n", stderr);
}
