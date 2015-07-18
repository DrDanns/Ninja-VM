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
    int objSize;
    int i;
    ObjRef objAddr; /*Variable zum lokalisieren der ObjRef*/
    int *address;

    while (haltFlag == FALSE){

      if (stepFlag == TRUE){
        if (OPCODE(program_memory[pos]) != HALT)
          pos=exec(program_memory[pos],pos); else break;
        stepFlag = FALSE;
      }

      printf("%04d:\t", pos);
      printInstruction(program_memory[pos]);

      printf("DEBUG: inspect, list, breakpoint, step, run ,quit?\n");
      scanf("%s", charInput );

        if (strcmp(charInput, "inspect")==0 || strcmp(charInput, "i")==0){
            printf("DEBUG [inspect]: stack, data, object?\n");
            scanf("%s", charInput );

            if (strcmp(charInput, "stack")==0 || strcmp(charInput, "s")==0){
                printStack();
            }
            else if (strcmp(charInput, "data")==0 || strcmp(charInput, "d")==0){
                printSDA();
            }
            else if (strcmp(charInput, "object")==0 || strcmp(charInput, "o")==0){
              printf("DEBUG [object]: Enter object address?\n");
              scanf("%p",(void **)&address);
              objAddr = (ObjRef)address;

              if(IS_PRIM(objAddr)){
                 bip.op1 = objAddr;
                 printf("value = ");
                 bigPrint(stdout);
                 printf("\n");
              } else {
                    printf("<compound object>\n");
                    objSize = GET_SIZE(objAddr);

                    for(i = 0;i < objSize; i++) {
                        printf("item[%i] = %p\n",i,(void* )getInstance(i,objAddr));
                    }
              }
            }
        }

        else if (strcmp(charInput, "list")==0 || strcmp(charInput, "l")==0){
          printAllInstructions(program_memory);
        }

        else if (strcmp(charInput, "breakpoint")==0 || strcmp(charInput, "b")==0){

            if (bpFlag == FALSE){
              printf("DEBUG [breakpoint]: cleared\n");
            }else {
              printf("DEBUG [breakpoint]: set at %d\n", breakPoint);
            }

            printf("DEBUG [breakpoint]: address to set, -1 to clear\n");

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

        else if (strcmp(charInput, "step")==0 || strcmp(charInput, "s")==0){
          stepFlag = TRUE;
        }

        else if (strcmp(charInput, "run")==0 || strcmp(charInput, "r")==0){
          pos=run(program_memory, pos, breakPoint);
          bpFlag = FALSE;
        }

        else if (strcmp(charInput, "quit")==0 || strcmp(charInput, "q")==0){
          haltFlag=TRUE;
        }
    }

}

int run(unsigned int program_memory[],int pos, int breakPoint){

    int instruction = program_memory[pos];

    while (OPCODE(instruction) != HALT) {

       if (bpFlag==TRUE && (breakPoint)==pos){
        return pos;
       }
       pos = exec(instruction, pos++);
       instruction = program_memory[pos];
    }

    haltFlag = TRUE;
    return pos;

}

ObjRef getInstance(int pos, ObjRef objref) {
	ObjRef inst;
	inst = *(GET_REFS(objref)+pos);
	return inst;
}

void printStack(void){
    int i;
    printf("------------ Show Stack -----------\n");
    printf("SP--> %04i:\t(xxxxxx)  xxxxxxxxx\n", stackPointer);
    for(i = stackPointer-1; i>=0; i--) {
        printf("      -----------------------------\n");
        if(i == framePointer) {
          if(stack[i]->isObjRef == TRUE) {
               if(stack[i]->u.objRef == NULL){
                 printf("FP--> %04i:\t(objref)  nil\n",i);
               } else {
                 printf("FP--> %04i:\t(objref) %10p\n", i, (void *)stack[i]->u.objRef);
               }
          } else {
                printf("FP--> %04i:\t(number)  %i\n", i, stack[i]->u.number);
          }
        } else if(stack[i]->isObjRef == TRUE){
            if (stack[i]->u.objRef == NULL){
              printf("      %04i:\t(objref)  nil\n",i);
            } else {
              printf("      %04i:\t(objref) %10p\n", i, (void *)stack[i]->u.objRef);
            }
        } else {
            printf("      %04i:\t(number)  %i\n",i , stack[i]->u.number);
        }

    }

    printf("      -----------------------------\n");
		printf("---------- End of Stack -----------\n");
}

void printSDA(void){
    int i;

    printf("\n--- Show Static Data Area ---\n");
    for(i = 0; i < sdaSize; i++) {
        if(staticData[i] == NULL){
            printf("Data [%i]:\tnil\n",i);
        } else {
            printf("Data [%i]:\t%10p\n",i,(void *)staticData[i]);
  		}
  	}
    printf("--- End of Static Data Area ---\n");
}

void printAllInstructions(unsigned int program_memory[]){

    int i;

    for (i=0; i < instructSize; i++) {
                printf("%04d:\t", i);
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

            case CALL:
                printf("call\t%d\n",immediate);
                break;

            case RET:
                printf("ret\t\n");
                break;

            case DROP:
                printf("drop\t%d\n",immediate);
                break;

            case PUSHR:
                printf("pushr\t\n");
                break;

            case POPR:
                printf("popr\t\n");
                break;

            case DUP:
                printf("dup\t\n");
                break;

            case NEW:
                printf("new\t%d\n", immediate);
                break;

            case GETF:
                printf("getf\t%d\n", immediate);
                break;

            case PUTF:
                printf("putf\t%d\n", immediate);
                break;

            case NEWA:
                printf("newa\t\n");
                break;

            case GETFA:
                printf("getfa\t\n");
                break;

            case PUTFA:
                printf("putfa\t\n");
                break;;

            case GETSZ:
                printf("getsz\t\n");
                break;

            case PUSHN:
                printf("pushn\t\n");
                break;

            case REFEQ:
                printf("refeq\t\n");
                break;

            case REFNE:
                printf("refne\t\n");
                break;
                }

}
