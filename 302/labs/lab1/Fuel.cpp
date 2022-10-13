/*
Drew Friend
Lab 1, 9/6/22
"Drescription of lab, idc to add it retroactively"
*/
#include <algorithm>
#include <exception>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

enum fuel_type { REGULAR, MIDGRADE, PREMIUM, DIESEL };
string fuelType[4]{"Regular", "Midgrade", "Premium", "Diesel"};
string months[12]{"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct sale {
  int day;
  int month;
  int year;
  int dateAdj;
  fuel_type type = {};
  double qty;
  double unitPrice;
  double subtotal;
};

struct sale_summary {
  sale_summary();
  sale_summary(const sale &);

  double subtotal;
  double qty;
  void operator+=(const sale &newSale) {
    subtotal += newSale.subtotal;
    qty += newSale.qty;
  }
};
sale_summary::sale_summary() {
  subtotal = 0;
  qty = 0;
}
sale_summary::sale_summary(const sale &start) {
  subtotal = start.subtotal;
  qty = start.qty;
}

bool operator>>(istream &stream, sale &purchase) {
  // extract data for sale object
  string date, type, temp;
  stream >> date >> type >> purchase.qty >> purchase.unitPrice;
  if (type == "Midgrade")
    purchase.type = MIDGRADE;
  else if (type == "Premium")
    purchase.type = PREMIUM;
  else if (type == "Diesel")
    purchase.type = DIESEL;
  else
    purchase.type = REGULAR;
  stringstream day(date);
  getline(day, temp, '-');
  try {
    purchase.month = stoi(temp);
  } catch (exception &) {
    return false;
  }
  getline(day, temp, '-');
  purchase.day = stoi(temp);
  getline(day, temp, '-');
  purchase.year = stoi(temp);
  purchase.subtotal = purchase.qty * purchase.unitPrice;

  purchase.dateAdj =
      purchase.year * 10000 + purchase.month * 100 + purchase.day;

  // check for EOF and return as necessary
  return (stream.peek() != EOF);
}

ostream &operator<<(ostream &stream, const sale &purchase) {
  // print properly formatted data
  stream << fixed << setprecision(2) << left << setw(3)
         << months[purchase.month - 1] << " " << setw(2) << right
         << purchase.day << ", " << setw(4) << right << purchase.year << " "
         << setw(8) << left << fuelType[purchase.type] << setw(8) << right
         << purchase.qty << " x " << setw(4) << purchase.unitPrice << " = "
         << setw(7) << right << purchase.subtotal;
  return stream;
}

void operator<<(ostream &, const sale_summary &) {
  // print properly formatted data
}

bool cmp_bydate(const sale &sale1, const sale &sale2) {
  return sale1.dateAdj < sale2.dateAdj;
}
bool cmp_bytype(const sale &sale1, const sale &sale2) {
  return sale1.type < sale2.type;
}

void print_details(vector<sale>::iterator p0, vector<sale>::iterator p1) {
  double total = 0.0;
  for (; p0 != p1; ++p0) {
    total += p0->subtotal;
    cout << *p0 << " : " << total << "\n";
  }
}
void print_summary_bydate(vector<sale>::iterator p0,
                          vector<sale>::iterator p1) {
  // std::map<date,sale_summary> build map from input data
  double total = 0.0;
  map<int, sale_summary> by_date;
  for (; p0 != p1; ++p0)
    if (by_date.find(p0->dateAdj) == by_date.end())
      by_date.insert({p0->dateAdj, sale_summary(*p0)});
    else
      by_date.at(p0->dateAdj) += *p0;
  // write iterator based output loop for summarized data
  for (map<int, sale_summary>::iterator i = by_date.begin(); i != by_date.end();
       ++i) {
    int year = i->first / 10000;
    int day = i->first % 100;
    int month = (i->first % 10000 - day) / 100;
    total += i->second.subtotal;
    cout << left << (months[month - 1]) << " " << right << setw(2) << day
         << ", " << setw(4) << year << " " << setw(10) << i->second.qty << " x "
         << setprecision(2) << fixed << i->second.subtotal / i->second.subtotal
         << " = " << setw(8) << i->second.subtotal << " : " << setw(9) << total
         << '\n';
  }
}

void print_summary_bytype(vector<sale>::iterator p0,
                          vector<sale>::iterator p1) {
  double total = 0.0;
  map<fuel_type, sale_summary> by_date;
  for (; p0 != p1; ++p0)
    if (by_date.find(p0->type) == by_date.end())
      by_date.insert({p0->type, sale_summary(*p0)});
    else
      by_date.at(p0->type) += *p0;
  // write iterator based output loop for summarized data
  for (map<fuel_type, sale_summary>::iterator i = by_date.begin();
       i != by_date.end(); ++i) {
    total += i->second.subtotal;
    cout << left << setw(12) << fuelType[i->first] << right << " " << setw(10)
         << i->second.qty << " x " << setprecision(2) << fixed
         << i->second.subtotal / i->second.subtotal << " = " << setw(8)
         << i->second.subtotal << " : " << setw(9) << total << '\n';
  }
}

int main(int argc, char *argv[]) {
  // command line processing:
  string sort_mode = argv[1];
  string output_mode = argv[2];
  string input_file = argv[3];
  vector<sale> DB;
  ifstream fin;
  sale F;
  map<fuel_type, sale_summary> by_type;

  fin.open(input_file);
  while (fin >> F) {
    DB.insert(DB.cend(), F);
  }

  if (sort_mode == "-bydate") {
    sort(DB.begin(), DB.end(), cmp_bydate);
  } else if (sort_mode == "-bytype") {
    sort(DB.begin(), DB.end(), cmp_bytype);
  }

  if (output_mode == "-summary") {
    if (sort_mode == "-bydate") {
      print_summary_bydate(DB.begin(), DB.end());
    } else if (sort_mode == "-bytype") {
      print_summary_bytype(DB.begin(), DB.end());
    }
  } else {

    print_details(DB.begin(), DB.end());
  }
}