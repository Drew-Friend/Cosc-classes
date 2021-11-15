#include <vector>
#include <iostream>
using namespace std;

vector<int> unsorted = {5, 1, 4, 2, 8};

vector<int> swap(vector<int> start, int i1, int i2)
{
    vector<int> fin = start;
    fin[i1] = start[i2];
    fin[i2] = start[i1];
    return fin;
}

int main()
{
    for (int i = 0; i < unsorted.size(); i++)
    {
        for (int j = i + 1; j < unsorted.size(); j++)
        {
            if (unsorted[i] > unsorted[j])
            {
                unsorted = swap(unsorted, i, j);
                break;
            }
        }
    }
    for (int i = 0; i < unsorted.size(); i++)
    {
        cout << unsorted[i] << ", ";
    }
}