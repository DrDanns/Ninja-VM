/*
 * File:	njvm_main.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Header-File for njvm_main.c
 */
#ifndef NJVM_MAIN
#define NJVM_MAIN

#include "njvm.h"
#include "njvm_filehandler.h"
#include "njvm_instructions.h"

int main (int argc, char *argv[]);
void menu(int argc,  char** argv);
void pc (unsigned int program_memory[]);
void exec(int IR);
void printPM(unsigned int program_memory[]);
void end(void);

#endif /*NJVM_MAIN*/
