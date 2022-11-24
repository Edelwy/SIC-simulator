#include "Machine.hpp"
#include <iostream>
#include <cstdio>

int main() {

    // TESTIRANJE REGISTROV:

    //Register &tmp = *registri[1]; // REFERENCE NINA: HOCEMO ISTEGA
    //cout << "vrednost registra tmp: " << tmp.get_value() << "\n"; tmp.set_value(20);
    //cout << "vrednost registra X: " << X.get_value() << "\n";

    // TESTIRANJE POMNILNIKA:
    //unsigned char testna_vrednost = 5;
    //A.set_value(testna_vrednost); // LDCH #5 
    int addr = pomnilnik.get_address(); // ukaz STCH
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

    pomnilnik.set_byte(addr, 'A');
    cout << "vrednost BYTE v pomnilniku: " << (unsigned int) pomnilnik.get_byte(addr)<< " na adresi: " << addr << "\n";
    //pomnilnik.set_word(addr, 286335539); // prevelik int
    //cout << "vrednost WORD v pomnilniku: " << (unsigned int) pomnilnik.get_word(addr) << "\n";
    //cout << "vrednost MP v pomnilniku: " << MP << "\n";

    //TESTIRANJE I/O:
    unsigned char in = std_in.read();
    OutputDev test_out(4); 
    std_out.write(in);
    test_out.write(in);
    

}
