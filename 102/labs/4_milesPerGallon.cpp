/*
 Drew Friend
 9/8/21
 Miles per gallon calculator
*/

#include <iostream>
#include <string>
#include <limits>
using namespace std;
double mpg(string type, string value)
{
    //Finds the miles and gallons of an individual vehicle and returns them
    double temp;
    string trash;
    bool valid = false;
    while (!valid)
    {
        cout << "Enter " << type << "'s " << value << ":  ";
        cin >> temp;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            valid = true;
        }
    }
    return temp;
}

int main()
{
    bool running = true;
    double carMiles = 0;
    double carGallons = 0;
    double numCar = 0;
    double truckMiles = 0;
    double truckGallons = 0;
    double numTruck = 0;
    while (running)
    {
        //Initialize Variables
        string command;
        cout << "Input Command:  ";
        cin >> command;
        //Follow instruction of command
        if (command == "done")
        {
            if (numCar != 0)
            {
                cout << "Average car mpg: " << carMiles / carGallons << "\n";
            }
            else
            {
                cout << "Fleet has no cars.\n";
            }
            if (numTruck != 0)
            {
                cout << "Average truck mpg: " << truckMiles / truckGallons << "\n";
            }
            else
            {
                cout << "Fleet has no trucks.\n";
            }
            running = false;
        }
        else if (command == "truck")
        {
            //Add truck to fleet
            numTruck += 1;
            //Add miles and gallons of truck
            truckMiles += mpg("truck", "miles");
            truckGallons += mpg("truck", "gallons");
        }
        else if (command == "car")
        {
            //Add car to fleet
            numCar += 1;
            //Add miles and gallons of car
            carMiles += mpg("car", "miles");
            carGallons += mpg("car", "gallons");
        }
        else
        {
            cout << "Unknown Command.\n";
        }
    }
    return 1;
}