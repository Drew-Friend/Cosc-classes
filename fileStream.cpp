#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    ifstream fin;
    fin.open("myfile.txt");
    if (!fin.is_open())
    {
        cout << "COuld not open file myfile.txt\n";
    }
    int data;
    fin >> data;
    cout << "File contained integer:  " << data << '\n';
    fin.close();
}