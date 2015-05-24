/*
 * File:	njvm_memory.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	includes the variables and functions for simulating
 * the Stack and the Static Data Area
 */

#include "njvm_memory.h"

int STACK[STACKSIZE];
int *StaticDataArea;
int SDASize;
int stackPointer;
int framePointer;


void allocateSDA(int sdaSize)
{
    StaticDataArea = (int*) malloc (sdaSize * sizeof(int));
    SDASize = sdaSize;
    if (StaticDataArea == NULL)
      fputs("Error: cannot allocate memory for the Static Data Area.\n", stderr);
}
