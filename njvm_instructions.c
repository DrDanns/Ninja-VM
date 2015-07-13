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

StackSlot *pop(void){
    stackPointer =  stackPointer - 1;
    return stack[stackPointer];
}

void rdint(void){
    bigRead(stdin);
    push(newStackSlot(bip.res));
}

void wrint(void){
    StackSlot *slot = pop();
    if (slot->isObjRef == FALSE){
      fatalError("cannot wrint; it's not an ObjRef.\n");
    }
    bip.op1 = slot->u.objRef;
    bigPrint(stdout);
}

void rdchr(void){
    char c;
    scanf("%c",&c);
    push(newObjRef((int) c));
}

void wrchr(void)
{
  StackSlot *slot = pop();
  if (slot->isObjRef == FALSE){
    fatalError("cannot wrchr; it's not an ObjRef.\n");
  }
  bip.op1 = slot->u.objRef;
  printf("%c",bigToInt());
}

void pushg(int pos)
{
  push(newStackSlot(staticData[pos]));
}

void popg(int pos)
{
  StackSlot *slot = pop();
  if(slot->isObjRef == FALSE){
    fatalError("cannot popg; it's not an ObjRef.\n");
  }
  staticData[pos]=slot->u.objRef;
}

void asf(int places){
  int i;
  push(newObjNum(framePointer));
  if((stackPointer + places)*sizeof(StackSlot) <= stackByteSize) {
        framePointer = stackPointer;
		    for(i = framePointer; i < framePointer + places; i++) {
			         push(newObjNum(0));
		    }

	} else {
      fatalError("StackOverflow");
	}
}

void rsf (void){
    StackSlot *slot;
    stackPointer=framePointer;
    slot = pop();
    if(slot->isObjRef == TRUE){
      fatalError("cannot rsf; it's an ObjRef.\n");
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
  int result;
  bip.op2 = pop()->u.objRef;
	bip.op1 = pop()->u.objRef;

  switch(cmd){
    case ADD:
              bigAdd();
              push(newStackSlot(bip.res));
              break;
    case SUB:
              bigSub();
              push(newStackSlot(bip.res));
              break;
    case MUL:
              bigMul();
              push(newStackSlot(bip.res));
              break;
    case DIV:
              bigDiv();
              push(newStackSlot(bip.res));
              break;
    case MOD:
              bigDiv();
              push(newStackSlot(bip.rem));
              break;
    case EQ:
              result = bigCmp();
        			if(result == 0) {
        				push(newObjRef(1));
        			} else {
        				push(newObjRef(0));
        			}
              break;
    case NE:
              result = bigCmp();
              if(result < 0 || result > 0) {
                push(newObjRef(1));
              } else {
                push(newObjRef(0));
              }
              break;
    case LT:
              result = bigCmp();
              if(result < 0) {
                push(newObjRef(1));
              } else {
                push(newObjRef(0));
              }
              break;
    case LE:
              result = bigCmp();
              if(result < 0 || result == 0) {
                push(newObjRef(1));
              } else {
                push(newObjRef(0));
              }
              break;
    case GT:
              result = bigCmp();
              if(result > 0) {
                push(newObjRef(1));
              } else {
                push(newObjRef(0));
              }
              break;
    case GE:
              result = bigCmp();
              if(result > 0 || result == 0)  {
                push(newObjRef(1));
              } else {
                push(newObjRef(0));
              }
              break;
  }
}

int jmp(int pos){
  return pos;
}

int brf (int pos, int progCount){
  StackSlot *slot = pop();
  bigFromInt(0);

  if(slot->isObjRef == FALSE){
    fatalError("cannot brf; top of stack isn't an ObjRef.\n");
  }

  bip.op2 = bip.res;
  bip.op1 = slot->u.objRef;
  if(bigCmp() < 1 || bigCmp() > 1) {
    return pos;
  }
  else return ++progCount;
}

int brt (int pos, int progCount){
  StackSlot *slot = pop();
  bigFromInt(1);

  if(slot->isObjRef == FALSE){
    fatalError("cannot brt; top of stack is an ObjRef.\n");
  }

  bip.op2 = bip.res;
	bip.op1 = slot->u.objRef;
	if(bigCmp() == 0){
    return pos;
  } else {
    return ++progCount;
  }
}

int call(int pos, int progCount){
  push(newObjNum(++progCount));
  return pos;
}

int ret(void){
  StackSlot *slot = pop();

  if(slot->isObjRef == TRUE){
    fatalError("Error: cannot ret; top of stack is an ObjRef.\n");
  }

  return slot->u.number;
}

void drop(int entries){
  int i;
	for(i = 0;i<entries; i++) {
		pop();
	}
}

void pushr(void) {
  push(newStackSlot(retRegister));
}

void popr(void) {
	retRegister = pop()->u.objRef;
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
