/*
 * File:	njvm_main.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	main functions for using the NJVM
 */


#include "njvm_main.h"


int main(int argc, char *argv[])
{
    printf("Ninja Virtual Machine started\n");
    atexit(end); /*includes end() after every exit*/
    njvmMenu(argc, argv);
    return (EXIT_SUCCESS);

}

void njvmMenu(int argc,  char** argv)
{

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




void pc (unsigned int program_memory[])
{

    int progCount = 0;
    int instruction = program_memory[progCount];

    while (OPCODE(instruction) != HALT) {
       instruction = program_memory[progCount];
       progCount = exec(OPCODE(instruction), SIGN_EXTEND( IMMEDIATE( (instruction))), progCount);
    }

}

int exec(int opcode, int immediate, int progCount)
{

    switch (opcode) {

    case HALT:
        haltVM=TRUE;
        return ++progCount;

    case PUSHC:
        push(immediate);
        return ++progCount;

    case ADD:
        add();
        return ++progCount;

    case SUB:
        sub();
        return ++progCount;

    case MUL:
        mul();
        return ++progCount;

    case DIV:
        division();
        return ++progCount;

    case MOD:
        mod();
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
	
    default: fputs("Error: Unsupported Operation-Code.\n", stderr);
	     exit(EXIT_FAILURE);
    }
    
    return 0;


}


void end(void)
{
    printf("Ninja Virtual Machine stopped\n");
}



