#include <cstdbool>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MAX_DEV 255

class Device {

    public: int dev_no;
};

class InputDev: public Device {

    public: string file_name;

    public: InputDev(int n) {
            this->dev_no = n;
            this->file_name = "dev_" + to_string(this->dev_no);
        }
    
    public: unsigned char read() { 
        
        unsigned char input; 

        if(this->dev_no == 0) {
            cin >> input;
        } else {
            ifstream file(file_name, ios::app);
            input = file.get();
            file.close();
        }

        return input;
    }

};

class OutputDev: public Device {

    public: string file_name;

    public: OutputDev(int n) {
            this->dev_no = n;
            this->file_name = "dev_" + to_string(this->dev_no);
        }
    
    public: void write(unsigned char output) { 
        
        if(this->dev_no == 1) {
            cout << output;
        } else {
            if(this->dev_no == 2) file_name = "error_log";
            ofstream file(file_name, ios::app);
            file << output;
            file.close();
        }
    }

};

static InputDev std_in(0);
static OutputDev std_out(1);
static OutputDev std_err(2);