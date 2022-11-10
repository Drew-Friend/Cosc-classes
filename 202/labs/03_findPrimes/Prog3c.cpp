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

int random_number() { return (rand() % 202) + 1; }

int main(int argc, char *argv[]) {
  // Setup
  int N = (argc == 2) ? strtol(argv[1], NULL, 10) : 202;
  isprime check;
  srand(N);
  vector<int> nums(N);
  generate(nums.begin(), nums.end(), random_number);

  // Check for primes, reuse array because it isn't used for anything else
  transform(nums.begin(), nums.end(), nums.begin(), check);
  int c = count(nums.begin(), nums.end(), true);
  cout << "Sequence contained " << c << " prime numbers.\n";
}

// Make sure list covers input, search list for input
bool isprime::operator()(int number) {
  if (pList.back() <= number)
    expand_plist(number);

  return binary_search(pList.begin(), pList.end(), number);
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