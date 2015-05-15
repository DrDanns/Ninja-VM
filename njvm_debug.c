/*
 * File:	njvm_debug.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	14.01.2015
 * Describtion:	extends functions for the using of the debugger
 */

#include "njvm_debug.h"




void debugMenu(unsigned int program_memory[], int pos){
    int breakPoint;
    int haltVM = FALSE;
    int setBP = FALSE;
    int doStep = TRUE;
    char charInput[50];
    int intInput;
    int i;


    while (strcmp(charInput, "quit")==0 || haltVM == TRUE){

        printProgLine(program_memory[pos]);

        if (doStep == TRUE){
            debugPC(program_memory, pos);
            doStep = FALSE;
        }

        printf("DEBUG: inspect, list, breakpoint, step, run ,quit?\n");
        scanf("%s", &charInput );

        if (strcmp(charInput, "inspect")==0){
            printf("DEBUG [inspect]: stack, data?\n");
            scanf("%s", &charInput );

            if (strcmp(charInput, "stack")==0){
                printStack();
            }
            else if (strcmp(charInput, "data")==0){
                printSDA();
            }
        }

        else if (strcmp(charInput, "list")==0){
            for (i=0; OPCODE(program_memory[i]) != HALT ;i++) {
                printProgLine(program_memory[i]);
            }
            printf("--- end of code ---\n");
        }

        else if (strcmp(charInput, "breakpoint")==0){

            if (setBP == FALSE){
                printf("DEBUG [breakpoint]: cleared\n");
            }else {
                printf("DEBUG [breakpoint]: set at %d\n", breakPoint);
            }

            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change\n");

            if (scanf("%d", &intInput )!=0){

                if (intInput == -1){
                    setBP = FALSE;
                    printf("DEBUG [breakpoint]: now cleared\n");
                }
                else{
                    setBP = TRUE;
                    breakPoint = intInput;
                    printf("DEBUG [breakpoint]: now set at %d\n", breakPoint);
                }
            }

        }

        else if (strcmp(charInput, "step")==0){
            pos++;
            doStep = TRUE;
        }

        else if (strcmp(charInput, "run")==0){

            if (setBP ==TRUE){
                while (pos != breakPoint){
                    debugPC(program_memory, pos);
                }
            }
            else {
                while (haltVM != TRUE){
                    haltVM = debugPC(program_memory, pos);
                }
            }

        }
    }

}

int debugPC(unsigned int *program_memory[],int *pos){


    int instruction = program_memory[pos];

    if (OPCODE(instruction) != HALT) {
        instruction = program_memory[progCount];
        &pos = exec(OPCODE(instruction), SIGN_EXTEND( IMMEDIATE( (instruction))), progCount);
        return FALSE;
    }

    return TRUE;


}

void printStack(void){
    int i;
    printf("--- Show Stack ---\n");
    printf("SP--> | %10c           | -- %i\n", 'x',stackPointer);
    for(i = sC-1; i>=0; i--) {
        printf("      ------------------------\n");
        if(i == fP) {
            printf("FP--> | %10i           | -- %i\n", stack[i],i);
        } else {
            printf("      | %10i           | -- %i\n", stack[i],i);
        }
    }
    printf("      ------------------------\n");
    printf("--- End of Stack ---\n");
}

void printSDA(void){
    int i;
    int sdaSize = sizeof(StaticDataArea) / sizeof(int);;
    printf("--- Show Data ---\n");
    for(i = 0; i<sdaSize; i++) {
        printf("Data %i: %i\n",i,StaticDataArea[i]) ;
    }
    printf("--- End of Data ---\n");
}

void printProgLine(unsigned int *program_line)
{
    int i = 0;

        printf("%03d:\t", i);

        switch (OPCODE(program_line)) {
            case PUSHC:
                printf("pushc\t%d\n", SIGN_EXTEND(IMMEDIATE(program_line)));
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
                printf("pushg\t%d\n", SIGN_EXTEND(IMMEDIATE( program_line)));
                break;

            case POPG:
                printf("popg\t%d\n", SIGN_EXTEND(IMMEDIATE( program_line)));
                break;

            case ASF:
                printf("asf\t%d\n", SIGN_EXTEND(IMMEDIATE( program_line)));
                break;

            case RSF:
                printf("rsf\t\n");
                break;

            case PUSHL:
                printf("pushl\t%d\n", SIGN_EXTEND(IMMEDIATE( program_line)));
                break;

            case POPL:
                printf("popl\t%d\n", SIGN_EXTEND(IMMEDIATE( program_line)));
                break;
//TODO: ab hier überarbeiten
            case EQ:
                compare(EQ);
                return ++progCount;

            case NE:
                compare(NE);
                return ++progCount;

            case LT:
                compare(LT);
                return ++progCount;

            case LE:
                compare(LE);
                return ++progCount;

            case GT:
                compare(GT);
                return ++progCount;

            case GE:
                compare(GE);
                return ++progCount;

            case JMP:
                return jmp(immediate);

            case BRF:
                return brf(immediate, progCount);

            case BRT:
                return brt(immediate, progCount);

        }

        i = i+1;


}


