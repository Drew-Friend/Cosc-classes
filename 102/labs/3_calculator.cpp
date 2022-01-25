/*
 Drew Friend
 9/1/21
 Basic Calculator
*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
string modKey = "MASDBmasdbx+-/|*";
/*
%=0; Multiply
%=1; Add
%=2; Subtract
%=3; Divide
%=4; Abs Value 
*/
int main()
{
    bool checkOne = true;
    bool checkTwo = true;
    int caseHandler;
    double numOne, numTwo;
    string inOne, inTwo, op;
    cout << "Input left operand:  ";
    cin >> inOne;
    //Checks to make sure the left operand is a number
    for (int i = 0; i < inOne.length(); i++)
    {
        if (!isdigit(inOne[i]))
        {
            cerr << "Invalid Left Operand";
            checkOne = false;
        }
    }
    //Continue only if operand 1 is a number
    if (checkOne)
    {
        numOne = stod(inOne);
        cout << "Input operation:  ";
        cin >> op;
        //Find operation in key list
        caseHandler = modKey.find(op);
        //Runs if operator not in key list
        if (caseHandler > modKey.length())
        {
            cerr << "Unknown Operation";
        }
        else
        {
            //Finds the operator
            caseHandler = caseHandler % 5;
            if (caseHandler != 4)
            //Run only if not abs. value
            {
                cout << "Input Right operand:  ";
                cin >> inTwo;
                //Check that operator 2 is a number
                for (int i = 0; i < inTwo.length(); i++)
                {
                    if (!isdigit(inTwo[i]))
                    {
                        cerr << "Invalid Right Operand";
                        checkTwo = false;
                    }
                }
            }
            //Continue only if operand 2 is a number
            if (checkTwo)
            {
                numTwo = stod(inTwo);
                switch (caseHandler)
                {
                case (0):
                    cout << "Result = " << numOne * numTwo;
                    break;
                case (1):
                    cout << "Result = " << numOne + numTwo;
                    break;
                case (2):
                    cout << "Result = " << numOne - numTwo;
                    break;
                case (3):
                    cout << "Result = " << numOne / numTwo;
                    break;
                case (4):
                    cout << "Result = " << abs(numOne);
                    break;
                default:
                    cerr << "Invalid Operation Performed";
                    break;
                }
            }
        }
    }

    return 1;
}