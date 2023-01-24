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
    for (int a = 1; a < arr.size(); a++) {
      for (int b = 1; b < arr[a].size(); b++) {
        cout << setw(3) << arr[a - 1][b - 1];
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
  void print_diff(); //{ print_diff(0, 0); }

private:
  void print_edit(int, int, int, int);
  void print_diff(int, int);

  vector<string> text1;
  vector<string> text2;
  vector<int> trace;
  matrix cost;
  matrix link;
  const int DIAG, VERT, HORZ;
  int m, n, trcMk;
};
text_align::text_align() : DIAG(1), VERT(2), HORZ(4) {}

void text_align::compute_lcs() {
  m = text1.size() + 1;
  n = text2.size() + 1;

  trace.resize(m + n);
  cost.append(m, n, 0);
  link.append(m, n, 0);
  // Across the top, all horizontal
  for (int i = 1; i <= m; i++) {
    cost.append(i, 0, cost.get(i - 1, 0) + 1);
    link.append(i, 0, HORZ);
  }
  // Down the left, all vertical
  for (int j = 1; j <= n; j++) {
    cost.append(0, j, cost.get(0, j - 1) + 1);
    link.append(0, j, VERT);
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      // May need to change, Involved substitution
      if (text1[i] == text2[j]) {
        cost.append(i, j, cost.get(i - 1, j - 1));
        link.append(i, j, DIAG);
      } else
        cost.append(i, j, INT_MAX);

      int delcost = cost.get(i - 1, j) + 1;
      if (delcost < cost.get(i, j)) {
        cost.append(i, j, delcost);
        link.append(i, j, HORZ);
      }

      int inscost = cost.get(i, j - 1) + 1;
      if (inscost < cost.get(i, j)) {
        cost.append(i, j, inscost);
        link.append(i, j, VERT);
      }
    }
  }
  // cost.print();
  // cout << "\n";
  // link.print();
}

void text_align::print_diff(int i, int j) {
  // if (i == 0 && j == 0) {
  //   for (int k = 0, i = (int)trace.size() - 1; 0 <= i; i--) {
  //     if (trace[i] != HORZ)
  //       cout << text1[++k];
  //     else
  //       cout << '-';
  //   }
  //   cout << "\n";
  //   for (int k = 0, i = (int)trace.size() - 1; 0 <= i; i--) {
  //     if (trace[i] != VERT)
  //       cout << text2[++k];
  //     else
  //       cout << '-';
  //   }
  //   cout << "\n";
  //   return;
  // }

  if (link.get(i, j) & DIAG) {
    trace[trcMk++] = DIAG;
    print_diff(i - 1, j - 1);
  } else if (link.get(i, j) & VERT) {
    trace[trcMk++] = VERT;
    print_diff(i, j - 1);
  } else if (link.get(i, j) & HORZ) {
    trace[trcMk++] = HORZ;
    print_diff(i - 1, j);
  }
}

void text_align::print_diff() {
  trcMk = 0;
  print_diff(text1.size(), text2.size());

  int i1 = 0;
  int e1 = 0;
  int i2 = 0;
  int e2 = 0;
  for (int i = trcMk; i >= 0; --i) {
    if (trace[i] == DIAG) {
      print_edit(++i1, e1, ++i2, e2);
      e1 = i1 + 1;
      e2 = i2 + 1;
    } else if (trace[i] == VERT)
      ++i1;
    else if (trace[i] == HORZ)
      ++i2;
  }
}

void text_align::print_edit(int i1, int e1, int i2, int e2) {
  // Print Description
  if (i1 > e1 || i2 > e2) {
    if (i2 - e2 <= 1)
      cout << i2;
    else
      cout << e2 + 1 << ',' << i2;
    if (i2 == e2)
      cout << 'a';
    else if (i1 == e1)
      cout << 'd';
    else
      cout << 'c';

    if (i1 - e1 <= 1)
      cout << i1;
    else
      cout << e1 + 1 << ',' << i1;
    cout << '\n';
  }

  // Print from text 1
  for (int i = e2; i < i2; ++i) {
    cout << "< " << text1[i] << '\n';
  }
  // Line if change
  if (i1 != e1 && i2 != e2)
    cout << "---\n";
  // Print from text 2
  for (int i = e1; i < i1; ++i) {
    cout << "> " << text2[i] << '\n';
  }
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
  align.print_diff();
}
