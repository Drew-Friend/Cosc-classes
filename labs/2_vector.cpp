/*
 Drew Friend
 8/25/21
 Swap Around Street name, first name, middle name, age, and address
*/
//Includes
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	//Initialize variables
	string firstName;
	string middleName;
	int age;
	int streetNum;
	string address;
	string roadType;

	cout << "Enter your first and middle names:  ";
	cin >> firstName;
	cin >> middleName;

	cout << "Enter your age:  ";
	cin >> age;

	cout << "Enter your street number, name, and type:  ";
	cin >> streetNum;
	cin >> address;
	cin >> roadType;
	cout << "\n";

	// the % operator returns the remainder
	int newAge = (streetNum % age) * 3;
	streetNum = (age * 700) / streetNum;
	//Variable placement in the following statements is determined by what the assignment required
	cout << "Your movie star name is " << address << " " << middleName << ".\n";
	cout << "You will play a " << newAge << " year old. \n";
	cout << "Your address is " << streetNum << " " << firstName << " " << roadType << ".\n";

	return 0;
}
