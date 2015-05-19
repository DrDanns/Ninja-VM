/*
 * File:	njvm_debug.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	14.01.2015
 * Describtion:	Header-File for njvm_debug.c
 */
#ifndef NJVM_DEBUG
#define NJVM_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "njvm_memory.h"
#include "njvm_main.h"
#include "njvm.h"

void debugMenu(unsigned int program_memory[], int pos);
int debugPC(unsigned int *program_memory[],int *pos);
void printAllInstructions(unsigned int* program_memory)
void printStack(void);
void printSDA(void);
void printInstruction(unsigned int *instruction);


#endif /*NJVM_DEBUG*/
