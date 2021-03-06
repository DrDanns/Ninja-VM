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
#include "njvm_object.h"
#include "bigint.h"

void debugMenu(unsigned int program_memory[], int pos);
ObjRef getInstance(int pos, ObjRef objref);
int run(unsigned int program_memory[],int pos, int breakPoint);
void printStack(void);
void printSDA(void);
void printAllInstructions(unsigned int program_memory[]);
void printInstruction(unsigned int instruction);


#endif /*NJVM_DEBUG*/
