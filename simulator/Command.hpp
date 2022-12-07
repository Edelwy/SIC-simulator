#include "Machine.hpp"
#include <iostream>
#include <string>
using namespace std;

class Command {

};

class F1: public Command {
    
    public: void FLOAT() {
        not_implemented("FLOAT");
    }

    public: void FIX() {
        not_implemented("FIX");
    }

    public: void NORM() {
        not_implemented("NORM");
    }

    public: void SIO() {
        not_implemented("SIO");
    }

    public: void TIO() {
        not_implemented("TIO");
    }

    public: void HIO() {
        not_implemented("HIO");
    }
};

class F2: public Command { 

    public: 
        int r1;
        int r2;
        int val1;
        int val2;

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

class FSIC34: public Command { 

    public: int operand;

        FSIC34(int op) {
            this->operand = op;
        }

    public: void STA() {
        pomnilnik.set_word(operand, A.get_value());
    }

    public: void STX() {
        pomnilnik.set_word(operand, X.get_value());
    }

    public: void STL() {
        pomnilnik.set_word(operand, L.get_value());
    }

    public: void STB() {
        pomnilnik.set_word(operand, B.get_value());
    }

    public: void STS() {
        pomnilnik.set_word(operand, S.get_value());
    }

    public: void STF() {
        pomnilnik.set_word(operand, F.get_value());
    }

    public: void STT() {
        pomnilnik.set_word(operand, T.get_value());
    }

    public: void STSW() {
        pomnilnik.set_word(operand, SW.get_value());
    }

    public: void STCH() {
        unsigned char byte = (A.get_value() & 0x000000FF);
        pomnilnik.set_byte(operand, byte);
    }

    public: void JEQ() {
        if(SW.get_value() == 0x40) PC.set_value(operand);
    }

    public: void JGT() {
        if(SW.get_value() == 0x80) PC.set_value(operand);
    }

    public: void JLT() {
        if(SW.get_value() == 0x00) PC.set_value(operand);
    }

    public: void J() {
        PC.set_value(operand);
    }

    public: void JSUB() {
        L.set_value(PC.get_value());
        PC.set_value(operand);
    }

    public: void RSUB() {
        PC.set_value(L.get_value());
    }

    public: void LDA() {
        A.set_value(operand);
    }

    public: void LDX() {
        X.set_value(operand);
    }

    public: void LDL() {
        L.set_value(operand);
    }

    public: void LDB() {
        B.set_value(operand);
    }

    public: void LDS() {
        S.set_value(operand);
    }

    public: void LDF() {
        F.set_value(operand);
    }

    public: void LDT() {
        T.set_value(operand);
    }

    public: void LDCH() {
        unsigned char byte = (operand & 0x000000FF);
        A.set_value(byte);
    }

    public: void ADD() {
        A.set_value(A.get_value() + operand);
    }

    public: void SUB() {
        A.set_value(A.get_value() - operand);
    }

    public: void MUL() {
        A.set_value(A.get_value() * operand);
    }

    public: void DIV() {
        A.set_value(A.get_value() * operand);
    }

    public: void AND() {
        A.set_value(A.get_value() & operand);
    }

    public: void OR() {
        A.set_value(A.get_value() | operand);
    }

    public: void COMP() {
        if(A.get_value() > operand) SW.set_value(0x80);
        if(A.get_value() < operand) SW.set_value(0x00);
        if(A.get_value() == operand) SW.set_value(0x40);
    }

    public: void TIX() {
        int valX = X.get_value();
        if(valX < operand) X.set_value(valX + 1);
    }

    public: void RD() {
        if(operand == 0) {
            unsigned char val = std_in.read();
            A.set_value(val);
        } else {
            InputDev dev_in(operand);
            unsigned char val = dev_in.read();
            A.set_value(val);
        }
    }

    public: void WD() {
        if(operand == 1) {
            int val = A.get_value();
            std_out.write(val);
        } else {
            OutputDev dev_out(operand);
            int val = A.get_value();
            dev_out.write(val);
        }
    }

    public: void TD() {
        if(operand > MAX_DEV) throw invalid_argument("DEVICE IS OUT OF RANGE");
    }

    public: void ADDF() {
        not_implemented("ADDF");
    }

    public: void SUBF() {
        not_implemented("SUBF");
    }

    public: void MULF() {
        not_implemented("MULF");
    }

    public: void DIVF() {
        not_implemented("DIVF");
    }

    public: void COMPF() {
        not_implemented("COMPF");
    }

    public: void LPS() {
        not_implemented("LPS");
    }

    public: void STI() {
        not_implemented("STI");
    }

    public: void SSK() {
        not_implemented("SSK");
    }
};
