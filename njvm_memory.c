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
int stackPointer;
int framePointer;
int SDASize;

void allocateSDA(int sdaSize)
{
  /*TODO: SDA Size lässt sich nicht errechnen*/
    printf("sizeof(StaticDataArea) sollte = %d \n", (sdaSize * sizeof(int)));
    StaticDataArea = (int*) malloc (sdaSize * sizeof(int));
    printf("sizeof(int) : %d\n", sizeof(int));
    printf("sizeof(sdaSize) : %d\n", sdaSize);
    printf("sizeof(StaticDataArea) ist : %d\n", sizeof(StaticDataArea));
    if (StaticDataArea == NULL)
      fputs("Error: cannot allocate memory for the Static Data Area.\n", stderr);
    SDASize = sdaSize;
    printf("sda size globale variable: %d\n", SDASize);
}
