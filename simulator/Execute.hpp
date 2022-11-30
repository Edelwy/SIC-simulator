#include "Command.hpp"
#include <iostream>
#include <string>
using namespace std;

// *************** CODE EXECUTION ************** //

void execute_F1(int opcode) {
    
}

void execute_F2(int opcode, int r1, int r2) {
    F2 c(r1, r2);
    //cout << "Smo v execute: " << r1 << " " << r2;

    switch(opcode) {
        case ADDR:      {c.ADDR();   break; }
        case SUBR:      {c.SUBR();   break; }
        case DIVR:      {c.DIVR();   break; }
        case COMPR:     {c.COMPR();  break; }
        case MULR:      {c.MULR();   break; }
        case SHIFTL:    {c.SHIFTL(); break; }
        case SHIFTR:    {c.SHIFTR(); break; }
        case RMO:       {c.RMO();    break; }
        case CLEAR:     {c.CLEAR();  break; }
        case TIXR:      {c.TIXR();   break; }
    }
}

void execute_FSIC(int opcode, int x, int UN) {
    
}

void execute_F3(int opcode, int ni, int x, int UN) {
    
}

void execute_F4(int opcode, int ni, int x, int UN) {
    
}


