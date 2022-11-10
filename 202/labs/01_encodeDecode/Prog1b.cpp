#include <iostream>

int main() {
  // Initialize variables
  int min = 0;
  int iter = 0;
  int sum = 0;
  int big = 0;
  int rec = 0;

  // Continue using input while available
  while (std::cin >> rec) {
    // Add to the sum and iterations, replace max and min if relevant
    sum += rec;
    iter++;
    big = (rec > big) ? rec : big;
    min = (rec < min || min == 0) ? rec : min;
    rec = 0;
  }
  // Output the variables
  std::cout << "N   = " << iter << "\nsum = " << sum << "\nmin = " << min
            << "\nmax = " << big << '\n';
  return 0;
}
