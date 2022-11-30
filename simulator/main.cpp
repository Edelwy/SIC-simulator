#include "Executer.hpp"
#include <iostream>
#include <cstdio>

extern int execute();

int main() {

    // TESTIRANJE REGISTROV:
    //X.set_value(30);
    //Register &tmp = reg(1); // REFERENCE NINA: HOCEMO ISTEGA
    //cout << "vrednost registra tmp: " << (int) tmp.get_value() << "\n"; tmp.set_value(20);
    //cout << "vrednost registra X: " << (int) X.get_value() << "\n";

    // TESTIRANJE POMNILNIKA:
    //unsigned char testna_vrednost = 5;
    //A.set_value(testna_vrednost); // LDCH #5 
    //unsigned char addr = pomnilnik.get_address(); // ukaz STCH
    //pomnilnik.set_byte(addr, A.get_value()); // ukaz STCH

    //cout << "vrednost registra A: " << A.get_value() << "\n";
    //cout << "naslov: " << addr << "\n";
    //cout << "vrednost BYTE v pomnilniku: " << (int) pomnilnik.get_byte(addr) << "\n";

    // TESTIRANJE ZA WORD:
    //pomnilnik.set_byte(addr + 1, 5);
    //pomnilnik.set_byte(addr + 2, 6);
    //cout << "vrednost BYTE v pomnilniku: " << (int) pomnilnik.get_byte(addr + 1) << "\n";
    //cout << "vrednost BYTE v pomnilniku: " << (int) pomnilnik.get_byte(addr + 2) << "\n";
    //cout << "vrednost WORD v pomnilniku: " << (unsigned int) pomnilnik.get_word(addr) << "\n";

    //pomnilnik.set_byte(addr, '0');
    //cout << "vrednost BYTE v pomnilniku: " << (unsigned int) pomnilnik.get_byte(addr)<< " na adresi: " << addr << "\n";
    //pomnilnik.set_word(addr, 2222222222); // prevelik int
    //cout << "vrednost WORD v pomnilniku: " << (unsigned int) pomnilnik.get_word(addr) << "\n";
    //cout << "vrednost MP v pomnilniku: " << pomnilnik.MP << "\n";

    //TESTIRANJE I/O:
    //unsigned char in = std_in.read();
    //OutputDev test_out(4); 
    //std_out.write(in);
    //test_out.write(in);
    //OutputDev test_out(2);
    //test_out.write('3');

   
    //VALIDATING CODE:
    //cout << "opcode NAME: " << get_name(LDA) << "\n";
    //opcodes opcode = TIO;
    //not_implemented("TEST");
    //not_implemented("LDA");

    //valid_code(STF);
    //valid_code(TIO);
    //valid_code(0x15);
    //cout << get_directive_name(-6);
    
    //EXECUTING TEST:
    // cout << get_opcode_name(opcode) << "\nBIT NI: " << ni << "\nUN: " << UN << "\n\n";
    PC.set_value(2);

    // TIP1:
    unsigned char ukaz1 = TIO; 
    pomnilnik.set_byte(2, ukaz1);

    // TIP2: R1 = 2 R2 = 4
    unsigned char ukaz21 = ADDR;
    unsigned char ukaz22 = 0x24;
    pomnilnik.set_byte(3, ukaz21);
    pomnilnik.set_byte(4, ukaz22);

    // TIPSIC: X = 1 UN = 14
    /*unsigned char ukaz31 = STA;
    unsigned char ukaz32 = 0x80;
    unsigned char ukaz33 = 0x0E;
    pomnilnik.set_byte(5, ukaz31);
    pomnilnik.set_byte(6, ukaz32);
    pomnilnik.set_byte(7, ukaz33);

    // TIP4: NI = 01 X = 0 ADDRESS = 262145
    unsigned char ukaz41 = STA + 1;
    unsigned char ukaz42 = 0x14;
    unsigned char ukaz43 = 0;
    unsigned char ukaz44 = 0x01;
    pomnilnik.set_byte(8, ukaz41);
    pomnilnik.set_byte(9, ukaz42);
    pomnilnik.set_byte(10, ukaz43);
    pomnilnik.set_byte(11, ukaz44);

    // TIP3: neposredno naslavljanje NI: 01 X = 1 OFFSET = 1025
    unsigned char ukaz51 = LDL + 1;
    unsigned char ukaz52 = 0x84;
    unsigned char ukaz53 = 0x01;
    pomnilnik.set_byte(12, ukaz51);
    pomnilnik.set_byte(13, ukaz52);
    pomnilnik.set_byte(14, ukaz53);

    // TIP3: bazno naslavljanje NI: 10 X = 1 OFFSET = 1035
    B.set_value(10);
    unsigned char ukaz61 = LDS + 2;
    unsigned char ukaz62 = 0xC4;
    unsigned char ukaz63 = 0x01;
    pomnilnik.set_byte(15, ukaz61);
    pomnilnik.set_byte(16, ukaz62);
    pomnilnik.set_byte(17, ukaz63);

    // TIP3: PC relativno naslavljanje NI: 11 X = 0 OFFSET: 1046
    unsigned char ukaz71 = LDT + 3;
    unsigned char ukaz72 = 0x24;
    unsigned char ukaz73 = 0x01;
    pomnilnik.set_byte(18, ukaz71);
    pomnilnik.set_byte(19, ukaz72);
    pomnilnik.set_byte(20, ukaz73);

    // TIP3: napačno naslavljanje
    //unsigned char ukaz81 = LDA + 1;
    //unsigned char ukaz82 = 0x64;
    //unsigned char ukaz83 = 0x01;
    //pomnilnik.set_byte(21, ukaz81);
    //pomnilnik.set_byte(22, ukaz82);
    //pomnilnik.set_byte(23, ukaz83);*/

    
    L.set_value(5);
    S.set_value(2);
    execute();
    execute();
    cout << " " << (int) S.get_value() << "\n";
    
    return 0;
}
