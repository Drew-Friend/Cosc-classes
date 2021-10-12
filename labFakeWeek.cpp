#include <string>
using namespace std;
class Initials
{
public:
    string getInitials(string name)
    {
        string initials = "";
        initials = initials + name[0];
        for (int i = 0; i < name.size(); i++)
        {
            if (name[i] == ' ')
            {
                initials = initials + name[i + 1];
            }
        }
        return initials;
    }
};