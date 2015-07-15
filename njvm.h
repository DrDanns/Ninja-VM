/*
 * File:	njvm.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	Header-File for NJVM
 */
#ifndef NJVM
#define NJVM

#define VERSION 7
#define STACKSIZE 1000

#define FALSE   0
#define TRUE    1

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))
#define OPCODE(j) (((j) & 0xFF000000) >> 24)
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6

#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10

#define PUSHG 11
#define POPG 12

#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16

#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22

#define JMP 23
#define BRF 24
#define BRT 25

#define CALL 26
#define RET 27
#define DROP 28
#define PUSHR 29
#define POPR 30
#define DUP 31

#endif /*NJVM*/
