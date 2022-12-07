#include <iostream>
#include <iostream>
#include <chrono>
#include <thread>
static void step(int i, int k);

#define MAX_SPEED 100000000 
using namespace std;

class CPU {

    public:
        int period;      // PERIOD IN MILISECONDS
        int repeat;      // LOOP REPEAT COUNT
        bool running = false;

        CPU(int period, int repeat) {
            this->period = period;
            this->repeat = repeat;
        }

    public: void set_speed(int Hz) {  
        if(Hz > MAX_SPEED) Hz = MAX_SPEED;
        repeat = (Hz + 99) / 100;     // PONOVITVE
        period = 1000 * repeat / Hz;  // SEKUNDE * 1000
    }

    public: int get_speed() {
        return 1000 / period * repeat;
    }

    public: void run(void (*task)(), int delay, int k) {
        int indeks = 1;
        
        while(running) {
            task();
            step(indeks, k);
            this_thread::sleep_for(chrono::milliseconds(period)); // ZAMIK
            indeks++;
        }
    };
};

static CPU cpu(10, 1);

