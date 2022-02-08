#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct MyStruct
{
    float a;
    double b;
};

int main()
{
    MyStruct ms;
    int data;
    ifstream fin;

    fin.open("mybinaryfile", ios::binary);
    if (!fin)
    {
        perror("mybinaryfile");
        return -1;
    }

    fin.read(reinterpret_cast<char *>(&data), sizeof(int));
    fin.seekg(10, ios::beg);

    cout << hex << data;
    fin.close();
}