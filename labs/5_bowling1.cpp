#include <iostream>
#include <string>

using namespace std;
int main()
{
    string playerName;
    int trashVar;

    cout << "Enter player's name(done for no more players):  ";
    cin >> playerName;
    //I know I could just add one to frame in the print statements, or say <11, but I like this way for legibility
    for (int frame = 1; frame <= 10; frame++)
    {
        for (int roll = 1; roll <= 2; roll++)
        {
            cout << "Enter score for frame " << frame << " , roll " << roll << ":  ";
            cin >> trashVar;
            if (frame != 10 && trashVar == 10)
            {
                roll++;
            }
        }
        if (frame == 10)
        {
            cout << "Enter score for frame " << frame << " , roll 3:  ";
            cin >> trashVar;
        }
    }
    cout << playerName << " won the game.";
}