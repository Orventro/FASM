#include <map>
#include <string>

using namespace std;

enum code {
    HALT = 0,
    SYSCALL = 1,
    ADD = 2,
    ADDI = 3,
    SUB = 4,
    SUBI = 5,
    MUL = 6,
    MULI = 7,
    DIV = 8,
    DIVI = 9,
    LC = 12,
    SHL = 13,
    SHLI = 14,
    SHR = 15,
    SHRI = 16,
    AND = 17,
    ANDI = 18,
    OR = 19,
    ORI = 20,
    XOR = 21,
    XORI = 22,
    NOT = 23,
    MOV = 24,
    ADDD = 32,
    SUBD = 33,
    MULD = 34,
    DIVD = 35,
    ITOD = 36,
    DTOI = 37,
    PUSH = 38,
    POP = 39,
    CALL = 40,
    CALLI = 41,
    RET = 42,
    CMP = 43,
    CMPI = 44,
    CMPD = 45,
    JMP = 46,
    JNE = 47,
    JEQ = 48,
    JLE = 49,
    JL = 50,
    JGE = 51,
    JG = 52,
    LOAD = 64,
    STORE = 65,
    LOAD2 = 66,
    STORE2 = 67,
    LOADR = 68,
    LOADR2 = 69,
    STORER = 70,
    STORER2 = 71
};

enum syscalls {
    SCANINT     = 100,
    SCANDOUBLE  = 101,
    PRINTINT    = 102,
    PRINTDOUBLE = 103,
    GETCHAR     = 104,
    PUTCHAR     = 105
};

enum format{
    RM = 100001, // load  r0 1232
    RR = 100002, // mov   r1 r2 0
    RI = 100003, // ori   r2 64
    J  = 100004  // calli 3121
};

extern map<string, int> cmd;
extern int fmt[100];

void prepare();