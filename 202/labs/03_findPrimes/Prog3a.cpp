#include <iostream>

using namespace std;

// Check integers up to the square root of the input
// If the modulo is ever 0, it is not prime, and returns false
// One is a corner case, is not prime
bool isprime(int number) {
  if (number == 1)
    return false;
  for (int i = 2; i * i <= number; i++)
    if (!(number % i))
      return false;
  return true;
};

int main() {
  int number;

  // Take in values and evaluate
  while (cin >> number) {
    if (isprime(number))
      cout << number << " is a prime number\n";
  }
}
