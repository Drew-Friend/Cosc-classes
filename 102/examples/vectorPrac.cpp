#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> names;
    vector<int> grades;
    int total = 0;
    int modeCheck = 0;
    int classSize;
    cout << "What is the size of the class?  ";
    cin >> classSize;
    for (int i = 0; i < classSize; i++)
    {
        int grade;
        string name;
        cout << "What is the name of student " << i + 1 << "?  ";
        cin >> name;
        names.push_back(name);
        cout << "What is the grade of student " << i + 1 << "?  ";
        cin >> grade;
        grades.push_back(grade);
    }

    for (int i = 0; i < classSize; i++)
    {
        total += grades[i];
    }
    cout << "Mean:  " << total / classSize << "\n";
    cout << "Mode:  ";
    for (int i = 0; i < classSize; i++)
    {
        if (count(grades.begin(), grades.end(), grades[i]) > count(grades.begin(), grades.end(), grades[modeCheck]))
        {
            modeCheck = i;
        }
    }
    cout << grades[modeCheck] << "\nAll Students with the mode grade:  \n";
    for (int i = 0; i < classSize; i++)
    {
        if (grades[i] == grades[modeCheck])
        {
            cout << names[i] << "\n";
        }
    }
}