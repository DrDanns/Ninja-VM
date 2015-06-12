/*
 * File:	njvm_instructions.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Operation-Functions / instructions for the stack
 */

#include <stdio.h>
#include <stdlib.h>

#include "njvm_instructions.h"


void push(int c)
{
    STACK[stackPointer] = c;
    stackPointer = stackPointer + 1;
}

int pop(void)
{
    stackPointer =  stackPointer - 1;
    return STACK[stackPointer];
}

void add(void)
{
    push(pop() + pop());
}

void sub(void)
{
    int num = pop();
    push(pop() - num);
}

void mul(void)
{
    push(pop() * pop());
}

void division(void)
{
    int n2 = pop();
    int n1= pop();
    push(n1 / n2);
}

void mod(void)
{
    int n2 = pop();
    int n1= pop();
    push(n1 % n2);
}

void rdint(void)
{
    int i;
    scanf("%d", &i);
    push(i);
}

void wrint(void)
{
    printf("%d", (int) pop());
}

void rdchr(void)
{
    char c;
    scanf("%c",&c);
    push((int) c);
}

void wrchr(void)
{
    printf("%c", (char) pop());
}

void pushg(int pos)
{
    push(StaticDataArea[pos]);
}

void popg(int pos)
{
    StaticDataArea[pos]=pop();
}

void asf(int places)
{
    push(framePointer);
    framePointer = stackPointer;
    stackPointer = stackPointer + places;
}

void rsf (void)
{
    stackPointer=framePointer;
    framePointer=pop();
}

void pushl(int pos)
{
    push(STACK[framePointer + pos]);
}

void popl (int pos)
{
    STACK[framePointer + pos] = pop();
}

void compare (int compCMD){
  int n2 = pop();
  int n1= pop();

  switch(compCMD){
    case EQ:
        (n1==n2) ? push(TRUE) : push(FALSE);
	break;
    case NE:
        (n1!=n2) ? push(TRUE) : push(FALSE);
        break;
    case LT:
	(n1<n2) ? push(TRUE) : push(FALSE);
	break;
    case LE:
	(n1<=n2) ? push(TRUE) : push(FALSE);
	break;
    case GT:
	(n1>n2) ? push(TRUE) : push(FALSE);
	break;
    case GE:
	(n1>=n2) ? push(TRUE) : push(FALSE);
	break;
  }
}

int jmp(int pos){
  return pos;
}

int brf (int pos, int progCount){
  int top = pop();
  if (top == FALSE){
    return pos;
  }
  else return ++progCount;
}

int brt (int pos, int progCount){
  int top = pop();
  if (top == TRUE){
    return pos;
  }
  else return ++progCount;
}

int call(int pos, int progCount){
  push(++progCount);
  return pos;
}

int ret(void){
  return pop();
}

void drop(int entries){
  stackPointer = stackPointer - entries;
}

void pushr(void) {
	push(retRegister);
}

void popr(void) {
	retRegister = pop();
}

void dup(void){
  int value = pop();
  push(value);
  push(value);
}
