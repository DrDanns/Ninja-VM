/*
 * File:   njvm_object.h
 * Author: Stanislav Hannes, 5000458
 * Date:	12.06.2015
 * Describtion: Header-File for the njvm_object.c
 */

#ifndef NJVM_OBJECT
#define NJVM_OBJECT

#include <stdio.h>
#include <stdlib.h>
#include "njvm.h"



typedef struct{
  unsigned int size;
  unsigned char data[1];
} *ObjRef;

typedef struct{
  int isObjRef;
  union {
    ObjRef objRef;
    int number;
  } u;
} StackSlot;

StackSlot *newStackSlot(ObjRef objRef);
StackSlot *newObjRef(int value);
StackSlot *newObjNum(int value);

#endif /*NJVM_OBJECT*/
