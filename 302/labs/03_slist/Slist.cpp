/*
    Drew Friend
    9/22/2022
    Smart pointer sorting
    Score: 98/100
*/
#include "Slist.h"
using namespace std;

// modify the data class and the associated input
// and output operators to store, set and print a
// line number identifier called ID

int IDtrack = 0;

class Data {
public:
  // add operator< using lastname, firstname, phone number
  bool operator<(Data &other) {
    if (lastname == other.lastname) {
      if (firstname == other.firstname)
        return phonenum < other.phonenum;
      return firstname < other.firstname;
    }
    return lastname < other.lastname;
  }
  friend istream &operator>>(istream &, Data &);
  friend ostream &operator<<(ostream &, const Data &);

private:
  string firstname;
  string lastname;
  string phonenum;
  int ID;
};

istream &operator>>(istream &in, Data &r) {
  // write this to read data object data
  in >> r.firstname >> r.lastname >> r.phonenum;
  r.ID = IDtrack++;
  return in;
}

ostream &operator<<(ostream &out, const Data &r) {
  // write this to write data object data
  // 22-r.firstname.length()-r.lastname.length()
  int size = 22 - r.lastname.length();
  out << left << r.lastname << ", " << setw(size) << r.firstname << setw(21)
      << r.phonenum << r.ID;
  return out;
}

template <typename dataIt> void printlist(dataIt start, dataIt end) {
  for (; start != end; ++start) {
    cout << *start << '\n';
  }
}

int main(int argc, char *argv[]) {
  // copy command-line check from Qsort.cpp,
  // then modify to apply to this assignment
  if (argc != 3) {
    cerr << "Usage: ./Slist -[algName] [fileName].txt";
    return 1;
  }
  string sortType = argv[1];
  if (sortType != "-quicksort" && sortType != "-mergesort") {
    cerr << "Usage: ./Slist -[algName] [fileName].txt";
    return 1;
  }
  // open input file
  ifstream fin;
  fin.open(argv[argc - 1]);
  slist<Data> A;
  Data din;
  while (!fin.eof()) {
    fin >> din;
    A.push_back(din);
  }
  fin.close();
  // close input file
  A.sort(sortType);

  printlist(A.begin(), A.end());
}
