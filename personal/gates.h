class Gates
{
public:
    //True if both are true
    bool AND(bool arg1, bool arg2);
    //True if either is true
    bool OR(bool arg1, bool arg2);
    //True if input is false
    bool NOT(bool arg1);
    //True if exactly one input is true
    bool XOR(bool arg1, bool arg2);
    //Inverses
    //False if both are true
    bool NAND(bool arg1, bool arg2);
    //False if either are true
    bool NOR(bool arg1, bool arg2);
    //False if exactly one is true
    bool XNOR(bool arg1, bool arg2);
};