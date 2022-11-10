#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
typedef unsigned int uint;
typedef unordered_multimap<string, int> hashTable;

template <typename T> void replace_punctuation(T start, T end) {
  for (; start != end; ++start)
    (*start) = (ispunct((*start)) && (*start) != '_') ? ' ' : (*start);
}

void show_load(hashTable table) {
  float percent_inuse = table.load_factor();
  cout << fixed << setprecision(2) << "** N = " << right << setw(6)
       << table.bucket_count() << " load = " << percent_inuse << "\n";
}

int main(int argc, char *argv[]) {
  // Initializations
  bool verbose = false;
  ifstream fin;
  istringstream sin;
  vector<string> cache;
  vector<int> lines;
  pair<hashTable::iterator, hashTable::iterator> bounds;
  hashTable H;
  string key;

  // Command line parsing / error checking
  if (argc != 3 && argc != 4) {
    cout << "usage: ./hash1 [-verbose] -f textfile\n";
    return 1;
  }
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], "-f")) {
      if (argc > i + 1) {
        fin.open(argv[i + 1]);
        if (!fin.is_open()) {
          cerr << "error opening file: " << argv[i + 1] << '\n';
          return 1;
        }
      }
    } else if (!strcmp(argv[i], "-verbose")) {
      verbose = true;
      show_load(H);
    }
  }

  // Read into cache entries with punctuation
  // Read into stringstream without punctuation, parse words from stringstream
  while (getline(fin, key)) {
    cache.push_back(key);
    replace_punctuation(key.begin(), key.end());
    sin.clear();
    sin.str(key);
    while (sin >> key) {
      H.insert(make_pair(key, cache.size() - 1));
    }
  }
  fin.close();

  // Show extra information if requested
  if (verbose)
    show_load(H);

  // Search loop with user input
  cout << "find> ";
  while (cin >> key) {
    bounds = H.equal_range(key);
    // Double for loop is because the bucket has the line numbers in reverse
    // order, and I was having issues decrementing through the bounds
    for (; bounds.first != bounds.second; ++bounds.first)
      lines.push_back((*bounds.first).second);
    for (int i = lines.size() - 1; i >= 0; --i)
      cout << lines[i] + 1 << ": " << cache[lines[i]] << '\n';
    lines.clear();
    cout << "find> ";
  }
}