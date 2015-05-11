/*
 * File:	njvm_filehandler.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Header-File for njvm_filehandler.c
 */

#ifndef NJVM_FILEHANDLER
#define NJVM_FILEHANDLER

#include "njvm_memory.h"


FILE* openFile(char *path);
unsigned int* readFile(FILE* file);

#endif /*NJVM_FILEHANDLER*/