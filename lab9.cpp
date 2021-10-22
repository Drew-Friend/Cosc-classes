/*
    Drew Friend
    10/20/21
    Store multiple booleans in a single integer bitset
*/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class BITSET
{
    vector<int> mSets;

public:
    BITSET();
    bool Test(int index) const;
    void Set(int index);
    void Clear(int index);
    int GetNumSets() const;
    int GetSet(int index) const;
};
string ToBinary(int bit_set, int spacing = 4);

int main()
{
    BITSET sets;
    string command;
    int which;
    do
    {
        cout << "> ";
        //Quit
        if (!(cin >> command) || "q" == command)
        {
            // If cin fails for any reason, it usually means
            // an EOF state, break and quit.
            break;
        }
        // Handle the commands here

        //Test Bit, returns value of chosen bit
        if ("t" == command)
        {
            if (!(cin >> which))
            {
                cout << "Invalid index\n";
            }
            else
            {
                cout << sets.Test(which) << '\n';
            }
        }

        //Set Bit, sets the chosen bit to 1
        else if ("s" == command)
        {
            if (!(cin >> which))
            {
                cout << "Invalid index\n";
            }
            else
            {
                sets.Set(which);
            }
        }

        //Get Set, prints the chosen set with the chosen spacing, with the spacing defaulting to 4
        else if ("g" == command)
        {
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin{line};
            if (!(sin >> which))
            {
                cout << "Invalid index\n";
            }
            else
            {
                // This is a little redundant when you can just have a default value set
                // but it was part of the template
                if (!(sin >> spacing))
                {
                    spacing = 4;
                }
                cout << ToBinary(sets.GetSet(which), spacing) << '\n';
            }
        }

        //Clear Bit, sets the chosen bit to 0
        else if ("c" == command)
        {
            // Done: Finish the "clear" command here.
            if (!(cin >> which))
            {
                cout << "Invalid index\n";
            }
            else
            {
                sets.Clear(which);
            }
        }
        // Done: Finish the rest of the commands here.

        //Get number of Sets in bitSet
        else if ("n" == command)
        {
            cout << sets.GetNumSets() << '\n';
        }

        //Unknown command
        else
        {
            cout << "Unknown command '" << command << "'\n";
        }

    } while (true);
    return 0;
}
string ToBinary(int bit_set, int spacing)
{
    string ret;
    for (int i = 31; i >= 0; i--)
    {
        //integers are true if nonzero
        if (bit_set & (1 << i))
        {
            ret += '1';
        }
        else
        {
            ret += '0';
        }
        // Builds from the MSI, so this evaluates if it has gone the specified
        // number of digits since the last space or begining
        if ((32 - i) % spacing == 0)
        {
            ret += ' ';
        }
    }
    return ret;
}

// BITSET Class Members
BITSET::BITSET() : mSets(1, 0)
{
}

bool BITSET::Test(int index) const
{
    int which_set = index / 32;
    int which_bit = index % 32;
    if (which_set >= GetNumSets())
    {
        // The BITSET is an "infinite" set, so if the requested set
        // is bigger than what we are storing, that means it's a 0.
        return false;
    }

    //Second value, in parenthesis, is mask. when returning a bool
    //from an int, 0 is false, and any other value is true
    return mSets[which_set] & (1 << which_bit);
}

void BITSET::Set(int index)
{
    int which_set = index / 32;
    int which_bit = index % 32;

    // Resize the vector if the user wants to set a number
    // larger than what is currently stored
    if (which_set >= GetNumSets())
    {
        mSets.resize(which_set + 1, 0);
    }

    //Second value, in parenthesis, is the mask.
    //A | with this mask garuntees that that the chosen bit will be a 1
    mSets.at(which_set) = mSets[which_set] | (1 << which_bit);
}

void BITSET::Clear(int index)
{
    int which_set = index / 32;
    int which_bit = index % 32;
    //If the value isn't currently stored, it is treated as a 0 anyway
    if (which_set < GetNumSets())
    {
        //Inverted mask with a & operator garuntees that the
        //chosen bit will be cleared, and nothing else will be affected
        mSets.at(which_set) = mSets[which_set] & (~(1 << which_bit));

        //Clear any sets that are equal to 0
        for (int i = 0; i < GetNumSets(); i++)
        {
            if (mSets[i] == 0)
            {
                mSets.erase(mSets.begin() + i);
            }
        }
    }
}

int BITSET::GetNumSets() const
{
    return static_cast<int>(mSets.size());
}

int BITSET::GetSet(int index) const
{
    // if the desired set isn't stored, it is treated as a 0
    if (index >= GetNumSets())
    {
        return 0;
    }
    return mSets.at(index);
}