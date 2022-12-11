#include "Loader.hpp"
#include <iostream>
#include <cstdio>
extern ofstream log;

extern void start();
extern void stop();

int main() {

    load_obj();
    int steps;
    cout << "STEPS: ";
    cin >> steps;
    start(steps);
    log << "REGISTER A: " << A.get_value() << "\n";
    log << "REGISTER X: " << X.get_value() << "\n";
    log << "REGISTER S: " << S.get_value() << "\n";
    log << "REGISTER L: " << L.get_value() << "\n";
    log << "REGISTER B: " << B.get_value() << "\n";
    log << "REGISTER T: " << T.get_value() << "\n";
    log << "REGISTER SW: " << SW.get_value() << "\n";
    log << "REGISTER PC: " << PC.get_value() << "\n";
    return 0;
}
