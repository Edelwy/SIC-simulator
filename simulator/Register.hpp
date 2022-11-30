class Register {
    
    private: unsigned char value = 0;
    public: unsigned char get_value() { return value; }
    public: void set_value(unsigned char v) { this->value = v; }

};

static Register A;
static Register X;
static Register L;
static Register B;
static Register S;
static Register T;
static Register F;
static Register PC;
static Register SW;

static Register& reg(int i) {
    switch(i) { 
    case 1: return X;
    case 2: return L;
    case 3: return B;
    case 4: return S;
    case 5: return T;
    case 6: return F;
    case 7: return PC;
    case 8: return SW; 
    default: return A; }
}