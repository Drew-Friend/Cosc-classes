/*
 Drew Friend
 8/26/21
 Find the final position of the robot given a command list and boundaries
*/
//Includes
#include <iostream>
#include <string>
using namespace std;
//Class, represents the robot as an object in code
class OneDimensionalRobotEasy
{
public:
    //Calculate the sum movement of the robot
    int finalPosition(string commands, int A, int B)
    {
        //Error acounting for whether the left boundary was input as a positive or negative
        if (A > 0)
        {
            A = A * -1;
        }
        int endPosition = 0;
        //Check each character in the commadn list for an L or an R
        //Does nothing if the command is invalid or if the robot is already at the boundary
        for (int i = 0; i < commands.size(); i++)
        {
            if (commands.at(i) == 'R')
            {
                if (endPosition < B)
                {
                    endPosition++;
                }
            }
            if (commands.at(i) == 'L')
            {
                if (endPosition > A)
                {
                    endPosition--;
                }
            }
        }
        return endPosition;
    }
};
//I really don't like needing a semicolon at the end of a class. I'm a java boi, this is not for me.

int main()
{
    //Instance of the class
    OneDimensionalRobotEasy robot;
    //Variables to hold inputs
    string commandList;
    int A;
    int B;

    cout << "Input Command List:  ";
    cin >> commandList;
    cout << "Input Left Boundary:  ";
    cin >> A;
    cout << "Input Right Boundary:  ";
    cin >> B;
    cout << robot.finalPosition(commandList, A, B);
    //Cool lil piece of code I found to hold open the terminal after it finishes running
    cout << "\n";
    system("pause");
    return 0;
}
