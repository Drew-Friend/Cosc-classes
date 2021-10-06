#include <string>
#include <vector>
#include <iostream>
using namespace std;

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

int main()
{
    Gates logic;
    vector<bool> seen = {false, false, false, false};
    vector<bool> l1 = {false, false, false, false};
    vector<bool> l2 = {false, false};
    bool output;
    char bleh;
    cout << "12\n34\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "Is square " << i + 1 << " full?  ";
        cin >> bleh;
        if (bleh == 'y')
        {
            seen[i] = true;
            continue;
        }
        seen[i] = false;
    }

    //Find diagonal lines
    l1[0] = logic.AND(seen[0], seen[3]); //   \ Black
    l1[1] = logic.NOR(seen[0], seen[3]); //   \ White
    l1[2] = logic.AND(seen[1], seen[2]); //   / Black
    l1[3] = logic.NOR(seen[1], seen[2]); //   / White

    //Make sure only one diagonal exists
    l2[0] = logic.AND(l1[0], l1[3]);
    l2[1] = logic.AND(l1[1], l1[2]);

    //If either diagonal is true, output true
    output = logic.OR(l2[0], l2[1]);

    cout << output;
}