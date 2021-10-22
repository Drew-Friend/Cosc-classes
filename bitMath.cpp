//  AND     OR     XOR        NOT       LSHIFT   RSHIFT
//   &      |       ^          ~          <<       >>
//  0110   0110    0110    (One Arg)     0110     0110
//+ 0100   0100    0100       0110       <<2       >>2
//= 0100   0110    0010       1001       1000     0001

// uint8_t char
// uint16_t short
// uint32_t int
// uint64_t long long

#include <string>
#include <iostream>
enum SensorType
{
    HR,
    Power,
    Cadence,
    Speed
};

class SensorList
{
    int mySensors;

public:
    SensorList()
    {
        mySensors = 0;
    }
    int getMySensors() { return mySensors; }
    int test_bit_set(SensorType index) //Given a number (mySensors), test if the i-th bit is set
    {
        int mask = 1 << index;
        return mySensors & mask;
    }
    void set_bit(SensorType index) //Set the i-th bit to 1
    {
        int mask = 1 << index;
        mySensors = mySensors | mask;
    }
    void clear_bit(SensorType index) //Set the i-th bit to 0
    {
        int mask = ~(1 << index);
        mySensors = mySensors & mask;
    }
};

using namespace std;
int main()
{
    SensorList myWatch;
    //Add HR
    myWatch.set_bit(HR);
    //Add Power
    myWatch.set_bit(Power);
    //Remove HR
    myWatch.clear_bit(HR);
    //Check Cadence
    int first = myWatch.test_bit_set(Cadence);
    //Add Cadence
    myWatch.set_bit(Cadence);
    //Check Cadence
    int second = myWatch.test_bit_set(Cadence);

    cout << "First: " << first << "\nSecond: " << second << "\nWatch:" << myWatch.getMySensors();
}