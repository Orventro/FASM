#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "codes.h"

using namespace std;

int reg[16];
stack<int> stk;
int mem[2<<20];
map<string, int> ptr_num;
map<int, int> ptr_addr;

void end(){
    exit(0);
}

void syscall(char regnum, int op) {
    switch(op) {
        case halt:
            exit(op);
        break;
        case scanint:
            scanf("%d", reg[regnum]);
        break;
        case scandouble:

        break;
        case printint:
            printf("%d\n", reg[regnum]);
        break;
        case printdouble:

        break;
        case getchar:
        
        break;
        case putchar:

        break;
    }
}

int main() {
    fstream in("input.fasm", fstream::in);
    while(in.good()) {
        string command;
        in >> command;
        if(s.back() == ':') {
            // function declaration

        } else {
            int ccod = cmd[command]; // cmd code
            int cfmt = fmt[ccod]; // cmd fmt
            switch(cfmt) {
                case RM:
                    string r1, a1;
                    in >> r1 >> a1;
                break;
                case RR:
                    string r1, r2, m1;
                    in >> r1 >> r2 >> m1;
                break;
                case RI:
                    string r1, o1;
                    in >> r1 >> o1;
                break;
                case J:
                    string a1;
                    in >> a1;
                break;
            }
        }
    }   
}