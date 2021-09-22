#include <vector>
using namespace std;

class WakingUpEasy
{
public:
    int countAlarms(vector<int> volume, int S);
};

int WakingUpEasy::countAlarms(vector<int> volume, int S)
{
    int iterations = 0;
    while (S > 0)
    {
        S -= volume.front();
        volume.push_back(volume.front());
        volume.erase(volume.begin());
        iterations += 1;
    }
    return (iterations);
}