class Gates
{
public:
    //True if both are true
    bool AND(bool arg1, bool arg2) { return (arg1 && arg2); }
    //True if either is true
    bool OR(bool arg1, bool arg2) { return (arg1 || arg2); }
    //True if input is false
    bool NOT(bool arg1) { return !arg1; }
    //True if exactly one input is true
    bool XOR(bool arg1, bool arg2) { return NOT(AND(arg1, arg2) || NOR(arg1, arg2)); }

    //Inverses
    //False if both are true
    bool NAND(bool arg1, bool arg2) { return NOT(AND(arg1, arg2)); }
    //False if either are true
    bool NOR(bool arg1, bool arg2) { return NOT(OR(arg1, arg2)); }
    //False if exactly one is true
    bool XNOR(bool arg1, bool arg2) { return NOT(XOR(arg1, arg2)); }
};