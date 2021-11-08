#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class doublevector
{
     static constexpr double DOUBLE_DEFAULT_VALUE = -5.55;
     double *mValues;
     int mNumValues;

public:
     doublevector();
     ~doublevector();
     void resize(int new_size, double initial_value = DOUBLE_DEFAULT_VALUE);
     void push_back(double value);
     double &at(int index);
     const double &at(int index) const;
     unsigned long size() const;
};
void print_all(const doublevector &v)
{
     if (v.size() == 0)
     {
          cout << "Vector is empty.\n";
     }
     else
     {
          unsigned long i;
          for (i = 0; i < v.size(); i++)
          {
               cout << "[" << setfill('0') << right << setw(3) << i
                    << "] = " << fixed << setprecision(4) << v.at(i)
                    << '\n';
          }
     }
}
int main()
{
     doublevector v;
     do
     {
          string command;
          cout << "Enter a command ('quit' to quit): ";
          if (!(cin >> command) || command == "quit")
          {
               break;
          }
          else if (command == "push_back")
          {
               double value;
               cin >> value;
               v.push_back(value);
               cout << "Pushed back "
                    << fixed << setprecision(4)
                    << value << '\n';
          }
          else if (command == "resize")
          {
               string line;
               int new_size;
               double initial;
               cin >> new_size;
               getline(cin, line);
               istringstream sin(line);

               if (sin >> initial)
                    v.resize(new_size, initial);
               else
                    v.resize(new_size);
          }
          else if (command == "size")
          {
               cout << v.size() << '\n';
          }
          else if (command == "print")
          {
               print_all(v);
          }
          else if (command == "get")
          {
               int index;
               cin >> index;
               try
               {
                    cout << "Value at " << index << " = "
                         << setprecision(4) << fixed
                         << v.at(index) << '\n';
                    ;
               }
               catch (out_of_range &err)
               {
                    cout << err.what() << '\n';
               }
          }
          else if (command == "set")
          {
               double d;
               int index;
               cin >> index >> d;
               try
               {
                    v.at(index) = d;
                    cout << "SET: " << index << " = "
                         << setprecision(4) << fixed
                         << v.at(index) << '\n';
                    ;
               }
               catch (out_of_range &err)
               {
                    cout << err.what() << '\n';
               }
          }
          else if (command == "clear")
          {
               v.resize(0);
          }
          else
          {
               cout << "Invalid command '" << command << "'\n";
          }
     } while (true);
     cout << endl;
     return 0;
}
//Write your class members below here.

doublevector::doublevector()
{
     //Make sure pointer is null and we are storing no values
     mValues = nullptr;
     mNumValues = 0;
}

doublevector::~doublevector()
{
     //Only need to delete if it is not already null
     if (mValues != nullptr)
     {
          delete[] mValues;
     }
     mNumValues = 0;
}

void doublevector::resize(int new_size, double initial_value)
{
     //If we are growing or shrinking the vector
     if (new_size > 0)
     {
          double *temp = new double[new_size];
          for (int i = 0; i < new_size; i++)
          {
               //Set the index to the existing number if it does exist, otherwise set to chosen value
               temp[i] = (i < mNumValues) ? mValues[i] : initial_value;
          }
          //If there are already values in the array:
          if (mValues != nullptr)
          {
               delete[] mValues;
          }
          mValues = temp;
          mNumValues = new_size;
     }
     //If we are clearing the vector
     else if (new_size == 0)
     {
          if (mValues != nullptr)
          {
               delete[] mValues;
               mValues = nullptr;
          }
          mNumValues = 0;
     }
}

void doublevector::push_back(double value)
{
     //Push back just resizes the 1 larger with the chosen value
     resize(mNumValues + 1, value);
}

double &doublevector::at(int index)
{
     //Check that the index is valid, and return the value if it is
     if (index >= mNumValues)
     {
          ostringstream sout;
          sout << "Invalid index #" << index;
          throw out_of_range(sout.str());
     }
     else
     {
          return mValues[index];
     }
}

const double &doublevector::at(int index) const
{
     //Check that the index is valid, and return the value if it is
     if (index >= mNumValues)
     {
          ostringstream sout;
          sout << "Invalid index #" << index;
          throw out_of_range(sout.str());
     }
     else
     {
          return mValues[index];
     }
}

unsigned long doublevector::size() const
{
     //Typecast the number of values that we already track into an unsigned long
     unsigned long rtn = mNumValues;
     return rtn;
}