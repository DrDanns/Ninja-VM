/*
 * File:	njvm_main.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	main functions for using the NJVM
 */


#include "njvm_main.h"


int main(int argc, char *argv[]){
    printf("Ninja Virtual Machine started\n");
    atexit(end); /*includes end() after every exit*/
    njvmMenu(argc, argv);
    return (EXIT_SUCCESS);
}

void njvmMenu(int argc,  char** argv){

    if (argc==1){ /*if only "./njvm"*/
	    fputs("Error: no code file specified.\n", stderr);
	    exit(EXIT_FAILURE);
    }
    else if (strcmp(argv[1], "--version")==0) {
        printf("Version %d\n", VERSION);
    }
    else if (strcmp(argv[1], "--help")==0) {
      printf("Usage: ./njvm [OPTIONS] <code file>\n");
	    printf("Options:\n");
      printf("  --debug \tstart virtual machine in debug mode\n");
      printf("  --version \tshow version and exit\n");
      printf("  --help \tshow this help and exit\n");
    }
    else if (strcmp(argv[1], "--debug")==0){
	  if (argc != 3){
	      fputs("Error: no code file specified.\n", stderr);
	      exit(EXIT_FAILURE);
	  }
	  else{ /*debugger starten*/
          debugMenu(readFile(openFile(argv[2])), 0);
          return;
	  }
    }
    else{ /*load and execute the programm*/
        pc(readFile(openFile(argv[1])));
        return;

    }

}

void pc (unsigned int program_memory[]){

    int progCount = 0;
    int instruction = program_memory[progCount];

    while (OPCODE(instruction) != HALT) {
       progCount = exec(instruction, progCount);
       instruction = program_memory[progCount];
    }
}

int exec(int instruction, int progCount){

    int immediate = SIGN_EXTEND(IMMEDIATE((instruction)));
    int opcode = OPCODE(instruction);

    switch (opcode) {

    case HALT:
        break;

    case PUSHC:
        push(newObjRef(immediate));
        return ++progCount;
    case ADD:
        calc(opcode);
        return ++progCount;

    case SUB:
        calc(opcode);
        return ++progCount;

    case MUL:
        calc(opcode);
        return ++progCount;

    case DIV:
        calc(opcode);
        return ++progCount;
    case MOD:
        calc(opcode);
        return ++progCount;

    case RDINT:
        rdint();
        return ++progCount;

    case WRINT:
        wrint();
        return ++progCount;

    case RDCHR:
        rdchr();
        return ++progCount;

    case WRCHR:
        wrchr();
        return ++progCount;

    case PUSHG:
        pushg(immediate);
        return ++progCount;

    case POPG:
        popg(immediate);
        return ++progCount;

    case ASF:
        asf(immediate);
        return ++progCount;

    case RSF:
        rsf();
        return ++progCount;

    case PUSHL:
        pushl(immediate);
        return ++progCount;

    case POPL:
        popl(immediate);
        return ++progCount;

    case EQ:
        calc(opcode);
        return ++progCount;

    case NE:
        calc(opcode);
        return ++progCount;

    case LT:
        calc(opcode);
        return ++progCount;

    case LE:
        calc(opcode);
        return ++progCount;

    case GT:
        calc(opcode);
        return ++progCount;

    case GE:
        calc(opcode);
        return ++progCount;

    case JMP:
        return jmp(immediate);

    case BRF:
        return brf(immediate, progCount);

    case BRT:
        return brt(immediate, progCount);

    case CALL:
        return call(immediate, progCount);

    case RET:
        return ret();

    case DROP:
        drop(immediate);
        return ++progCount;

    case PUSHR:
        pushr();
        return ++progCount;

    case POPR:
        popr();
        return ++progCount;

    case DUP:
        dup();
        return ++progCount;

    case NEW:
        new(immediate);
        return ++progCount;

    case GETF:
        getf(immediate);
        return ++progCount;

    case PUTF:
        putf(immediate);
        return ++progCount;

    case NEWA:
        newa();
        return ++progCount;

    case GETFA:
        getfa();
        return ++progCount;

    case PUTFA:
        putfa();
        return ++progCount;

    case GETSZ:
        getsz();
        return ++progCount;

    case PUSHN:
        pushn();
        return ++progCount;

    case REFEQ:
        refeq();
        return ++progCount;

    case REFNE:
        refne();
        return ++progCount;

    default:
        fputs("Error: Unsupported Operation-Code.\n", stderr);
        exit(EXIT_FAILURE);
    }

    return 0;

}

void end(void){
    printf("Ninja Virtual Machine stopped\n");
}
