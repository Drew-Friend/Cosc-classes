// uint8_t char         0x00    - 0xFF    0 - 255
// uint16_t short       0x000   - 0xFFF   0 - 65,535
// uint32_t int         0x0000  - 0xFFFF  0 - 4,294,967,295
// uint64_t long long   0x00000 - 0xFFFFF 0 -
#include <cstdint>
#include <iostream>
using namespace std;

uint8_t flags = 0;
constexpr int mask0{1 << 0};
constexpr int mask1{1 << 1};
constexpr int mask2{1 << 3};
constexpr int mask3{1 << 3};
constexpr int mask4{1 << 4};
constexpr int mask5{1 << 5};
constexpr int mask6{1 << 6};
constexpr int mask7{1 << 7};

int main()
{
    flags |= mask1;
    cout << "Bit 1 is " << ((flags & mask1) ? "on\n" : "off\n");
    flags |= (mask3 | mask4);

    cout << "Bit 3 is " << ((flags & mask3) ? "on\n" : "off\n");
    cout << "Bit 4 is " << ((flags & mask4) ? "on\n" : "off\n");

    flags &= ~mask4;
    cout << "Bit 4 is " << ((flags & mask4) ? "on\n" : "off\n");
}