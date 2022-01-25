//Solving a problem in terms of itself
//i.e. a function that calls itself is recursive
//Must include:     base case(when to stop), work towards base case, recursive call
#include <iostream>
using namespace std;

int factorial(int num)
{
    return num > 1 ? (num * factorial(num - 1)) : num;
    // if (num == 1)
    // {
    //     return num;
    // }
    // return (num * factorial(num - 1));
}

int main()
{
    int val;
    cout << "Please submit a positive integer:  ";
    cin >> val;
    cout << "The factorial of " << val << " is: " << factorial(val);
}