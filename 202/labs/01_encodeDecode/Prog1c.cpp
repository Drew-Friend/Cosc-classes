#include <iostream>

class stats {
  // Initialize private variables
  int min = 0;
  int iterations = 0;
  int sum = 0;
  int big = 0;

public:
  // Output variables
  void print() {
    std::cout << "N   = " << iterations << "\nsum = " << sum
              << "\nmin = " << min << "\nmax = " << big << "\n";
  }
  // Update variables for each input
  void push(int val) {
    iterations++;
    sum += val;
    big = (val > big) ? val : big;
    min = (val < min || min == 0) ? val : min;
  }
};

int main() {
  stats math;
  int val;
  // Continue the cycle for each value given
  while (std::cin >> val) {
    math.push(val);
    val = 0;
  }
  math.print();
  return 0;
}
