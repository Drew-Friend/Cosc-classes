/*
  Drew Friend
  10/19/2022
  FriendNet Graph version 1
  Using dense matrix
*/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

class vtable {
public:
  int size() { return vLabels.size(); }
  void push(string &nLabel) { vLabels.push_back(nLabel); }
  string operator[](int i) { return vLabels[i]; }

  vector<string>::iterator begin() { return vLabels.begin(); }
  vector<string>::iterator end() { return vLabels.end(); }

private:
  vector<string> vLabels;
};

class adjtable {
public:
  int size() { return edges.size(); }

  void set_size(int s) {
    edges.resize(s);
    for (vector<int> &i : edges)
      i.resize(s);
  }
  vector<int> &operator[](int i) { return edges[i]; }

private:
  vector<vector<int>> edges;
};

void set_oldfriends(vtable &names, adjtable &friends, int M0, int M1) {
  int N = (int)names.size();
  friends.set_size(N);

  vector<int> do_know;
  for (int i = 0; i < N; ++i)
    do_know.push_back(i);

  for (int i = 0; i < N; ++i) {
    int num = (rand() % (M1 - M0)) + M0;
    random_shuffle(do_know.begin(), do_know.end());
    for (int j = 0; j < num; ++j) {
      // If the index is found, just skip and look another place down
      if (do_know[j] == i) {
        ++num;
        continue;
      }

      friends[do_know[j]][i] = 1;
      friends[i][do_know[j]] = 1;
    }
  }
}

void set_newfriends(adjtable &friends, adjtable &new_friends) {
  int N = (int)friends.size();
  new_friends.set_size(N);

  // I is the person we are recomending to
  // J is their friend we are looking at contacts of
  // K is a friend of J, who will be recomended to I
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (friends[i][j]) {
        for (int k = 0; k < N; ++k) {
          if (i != k && friends[j][k] && !friends[i][k])
            new_friends[i][k] = 1;
        }
      }
    }
  }
}

void writetofile(const char *fname, vtable &name, adjtable &friends) {
  int N = (int)name.size();
  int lenMax = 0;
  //   determine max name length
  for (int i = 0; i < N; ++i)
    lenMax = (lenMax < name[i].size()) ? name[i].size() : lenMax;
  ofstream fout(fname);

  for (int i = 0; i < N; ++i) {
    fout << left << setw(lenMax) << name[i] << " : ";
    for (int j = 0; j < N; ++j) {
      if (friends[i][j])
        fout << left << setw(lenMax) << name[j] << " ";
    }
    fout << '\n';
  }
  fout.close();
}

int main(int argc, char **argv) {
  // unix> ./Friendnet [-seed=N] [-M0=N] [-M1=N]
  int m0 = 1;
  int m1 = 2;
  vtable names;
  string newName = "";
  adjtable friends;
  adjtable newfriends;
  // ifstream fin;

  // Collect command line arguments
  for (int i = 1; i < argc; ++i) {
    if (((string)argv[i]).compare(0, 6, "-seed=") == 0)
      srand(stoi(argv[i] + 6));
    else if (((string)argv[i]).compare(0, 4, "-M0=") == 0)
      m0 = stoi(argv[i] + 4);
    else if (((string)argv[i]).compare(0, 4, "-M1=") == 0)
      m1 = stoi(argv[i] + 4);
    // else if (((string)argv[i]).compare(strlen(argv[i]) - 4, 4, ".txt") == 0)
    //   fin.open(argv[i]);
    else {
      cerr << "Usage: ./Friendnet datafile.txt [-seed=N] [-M0=N] [-M1=N]";
      return 1;
    }
  }
  // Error check friend boundaries
  if (m0 <= 0 || m1 < m0 || m1 >= 6) {
    cerr << "Error: ensure 0 < M0 ≤ M1 < 6.";
    return 1;
  }
  // if (!fin.is_open()) {
  //   cerr << "Error: Invalid File named.";
  //   return 1;
  // }

  // Collect Names
  while (cin >> newName) {
    if (cin.eof())
      break;
    else {
      names.push(newName);
    }
  }

  sort(names.begin(), names.end());
  set_oldfriends(names, friends, m0, m1);
  set_newfriends(friends, newfriends);
  writetofile("do_know1.txt", names, friends);
  writetofile("might_know1.txt", names, newfriends);
}