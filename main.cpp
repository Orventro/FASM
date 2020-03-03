#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include "codes.h"

using namespace std;

uint32_t reg[16];
uint32_t mem[2<<20];
map<string, int> ptr_num;
map<int, int> ptr_addr;

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

int main() {
    prepare_codes();
    reg[14] = 1048575;

    commands[SYSCALL]   = (void*)syscall;
    commands[LC]        = (void*)lc;
    fstream in("input.fasm", fstream::in);
    int read_addr = 0;
    while(in.good()) {
        string command;
        in >> command;
        if(command.back() == ':') {
            // pointer declaration
            command = command.substr(0, command.size()-1);
            if(!ptr_num.count(command)) 
                ptr_num[command] = ptr_num.size();
            ptr_addr[ptr_num[command]] = read_addr;
        } else if(command == "end") {
            string ptr_name;
            in >> ptr_name;
            reg[15] = ptr_addr[ptr_num[ptr_name]];
        } else if(command == "calli") {
            string ptr_name;
            in >> ptr_name;
            if(!ptr_num.count(ptr_name)) 
                ptr_num[ptr_name] = ptr_num.size();
            int word = (CALLI << 24) | ptr_num[ptr_name];
        } else {
            int ccod = cmd[command]; // cmd code
            int cfmt = fmt[ccod]; // cmd fmt
            string r1, r2;
            int a1, r1n, r2n;
            int word = 0;
            switch(cfmt) {
                case RM:
                    in >> r1 >> a1;
                    r1 = r1.substr(1, r1.size()-1);
                    r1n = stoi(r1);
                    word = (ccod << 24) | (r1n << 20) | a1;
                break;
                case RR:
                    in >> r1 >> r2 >> a1;
                    r1 = r1.substr(1, r1.size()-1);
                    r2 = r2.substr(1, r2.size()-1);
                    r1n = stoi(r1);
                    r2n = stoi(r2);
                    word = (ccod << 24) | (r1n << 20) | (r2n << 20) | a1;
                break;
                case RI:
                    in >> r1 >> a1;
                    r1 = r1.substr(1, r1.size()-1);
                    r1n = stoi(r1);
                    word = (ccod << 24) | (r1n << 20) | a1;
                break;
                case J:
                    in >> a1;
                    word = (ccod << 24) | a1;
                break;
            }
            mem[read_addr++] = word;
            //printf("%s %d %d\n", command.c_str(), ccod, word);
        }
    }
    for(int i = 0; i < read_addr; i++) {
        if((mem[i]>>24) == CALLI) {
            mem[i] = (mem[i]&0xFF000000) | ptr_addr[mem[i]&0x000FFFFF];
        }
    }
    do {
        int word = mem[reg[15]];
        char r1, r2;
        int ins, a, m;
        ins = word >> 24;
        r1 = (word & 0x00F00000) >> 20;
        r2 = (word & 0x000F0000) >> 16;
        a  = (word & 0x000FFFFF);
        m  = (word & 0x0000FFFF);
        switch(fmt[ins]) {
            case RR:
            break;
            case RM:
            break;
            case RI:
                (( void(*)(char, int) )commands[ins]) (r1, a);
            break;
            case J:
            break;
        }
        reg[15]++;
        //printf("%d %d %d\n", reg[15], word, ins);
    } while(reg[15] != read_addr);
}