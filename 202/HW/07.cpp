// Not really, but to fit the naming
#include <string>
#include <iostream>
#include <iomanip>

uint32_t strConv(std::string input)
{
    uint32_t out = 0x0;
    uint32_t store = 0x0;
    for (int i = 0; input[i]; ++i)
    {
        std::cout << "Old value: " << std::setw(8) << std::hex << out << "      ";
        store = out >> 24;
        out = out << 8;
        out = out | store;
        std::cout << "Temp value: " << std::setw(8) << std::hex << out << "      ";
        out = out + input[i];
        std::cout << "Current value: 0x" << std::setw(8) << std::hex << out << '\n';
    }
    std::cout << out << '\n';
    return out;
}

int hash(uint32_t value)
{
    return 0;
}

int main()
{
    strConv("hello world");
    strConv("HELLO");
}