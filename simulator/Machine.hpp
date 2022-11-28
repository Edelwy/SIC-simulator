#include "Register.hpp"
#include "Pomnilnik.hpp"
#include "Opcode.hpp"
#include "Device.hpp"
#define MAX_ADRESS 32768
using namespace std;

//REGISTRI:  
//1. PARAMETER: INDEKS, 2. PARAMETER: VREDNOST
extern Register A;
extern Register X;
extern Register L;
extern Register B;
extern Register S;
extern Register T;
extern Register F;
extern Register PC;
extern Register SW;
extern Register* registrs[];

//POMNILNIK:
extern Pomnilnik pomnilnik; 
extern InputDev std_in;
extern OutputDev std_out;
extern OutputDev std_err;

//MNEMONIKI
extern int no_opcodes;
extern int no_directives;
extern string directive_names[];
extern string opcode_names[];




