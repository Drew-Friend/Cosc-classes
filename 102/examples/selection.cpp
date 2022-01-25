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
void selectionSort(vector<int> &vec)
{
    int size = vec.size();
    int min;
    for (int i = 0; i < size - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (vec[j] < vec[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            int temp = vec[i];
            vec[i] = vec[min];
            vec[min] = temp;
        }
    }
}

int main()
{
    vector<int> data = {5, 20, 15, 10, 21, 1};
    cout << "Beginning Vector:\n";
    printVector(data);
    selectionSort(data);
    cout << "Sorted Vector:\n";
    printVector(data);
}