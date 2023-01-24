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
  void print_edit();
  vector<string> print_diff(int, int);

  vector<string> text1;
  vector<string> text2;
  matrix cost;
  matrix link;
  const int DIAG, VERT, HORZ;
  int m, n;
};
text_align::text_align() : DIAG(1), VERT(2), HORZ(4) {}

void text_align::compute_lcs() {
  m = text1.size() + 1;
  n = text2.size() + 1;
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
        // cout << "Vertical, (" << i << ',' << j << ')' << delcost << " vs "
        //      << cost.get(i, j) << '\n';
        cost.append(i, j, delcost);
        link.append(i, j, HORZ);
      }

      int inscost = cost.get(i, j - 1) + 1;
      if (inscost < cost.get(i, j)) {
        // cout << "Horizonal, (" << i << ',' << j << ')' << inscost << " vs "
        //      << cost.get(i, j) << '\n';
        cost.append(i, j, inscost);
        link.append(i, j, VERT);
      }
    }
  }
  cost.print();
  cout << "\n";
  link.print();
}

vector<string> text_align::print_diff(int x, int y) {
  /*
    Check for diagonal
    Check for Horizontal
    Check for Vertical
  */
  vector<string> fml = vector<string>();
  cout << '(' << x << ',' << y << "):  " << link.get(x, y) << '\n';
  if (link.get(x, y) == DIAG) {
    fml = print_diff(x - 1, y - 1);
    cout << " assigned M  ";
    fml.push_back("Match");
  } else if (link.get(x, y) == VERT) {
    fml = print_diff(x, y - 1);
    cout << fml.size();
    // fml.push_back("");
    // cout << fml.size();
  } else if (link.get(x, y) == HORZ) {
    fml = print_diff(x - 1, y);
    cout << " assigned H  ";
    fml.push_back("Insert");
  }
  cout << "Done (" << x << ',' << y << "):  " << fml.size() << '\n';
  return fml;
}

void text_align::print_diff() {
  vector<string> ugh = print_diff(text1.size(), text2.size());
  cout << ugh.size();
  cout << "here\n";
  for (int i = 0; i < ugh.size(); ++i)
    cout << ugh[i] << '\n';
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
