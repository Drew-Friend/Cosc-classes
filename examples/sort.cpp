#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void printVector(vector<int> vec)
{
    int size = vec.size();
    for (int i = 0; i < size; i++)
    {
        cout << ' ' << vec[i];
    }
    cout << '\n';
}
void bubbleSort(vector<int> &vec)
{
    int size = vec.size();
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (int i = 0; i < size - 1; i++)
        {
            if (vec[i] > vec[i + 1])
            {
                int temp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = temp;
                swapped = true;
            }
        }
    }
}

int main()
{
    vector<int> data = {5, 20, 15, 10, 21, 1};
    cout << "Beginning Vector:\n";
    printVector(data);
    bubbleSort(data);
    cout << "Sorted Vector:\n";
    printVector(data);
}