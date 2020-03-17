#include "codes.h"
#include "instructions.h"

void *commands[256];
uint32_t reg[16];
uint32_t mem[2<<20];
uint32_t flag;

void end(){
    exit(0);
}

void halt(char r1, int op) { // 0 RI
    exit(0);
}

void syscall(char r1, int op) { // 1 RI
    double ad;
    uint64_t a;
    switch(op) {
        case HALT:
            exit(op);
        break;
        case SCANINT:
            scanf("%d", &reg[r1]);
        break;
        case SCANDOUBLE:
            scanf("%lf", &ad);
            a = *((uint64_t*)&ad);
            reg[r1] = a;
            reg[r1+1] = a>>32;
        break;
        case PRINTINT:
            printf("%d", (int)reg[r1]);
        break;
        case PRINTDOUBLE:
            a = ((uint64_t)reg[r1+1]<<32) + reg[r1];
            ad = *((double*)&a);
            printf("%g", ad);
        break;
        case GETCHAR:
        
        break;
        case PUTCHAR:
            printf("%c", (char)reg[r1]);
        break;
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
    reg[r1+1] = t>>32;
    reg[r1] = t;
}

void muli(char r1, int op) { // 7 RI
    int64_t t = (int64_t)reg[r1] * (int64_t)op;
    reg[r1+1] = t>>32;
    reg[r1] = t;
}

void div_(char r1, char r2, int op) { // 8 RR
    int64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r1], b = reg[r2];
    reg[r1] = a / b;
    reg[r1+1] = a % b;
}

void divi(char r1, int op) { // 9 RI
    int64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r1], b = op;
    reg[r1] = a / b;
    reg[r1+1] = a % b;
}

void lc(char r1, int op) { // 12 RI
    reg[r1] = op;
}

void shl(char r1, char r2, int op) { // 13 RR
    reg[r1] <<= reg[r2];
}

void shli(char r1, int op) { // 14 RI
    reg[r1] <<= op;
}

void shr(char r1, char r2, int op) { // 15 RR
    reg[r1] >>= reg[r2];
}

void shri(char r1, int op) { // 16 RI
    reg[r1] >>= op;
}

void and_(char r1, char r2, int op) { // 17 RR
    reg[r1] &= reg[r2];
}

void andi(char r1, int op) { // 18 RI
    reg[r1] &= op;
}

void or_(char r1, char r2, int op) { // 19 RR
    reg[r1] |= reg[r2];
}

void ori(char r1, int op) { // 20 RI
    reg[r1] |= op;
}

void xor_(char r1, char r2, int op) { // 21 RR
    reg[r1] ^= reg[r2];
}

void xori(char r1, int op) { // 22 RI
    reg[r1] ^= op;
}

void not_(char r1, int op) { // 23 RI
    reg[r1] = ~reg[r1];
}

void mov(char r1, char r2, int op) { // 24 RR
    reg[r1] = reg[r2] + op;
}

void addd(char r1, char r2, int op) { // 32 RR
    uint64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r1], b = ((uint64_t)reg[r2+1]<<32) + reg[r2];
    double ad = *((double*)&a), bd = *((double*)&b);
    ad += bd;
    a = *((uint64_t*)&ad);
    reg[r1+1] = a>>32;
    reg[r1] = a;
}

void subd(char r1, char r2, int op) { // 33 RR
    uint64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r1], b = ((uint64_t)reg[r2+1]<<32) + reg[r2];
    double ad = *((double*)&a), bd = *((double*)&b);
    ad -= bd;
    a = *((uint64_t*)&ad);
    reg[r1+1] = a>>32;
    reg[r1] = a;
}

void muld(char r1, char r2, int op) { // 34 RR
    uint64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r1], b = ((uint64_t)reg[r2+1]<<32) + reg[r2];
    double ad = *((double*)&a), bd = *((double*)&b);
    ad *= bd;
    a = *((uint64_t*)&ad);
    reg[r1+1] = a>>32;
    reg[r1] = a;
}

void divd(char r1, char r2, int op) { // 35 RR
    uint64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r1], b = ((uint64_t)reg[r2+1]<<32) + reg[r2];
    double ad = *((double*)&a), bd = *((double*)&b);
    ad /= bd;
    a = *((uint64_t*)&ad);
    reg[r1+1] = a>>32;
    reg[r1] = a;
}

void itod(char r1, char r2, int op) { // 36 RR
    double ad = (int)reg[r2];
    uint64_t a = *((uint64_t*)&ad);
    reg[r1+1] = a>>32;
    reg[r1] = a;
}

void dtoi(char r1, char r2, int op) { // 37 RR
    uint64_t a = ((uint64_t)reg[r1+1]<<32) + reg[r2];
    double ad = *((double*)&a);
    reg[r2] = ad;
}

void push(char r1, int op) { // 38 RI
    mem[--reg[14]] = reg[r1] + op;
}

void pop(char r1, int op) { // 39 RI
    reg[r1] = mem[reg[14]++] + op;
}

void call(char r1, char r2, int op) { // 40 RR
    int a = reg[15] + 1;
    reg[15] = reg[r2] + op - 1;
    reg[r1] = a;
    push(r1, 0);
}

void calli(int op) { // 41 J
    push(15, 1);
    reg[15] = op-1;
}

void ret(char r1, int op) { // 42 RI
    pop(15, -1);
    reg[14] += op;
}

void cmp(char r1, char r2, int op) { // 43 RR
    if(reg[r1] == reg[r2]) flag = EQUAL;
    if((int)reg[r1] < (int)reg[r2]) flag = LESS;
    if((int)reg[r1] > (int)reg[r2]) flag = GREATER;
}

void cmpi(char r1, int op) { // 44 RI
    if(reg[r1] == op) flag = EQUAL;
    if((int)reg[r1] < op) flag = LESS;
    if((int)reg[r1] > op) flag = GREATER;
}

void cmpd(char r1, char r2, int op) { // 45 RR
    uint64_t a = reg[r1+1]<<32ull + reg[r1], b = reg[r2+1]<<32ull + reg[r2];
    double ad = *((double*)&a), bd = *((double*)&b);
    if(a == b) flag = EQUAL;
    if(a < b) flag = LESS;
    if(a > b) flag = GREATER;
}

void jmp(int op) { // 46 J
    reg[15] = op-1;
}

void jne(int op) { // 47 J
    if(flag == GREATER || flag == LESS) reg[15] = op-1;
}

void jeq(int op) { // 48 J
    if(flag == EQUAL) reg[15] = op-1;
}

void jle(int op) { // 49 J
    if(flag == EQUAL || flag == LESS) reg[15] = op-1;
}

void jl(int op) { // 50 J
    if(flag == LESS) reg[15] = op-1;
}

void jge(int op) { // 49 J
    if(flag == EQUAL || flag == GREATER) reg[15] = op-1;
}

void jg(int op) { // 50 J
    if(flag == GREATER) reg[15] = op-1;
}

void load(char r1, int op) { // 64 RM
    reg[r1] = mem[op];
}

void store(char r1, int op) { // 65 RM
    mem[op] = reg[r1];
}

void load2(char r1, int op) { // 66 RM
    reg[r1] = mem[op];
    reg[r1+1] = mem[op+1];
}

void store2(char r1, int op) { // 67 RM
    mem[op] = reg[r1];
    mem[op+1] = reg[r1+1];
}

void loadr(char r1, char r2, int op) { // 68 RR
    reg[r1] = mem[reg[r2]+op];
}

void loadr2(char r1, char r2, int op) { // 69 RR
    reg[r1] = mem[reg[r2]+op];
    reg[r1+1] = mem[reg[r2]+op+1];
}

void storer(char r1, char r2, int op) { // 70 RR
    mem[reg[r2]+op] = reg[r1];
}

void storer2(char r1, char r2, int op) { // 71 RR
    mem[op+reg[r2]] = reg[r1];
    mem[op+1+reg[r2]] = reg[r1+1];
}

void prepare_instructions() {
    reg[14] = 1048575;
    for(int i = 0; i < 14; i++) reg[i] = 0;
    for(int i = 0; i < (2<<20); i++) mem[i] = 0;
    commands[0]  = (void*)halt;
    commands[1]  = (void*)syscall;
    commands[2]  = (void*)add;
    commands[3]  = (void*)addi;
    commands[4]  = (void*)sub;
    commands[5]  = (void*)subi;
    commands[6]  = (void*)mul;
    commands[7]  = (void*)muli;
    commands[8]  = (void*)div_;
    commands[9]  = (void*)divi;
    commands[12] = (void*)lc;
    commands[13] = (void*)shl;
    commands[14] = (void*)shli;
    commands[15] = (void*)shr;
    commands[16] = (void*)shri;
    commands[17] = (void*)and_;
    commands[18] = (void*)andi;
    commands[19] = (void*)or_;
    commands[20] = (void*)ori;
    commands[21] = (void*)xor_;
    commands[22] = (void*)xori;
    commands[23] = (void*)not_;
    commands[24] = (void*)mov;
    commands[32] = (void*)addd;
    commands[33] = (void*)subd;
    commands[34] = (void*)muld;
    commands[35] = (void*)divd;
    commands[36] = (void*)itod;
    commands[37] = (void*)dtoi;
    commands[38] = (void*)push;
    commands[39] = (void*)pop;
    commands[40] = (void*)call;
    commands[41] = (void*)calli;
    commands[42] = (void*)ret;
    commands[43] = (void*)cmp;
    commands[44] = (void*)cmpi;
    commands[45] = (void*)cmpd;
    commands[46] = (void*)jmp;
    commands[47] = (void*)jne;
    commands[48] = (void*)jeq;
    commands[49] = (void*)jle;
    commands[50] = (void*)jl;
    commands[51] = (void*)jge;
    commands[52] = (void*)jg;
    commands[64] = (void*)load;
    commands[65] = (void*)store;
    commands[66] = (void*)load2;
    commands[67] = (void*)store2;
    commands[68] = (void*)loadr;
    commands[69] = (void*)loadr2;
    commands[70] = (void*)storer;
    commands[71] = (void*)storer2;
}