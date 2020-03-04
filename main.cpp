#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include "codes.h"
#include "instructions.h"

using namespace std;

map<string, int> ptr_num;
vector<int> ptr_addr;

void reg_dump() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%d ", reg[i*4+j]);
        printf(" ");
    }
    printf("\n");
}

void stk_dump(int n) {
    for(int i = reg[14]; i > reg[14]-n; i--) printf("%d ", mem[i]);
    printf("\n");
}

int main() {
    prepare_codes();
    prepare_instructions();

    // compile
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
            ptr_addr.push_back(read_addr);
        } else if(command == "end") {
            string ptr_name;
            in >> ptr_name;
            reg[15] = ptr_addr[ptr_num[ptr_name]];
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
                    word = (ccod << 24) | (r1n << 20) | (r2n << 16) | a1;
                break;
                case RI:
                    in >> r1 >> a1;
                    r1 = r1.substr(1, r1.size()-1);
                    r1n = stoi(r1);
                    word = (ccod << 24) | (r1n << 20) | a1;
                break;
                case J:
                    string ptr_name;
                    in >> ptr_name;
                    if(!ptr_num.count(ptr_name)) 
                        ptr_num[ptr_name] = ptr_num.size();
                    word = (ccod << 24) | ptr_num[ptr_name];
                break;
            }
            mem[read_addr++] = word;
            //printf("%s %d %d\n", command.c_str(), ccod, word);
        }
    }
    for(int i = 0; i < read_addr; i++) {
        if(fmt[mem[i]>>24] == J) {
            // printf("jmp altered!\n");
            // printf("%d -> %d\n", mem[i]&0x000FFFFF, ptr_addr[mem[i]&0x000FFFFF]);
            mem[i] = (mem[i]&0xFF000000) | ptr_addr[mem[i]&0x000FFFFF];
        }
    }
    // run
    do {
        // stk_dump(1);
        // printf("flag = %d\n", flag);
        int word = mem[reg[15]];
        char r1, r2;
        int ins, a, m;
        ins = word >> 24;
        r1 = (word & 0x00F00000) >> 20;
        r2 = (word & 0x000F0000) >> 16;
        a  = (word & 0x000FFFFF);
        m  = (word & 0x0000FFFF);
        // printf("ins = %d\n", ins);
        // reg_dump();
        // printf("%d %d\n", r1, r2);
        switch(fmt[ins]) {
            case RR:
                (( void(*)(char, char, int) )commands[ins]) (r1, r2, m);
            break;
            case RM:
                (( void(*)(char, int) )commands[ins]) (r1, a);
            break;
            case RI:
                (( void(*)(char, int) )commands[ins]) (r1, a);
            break;
            case J:
                (( void(*)(int) )commands[ins]) (a);
            break;
        }
        // reg_dump();
        reg[15]++;
        //printf("%d %d %d\n", reg[15], word, ins);
    } while(reg[15] != read_addr);
}