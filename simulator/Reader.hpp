#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static ifstream get_file() {
    string file_name;
    cout << "PROGRAM NAME: ";
    cin >> file_name;
    ifstream file(file_name);

    return file;
}

int hex(unsigned char byte) {
    switch (byte) {
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    case '0': return 0;
    default: return -1; }
}

static string read_line(ifstream& file) {
    string line;
    getline(file, line);
    return line;
}

static string read_string(ifstream& file) {
    string str;
    file >> str;
    return str;
}

static unsigned char read_byte(ifstream& file) {
    unsigned char byte;
    unsigned int ch1 = hex(file.get()) << 4;
    unsigned int ch2 = hex(file.get());

    byte = ch1 + ch2;
    //cout << "BYTE: " << (int) byte << "\n";
    return byte;
}

static unsigned int read_word(ifstream& file) {
    unsigned int word = 0;
    unsigned int ch1 = hex(file.get()) << 20;
    unsigned int ch2 = hex(file.get()) << 16;
    unsigned int ch3 = hex(file.get()) << 12;
    unsigned int ch4 = hex(file.get()) << 8;
    unsigned int ch5 = hex(file.get()) << 4;
    unsigned int ch6 = hex(file.get());

    word = ch1 + ch2 + ch3 + ch4 + ch5 + ch6;
    //cout << "WORD: " << (int) word << "\n";
    return word;
}
