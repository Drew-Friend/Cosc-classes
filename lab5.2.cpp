#include <iostream>
#include <string>
#include <vector>

using namespace std;

int calculate(int scoreArray[2][11])
{
    int runningTotal = 0;
    for (int frame = 0; frame < 10; frame++)
    {
        //If strike, add the next 2 rolls
        if (scoreArray[0][frame] == 10)
        {
            /*If the first 2 rolls of 10 were both strikes, the case is treated differently.
            If you get 2 consecutive strikes starting in frame 9, you check the second roll of frame 10,
            But if you get 2 consecutive rolls starting anywhere else, you just check the first roll of the third consecutive frame 
            */
            if (scoreArray[0][frame + 1] == 10 && (frame + 1 != 9))
            {
                runningTotal += scoreArray[0][frame + 1] + scoreArray[0][frame + 2];
            }
            else
            {
                runningTotal += scoreArray[0][frame + 1] + scoreArray[1][frame + 1];
            }
        }
        //If spare, add the next roll
        else if ((scoreArray[1][frame] + scoreArray[0][frame]) == 10)
        {
            runningTotal += scoreArray[0][frame + 1];
        }
        //Add the roll being scored
        runningTotal += scoreArray[0][frame] + scoreArray[1][frame];
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
            //If, in frame 10, they got a spare or strike
            if ((oneGame[0][9] + oneGame[1][9] == 10) || oneGame[0][9] == 10)
            {
                cout << "Enter score for frame 10, roll 3:  ";
                cin >> rollVal;
                oneGame[0][10] = rollVal;
            }
        }

        //Calculate total score of player and add it to the list of scores
        scoreTotals.push_back(calculate(oneGame));
    }
    //If no players
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