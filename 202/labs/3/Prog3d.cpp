#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

class isprime
{
public:
  isprime() { pList.push_back(2); }
  bool operator()(int);

private:
  list<int> pList;
  void expand_plist(int);
};

int random_number()
{
  return (rand() % 202) + 1;
}

// Copy all values cooresponding to a "true" to the primes array
void extract_prime(vector<int> *vals, vector<bool> *cat, vector<int> *out)
{
  for (int i = 0; i < cat->size(); i++)
    if (cat->at(i))
      out->push_back(vals->at(i));
}

// Print formatted table
void print(vector<int> field)
{
  for (int i = 0; i < field.size(); i++)
    cout << setw(4) << field[i] << (((i + 1) % 20) ? ' ' : '\n');
  cout << '\n';
}

int main(int argc, char *argv[])
{
  // Setup
  int N = (argc == 2) ? strtol(argv[1], NULL, 10) : 202;
  isprime check;
  srand(N);
  vector<int> nums(N);
  generate(nums.begin(), nums.end(), random_number);

  // Check for primes
  vector<bool> cat(N);
  transform(nums.begin(), nums.end(), cat.begin(), check);
  int c = count(cat.begin(), cat.end(), true);
  cout << "Sequence contained " << c << " prime numbers.\n";

  // Extract primes
  vector<int> primes;
  extract_prime(&nums, &cat, &primes);
  cout << "All numbers in order appearance:\n";
  print(primes);

  // Sort and remove duplicates
  sort(primes.begin(), primes.end());
  unique(primes.begin(), primes.end());
  cout << "Unique values in numerical order:\n";
  while (find(primes.begin(), primes.end(), primes.back()) != primes.end() - 1)
    primes.erase(primes.end() - 1);
  print(primes);
}

// Make sure list covers input, search list for input
bool isprime::operator()(int number)
{
  if (pList.back() < number)
    expand_plist(number);

  return binary_search(pList.begin(), pList.end(), number);
}

// Check increasing numbers until a prime is found larger than the desired number, add all primes as they are found
void isprime::expand_plist(int number)
{
  int counter = pList.back();
  while (pList.back() < number)
  {
    counter++;
    int root = ceil(sqrt(counter));
    for (int i = 2; i <= root; i++)
    {
      if (!(counter % i) || pList.back() == counter)
        break;
      if (i == root)
        pList.push_back(counter);
    }
  }
}