#include <iostream>
using namespace std;

bool isBad(int index)
{
    return index;
}

int search(int *base)
{
    int rLimit = 100;
    //int rLimit = sizeof(base) / sizeof(base[0]); /*Wasn't giving me accurate size info*/
    int lLimit = 1;
    int mid = (rLimit + 1) / 2;
    while (!(isBad(base[mid]) && !isBad(base[mid - 1])))
    {
        if (!isBad(base[mid]))
        {
            lLimit = mid;
        }
        else
        {
            rLimit = mid;
        }
        mid = (rLimit + lLimit) / 2;
    }
    return mid;
}

int main()
{
    int arr[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    //Returns number counted from 0
    cout << "First one at: " << search(arr);
    return 1;
}