#include <iostream>
#include <list>
using namespace std;

template <typename iT, typename T>
int my_count(iT start, iT end, T target)
{
    int counter = 0;
    // Step through each index of the list,
    // check if that index is a repeat of the start
    for (; start != end; ++start)
    {
        counter += (*start == target) ? 1 : 0;
    }
    return counter;
}

int main()
{
    list<int> v;
    list<int>::iterator iv;
    int value;
    while (cin >> value)
        v.push_back(value);

    int target = *v.begin();
    int N = my_count(v.begin(), v.end(), target);

    cout << "Found " << N << " instances of " << target << "\n";
}