#include <iostream>
#include <iomanip>

using namespace std;

//I do not like function prototypes
double total_cost(int num_items, double price)
{
    const double TAX_RATE = 0.095; //9.5%
    double sub = num_items * price;
    return sub + sub * TAX_RATE;
}

int main()
{
    double price, bill;
    int num;
    cout << "Enter the number of items purchased:  ";
    cin >> num;
    cout << "Enter the price per item:  ";
    cin >> price;
    bill = total_cost(num, price);
    cout << "Total cost is $" << bill << "\n";
    return 0;
}
