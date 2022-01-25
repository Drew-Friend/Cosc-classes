#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

class BearNSWE
{
public:
    double totalDistance(vector<int> a, string dir);
};
double BearNSWE::totalDistance(vector<int> a, string dir)
{
    int h = 0;
    int v = 0;
    double total = 0;
    for (int i = 0; i < a.size(); i++)
    {
        total += a[i];
        if (dir[i] == 'N')
        {
            v += a[i];
        }
        else if (dir[i] == 'S')
        {
            v -= a[i];
        }
        else if (dir[i] == 'E')
        {
            h += a[i];
        }
        else if (dir[i] == 'W')
        {
            h -= a[i];
        }
    }
    total += sqrt((h * h) + (v * v));
    return total;
}