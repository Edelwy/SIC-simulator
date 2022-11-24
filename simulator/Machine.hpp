#include "Register.hpp"
#include "Pomnilnik.hpp"
#include "Opcode.hpp"
#include <iostream>
#include <cstdlib>
#define MAX_ADRESS 32768
using namespace std;

//REGISTRI:  
//1. PARAMETER: INDEKS, 2. PARAMETER: VREDNOST
static Register A;
static Register X;
static Register L;
static Register B;
static Register S;
static Register T;
static Register F;
static Register PC;
static Register SW;
static Register* registri[9] = {&A,&X,&L,&B,&S,&T,&F,&PC,&SW};

//POMNILNIK:
static Pomnilnik pomnilnik; 
static InputDev std_in(0);
static OutputDev std_out(1);
static OutputDev std_err(2);




