#include <iostream>
using namespace std;

typedef int *intPtr;

int main()
{
    intPtr p;
    int a[10];
    int index;

    for (index = 0; index < 10; index++)
    {
        a[index] = index;
    }
    p = a;

    for (index = 0; index < 15; index++)
    {
        cout << p[index] << ' ';
    }
    for (index = 0; index < 10; index++)
    {
        p[index] = p[index] + 1;
    }
    for (index = 0; index < 10; index++)
    {
        cout << a[index] << '\n';
    }
}