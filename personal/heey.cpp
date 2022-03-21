#include <iostream>
#include <string>

int main()
{
    std::string first = "", second = "";
    std::cout << "Input a string:  ";
    std::cin >> first;
    for (int i = 0; i < first.size(); ++i)
        second += (first[i] == 'e') ? first[i] + first[i] : first[i];
}