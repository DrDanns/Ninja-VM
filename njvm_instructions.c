/*
 * File:	njvm_instructions.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Operation-Functions / instructions for the stack
 */

#include <stdio.h>
#include <stdlib.h>

#include "njvm_instructions.h"


void push(StackSlot *obj) {
  if(stackPointer*sizeof(StackSlot) <= stackByteSize) {
        stack[stackPointer] = obj;
        stackPointer = stackPointer + 1;
  } else {
        fputs("Error: StackOverFlow.\n", stderr);
        exit(EXIT_FAILURE);
	}
}

StackSlot *pop(void)
{
    stackPointer =  stackPointer - 1;
    return stack[stackPointer];
}

void rdint(void)
{
    int i;
    scanf("%d", &i);
    push(newObjRef(i));
}

void wrint(void)
{
    StackSlot *slot = pop();
    if (slot->isObjRef == FALSE){
      fputs("Error: cannot wrint; it's not an ObjRef.\n", stderr);
    }
    printf("%d", *(int *)slot->u.objRef->data);
}

void rdchr(void)
{
    char c;
    scanf("%c",&c);
    push(newObjRef((int) c));
}

void wrchr(void)
{
  StackSlot *slot = pop();
  if (slot->isObjRef == FALSE){
    fputs("Error: cannot wrchr; it's not an ObjRef.\n", stderr);
  }
  printf("%c", *(int *)slot->u.objRef->data);
}

void pushg(int pos)
{
  push(newStackSlot(staticData[pos]));
}

void popg(int pos)
{
  StackSlot *slot = pop();
  if(slot->isObjRef == FALSE){
    fputs("Error: cannot popg; it's not an ObjRef.\n", stderr);
  }
  staticData[pos]=slot->u.objRef;
}

void asf(int places) /*TODO: überdenken*/
{
    push(newObjNum(framePointer));
    framePointer = stackPointer;
    stackPointer = stackPointer + places;
}

void rsf (void)
{
    StackSlot *slot = pop();
    stackPointer=framePointer;
      printf("rsf: %d",slot->isObjRef);
    if(slot->isObjRef == TRUE){
      fputs("Error: cannot rsf; it's an ObjRef.\n", stderr);
    }
    framePointer=slot->u.number;
}

void pushl(int pos)
{
    push(stack[framePointer + pos]);
}

void popl (int pos)
{
    stack[framePointer + pos] = pop();
}

void calc (int cmd){
  StackSlot *ss2 = pop();
  StackSlot *ss1 = pop();
  int n2;
  int n1;
  if (ss1->isObjRef == FALSE || ss2->isObjRef == FALSE){
    fputs("Error: cannot calculate; values are't ObjRef.\n", stderr);
  }

  n2 = (int)(int *)ss2->u.objRef->data;
  n1 = (int)(int *)ss1->u.objRef->data;

  switch(cmd){
    case ADD:
              n1 = n1 + n2;
              push(ss1);
              break;
    case SUB:
              n1 = n1 - n2;
              push(ss1);
              break;
    case MUL:
              n1 = n1 * n2;
              push(ss1);
              break;
    case DIV:
              n1 = n1 / n2;
              push(ss1);
              break;
    case MOD:
              n1 = n1 % n2;
              push(ss1);
              break;
    case EQ:
              if(n1==n2){
                n1 = TRUE;
                push(ss1);
              } else {
                n2 = FALSE;
                push(ss2);
              }
              break;
    case NE:
              if(n1!=n2){
                n1 = TRUE;
                push(ss1);
              } else {
                n2 = FALSE;
                push(ss2);
              }
    case LT:
              if(n1<n2){
              n1 = TRUE;
              push(ss1);
              } else {
                n2 = FALSE;
                push(ss2);
              }
              break;
    case LE:
              if(n1<=n2){
                n1 = TRUE;
                push(ss1);
              } else {
                n2 = FALSE;
                push(ss2);
              }
              break;
    case GT:
              if(n1>n2){
                n1 = TRUE;
                push(ss1);
              } else {
                n2 = FALSE;
                push(ss2);
              }
              break;
    case GE:
              if(n1>=n2){
                n1 = TRUE;
                push(ss1);
              } else {
                n2 = FALSE;
                push(ss2);
              }
              break;
  }
}

int jmp(int pos){
  return pos;
}

int brf (int pos, int progCount){
  StackSlot *slot = pop();
  if(slot->isObjRef == TRUE){
    fputs("Error: cannot brf; top of stack is a ObjRef.\n", stderr);
  }
  if (slot->u.number == FALSE){
    return pos;
  }
  else return ++progCount;
}

int brt (int pos, int progCount){
  StackSlot *slot = pop();
  if(slot->isObjRef == TRUE){
    fputs("Error: cannot brt; top of stack is a ObjRef.\n", stderr);
  }
  if (slot->u.number == TRUE){
    return pos;
  }
  else return ++progCount;
}

int call(int pos, int progCount){
  push(newObjRef(++progCount));
  return pos;
}

int ret(void){
  return (int)(int *)pop()->u.objRef->data;
}

void drop(int entries){
  stackPointer = stackPointer - entries;
}

void pushr(void) {
  push(newStackSlot(*retRegister));
}

void popr(void) {
	retRegister = &pop()->u.objRef;
}

void dup(void){
  StackSlot *slot = pop();
  push(slot);

  if(slot->isObjRef == TRUE){
    push(newStackSlot(slot->u.objRef));
  } else {
    push(newObjNum(slot->u.number));
  }

}
