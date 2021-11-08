//American Standard Code for Information Interchange
#include <iostream>
#include <cstdint>
using namespace std;

constexpr int maskCase{1 << 5};   // Equal to the space character
constexpr int invMask{~(1 << 5)}; // Equal to the underscore character, aside from the far left bit, but that isn't relevant in ascii
constexpr int numMask{3 << 4};    //Equal to 0 character

char caseFlip(char letter)
{
    return letter ^ maskCase;
}
char lowerCase(char letter)
{
    return letter | maskCase;
}

char upperCase(char letter)
{
    return letter & ~maskCase;
}

int getVal(char number)
{
    //return number ^ numMask;
    return number ^ 0;
}

int main()
{
    //A: 65; 0b0100_0001
    //a: 97; 0b0110_0001
    char inputChar, outputChar;
    cout << "Enter a letter:  ";
    cin >> inputChar;
    outputChar = caseFlip(inputChar);
    cout << outputChar;

    cout << "Enter a letter:  ";
    cin >> inputChar;
    outputChar = lowerCase(inputChar);
    cout << outputChar;

    cout << "Enter a letter:  ";
    cin >> inputChar;
    outputChar = upperCase(inputChar);
    cout << outputChar;

    return 0;

    //Char values of '0', '1', '2', etc.
    //It is the number's value with 0011_0000
