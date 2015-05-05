#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))
#define OPCODE(j) (((j) & 0xFF000000) >> 24)
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

void push(int);
int pop();
void add();
void sub();
void mul();
void division();
void mod();
void exec(int);
void printPC(unsigned int[]);
void pc(unsigned int[]);
void rdchr();
void rdint();
void wrchr();
void wrint();

char version[] = "1.0";
int STACK[1000];
int sPointer;
int haltVM=0;

unsigned int code1[] = {
    (PUSHC << 24) | IMMEDIATE(3),
    (PUSHC << 24) | IMMEDIATE(4),
    (ADD << 24),
    (PUSHC << 24) | IMMEDIATE(10),
    (PUSHC << 24) | IMMEDIATE(6),
    (SUB << 24) ,
    (MUL << 24) ,
    (WRINT << 24) ,
    (PUSHC << 24) | IMMEDIATE(10),
    (WRCHR << 24) ,
    (HALT << 24)
};

unsigned int code2[] = {
    (PUSHC << 24) | IMMEDIATE(-2),
    (RDINT << 24) ,
    (MUL << 24),
    (PUSHC << 24) | IMMEDIATE(3),
    (ADD << 24) ,
    (WRINT << 24) ,
    (PUSHC << 24) | IMMEDIATE(10),
    (WRCHR << 24) ,
    (HALT << 24)
};

unsigned int code3[] = {
    (RDCHR << 24),
    (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE(10),
    (WRCHR << 24) ,
    (HALT << 24)
};

int main(int argc, char *argv[]) {

    printf("Ninja Virtual Machine started\n");

    if (strcmp(argv[1], "--version")==0) {
        printf("Version %s\n", version);
    }

    else if (strcmp(argv[1], "--help")==0) {
        printf("Usage: ./njvm [OPTIONS] ... \n\n");
        printf("Allowed Arguments:\n");
        printf("--prog1\tselect program 1 to execute\n");
        printf("--prog1\tselect program 2 to execute\n");
        printf("--prog1\tselect program 3 to execute\n");
        printf("--version\tPrints the actual version\n");
        printf("--help\t\tPrints this help\n");
    }

    else if (strcmp(argv[1], "--prog1")==0) {
        pc(code1);
    } else if (strcmp(argv[1], "--prog2")==0) {
        pc(code2);
    } else if (strcmp(argv[1], "--prog3")==0) {
        pc(code3);
    }

    else {
        printf("%s is an unknown argument\n", argv[1]);
    }

    printf("Ninja Virtual Machine stopped\n");
    return (EXIT_SUCCESS);
}




void pc (unsigned int program_memory[]) {

    int PC = 0;
    int IR;
    sPointer = 0;
    haltVM = 0;
    
    /*1. Interpreter: Ausgabe des Programms*/
    printPC(program_memory);

    while(haltVM==0) {
        IR = program_memory[PC];
        exec(IR);
        PC = PC + 1;
    }

}

void exec(int IR) {

    switch (OPCODE(IR)) {
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

    case HALT:
        haltVM=1;
        break;
    }
}

void printPC(unsigned int program_memory[]) {
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
        }
        i = i+1;
    }

}

void push(int IR) {
    STACK[sPointer] = IR;
    sPointer = sPointer + 1;
}

int pop() {
    sPointer =  sPointer - 1;
    return STACK[sPointer];
}

void add() {
    push(pop() + pop());
}

void sub() {
    int num = pop();
    push(pop() - num);
}

void mul() {
    push(pop() * pop());
}

void division() {
    push(pop() / pop());
}

void mod() {
    push(pop() % pop());
}

void rdint() {
    int i;
    scanf(" %d", &i);
    push(i);
}

void wrint() {
    printf("%d", (int) pop());
}

void rdchr() {
    char c;
    scanf(" %c",&c);
    push((int) c);
}

void wrchr() {
    printf("%c", (char) pop());
}

