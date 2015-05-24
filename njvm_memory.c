/*
 * File:	njvm_memory.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	includes all variables and functions for simulating
 * the Stack and the Static Data Area
 */

#include "njvm_memory.h"

int STACK[STACKSIZE];  /* Stack Array */
int *StaticDataArea;    /* Static Data Area (Array) */
int SDASize;          /* Size of the SDA. Calculatet from the Input-File */
int stackPointer;
int framePointer;
int retRegister;    /* Return Value */




void allocateSDA(int sdaSize)
{
    StaticDataArea = (int*) malloc (sdaSize * sizeof(int));
    SDASize = sdaSize;
    if (StaticDataArea == NULL)
      fputs("Error: cannot allocate memory for the Static Data Area.\n", stderr);
}
