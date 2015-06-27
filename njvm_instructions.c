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
      exit(EXIT_FAILURE);
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
    exit(EXIT_FAILURE);
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
    exit(EXIT_FAILURE);
  }
  staticData[pos]=slot->u.objRef;
}

void asf(int places)
{
  int i;
  push(newObjNum(framePointer));
  if((stackPointer + places)*sizeof(StackSlot) <= stackByteSize) {
        framePointer = stackPointer;
		    for(i = framePointer; i < framePointer + places; i++) {
			         push(newObjNum(0));
		    }

	} else {
    fputs("Error: StackOverFlow.\n", stderr);
    exit(EXIT_FAILURE);
	}

}

void rsf (void)
{
    StackSlot *slot;
    stackPointer=framePointer;
    slot = pop();
    if(slot->isObjRef == TRUE){
      fputs("Error: cannot rsf; it's an ObjRef.\n", stderr);
      exit(EXIT_FAILURE);
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
    exit(EXIT_FAILURE);
  }

  n2 = *(int *)ss2->u.objRef->data;
  n1 = *(int *)ss1->u.objRef->data;

  switch(cmd){
    case ADD:
              push(newObjRef(n1+n2));
              break;
    case SUB:
              push(newObjRef(n1-n2));
              break;
    case MUL:
              push(newObjRef(n1*n2));
              break;
    case DIV:
              push(newObjRef(n1/n2));
              break;
    case MOD:
              push(newObjRef(n1%n2));
              break;
    case EQ:
              if(n1==n2){
                push(newObjRef(TRUE));
              } else {
                push(newObjRef(FALSE));
              }
              break;
    case NE:
              if(n1!=n2){
                push(newObjRef(TRUE));
              } else {
                push(newObjRef(FALSE));
              }
              break;
    case LT:
              if(n1<n2){
                push(newObjRef(TRUE));
              } else {
                push(newObjRef(FALSE));
              }
              break;
    case LE:
              if(n1<=n2){
                push(newObjRef(TRUE));
              } else {
                push(newObjRef(FALSE));
              }
              break;
    case GT:
              if(n1>n2){
                push(newObjRef(TRUE));
              } else {
                push(newObjRef(FALSE));
              }
              break;
    case GE:
              if(n1>=n2){
                push(newObjRef(TRUE));
              } else {
                push(newObjRef(FALSE));
              }
              break;
  }
}

int jmp(int pos){
  return pos;
}

int brf (int pos, int progCount){
  StackSlot *slot = pop();
  if(slot->isObjRef == FALSE){
    fputs("Error: cannot brf; top of stack isn't an ObjRef.\n", stderr);
    exit(EXIT_FAILURE);
  }
  if (*(int *)slot->u.objRef->data == FALSE){
    return pos;
  }
  else return ++progCount;
}

int brt (int pos, int progCount){
  StackSlot *slot = pop();
  if(slot->isObjRef == FALSE){
    fputs("Error: cannot brt; top of stack is an ObjRef.\n", stderr);
    exit(EXIT_FAILURE);
  }
  if (*(int *)slot->u.objRef->data == TRUE){
    return pos;
  }
  else return ++progCount;
}

int call(int pos, int progCount){
  push(newObjNum(++progCount));
  return pos;
}

int ret(void){
  StackSlot *slot = pop();
  if(slot->isObjRef == TRUE){
    fputs("Error: cannot ret; top of stack is an ObjRef.\n", stderr);
    exit(EXIT_FAILURE);
  }
  return slot->u.number;
}

void drop(int entries){
  stackPointer = stackPointer - entries;
}

void pushr(void) {
  push(newObjRef(retRegister));
}

void popr(void) {
	retRegister = *(int *)pop()->u.objRef->data;
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
