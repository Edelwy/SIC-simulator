#include "Machine.hpp"
#include <iostream>
#include <string>
using namespace std;

class Command {

};

class F1: public Command {

};

class F2: public Command { 

    public: 
        int r1;
        int r2;
        signed char val1;
        signed char val2;

        F2(int r1, int r2) {
            this->r1 = r1;
            this->r2 = r2;
            val1 = reg(r1).get_value();
            val2 = reg(r2).get_value();
        }

    public: void COMPR() {
        if(val1 > val2) SW.set_value(0x80);
        if(val1 < val2) SW.set_value(0x00);
        if(val1 == val2) SW.set_value(0x40);
    }

    public: void ADDR() {
        reg(r2).set_value(val1 + val2);
    }

    public: void SUBR() {
        reg(r2).set_value(val2 - val1);
    }

    public: void DIVR() {
        if(val1 == 0) return;
        reg(r2).set_value(val2 / val1);
    }

    public: void MULR() {
        reg(r2).set_value(val2 * val1);
    }

    public: void SHIFTL() {
        reg(r1).set_value(val1 << (r2 + 1));
    }

    public: void SHIFTR() {
        reg(r1).set_value(val1 >> (r2 + 1));
    }

    public: void RMO() {
        reg(r2).set_value(val1);
    }

    public: void CLEAR() {
        reg(r1).set_value(0);
    }  

    public: void TIXR() {
        int valX = X.get_value();
        if(valX < val1) X.set_value(valX + 1);
    }
};

class FSIC: public Command { 

      
};

class F3: public FSIC { 

      
};

class F4: public FSIC { 

       
};