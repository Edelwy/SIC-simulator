#include "Register.hpp"
#include <iostream>
using namespace std;


//REGISTRI:  
//1. PARAMETER: INDEKS, 2. PARAMETER: VREDNOST
static Register A (0, 0);
static Register X (1, 0);
static Register L (2, 0);
static Register B (3, 0);
static Register S (4, 0);
static Register T (5, 0);
static Register F (6, 0);
static Register PC (7, 0);
static Register SW (8, 0);
static Register* registri[9] = {&A,&X,&L,&B,&S,&T,&F,&PC,&SW};

/*static Register get_reg(int i) {
    return registri[i];
}*/

int main() {
    cout << "naslov registra X: " << &X << "\n";
    cout << "naslov registra tmp: " << registri[1] << "\n";

    
    Register &tmp = *(registri[1]);
    tmp.set_value(20);
    cout << "vrednost registra X: " << X.get_value() << "\n";
    cout << "vrednost registra tmp: " << tmp.get_value() << "\n";

}

//POMNILNIK:



