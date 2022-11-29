#include "Execute.hpp"

//FETCH AND EXECUTE:
extern int fetch();
extern int get_opcode(unsigned char byte);
extern int get_ni(unsigned char byte);
extern void execute();

extern void execute_FSIC(int opcode);
extern void execute_F1(int opcode);
extern void execute_F2(int opcode);
extern void execute_F34(int opcode, int ni);
