#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

int main(int argc, char **argv)
{
    int i;
    istringstream sin;
    if (argc != 2)
    {
        cerr << "Wrong number of parameters input.\nUsage: mainCMD argument1\n";
        return 1;
    }

    sin.str(argv[1]);
    if (sin >> i)
    {
        cout << "Thank you for providing an integer";
    }
    else
    {
        cerr << "The argument '" << argv[1] << "' is not an integer.\n";
        return 1;
    }
    return 0;
}