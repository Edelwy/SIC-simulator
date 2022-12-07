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
    } 
}

static void stop() {
    cpu.running = false;
}

static void start(int k) {
    cpu.running = true;
    cpu.run(&timer_tick, 0, k);
}

extern void step(int i, int k) {
    if(k == i && cpu.running) {
        stop();
        while(cin.get() != ' ') cout << "PRESS SPACE FOR EACH STEP\n PRESS ENTER TO CONTINUE\n";
        start(k);
    }
}


