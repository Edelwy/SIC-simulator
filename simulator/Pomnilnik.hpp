#include <cstdlib>
#include <string>
#define MAX_ADDRESS 32768
static int MP = 0;

class Pomnilnik {

    public:
        int size = MAX_ADDRESS;
        unsigned char mem[MAX_ADDRESS];

    public: int get_address() {
        int indeks = MP; 
        return indeks;
    }

    // METODE ZA BYTE OPERACIJE:
    public: unsigned char get_byte(int addr) {
        unsigned char val = mem[addr];
        return val; 
    }

    public: void set_byte(int addr, unsigned char val) {
        mem[addr] = val; 
        MP = MP + 1;
    }

    // METODE ZA WORD OPERACIJE:
    public: unsigned int get_word(int addr) {
        unsigned int val = 0;
        unsigned int byte_2 = mem[addr]<<16;
        unsigned int byte_3 = mem[addr + 1]<<8;
        unsigned int byte_4 = mem[addr + 2];
        
        val = byte_2 + byte_3 + byte_4;
        return val; 
    }

    public: int set_word(int addr, unsigned int val) {
        unsigned char byte_4 =  val & 0x000000ff;
        unsigned char byte_3 = (val & 0x0000ff00) >> 8;
        unsigned char byte_2 = (val & 0x00ff0000) >> 16;
        unsigned char byte_1 = (val & 0xff000000) >> 24;

        if(byte_1 != 0) return 1;
        
        mem[addr] = byte_2;
        mem[addr + 1] = byte_3;
        mem[addr + 2] = byte_4;
        MP = MP + 3;
        return 0;
    }
};