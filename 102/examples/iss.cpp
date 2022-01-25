#include <sstream>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    int a;
    double b;
    int c;
    //string data = "10 20.5 30";
    //istringstream sin(data);
    istringstream sin;
    ostringstream sout;
    sin.str("10 20.5 30");
    sin >> a >> b >> c;
    sout << a << ' ' << b << ' ' << c;
    string output = sout.str();
    cout << output;
    sin.clear();
    sout.str("");
    return 0;
}