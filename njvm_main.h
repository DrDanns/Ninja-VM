/*
 * File:	njvm_main.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Header-File for njvm_main.c
 */
#ifndef NJVM_MAIN
#define NJVM_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "njvm.h"
#include "njvm_filehandler.h"
#include "njvm_instructions.h"
#include "njvm_debug.h"

int main (int argc, char *argv[]);
void njvmMenu(int argc,  char** argv);
void pc (unsigned int program_memory[]);
int exec(int instruction, int progCount);
void end(void);

#endif /*NJVM_MAIN*/
