#include <cmath>
using namespace std;

class TestTaking
{
public:
    int findMax(int questions, int guessed, int actual)
    {
        int error = abs(guessed - actual);
        return questions - error;
    }
};