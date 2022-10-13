#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "usage: " << argv[0] << " A|B|C"
         << " k < numbers.txt\n";
    return 0;
  }

  char mode = argv[1][0];
  int k = atoi(argv[2]);

  vector<int> A;

  int din;
  while (cin >> din)
    A.push_back(din);

  int N = (int)A.size();

  if (mode == 'A') {
    // use std::partial_sort()
    partial_sort(A.begin(), A.begin() + k, A.end());
  } else if (mode == 'B') {
    // use std::make_heap(), loop w/std::pop_heap() and std::reverse()
    make_heap(A.begin(), A.end());
    for (int i = 0; i < k; ++i)
      // Popped elements are still within the vector,
      //  so the checked area must shrink each iteration
      //  to pop new elements
      pop_heap(A.begin(), A.end() - i);
    reverse(A.begin(), A.end());

  } else if (mode == 'C') {
    // modify the code from mode B work like mode A
    // Change the comparison from less than(default) to greater than
    make_heap(A.begin(), A.end(), greater<int>());
    for (int i = 0; i < k; ++i)
      pop_heap(A.begin(), A.end() - i, greater<int>());
    reverse(A.begin(), A.end());
  }

  for (int i = 0; i < k; i++)
    cout << A[i] << " *\n";
  for (int i = k; i < N; i++)
    cout << A[i] << "\n";
}