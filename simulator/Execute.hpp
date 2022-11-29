#include "Machine.hpp"

static int fetch() {
    unsigned char addr = PC.get_value();
    unsigned char instruction_byte = pomnilnik.get_byte(addr);
    PC.set_value(addr + 1);
    return instruction_byte;
}

// *********** CODE DECONSTRUCTING ************ //
static int get_opcode(unsigned char byte) {
    int opcode = byte & 0x000000FC;
    return opcode;
}

static int get_ni(unsigned char byte) {
    int ni = byte & 0x00000003;
    return ni;
}

static int get_r1(unsigned char byte) {
    int r1 = (byte & 0x000000F0) >> 4;
    return r1;
}

static int get_r2(unsigned char byte) {
    int r2 = byte & 0x0000000F;
    return r2;
}


// *************** CODE EXECUTION ************** //
static void execute_FSIC(int opcode) {
}

static void execute_F1(int opcode) {
    
    //switch()
}

static void execute_F2(int opcode) {
    unsigned char byte_2 = fetch();
    int r1 = get_r1(byte_2);
    int r2 = get_r2(byte_2);
}

static void execute_F34(int opcode, int ni) {
}

// EXECUTE: PREBERE 1 BYTE
static void execute() {
    unsigned char byte_1 = fetch();
    int opcode = get_opcode(byte_1);
    int ni = get_ni(byte_1); 
    int type;

    if(opcode >= FLOAT && opcode <= TIO) type = 1;
    else if(opcode >= ADDR && opcode <= TIXR) type = 2;
    else if(ni == 0) type = 0; //SIC
    else type = 3;

    switch(type) {
        case 0: execute_FSIC(opcode);
        case 1: execute_F1(opcode);
        case 2: execute_F2(opcode);
        case 3: execute_F34(opcode, ni); 
    }
}

