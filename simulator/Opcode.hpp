#include "Device.hpp"
#define get_name(var) #var

// LOAD AND STORE: 
#define LDA     0x00;
#define LDX     0x04;
#define LDL     0x08;
#define STA     0x0C;
#define STX     0x10;
#define STL     0x14;

// ARITMETICNI UKAZI:
#define ADD     0x18;
#define SUB     0x1C;
#define MUL     0x20;
#define DIV     0x24;
#define COMP    0x28;
#define TIX     0x2C;

// JUMPS:
#define JEQ     0x30;
#define JGT     0x34;
#define JLT     0x38;
#define J       0x3C;

// BITNE OPERACIJE:
#define AND     0x40;
#define OR      0x44;

// SUBRUTINE:
#define JSUB    0x48;
#define RSUB    0x4C;

// LOAD IN STORE BYTE
#define LDCH    0x50;
#define STCH    0x54;

// FLOATING POINT ARITMETIKA:
#define ADDF    0x58;
#define SUBF    0x5C;
#define MULF    0x60;
#define DIVF    0x64;
#define COMPF   0x88;

// LOAD AND STORE:
#define LDB     0x68;
#define LDS     0x6C;
#define LDF     0x70;
#define LDT     0x74;
#define STB     0x78;
#define STS     0x7C;
#define STF     0x80;
#define STT     0x84;


#define LPS     0xD0;
#define STI     0xD4;
#define STSW    0xE8;

// I/O NAPRAVE:
#define RD      0xD8;
#define WD      0xDC;
#define TD      0xE0;

// SISTEMSKI UKAZI:
#define SSK     0xEC;

// UKAZI TIPA 1:
#define FLOAT   0xC0;
#define FIX     0xC4;
#define NORM    0xC8;
#define SIO     0xF0;
#define HIO     0xF4;
#define TIO     0xF8;

// UKAZI TIPA 2:
#define ADDR    0x90;
#define SUBR    0x94;
#define MULR    0x98;
#define DIVR    0x9C;
#define COMPR   0xA0;
#define SHIFTL  0xA4;
#define SHIFTR  0xA8;
#define RMO     0xAC;
#define SVC     0xB0;
#define CLEAR   0xB4;
#define TIXR    0xB8;


#define START   0;
#define END     1;
#define CSECT   2;
#define USE     3;
#define EXTREF  4;
#define EXTDEF  5;
#define ORG     6;
#define LTORG   7;
#define BASE    8;
#define NOBASE  9;
#define EQU     10;

// STORAGE:
#define RESB  0;
#define RESW  1;
#define RESF  2;
#define BYTE  3;
#define WORD  4;
#define FLOT  5;

// ERRORS:
static void not_implemented(string mnemonic) {
    
}