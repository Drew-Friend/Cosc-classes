// Generate a list of random cities in a 20x20 grid
// Number of cities is chosen in the command terminal
// Find the shortest route that visits each city once, and returns to original
// point Add something visual maybe?

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> coord;

class Salesman {
  vector<coord> schedule;
  int len;

public:
  // Takes the list of cities generated and mixes it up by poping random
  // elements and putting them at the end
  Salesman(vector<coord> gen) {
    len = gen.size();
    int ind;
    coord ph;
    for (int i = 0; i < len / 3; ++i) {
      ind = rand() % len;
      ph = gen[ind];
      gen.erase(gen.begin() + ind);
      gen.push_back(ph);
    }
    schedule = gen;
  }

  // Adding the 2 will take the lower half of the
  // second parent and insert it to the end of
  // parent 1's list, removing the earlier instance
  // At some point please make this return a salesman, not a vector
  vector<coord> operator+(Salesman &p2) {
    vector<coord> top = schedule;
    vector<coord> bottom = p2.lower();
    for (vector<coord>::iterator check = bottom.begin(); check != bottom.end();
         check++) {
      for (vector<coord>::iterator search = top.begin(); search != top.end();
           search++) {
        if (*search == *check) {
          top.erase(search);
          break;
        }
      }
      top.push_back(*check);
    }
    return top;
  }

  bool operator<(Salesman &p2) { return distCalc() < p2.distCalc(); }
  bool operator>(Salesman &p2) { return distCalc() > p2.distCalc(); }

  // Used to do breeding
  vector<coord> lower() {
    vector<coord> half = schedule;
    while (half.size() > len)
      half.pop_back();
    return half;
  }

  // Returns the total distance traveled by the mailman, basically the opposite
  // of the fitness of the individual
  double distCalc() {
    double dist = 0.0;
    double check = 0;
    for (int i = 1; i < len; ++i) {
      dist += sqrt(pow(schedule[i].first - schedule[i - 1].first, 2) +
                   pow(schedule[i].second - schedule[i - 1].second, 2));
    }
    dist += sqrt(pow(schedule[0].first - schedule[len - 1].first, 2) +
                 pow(schedule[0].second - schedule[len - 1].second, 2));
    return dist;
  }

  void print() {
    for (int i = 0; i < len; ++i)
      cout << '(' << setw(2) << schedule[i].first << ", " << setw(2)
           << schedule[i].second << "), ";
    cout << "\nTotal Distance: " << distCalc() << '\n';
  }
};

template <typename AI> class BreedingPool {
  int breeding, size;

public:
  BreedingPool(int parent, int pop) {
    breeding = parent;
    size = pop;
  }

  // For every index past the parents, replace with a child of 2 random parents
  // mutation is the same as the initial mix-up, so it isn't needed.
  void newPop(vector<AI> &pop) {
    sort(pop);
    for (int i = breeding; i < size; ++i) {
      pop[i] = Salesman(pop[rand() % breeding] + pop[rand() % breeding]);
      // pop[i].mutate;
    }
  }

  void sort(vector<AI> &pop) {
    Salesman temp({});
    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
        if (pop[i] > pop[j]) {
          temp = pop[i];
          pop[i] = pop[j];
          pop[j] = temp;
        }
      }
    }
  }
};

int main() {
  int gridSize = 20;
  vector<coord> list;

  int len, par, pop;
  cout << "How many cities should be traveled too?  ";
  cin >> len;
  cout << "How many parents are in the population?  ";
  cin >> par;
  cout << "How large is the population? ";
  cin >> pop;

  for (int i = 0; i < len; ++i) {
    list.push_back(make_pair(rand() % gridSize, rand() % gridSize));
    for (int j = 0; j < list.size() - 1; ++j)
      if (list[i] == list[j]) {
        list.pop_back();
        --i;
      }
  }
  BreedingPool<Salesman> bedroom(par, pop);
  vector<Salesman> jerry(pop, Salesman(list));

  // Every cycle, find distances of each, sort them, then create the new
  // generation from the best of the previous
  for (int gen = 0; true; ++gen) {
    bedroom.newPop(jerry);
    if (!(gen % 50)) {
      cout << "Generation " << gen << ":\n";
      for (int i = 0; i < par; ++i) {
        jerry[i].print();
      }
      cin.get();
    }
  }
}