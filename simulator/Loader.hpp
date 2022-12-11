#include "Runner.hpp"
#include "Reader.hpp"
extern ofstream log;

static bool load_obj() {
    ifstream file = get_file();

    if(file.get() != 'H') return false;
    read_string(file); // IGNORIRAMO IME
    file.get();   // IGNORIRAMO WHITESPACE
    file.get();

    int start = read_word(file);
    int size = read_word(file);

    log << "PROGRAM: Start: " << start << " Length: " << size << "\n";
    file.get();
    char ch = file.get();

    while(ch == 'T') {
        int addr = read_word(file);
        int length = read_byte(file);

        while(length > 0) {
            if(addr < start || addr >= start + size) return false;
            unsigned char val = read_byte(file);
            pomnilnik.set_byte(addr, val);
            addr++;
            length--;
        }

        if(file.get() == '\r') file.get();
        ch = file.get();
    }

    if(ch != 'E') return false;
    PC.set_value(read_word(file));
    return true;
}
