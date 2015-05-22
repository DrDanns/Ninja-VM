/*
 * File:	njvm_debug.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	20.05.2015
 * Describtion:	extends functions for the using of the debugger
 */

#include "njvm_debug.h"

int haltFlag = FALSE;
int bpFlag = FALSE;


void debugMenu(unsigned int program_memory[], int pos){
    int breakPoint;
    int stepFlag = FALSE;
    char charInput[50];
    int intInput;


    while (strcmp(charInput, "quit")==0 || haltFlag == FALSE){


      if (stepFlag == TRUE){
        if (OPCODE(program_memory[pos]) != HALT)
          pos=exec(program_memory[pos],pos); else break;
        stepFlag = FALSE;
      }

      printf("%04d:\t", pos);
      printInstruction(program_memory[pos]);

      printf("DEBUG: inspect, list, breakpoint, step, run ,quit?\n");
      scanf("%s", charInput );

        if (strcmp(charInput, "inspect")==0){
            printf("DEBUG [inspect]: stack, data?\n");
            scanf("%s", charInput );

            if (strcmp(charInput, "stack")==0){
                printStack();
            }
            else if (strcmp(charInput, "data")==0){
                printSDA();
            }
        }

        else if (strcmp(charInput, "list")==0){
          printAllInstructions(program_memory);
        }

        else if (strcmp(charInput, "breakpoint")==0){

            if (bpFlag == FALSE){
              printf("DEBUG [breakpoint]: cleared\n");
            }else {
              printf("DEBUG [breakpoint]: set at %d\n", breakPoint);
            }

            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change\n");

            /*TODO: return von scanf überarbeiten*/
            if (scanf("%d", &intInput )!=0){

                if (intInput == -1){
                    bpFlag = FALSE;
                    printf("DEBUG [breakpoint]: now cleared\n");
                }
                else{
                    bpFlag = TRUE;
                    breakPoint = intInput;
                    printf("DEBUG [breakpoint]: now set at %d\n", breakPoint);
                }
            }

        }

        else if (strcmp(charInput, "step")==0){
            stepFlag = TRUE;
        }

        else if (strcmp(charInput, "run")==0){
            run(program_memory, pos, breakPoint);
        }
    }

}

void run(unsigned int program_memory[],int pos, int breakPoint){

    int instruction = program_memory[pos];

    while (OPCODE(instruction) != HALT) {

       if (bpFlag==TRUE && (breakPoint-1)==pos){
        return;
       }
       pos = exec(instruction, pos++);
       instruction = program_memory[pos];
    }

    haltFlag = TRUE;
    printf("haltFlage = true");

}

void printStack(void){/*
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
    printf("--- End of Stack ---\n");*/
}

void printSDA(void){/*

    int i;
    int sdaSize = sizeof(StaticDataArea) / sizeof(int);;
    printf("--- Show Data ---\n");
    for(i = 0; i<sdaSize; i++) {
        printf("Data %i: %i\n",i,StaticDataArea[i]) ;
    }
    printf("--- End of Data ---\n");*/

}

void printAllInstructions(unsigned int program_memory[]){

    int i;

    for (i=0; OPCODE(program_memory[i]) != HALT ;i++) {
                printf("%03d:\t", i);
                printInstruction(program_memory[i]);
         }
    printf("--- end of code ---\n");

}

void printInstruction(unsigned int instruction){

    int immediate = SIGN_EXTEND(IMMEDIATE((instruction)));
    int opcode = OPCODE(instruction);

        switch (opcode) {
            case PUSHC:
                printf("pushc\t%d\n", immediate);
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
                printf("pushg\t%d\n", immediate);
                break;

            case POPG:
                printf("popg\t%d\n", immediate);
                break;

            case ASF:
                printf("asf\t%d\n", immediate);
                break;

            case RSF:
                printf("rsf\t\n");
                break;

            case PUSHL:
                printf("pushl\t%d\n", immediate);
                break;

            case POPL:
                printf("popl\t%d\n", immediate);
                break;
            case EQ:
                printf("eq\t\n");
                break;

            case NE:
                printf("ne\t\n");
                break;

            case LT:
                printf("lt\t\n");
                break;

            case LE:
                printf("le\t\n");
                break;

            case GT:
                printf("gt\t\n");
                break;

            case GE:
                printf("ge\t\n");
                break;

            case JMP:
                printf("jmp\t%d\n", immediate);
                break;

            case BRF:
                printf("brf\t%d\n",immediate);
                break;

            case BRT:
                printf("brt\t%d\n",immediate);
                break;

                }

}
