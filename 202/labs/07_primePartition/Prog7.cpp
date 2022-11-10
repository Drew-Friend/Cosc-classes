#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class prime_partition {
public:
  // constructor
  prime_partition();
  // operator(int)
  void operator()(int);

private:
  void create_pset();
  bool find_partition(int);

  set<int> pset;
  // miscl member data
  int maxPrime;
  int minPrime;
  vector<int> vals;
  set<int>::iterator last;
};

int main(int argc, char *argv[]) {
  prime_partition goldbach;
  int number;
  while (1) {
    cout << "number = ";
    cin >> number;
    if (cin.eof())
      break;

    goldbach(number);
  }

  cout << "\n";
}

prime_partition::prime_partition() {
  maxPrime, minPrime = 2, 2;
  pset.insert(minPrime);
  create_pset();
  last = pset.find(maxPrime);
}

void prime_partition::create_pset() {
  int counter = maxPrime;
  while (maxPrime <= 20000) {
    counter++;
    int root = ceil(sqrt(counter));
    for (int i = 2; i <= root; ++i) {
      if (!(counter % i) || maxPrime == counter)
        break;
      if (i == root) {
        pset.insert(counter);
        maxPrime = counter;
      }
    }
  }
}

void prime_partition::operator()(int num) {
  if (num < minPrime || num > maxPrime)
    return;
  find_partition(num);
  vals.clear();
}

bool prime_partition::find_partition(int num) {
  set<int>::iterator upper_bound = last;
  set<int>::iterator lower_bound = last;
  int sum = 0;
  for (int i = 0; i < vals.size(); ++i)
    sum += vals.at(i);
  if (vals.size() == 2 + (num % 2)) {
    if (sum == num) {
      for (int i = 0; i < vals.size(); ++i)
        cout << vals.at(i) << ' ';
      cout << '\n';
      return true;
    }
    return false;
  }

  // Create testing iterators
  sum = num - sum;
  for (int i = sum; upper_bound == last; ++i) {
    upper_bound = pset.find(i);
    upper_bound = (upper_bound == pset.end()) ? last : upper_bound;
  }
  for (int i = sqrt(sum); lower_bound == last; ++i) {
    lower_bound = pset.find(i);
    lower_bound = (lower_bound == pset.end()) ? last : lower_bound;
  }

  // Check the prime larger than the remainder
  for (; *upper_bound >= *lower_bound; ++lower_bound) {
    vals.push_back(*lower_bound);
    if (find_partition(num))
      return true;
    vals.pop_back();
  }
  return false;
}