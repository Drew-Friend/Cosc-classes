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
void insertionSort(vector<int> &vec)
{
    int size = vec.size();
    int index;
    //This runs for each number, to find where it goes
    for (int i = 1; i < size; i++)
    {
        //The if the first for loop's condition is never met, it should become the first index
        index = 0;
        //This runs to update the index with the biggest number that is smaller than the i element
        for (int j = 0; vec[i] > vec[j]; j++)
        {
            index = j + 1;
        }
        //Save the value we're placing
        int save = vec[i];
        //shift everything between the old and new indices to the right by 1
        for (int k = i; k > index; k--)
        {
            vec[k] = vec[k - 1];
        }
        //Place the value at it's new index
        vec[index] = save;
    }
}

int main()
{
    vector<int> data = {2, 20, 9, 10, 12, 1};
    cout << "Beginning Vector:\n";
    printVector(data);
    insertionSort(data);
    cout << "Sorted Vector:\n";
    printVector(data);
}