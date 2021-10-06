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
    vector<bool> l1 = {false, false, false, false, false, false, false, false};
    vector<bool> l2 = {false, false, false, false};
    vector<bool> output = {false, false, false, false};
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

    //Check Verticals
    l1[0] = logic.XOR(seen[0], seen[2]); // Left different
    l1[1] = logic.NOT(l1[0]);            //Left same, same as using an XNOR from the same inputs
    l1[2] = logic.XOR(seen[1], seen[3]); // Right different
    l1[3] = logic.NOT(l1[2]);            //Right same, same as using an XNOR from the same inputs
    l1[4] = logic.XOR(seen[0], seen[1]); // Top different
    l1[5] = logic.NOT(l1[4]);            //Top same, same as using an XNOR from the same inputs
    l1[6] = logic.XOR(seen[2], seen[3]); // Bottom different
    l1[7] = logic.NOT(l1[6]);            //Bottom same, same as using an XNOR from the same inputs

    //Begin comparisons
    l2[0] = logic.AND(l1[1], l1[3]); // Filled or vertical
    l2[1] = logic.AND(l1[0], l1[2]); // Horizontal or diagonal
    l2[2] = logic.AND(l1[4], l1[6]); // Vertical or diagonal
    l2[3] = logic.AND(l1[5], l1[7]); // Filled or horizontal

    //Determine pattern
    output[0] = logic.AND(l2[0], l2[2]); //Vertical
    output[1] = logic.AND(l2[0], l2[3]); //Filled
    output[2] = logic.AND(l2[1], l2[2]); //Diagonal
    output[3] = logic.AND(l2[1], l2[3]); //Horizontal

    cout << "Vertical: " << output[0]
         << "\nFilled: " << output[1]
         << "\nDiagonal: " << output[2]
         << "\nHorizontal: " << output[3];
}