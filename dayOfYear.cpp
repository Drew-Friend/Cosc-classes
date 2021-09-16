#include <iostream>
using namespace std;

class DayOfYear
{
public:
    void output();
    int month;
    int day;
};

class Date
{
    int month;
    int day;

public:
    void output();
    void input();
    void set(int new_month, int new_day);
    int get_month();
    int get_day();
};

int main()
{
    //Print if today  is birthday and wish them happy birthday
    Date today, birthday;
    cout << "For Today's date:  \n";
    today.input();
    cout << "For Your birthday:  \n";
    birthday.input();

    if (today.get_day() == birthday.get_day() && today.get_month() == birthday.get_month())
    {
        cout << "Happy Birthday!";
    }
    else
    {
        cout << "Happy Un-Birthday";
    }
    return 0;
}

void DayOfYear::output()
{
    cout << "Month = " << month
         << ", day = " << day << "\n";
}

void Date::output()
{
    cout << "Month = " << month
         << ", day = " << day << "\n";
}
void Date::input()
{
    cout << "Enter month as a number:  ";
    cin >> month;
    cout << "Enter day of month as a number:  ";
    cin >> day;
}
void Date::set(int new_month, int new_day)
{
    month = new_month;
    day = new_day;
}
int Date::get_day()
{
    return day;
}
int Date::get_month()
{
    return month;
}