/*
 * File:	njvm_memory.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	includes the variables and functions for simulating the stack
 */

#include "njvm_memory.h"

void allocateSDA(int size)
{
    StaticDataArea = (int*) malloc (size * sizeof(int));
}
