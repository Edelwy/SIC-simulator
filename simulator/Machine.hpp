#include "Device.hpp"
#include "Register.hpp"
#include "Pomnilnik.hpp"
#include "Opcode.hpp"
#define MAX_ADRESS 1048576
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
extern Register& get_reg(int i);

//POMNILNIK:
extern Pomnilnik pomnilnik; 
extern InputDev std_in;
extern OutputDev std_out;
extern OutputDev std_err;

//MNEMONIKI:
extern int no_opcodes;
extern int no_directives;
extern bool not_implemented();
extern bool invalid_code();
extern string get_opcode_name();
extern string get_directive_name();




