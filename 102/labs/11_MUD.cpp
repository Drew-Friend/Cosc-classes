/*
Drew Friend
10/27/21
Multi User Dungeon, but only for 1 user
    must work with any input file of rooms
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//Room structure that contains the name, description, and exits
struct Room
{
    string name = "";
    string description = "";
    int exits[4] = {-1, -1, -1, -1};
};

int action(char input, Room *list);

char input;
string desc;
string dir;
ifstream fin;
istringstream iss;
int numRooms;
int currentRoom;

int main(int argc, char **argv)
{
    fin.open(argv[1]);
    //Count ~ to find number of rooms, divided byt the 3 ~'s per room
    while (getline(fin, desc, '~'))
    {
        numRooms++;
    }
    numRooms = numRooms / 3;

    //Room *roomArr = new Room[numRooms];
    Room roomArr[numRooms] = {*(new Room)};
    fin.clear();
    fin.seekg(0);
    //Set the Reader at the beginning again and read for exits
    for (int i = 0; i < numRooms; i++)
    {
        //First section before ~ is the name
        getline(fin, desc, '~');
        roomArr[i].name = desc;
        //Second section is the description
        getline(fin, desc, '~');
        roomArr[i].description = desc;
        //Last section is exits
        while (true)
        {
            getline(fin, desc, '\n');
            //If it hit's a ~ this room is done
            if (desc == "~")
            {
                break;
            }
            else
            {
                //Break up the line into a direction and a room it leads to
                //Then add that exit to the array of the room
                iss.clear();
                iss.str(desc);
                iss >> dir >> currentRoom;
                if (dir == "n")
                {
                    roomArr[i].exits[0] = currentRoom;
                }
                else if (dir == "e")
                {
                    roomArr[i].exits[1] = currentRoom;
                }
                else if (dir == "s")
                {
                    roomArr[i].exits[2] = currentRoom;
                }
                else if (dir == "w")
                {
                    roomArr[i].exits[4] = currentRoom;
                }
            }
        }
    }
    fin.close();

    currentRoom = 0;
    //Doesn't need a condition because the quit function has a return that ends the program
    while (true)
    {

        cout << "\n> ";
        if (cin >> input)
        {
            //Quit if the user inputs q
            if (input == 'q')
            {
                return 0;
            }
            //Run the desired action otherwise
            currentRoom = action(input, roomArr);
        }
    }
}

int action(char input, Room *list)
{
    //Look around the room
    if (input == 'l')
    {
        //List name, descriptions, and any exits that exist
        cout << list[currentRoom].name << '\n'
             << list[currentRoom].description << '\n'
             << "Exits: "
             << ((list[currentRoom].exits[0] != -1) ? "n " : "")
             << ((list[currentRoom].exits[1] != -1) ? "e " : "")
             << ((list[currentRoom].exits[2] != -1) ? "s " : "")
             << ((list[currentRoom].exits[3] != -1) ? "w " : "");
        //Doesn't change position
        return currentRoom;
    }

    //Movement
    else
    {
        //Logic repeats for each direction
        if (input == 'n')
        {
            //Confirm whether or not an exit exists in the right direction
            if (list[currentRoom].exits[0] != -1)
            {
                cout << "You moved NORTH";
                //Move the player
                return list[currentRoom].exits[0];
            }
            cout << "You can't go NORTH";
            return currentRoom;
        }
        else if (input == 'e')
        {
            if (list[currentRoom].exits[1] != -1)
            {
                cout << "You moved EAST";
                return list[currentRoom].exits[1];
            }
            cout << "You can't go EAST";
            return currentRoom;
        }
        else if (input == 's')
        {
            if (list[currentRoom].exits[2] != -1)
            {
                cout << "You moved SOUTH";
                return list[currentRoom].exits[2];
            }
            cout << "You can't go SOUTH";
            return currentRoom;
        }
        else if (input == 'w')
        {
            if (list[currentRoom].exits[3] != -1)
            {
                cout << "You moved WEST";
                return list[currentRoom].exits[3];
            }
            cout << "You can't go WEST";
            return currentRoom;
        }
    }
    return currentRoom;
}