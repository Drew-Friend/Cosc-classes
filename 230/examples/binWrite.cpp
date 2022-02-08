#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int data = 12345678;
    ofstream fout;

    fout.open("mybinaryfile", ios::binary);
    if (!fout)
    {
        perror("mybinaryfile");
        return -1;
    }

    //fin.read()
    fout.write(reinterpret_cast<char *>(&data), sizeof(data));

    fout.close();
}