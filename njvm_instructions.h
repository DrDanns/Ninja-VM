/* 
 * File:	njvm_instructions.h
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Description:	Header-File for njvm_instructions.c
 */
#ifndef NJVM_INSTRUCTIONS
#define NJVM_INSTRUCTIONS

#include "njvm_memory.h"


void push(int c);
int pop(void);
void add(void);
void sub(void);
void mul(void);
void division(void);
void mod(void); 
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

#endif /*NJVM_INSTRUCTIONS*/
