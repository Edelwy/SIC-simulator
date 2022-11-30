#include "Executer.hpp"
#include "CPU.hpp"
using namespace std;

extern CPU cpu;

void timer_tick() {
    for(int i = 0; i < cpu.repeat; i++) {

        int old_PC = PC.get_value();
        execute();
        int new_PC = PC.get_value();

    //  PRIDEMO DO KONCA PROGRAMA:
        if(old_PC == new_PC) cpu.running = false;

    //  ROCNO USTAVIMO PROGRAM:
    } 
}

static void stop() {
    cpu.running = false;
}

static void start() {
    cpu.running = true;
    cpu.run(&timer_tick, 0);
}

static bool is_running() {
    return cpu.running;
}

