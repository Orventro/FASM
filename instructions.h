extern void *commands[256];
extern unsigned int reg[16];
extern unsigned int mem[2<<20];
extern unsigned int flag;

void prepare_instructions();

void add(char r1, char r2, int op); // 2 RR
void addd(char r1, char r2, int op); // 32 RR
void addi(char r1, int op); // 3 RI
void and_(char r1, char r2, int op); // 17 RR
void andi(char r1, int op); // 18 RI
void call(char r1, char r2, int op); // 40 RR
void calli(int op); // 41 J
void cmp(char r1, char r2, int op); // 43 RR
void cmpd(char r1, char r2, int op); // 45 RR
void cmpi(char r1, int op); // 44 RI
void div_(char r1, char r2, int op); // 8 RR
void divd(char r1, char r2, int op); // 35 RR
void divi(char r1, int op); // 9 RI
void dtoi(char r1, char r2, int op); // 37 RR
void halt(char r1, int op); // 0 RI
void itod(char r1, char r2, int op); // 36 RR
void jeq(int op); // 48 J
void jg(int op); // 52 J
void jge(int op); // 51 J
void jl(int op); // 50 J
void jle(int op); // 49 J
void jmp(int op); // 46 J
void jne(int op); // 47 J
void lc(char r1, int op); // 12 RI
void load(char r1, int op); // 64 RM
void load2(char r1, int op); // 66 RM
void loadr(char r1, char r2, int op); // 68 RR
void loadr2(char r1, char r2, int op); // 69 RR
void mov(char r1, char r2, int op); // 24 RR
void mul(char r1, char r2, int op); // 6 RR
void muld(char r1, char r2, int op); // 34 RR
void muli(char r1, int op); // 7 RI
void not_(char r1, int op); // 23 RI
void or_(char r1, char r2, int op); // 19 RR
void ori(char r1, int op); // 20 RI
void pop(char r1, int op); // 39 RI
void push(char r1, int op); // 38 RI
void ret(char r1, int op); // 42 RI
void shl(char r1, char r2, int op); // 13 RR
void shli(char r1, int op); // 14 RI
void shr(char r1, char r2, int op); // 15 RR
void shri(char r1, int op); // 16 RI
void store(char r1, int op); // 65 RM
void store2(char r1, int op); // 67 RM
void storer(char r1, char r2, int op); // 70 RR
void storer2(char r1, char r2, int op); // 71 RR
void sub(char r1, char r2, int op); // 4 RR
void subd(char r1, char r2, int op); // 33 RR
void subi(char r1, int op); // 5 RI
void syscall(char r1, int op); // 1 RI
void xor_(char r1, char r2, int op); // 21 RR
void xori(char r1, int op); // 22 RI