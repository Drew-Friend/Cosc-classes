#include <iostream>

// I saw this in code i used one time. I'm not sure what the use case is,
// but it seems pretty cool to me to store multiple numbers in one location
int main()
{
    char store;
    int rec;
    std::cout << "Input a number between 0-8, inclusive:  ";
    std::cin >> rec;
    store = rec << 4;
    std::cout << "Input a second number between 0-8, inclusive:  ";
    std::cin >> rec;
    store += rec;
    std::cout << "\nChar representation is: " << store
              << "\nFirst number is: " << (store >> 4)
              << "\nSecond number is: " << (store & 0b1111);
};
