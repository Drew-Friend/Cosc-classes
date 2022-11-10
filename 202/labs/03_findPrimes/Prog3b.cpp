#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

class isprime {
public:
  isprime() { pList.push_back(2); }
  bool operator()(int);

private:
  vector<int> pList;
  void expand_plist(int);
};

// Make sure list covers input, search list for input
bool isprime::operator()(int number) {
  if (pList.back() <= number)
    expand_plist(number);
  vector<int>::iterator index;

  index = find(pList.begin(), pList.end(), number);

  return index != pList.end();
}

// Check increasing numbers until a prime is found larger than the desired
// number, add all primes as they are found
void isprime::expand_plist(int number) {
  int counter = pList.back();
  while (pList.back() <= number) {
    counter++;
    int root = ceil(sqrt(counter));
    for (int i = 2; i <= root; i++) {
      if (!(counter % i) || pList.back() == counter)
        break;
      if (i == root)
        pList.push_back(counter);
    }
  }
}

int main() {
  // Set up
  isprime pcheck;
  int number;

  // Take in values and evaluate
  while (cin >> number) {
    if (pcheck(number))
      cout << number << " is a prime number\n";
  }
}
