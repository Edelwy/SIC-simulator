class Register {
    
    private: int value = 0;
    public: int get_value() { return value; }
    public: void set_value(int v) { this->value = v; }

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

static Register* registrs[9] = {&A,&X,&L,&B,&S,&T,&F,&PC,&SW};