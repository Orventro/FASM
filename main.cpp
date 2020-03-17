#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include "codes.h"
#include "instructions.h"

using namespace std;

map<string, int> ptr_addr;

void reg_dump() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%d ", reg[i*4+j]);
        printf(" ");
    }
    printf("\n");
}

void stk_dump(int n) {
    for(int i = reg[14]; i < reg[14]+n; i++) printf("%d ", mem[i]);
    printf("\n");
}

bool sort_str(pair<string, int> &a, pair<string, int> &b) {
    return a.first.size() > b.first.size();
}

int main() {
    prepare_codes();
    prepare_instructions();

    // preprocess
    fstream fin("input.fasm", fstream::in);
    string input;
    int lin_num = 0;
    while(fin.good()) {
        string line;
        getline(fin, line);
        input += line + '\n';
        istringstream strm(line);
        bool b = 0;
        while(strm.good()) {
            string word;
            strm >> word;
            if(word.back() == ':') {
                word = word.substr(0, word.size()-1);
                ptr_addr[word] = lin_num - ptr_addr.size();
                b = 1;
            } else if(b && word.front() != ';') {
                lin_num++;
                b = 0;
            }
        }
        lin_num++;
    }
    vector<pair<string, int>> psi;
    for(auto a : ptr_addr) psi.push_back({a.first, a.second});
    sort(psi.begin(), psi.end(), sort_str);
    for(auto a : psi) {
        while(input.find(a.first) != string::npos) {
            input.replace(input.find(a.first), a.first.size(), to_string(a.second));
        }
    }
    
    // compile
    istringstream in(input);
    int read_addr = 0;
    while(in.good()) {
        string command;
        in >> command;
        char c;
        if(command.size() == 0) break;
        if(command.front() == ';') {
            while(in.peek() != '\n' && in.good()) 
                in.get(c);
            in >> c;
            continue;
        } else if(command.back() == ':') {
            continue;
        } else if(command == "end") {
            in >> reg[15];
        } else if(command == "ret") {
            int word = 0;
            string shift;
            in >> shift;
            word = (cmd["ret"] << 24) | stoi(shift);
            mem[read_addr++] = word;
        } else if(command == "call") {
            int ccod = cmd[command];
            int a1, r1n, r2n;
            string r1, r2;
            in >> r1 >> r2;
            r1 = r1.substr(1, r1.size()-1);
            r2 = r2.substr(1, r2.size()-1);
            r1n = stoi(r1);
            r2n = stoi(r2);
            mem[read_addr++] = (ccod << 24) | (r1n << 20) | (r2n << 16);
        } else if(command == "word") {
            read_addr++;
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
                    in >> a1;
                    word = (ccod << 24) | a1;
                break;
            }
            mem[read_addr++] = word;
        }
    }
    
    // run
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
        reg[15]++;
    } while(reg[15] != read_addr);
}