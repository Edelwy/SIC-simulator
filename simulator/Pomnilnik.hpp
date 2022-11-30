#include <cstdlib>
#define MAX_ADDRESS 1048576

class Pomnilnik {

    public:
        int size = MAX_ADDRESS;
        unsigned char mem[MAX_ADDRESS];
        int MP = 0;

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
    }

    // METODE ZA WORD OPERACIJE:
    public: unsigned int get_word(int addr) {
        unsigned int val = 0;
        unsigned int byte2 = mem[addr] << 16;
        unsigned int byte3 = mem[addr + 1] << 8;
        unsigned int byte4 = mem[addr + 2];
        
        val = byte2 + byte3 + byte4;
        return val; 
    }

    public: int set_word(int addr, unsigned int val) {
        unsigned char byte4 =  val & 0x000000FF;
        unsigned char byte3 = (val & 0x0000FF00) >> 8;
        unsigned char byte2 = (val & 0x00FF0000) >> 16;
        unsigned char byte1 = (val & 0xFF000000) >> 24;

        if(byte1 != 0) return 1;
        
        mem[addr] = byte2;
        mem[addr + 1] = byte3;
        mem[addr + 2] = byte4;
        return 0;
    }
};

static Pomnilnik pomnilnik; 
