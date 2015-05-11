/*
 * File:	njvm_main.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	main functions for using the NJVM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "njvm_main.h"


int haltVM;


int main(int argc, char *argv[])
{
    printf("Ninja Virtual Machine started\n");
    atexit(end); /*includes end() after every exit*/
    menu(argc, argv);
    return (EXIT_SUCCESS);

}



void menu(int argc,  char** argv)
{

    if (strcmp(argv[1], "--version")==0) {
        printf("Version %d\n", VERSION);
    }

    else if (strcmp(argv[1], "--help")==0) {
        printf("usage: ./njvm [OPTIONS] <code file> \n\n");
        printf("--version\tshow version and exit.\n");
        printf("--help\tshow this help and exit.\n");
    }

    else {
        pc(readFile(openFile(argv[1])));
    }

}




void pc (unsigned int program_memory[])
{

    int PC = 0;
    int IR;
    haltVM = FALSE;

    printPM(program_memory);

    while(haltVM != TRUE) {
        IR = program_memory[PC];
        exec(IR);
        PC = PC + 1;
    }

}

void exec(int IR)
{

    switch (OPCODE(IR)) {

    case HALT:
        haltVM=TRUE;
        break;

    case PUSHC:
        push(SIGN_EXTEND( IMMEDIATE( (IR))));
        break;

    case ADD:
        add();
        break;

    case SUB:
        sub();
        break;

    case MUL:
        mul();
        break;

    case DIV:
        division();
        break;

    case MOD:
        mod();
        break;

    case RDINT:
        rdint();
        break;

    case WRINT:
        wrint();
        break;

    case RDCHR:
        rdchr();
        break;

    case WRCHR:
        wrchr();
        break;

    case PUSHG:
        pushg(SIGN_EXTEND( IMMEDIATE( (IR))));
        break;

    case POPG:
        popg(SIGN_EXTEND( IMMEDIATE( (IR))));
        break;

    case ASF:
        asf(SIGN_EXTEND( IMMEDIATE( (IR))));
        break;

    case RSF:
        rsf();
        break;
    case PUSHL:
        pushl(SIGN_EXTEND( IMMEDIATE( (IR))));
        break;
    case POPL:
        popl(SIGN_EXTEND( IMMEDIATE( (IR))));
        break;

    }


}

void printPM(unsigned int program_memory[])
{
    int i = 0;
    int opcode=program_memory[i];

    while(opcode != HALT) {

        printf("%03d:\t", i);
        opcode = OPCODE(program_memory[i]);
        switch (opcode) {
        case PUSHC:
            printf("pushc\t%d\n", SIGN_EXTEND(IMMEDIATE( program_memory[i])));
            break;

        case ADD:
            printf("add\t\n");
            break;

        case SUB:
            printf("sub\t\n");
            break;

        case MUL:
            printf("mul\t\n");
            break;

        case DIV:
            printf("div\t\n");
            break;

        case MOD:
            printf("mod\t\n");
            break;

        case RDINT:
            printf("rdint\t\n");
            break;

        case WRINT:
            printf("wrint\t\n");
            break;

        case RDCHR:
            printf("rdchr\t\n");
            break;

        case WRCHR:
            printf("wrchr\t\n");
            break;

        case HALT:
            printf("halt\t\n");
            break;

        case PUSHG:
            printf("pushg\t%d\n", SIGN_EXTEND(IMMEDIATE( program_memory[i])));
            break;

        case POPG:
            printf("popg\t%d\n", SIGN_EXTEND(IMMEDIATE( program_memory[i])));
            break;

        case ASF:
            printf("asf\t%d\n", SIGN_EXTEND(IMMEDIATE( program_memory[i])));
            break;

        case RSF:
            printf("rsf\t\n");
            break;

        case PUSHL:
            printf("pushl\t%d\n", SIGN_EXTEND(IMMEDIATE( program_memory[i])));
            break;

        case POPL:
            printf("popl\t%d\n", SIGN_EXTEND(IMMEDIATE( program_memory[i])));
            break;

        }

        i = i+1;
    }

}

void end(void)
{
    printf("Ninja Virtual Machine stopped\n");
}



