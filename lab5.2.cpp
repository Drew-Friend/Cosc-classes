#include <iostream>
#include <string>
#include <vector>

using namespace std;

int calculate(int scoreArray[2][11])
{
    int runningTotal = 0;
    for (int frame = 0; frame < 10; frame++)
    {
        cout << frame << "     " << scoreArray[0][frame] << "     " << scoreArray[1][frame] << "\n";
        //If strike
        if (scoreArray[0][frame] == 10)
        {
            if (scoreArray[0][frame + 1] == 10 && (frame + 1 != 9))
            {
                runningTotal += scoreArray[0][frame + 1] + scoreArray[0][frame + 2];
            }
            else
            {
                runningTotal += scoreArray[0][frame + 1] + scoreArray[1][frame + 1];
            }
        }
        //If spare
        else if ((scoreArray[1][frame] + scoreArray[0][frame]) == 10)
        {
            runningTotal += scoreArray[0][frame + 1];
        }
        runningTotal += scoreArray[0][frame] + scoreArray[1][frame];
        cout << frame << "     " << runningTotal << "\n";
    }
    return runningTotal;
}

int main()
{
    vector<string> playerNames;
    vector<int> scoreTotals;
    bool done = false;
    string name;
    while (!done)
    {
        cout << "Enter player's name(done for no more players):  ";
        cin >> name;
        if (name == "done")
        {
            done = true;
            continue;
        }
        else
        {
            playerNames.push_back(name);
        }
        //2 rolls per frame, 10 frames(the possible 3rd roll in frame 10 is treated as a roll of "frame 11")
        int oneGame[2][11] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        int rollVal;
        for (int frame = 0; frame < 10; frame++)
        {
            for (int roll = 0; roll < 2; roll++)
            {
                cout << "Enter score for frame " << frame + 1 << ", roll " << roll + 1 << ":  ";
                cin >> rollVal;
                oneGame[roll][frame] = rollVal;
                //If all pins were knocked down and it is not the tenth frame, don't ask for the next roll
                if (rollVal == 10 && frame != 9)
                {
                    roll++;
                }
            }
            if ((oneGame[0][9] + oneGame[1][9] == 10) || oneGame[0][9] == 10)

            //if, in frame 10, they got a spare or strike
            {
                cout << "Enter score for frame 10, roll 3:  ";
                cin >> rollVal;
                //Add third roll to second roll
                oneGame[0][10] = rollVal;
            }
        }
        scoreTotals.push_back(calculate(oneGame));
    }
    if (playerNames.size() == 0)
    {
        cout << "No players were entered.\n";
    }
    else
    {
        //Print all players and scores
        for (int a = 0; a < scoreTotals.size(); a++)
        {
            cout << playerNames[a] << " scored " << scoreTotals[a] << ".\n";
        }

        int index = 0;
        //Find index of min score
        for (int a = 0; a < scoreTotals.size(); a++)
        {
            if (scoreTotals[a] < scoreTotals[index])
            {
                index = a;
            }
        }
        cout << playerNames[index] << " did the worst by scoring " << scoreTotals[index] << ".\n";

        index = 0;
        //Find index of max score
        for (int a = 0; a < scoreTotals.size(); a++)
        {
            if (scoreTotals[a] > scoreTotals[index])
            {
                index = a;
            }
        }
        cout << playerNames[index] << " won the game by scoring " << scoreTotals[index] << ".\n";
    }
}