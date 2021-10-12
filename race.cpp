#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    int countLines = 0;
    ifstream fin;
    string fName, lName, time, line, filePath;
    filePath = argv[1];
    istringstream sin;
    if (argc != 2)
    {
        cerr << "Incorrect usage \nUsage: race.exe fileName \n";
        return 1;
    }

    fin.open(filePath);
    if (!fin.is_open())
    {
        cerr << "Could not open file.";
        return 1;
    }

    while (getline(fin, line))
    {
        countLines++;
        sin.clear();
        sin.str(line);
        sin >> fName >> lName >> time;
        cout << "Full Name: " << fName << " " << lName << '\n';
        cout << "   Marathon TIme: " << time << '\n';
    }

    fin.close();
}

string convert(int hours, int minutes, int seconds)
{
    ostringstream formattedTime;
    formattedTime << hours << ':' << minutes << ':' << seconds;
    return formattedTime.str();
}