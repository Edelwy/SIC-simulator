#include <iostream>
#include <string>
using namespace std;

enum opcodes { 

//LOAD AND STORE: 
    LDA =   0x00, 
    LDX =   0x04,
    LDL =   0x08,
    STA =   0x0C,
    STX =   0x10,
    STL =   0x14,

//ARITMETICNI UKAZI:
    ADD =   0x18,
    SUB =   0x1C,
    MUL =   0x20,
    DIV =   0x24,
    COMP =  0x28,
    TIX =   0x2C,

//JUMPS:
    JEQ =   0x30,
    JGT =   0x34,
    JLT =   0x38,
    J =     0x3C,

//BITNE OPERACIJE:
    AND =   0x40,
    OR =    0x44,

//SUBRUTINE:
    JSUB =  0x48,
    RSUB =  0x4C,

//LOAD IN STORE BYTE
    LDCH =  0x50,
    STCH =  0x54,

//FLOATING POINT ARITMETIKA:
    ADDF =  0x58, // X
    SUBF =  0x5C, // X
    MULF =  0x60, // X
    DIVF =  0x64, // X
    COMPF = 0x88, // X

//LOAD AND STORE:
    LDB =   0x68,
    LDS =   0x6C,
    LDF =   0x70,
    LDT =   0x74,
    STB =   0x78,
    STS =   0x7C,
    STF =   0x80,
    STT =   0x84,

    LPS =   0xD0, // X
    STI =   0xD4, // X
    STSW =  0xE8,

//I/O NAPRAVE:
    RD =    0xD8,
    WD =    0xDC,
    TD =    0xE0,

//SISTEMSKI UKAZI:
    SSK =   0xEC, // X

//UKAZI TIPA 1:
    FLOAT = 0xC0, // X
    FIX =   0xC4, // X
    NORM =  0xC8, // X
    SIO =   0xF0,
    HIO =   0xF4,
    TIO =   0xF8,

//UKAZI TIPA 2:
    ADDR =  0x90,
    SUBR =  0x94,
    MULR =  0x98,
    DIVR =  0x9C,
    COMPR = 0xA0,
    SHIFTL = 0xA4,
    SHIFTR = 0xA8,
    RMO =   0xAC,
    SVC =   0xB0, // X
    CLEAR = 0xB4,
    TIXR =  0xB8, };

enum directives {

    START =  -0,
    END =    -1,
    ORG =    -2,
    BASE =   -3,
    NOBASE = -4,
    EQU =    -5,

//STORAGE:
    RESB = -6,
    RESW = -7,
    BYTE = -8,
    WORD = -9 };

static string opcode_names[] = {
    "LDA", "LDX", "LDL", "STA", "STX", "STL", "ADD", "SUB",
    "MUL", "DIV", "COMP", "TIX", "JEQ", "JGT", "JLT", "J",
    "AND", "OR", "JSUB", "RSUB", "LDCH", "STCH", "", "",
    "", "", "LDB", "LDS", "LDF", "LDT", "STB", "STS",
    "STF", "STT", "", "", "ADDR", "SUBR", "MULR", "DIVR",
    "COMPR", "SHIFTL", "SHIFTR", "RMO", "", "CLEAR", "TIXR", "",
    "", "", "", "", "", "", "RD", "WD",
    "TD", "", "STSW", "", "SIO", "HIO", "TIO", "" };

static string directive_names[] = {
    "START", "END", "ORG", "BASE", "NOBASE", "EQU",
    "RESB", "RESW", "BYTE", "WORD" };

int no_opcodes = sizeof(opcode_names) / sizeof(string); 
int no_directives = sizeof(directive_names) / sizeof(string);


// ------------ NAPAKE: ---------------- //
static int not_implemented(string mnemonic) {

    for (int i = 0; i <= no_opcodes; i++) 
        if(opcode_names[i] == mnemonic) return 0;

    for (int i = 0; i <= no_directives; i++) 
        if(directive_names[i] == mnemonic) return 1;

    cout << "MNEMONIC NOT IMPLEMENTED\n";
    return -1;
}

static string get_opcode_name(int code) {
    if((code / 4) > no_opcodes) return "";
    return opcode_names[code >> 2];
}


static string get_directive_name(int code) {
    if(code > 0 || code < -9) return "";
    return directive_names[-code];
}

static int valid_code(int code) {

    string mnemonic = get_opcode_name(code);
    if(mnemonic != "") return 0;

    mnemonic = get_directive_name(code);
    if(mnemonic != "") return 1;

    cout << "OPCODE IS INVALID\n";
    return -1;
}

