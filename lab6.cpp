/*
 Drew Friend
 10/6/2021
 Calculate speeding tickets within a time frame
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    const string MONTHS[12]{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const double MULT[4]{5.2252, 9.4412, 17.1525, 12.152};
    istringstream sin;
    ostringstream sout;
    ifstream fin;
    ofstream fout;
    string fileLoc, reportLoc;
    int m1, d1, y1;
    int m2, d2, y2;
    string reportNum, dayStr;
    int reportDay, reportMonth, reportYear, speed, limit;
    double over;
    char type;

    cout << "Enter a ticket file:  ";
    cin >> fileLoc;
    fin.open(fileLoc);
    if (!fin.is_open())
    {
        cout << "Unable to open " << fileLoc << '\n';
        return 1;
    }

    cout << "Enter a report file:  ";
    cin >> reportLoc;
    fout.open(reportLoc);
    if (!fout.is_open())
    {
        cout << "Unable to open " << reportLoc << '\n';
        return 1;
    }

    cout << "Enter report start date (mm dd yyyy):  ";
    cin >> m1 >> d1 >> y1;
    cout << "Enter report end date (mm dd yyyy):  ";
    cin >> m2 >> d2 >> y2;

    //This while loop runs once per line, and only while there are valid lines to read
    while (fin >> reportNum)
    {
        fin >> reportMonth >> reportDay >> reportYear >> speed >> limit >> type;

        //Accounting for 2 digit years
        if (reportYear < 100)
        {
            reportYear += 2000;
        }

        //Checking date to see if it needs to be written
        if (reportYear < y1 ||                                           //If the year is too early
            (reportYear == y1 && reportMonth < m1) ||                    //If its the starting year but the month is too early
            (reportYear == y1 && reportMonth == m1 && reportDay < d1) || //If it's the starting year and month but the day is too early
            reportYear > y2 ||                                           //If the year is too late
            (reportYear == y2 && reportMonth > m2) ||                    //If it's the last year but the month is too late
            (reportYear == y2 && reportMonth == m2 && reportDay > d2))   //If it's the last year and month but the day is too late
        {
            continue;
        }

        //Else is implied by the continue
        //Make the day defined to 2 digits
        sout.str("");
        sout.width(2);
        sout.fill('0');
        sout << right << reportDay;
        dayStr = sout.str();

        //Put the date in the file
        fout << dayStr << '-' << MONTHS[reportMonth - 1] << '-' << reportYear << " ";

        //Make the report number 10 characters wide and left aligned
        sout.str("");
        sout.width(10);
        sout.fill(' ');
        sout << left << reportNum;
        fout << sout.str();

        //Find amount owed based on type of infraction
        over = speed - limit;
        switch (type)
        {
        case 'i':
        case 'I':
            //Interstate
            over = over * MULT[0];
            break;
        case 'h':
        case 'H':
            //Highway
            over = over * MULT[1];
            break;
        case 'r':
        case 'R':
            //Residential
            over = over * MULT[2];
            break;
        default:
            //Other
            over = over * MULT[3];
            break;
        }

        //Check for negative fines and default them to 0
        if (over < 0)
        {
            over = 0.00;
        }

        //Make the total fine amount 9 characters wide and 2 digits past the decimal
        fout << '$';
        sout.str("");
        sout.width(9);
        sout.fill(' ');
        sout << fixed << setprecision(2);
        sout << right << over;
        fout << sout.str() << '\n';
    }
    fout.close();
    fin.close();
}