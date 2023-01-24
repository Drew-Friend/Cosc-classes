#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class matrix {
  vector<vector<int>> arr;

public:
  matrix();
  void append(int, int, int);
  int get(int x, int y) { return arr[x][y]; }
  void print() {
    for (auto x : arr) {
      for (auto y : x) {
        cout << setw(3) << y;
      }
      cout << '\n';
    }
  }
};
void matrix::append(int x, int y, int val) {
  if (x >= arr.size())
    arr.resize(x + 1, vector<int>(y + 1, 0));
  arr[x][y] = val;
}
matrix::matrix() { arr.push_back({0}); }

class text_align {
public:
  text_align();

  void load_data1(string &);
  void load_data2(string &);

  void compute_lcs();
  void print_diff();

private:
  void print_edit();
  void print_diff(int, int);

  vector<string> text1;
  vector<string> text2;
  matrix costs;
  matrix links;
  const int DIAG, VERT, HORZ;
};
text_align::text_align() : DIAG(1), VERT(2), HORZ(4) {}

void text_align::compute_lcs() {
  int x = 0;
  int y = 0;

  int j = 0;
  for (int i = 0; i < text1.size(); ++i) {
    int cost = costs.get(x, y);
    cout << "(" << x << ',' << y << "):  " << cost << '\n';
    cout << text1[i] << "\n" << text2[j] << "\n";
    if (text1[i] == text2[j]) { // Match
      cout << "match\n";
      costs.append(++x, ++y, cost);
      links.append(x, y, DIAG);
    } else if (text1[i + 1] == text2[j]) { // Delete
      cout << "delete\n";
      ++i;
      costs.append(x, ++y, cost + 1);
      links.append(x, y, VERT);
    } else { // Insert
      cout << "insert\n";
      costs.append(++x, y, cost + 1);
      links.append(x, y, HORZ);
    }
    ++j;
  }
  costs.print();
  links.print();
}

void text_align::load_data1(string &data) { text1.push_back(data); }
void text_align::load_data2(string &data) { text2.push_back(data); }

int main(int argc, char *argv[]) {
  // check that input files are specified on command line
  // ensure they can be opened and if not, report and exit
  ifstream fin;
  string line;

  text_align align = text_align(); // instantiate "LCS based diff" object
  // read the text from file1 into text_align::text1 buffer
  fin.open(argv[1]);
  while (getline(fin, line))
    align.load_data1(line);
  fin.close();

  // // read the text from file2 into text_align::text2 buffer
  fin.open(argv[2]);
  while (getline(fin, line))
    align.load_data2(line);
  fin.close();

  align.compute_lcs();
  // align.print_diff();
}
