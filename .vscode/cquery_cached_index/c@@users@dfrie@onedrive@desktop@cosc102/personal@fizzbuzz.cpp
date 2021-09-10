#include <iostream>
#include <string>
using namespace std;

int main()
{
    while (true)
    {
        int input;
        cout << "Please input a number:  ";
        cin >> input;

        if (input % 3 == 0)
        {
            cout << "fizz";
        }
        if (input % 5 == 0)
        {
            cout << "buzz";
        }
        cout << "\n";
    }
}