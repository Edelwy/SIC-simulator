#include "Execute.hpp"
#include <iostream>
#include <string>
using namespace std;

// **************************** FETCH PHASE: *********************************//

static int fetch() {
    int addr = PC.get_value();
    unsigned char instruction_byte = pomnilnik.get_byte(addr);
    PC.set_value(addr + 1);
    return instruction_byte;
}

// ******************************* GET BITS: *********************************//

static int get_opcode(unsigned char byte) {
    int opcode = byte & 0xFC;
    return opcode;
}

static int get_ni(unsigned char byte) {
    int ni = byte & 0x03;
    //cout << "NI: " << ni << "\n";
    return ni;
}

static int get_x(unsigned char byte) {
    int x = (byte & 0x80) >> 7;
    //cout << "X: " << x << "\n";
    return x;
}

static int get_bp(unsigned char byte) {
    int bp = (byte & 0x60) >> 5;
    //cout << "BP: " << bp << "\n";
    return bp;
}

static int get_e(unsigned char byte) {
    int e = (byte & 0x10) >> 4;
    //cout << "E: " << e << "\n";
    return e;
}

static int get_r1(unsigned char byte) {
    int r1 = (byte & 0x000000F0) >> 4;
    return r1;
}

static int get_r2(unsigned char byte) {
    int r2 = byte & 0x0000000F;
    return r2;
}

static int get_offset_F3(unsigned byte2, unsigned byte3) {
    int val = (byte2 & 0x0F) << 8;
    val = val + byte3;
    return val;
}

static int get_addr_F4(unsigned byte2, unsigned byte3, unsigned byte4) {
    int val = (byte2 & 0x0F) << 16;
    val = val + (byte3 << 8) + byte4;
    return val;
}

static int get_addr_FSIC(unsigned byte2, unsigned byte3) {
    int val = (byte2 & 0x7F) << 8;
    val = val + byte3;
    return val;
}

// **************************** NASLAVLJANJE: *********************************//

int naslavljanje_F3(int offset, int bp) {
    int UN = offset;
    if(bp == 1) { if(offset >= 2048) offset = offset - 4096; UN = PC.get_value() + offset; } 
    if(bp == 2) UN = B.get_value() + offset;
    if(bp == 3) throw invalid_argument("BITA BP(11) UNDEFINED!");
    return UN;
}
// **************************** EXECUTE PHASE: ********************************//

extern bool execute_F1(int opcode);
extern bool execute_F2(int opcode, int r1, int r2);
extern bool execute_FSIC34(int opcode, int UN);

static int execute() {

    unsigned char byte1 = fetch();
    int opcode = get_opcode(byte1);
    int ni = get_ni(byte1);

    cout << "OPCODE: " << opcode_name(opcode) << "\n";
    valid_code(opcode);

    if((opcode >= FLOAT && opcode <= NORM) || (opcode >= SIO && opcode <= HIO)) {
        execute_F1(opcode);
        return 1;

    } else if(opcode >= ADDR && opcode <= TIXR) {
        unsigned char byte2 = fetch();
        int r1 = get_r1(byte2);
        int r2 = get_r2(byte2);
        execute_F2(opcode, r1, r2);
        return 2;

    } else if(ni == 0) { //SIC 
        unsigned char byte2 = fetch();
        unsigned char byte3 = fetch();
        int x = get_x(byte2);
        int UN = get_addr_FSIC(byte2, byte3);
        if(x == 1) UN = UN + X.get_value();

        execute_FSIC34(opcode, ni, UN);
        return 0; 

    } else {
        unsigned char byte2 = fetch();
        unsigned char byte3 = fetch();
        int x = get_x(byte2);
        int bp = get_bp(byte2);
        int e = get_e(byte2);

        if(bp == 0 && e == 1) {
            unsigned char byte4 = fetch();
            int UN = get_addr_F4(byte2, byte3, byte4);
            if(x == 1) UN = UN + X.get_value();

            execute_FSIC34(opcode, ni, UN);
            return 4;

        } else {
            int offset = get_offset_F3(byte2, byte3);
            int UN = naslavljanje_F3(offset, bp);
            if(x == 1) UN = UN + X.get_value();

            execute_FSIC34(opcode, ni, UN);
            return 3;
        }
    }
}


