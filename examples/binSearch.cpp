
#include <iostream>
#include <vector>
using namespace std;

/* Binary search function that returns the 
   location of x in given a vector arr[l..r] if present,
   otherwise -1
*/
int binarySearch(vector<int> data, int goal, int l = 0, int r = -1)
{
    r = (r == -1) ? data.size() : r;
    //If the middle number is the number we want, return true
    int mid = (l + r) / 2;
    if (data[mid] == goal)
    {
        return mid;
    }
    if (r - l == 1)
    {
        return -1;
    }
    return (data[mid] < goal) ? binarySearch(data, goal, mid, r) : binarySearch(data, goal, l, mid);
    //If the length of the section is 1, return -1
    //else:
    //If the middle number is greater than the goal, search the upper half of the section
    //If the middle number is less than the goal, search bottom half of the section
}

/* Driver code - use C++11 to compile */
int main(void)
{
    vector<int> data = {2, 3, 4, 10, 40}; // Remember this line requires C++11
    int x = 40;
    /* Hint: to make it recursive, adding parameters... specifically 2 
parameters... will help. */
    int result = binarySearch(data, x);
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result;
    cout << endl;
    return 0;
}
