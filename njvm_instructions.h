/*
 * File:	njvm_instructions.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Description:	Header-File for njvm_instructions.c
 */
#ifndef NJVM_INSTRUCTIONS
#define NJVM_INSTRUCTIONS

#include "njvm_memory.h"
#include "njvm_object.h"



void push(StackSlot *obj);
StackSlot pop(void);
void rdint(void);
void wrint(void);
void rdchr(void);
void wrchr(void);
void pushg(int pos);
void popg(int pos);
void asf(int places);
void rsf (void);
void pushl(int pos);
void popl (int pos);
void calc (int cmd);
int jmp(int pos);
int brf (int pos, int progCount);
int brt (int pos, int progCount);
int call (int pos, int progCount);
int ret (void);
void drop(int entries);
void pushr(void);
void popr(void);
void dup(void);

#endif /*NJVM_INSTRUCTIONS*/
