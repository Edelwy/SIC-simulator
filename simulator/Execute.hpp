#include "Command.hpp"
#include <iostream>
#include <string>
#include <cstdbool>
using namespace std;

// *************** CODE EXECUTION ************** //

bool execute_F1(int opcode) {
    F1 c;
    switch(opcode) {
        case FIX:       {c.FIX();    break; }
        case FLOAT:     {c.FLOAT();  break; }
        case NORM:      {c.NORM();   break; }
        case SIO:       {c.SIO();    break; }
        case HIO:       {c.HIO();    break; }
        case TIO:       {c.TIO();    break; }
        default: return false;
    }   return true;
}

bool execute_F2(int opcode, int r1, int r2) {
    F2 c(r1, r2);
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
        default: return false;
    }   return true;
}

bool execute_FSIC34(int opcode, int ni, int UN) {

    int operand = pomnilnik.get_word(UN); //SIC in NI: 11
    if(ni == 0x01) operand = UN;
    if(ni == 0x02) operand = pomnilnik.get_word(operand);
    cout << "UN: " << UN << "\n";
    cout << "operand: " << operand << "\n";

    FSIC34 c(operand);
    switch(opcode) {
        case STA:	{c.STA();   break; }
        case STX:	{c.STX();   break; }
        case STL:	{c.STL();   break; }
        case STCH:	{c.STCH();  break; }
        case STB:	{c.STB();   break; }
        case STS:	{c.STS();   break; }
        case STF:	{c.STF();   break; }
        case STT:	{c.STT();   break; }
        case STSW:	{c.STSW();  break; }
        
        case JEQ:	{c.JEQ();   break; }
        case JGT:	{c.JGT();   break; }
        case JLT:	{c.JLT();   break; }
        case J:		{c.J();     break; }
        case RSUB:	{c.RSUB();  break; }
        case JSUB:	{c.JSUB();  break; }
    
        case LDA:	{c.LDA();   break; }
        case LDX:	{c.LDX();   break; }
        case LDL:	{c.LDL();   break; }
        case LDCH:	{c.LDCH();  break; }
        case LDB:	{c.LDB();   break; }
        case LDS:	{c.LDS();   break; }
        case LDF:	{c.LDF();   break; }
        case LDT:	{c.LDT();   break; }
        
        case ADD:	{c.ADD();   break; }
        case SUB:	{c.SUB();   break; }
        case MUL:	{c.MUL();   break; }
        case DIV:	{c.DIV();   break; }
        case AND:	{c.AND();   break; }
        case OR:	{c.OR();    break; }
        case COMP:	{c.COMP();  break; }
        case TIX:	{c.TIX();   break; }
        
        case RD:	{c.RD();    break; }
        case WD:	{c.WD();    break; }
        case TD:	{c.TD();    break; }
        
        case ADDF:	{c.ADDF();  break; }
        case SUBF:	{c.SUBF();  break; }
        case MULF:	{c.MULF();  break; }
        case DIVF:	{c.DIVF();  break; }
        case COMPF: {c.COMPF(); break; }
        
        case LPS:	{c.LPS();   break; }
        case STI:	{c.STI();   break; }
        case SSK:	{c.SSK();   break; }
        default: return false;
    }   return true;
}




