/*
    Drew Friend
    9/12/2022
    Quicksort and Quickselect algorithm
    Score: 98/100
*/
// include header files needed
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

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
};

istream &operator>>(istream &in, Data &r) {
  // write this to read data object data
  in >> r.firstname >> r.lastname >> r.phonenum;
  return in;
}

ostream &operator<<(ostream &out, const Data &r) {
  // write this to write data object data
  // 22-r.firstname.length()-r.lastname.length()
  int size = 22 - r.lastname.length();
  out << left << r.lastname << ", " << setw(size) << r.firstname << r.phonenum;
  return out;
}

template <typename T> int partition(vector<T> &A, int left, int right) {
  // Make random pivot
  int pindex = left + (rand() % (right - left));
  T pivot = A[pindex];
  // Move pivot to it's correct location in the list
  // Move values less than pivot to the left side
  swap(A[pindex], A[right]);
  int i = left - 1;
  for (int j = left; j < right; ++j)
    if (A[j] < pivot)
      swap(A[++i], A[j]);
  swap(A[right], A[++i]);
  return i;
}

template <typename T> void quicksort(vector<T> &A, int left, int right) {
  // int far = A.size() - 1;
  if (left < right) {
    // int pindex = partition(A, left, right);
    int pindex = left + (rand() % (right - left + 1));
    T pivot = A[pindex];
    // Move pivot to it's correct location in the list
    // Move values less than pivot to the left side
    swap(A[pindex], A[right]);
    int i = left - 1;
    for (int j = left; j < right; ++j)
      if (A[j] < pivot)
        swap(A[++i], A[j]);
    swap(A[right], A[++i]);
    pindex = i;
    quicksort(A, left, pindex - 1);
    quicksort(A, pindex + 1, right);
  }
  // printlist(A.begin(), A.end());
}

template <typename Tdata>
void quickselect(vector<Tdata> &A, int left, int k, int right) {
  // write this
  int pindex;
  Tdata pivot;
  // int far = A.size() - 1;
  while (1) {
    // Partition Begin
    pindex = left + (rand() % (right - left + 1));
    pivot = A[pindex];
    swap(A[pindex], A[right]);
    int i = left - 1;
    // Partition around pivot, < >
    for (int j = left; j < right; ++j)
      if (A[j] < pivot)
        swap(A[++i], A[j]);
    swap(A[right], A[++i]);
    // Partition End
    pindex = i;
    // If the pivot was the desired partition, exit
    if (pindex == k)
      return;
    // If the pivot was greater than desired, take a large index out of the list
    if (k < pindex)
      right = pindex - 1;
    // if less than desired, take out a small index
    else
      left = pindex + 1;
    // Problem may be:
  }
}

template <typename dataIt> void printlist(dataIt start, dataIt end) {
  for (; start != end; ++start) {
    cout << *start << '\n';
  }
}

int main(int argc, char *argv[]) {
  // perform command-line error checking
  // usage: Qsort -stl | -rpivot [k0 k1] file.txt
  ifstream fin;
  string sorting_option = argv[1];
  fin.open(argv[argc - 1]);
  vector<Data> A;
  Data din;
  srand(time(NULL));
  while (fin >> din)
    A.push_back(din);
  fin.close();

  if (sorting_option == "-stl") {
    sort(A.begin(), A.end());
  } else if (sorting_option == "-rpivot") {
    int N = (int)A.size();
    int k0, k1;
    if (argc == 3) {
      k0 = 0;
      k1 = N - 1;
    } else {
      k0 = atoi(argv[2]);
      k0 = (k0 < 0) ? 0 : k0;
      k1 = atoi(argv[3]);
      k1 = (k1 >= (N)) ? N - 1 : k1;
      quickselect(A, 0, k0, N - 1);
      printlist(A.begin(), A.end());
      quickselect(A, k0, k1, N - 1);
    }

    // if specified, update k0, k1 and apply quickselect
    // to ensure that A[0:k0-1] <= A[k0:k1] <= A[k1+1:N-1]

    quicksort(A, k0, k1);
  }

  printlist(A.begin(), A.end());
}
