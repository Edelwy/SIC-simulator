#include "Executer.hpp"
#include "CPU.hpp"
using namespace std;

extern CPU cpu;

bool timer_tick() {
    for(int i = 0; i < cpu.repeat; i++) {

        int old_PC = PC.get_value();
        execute();
        int new_PC = PC.get_value();

    //  PRIDEMO DO KONCA PROGRAMA:
        if(old_PC == new_PC) return true;
    }
    return false;
}

static void stop() {
    // IMPLEMENT
}

static void start() {
    cpu.run(&timer_tick, 0);
}

static bool is_running() {
    // IMPLEMENT
    return false;
}

