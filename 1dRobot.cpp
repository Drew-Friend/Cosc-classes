#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class OneDimensionalRobotEasy()
// {
//    public;
// }
int finalPosition(string commands, int A, int B)
{
    int endPosition = 0;
    vector<char> v(commands.begin(), commands.end());
    for (int i = 0; i <= v.size(); i++)
    {
        if (v[i] == 'R' &&)
    }
}

void main()
{
    string commandList;
    int A;
    int B;

    cout << "Input Command List";
    cin >> commandList;
    cout << "Input Left Boundary";
    cin >> commandList;
    cout << "Input Right Boundary";
    cin >> commandList;
    cout << finalPosition(commandList, A, B);
}
