#include "instructions.h"
#include "codes.h"

void *commands[256];

void end(){
    exit(0);
}

void syscall(char r1, int op) { // 1 RI
    switch(op) {
        case HALT:
            exit(op);
        break;
        case SCANINT:
            scanf("%d", &reg[r1]);
        break;
        case SCANDOUBLE:

        break;
        case PRINTINT:
            printf("%d\n", (int)reg[r1]);
        break;
        case PRINTDOUBLE:

        break;
        case GETCHAR:
        
        break;
        case PUTCHAR:

        break;
    }
}

void add(char r1, char r2, int op) { // 2 RR
    reg[r1] += reg[r2] + op;
}

void addi(char r1, int op) { // 3 RI
    reg[r1] += op;
}

void sub(char r1, char r2, int op) { // 4 RR
    reg[r1] -= reg[r2] + op;
}

void subi(char r1, int op) { // 5 RI
    reg[r1] -= op;
}

void mul(char r1, char r2, int op) { // 6 RR
    int64_t t = (int64_t)reg[r1] * (int64_t)reg[r2];
    reg[r1] = t>>32;
    reg[r1+1] = t;
}

void muli(char r1, int op) { // 7 RI
    int64_t t = (int64_t)reg[r1] * (int64_t)op;
    reg[r1] = t>>32;
    reg[r1+1] = t;
}

// void div(char r1, char r2, int op) { // 8 RR
//     int d = (int)reg[r1] / 
// }

void lc(char r1, int op) { // 12 RI
    reg[r1] = op;
}

void shl(char r1, char r2, int op) { // 13 RR
    reg[r1] >>= reg[r2];
}

void shli(char r1, int op) { // 14 RI
    reg[r1] >>= op;
}

void shr(char r1, char r2, int op) { // 15 RR
    reg[r1] <<= reg[r2];
}

void shri(char r1, int op) { // 16 RI
    reg[r1] <<= op;
}

void and(char r1, char r2, int op) { // 17 RR
    reg[r1] &= reg[r2];
}

void andi(char r1, int op) { // 18 RI
    reg[r1] &= op;
}

void or(char r1, char r2, int op) { // 19 RR
    reg[r1] |= reg[r2];
}

void ori(char r1, int op) { // 20 RI
    reg[r1] |= op;
}

void xor(char r1, char r2, int op) { // 21 RR
    reg[r1] ^= reg[r2];
}

void xori(char r1, int op) { // 22 RI
    reg[r1] ^= op;
}

void not(char r1, int op) { // 23 RI
    reg[r1] = ~reg[r1];
}

void mov(char r1, char r2, int op) { // 24 RR
    reg[r1] = reg[r2] + op;
}

void push(char r1, int op) { // 38 RI
    mem[reg[14]--] = reg[r1] + op;
}

void pop(char r1, int op) { // 39 RI
    reg[r1] = mem[reg[14]++] + op;
}

void call(char r1, char r2, int op) { // 40 RR
    reg[r1] = reg[15] + 1;
    push(r1, 0);
    reg[15] = reg[r2] + op - 1;
}

void calli(int op) { // 41 J
    push(15, 1);
    reg[15] = op;
}

void ret(char r1, int op) { // 42 RI
    reg[14] += op;
    reg[15] = mem[reg[14]]-1;
}

void prepare_instructions() {
    reg[14] = 1048575;
    commands[SYSCALL]   = (void*)syscall;
    commands[LC]        = (void*)lc;
}