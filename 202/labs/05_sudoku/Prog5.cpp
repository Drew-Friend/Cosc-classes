#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define ROW_INUSE 0x1
#define COLUMN_INUSE 0x2
#define SQUARE_INUSE 0x4

class sudoku {
  struct cell {
    int col, row;
  };

public:
  sudoku();
  void solve();
  void test_error_check();

  void read(const char *);
  void write(const char *);
  void write(const char *, const char *);

private:
  bool solve(bool);

  void set_inuse(int, int, int);
  void unset_inuse(int, int, int);

  void get_values(int, int, vector<int> &);

  void display();
  void error_check(int);

  int square_index(int, int);
  int game[9][9];
  int inuse[9][10];
  vector<int> empty_sqrs;
};

sudoku::sudoku() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      game[i][j] = 0;

    for (int j = 0; j < 10; j++)
      inuse[i][j] = 0;
  }
  for (int i = 0; i < 81; i++)
    empty_sqrs.push_back(i);
}

int sudoku::square_index(int i, int j) { return 3 * (i / 3) + (j / 3); }

void sudoku::solve() {
  display();
  error_check(0);
  cout << "SOLVE\n";

  // call recursive solve function
  solve(true);

  if (empty_sqrs.size() == 0)
    display();

  error_check(1);
}

bool sudoku::solve(bool trash) {
  // I used all class variables, so I didn't need arguements, but because there
  // are 2 functions named solve it had to have an arguement to distinguish it

  // If complete, return true
  if (empty_sqrs.size() == 0)
    return true;

  // Find cell with fewest values
  // If a cell is empty and still has no valid moves, return false
  vector<int> prevLow, test;
  int index, place;
  prevLow.resize(10, 10);
  for (int i = 0; i < empty_sqrs.size(); ++i) {
    get_values(empty_sqrs[i] / 9, empty_sqrs[i] % 9, test);
    if (prevLow.size() >= test.size()) {
      if (test.size() == 0)
        return false;
      if (prevLow[0] > test[0]) {
        index = empty_sqrs[i];
        prevLow = test;
      }
    }
    test.resize(0);
  }

  // For each possible value of the cell with the least options, attempt to
  // solve the rest of the puzzle.
  for (int i = 0; i < prevLow.size(); ++i) {
    set_inuse(index / 9, index % 9, prevLow[i]);
    if (solve(true))
      return true;
    unset_inuse(index / 9, index % 9, prevLow[i]);
  }

  // If no valid value in this square completes the game, empty it and go up a
  // level
  return false;
}

void sudoku::read(const char *fname) {
  cout << "READ\n";

  ifstream fin(fname);

  int i, j, value, line = 0;
  bool err = false;

  while (fin >> i >> j >> value) {
    ++line;
    // error check value
    if (0 > i || i > 8 || 0 > j || j > 8 || 0 > value || value > 9) {
      cout << "line " << line << ": " << i << ' ' << j << ' ' << value
           << " out-of-bounds grid index\n";
      err = true;
      continue;
    }
    set_inuse(i, j, value);
  }
  fin.close();
  if (err)
    exit(1);

  // if bad indices, value encountered
  // print error message and exit
}

void sudoku::write(const char *fname) {
  ofstream fout(fname);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (0 < game[i][j]) {
        fout << i << " " << j << " " << game[i][j] << "\n";
      }
    }
  }

  fout.close();
}

void sudoku::write(const char *fname, const char *addon) {
  int N1 = strlen(fname);
  int N2 = strlen(addon);

  char *n_fname = new char[N1 + N2 + 2];

  // strip .txt suffix, then concatenate _addon.txt
  strncpy(n_fname, fname, N1 - 4);
  strcpy(n_fname + N1 - 4, "_");
  strcpy(n_fname + N1 - 3, addon);
  strcpy(n_fname + N1 - 3 + N2, ".txt");

  write(n_fname);

  delete[] n_fname;
}

void sudoku::set_inuse(int i, int j, int value) {
  game[i][j] = value;
  int k = square_index(i, j);

  inuse[i][value] |= ROW_INUSE;
  inuse[j][value] |= COLUMN_INUSE;
  inuse[k][value] |= SQUARE_INUSE;

  for (int ctr = 0; ctr < empty_sqrs.size(); ++ctr)
    if (empty_sqrs[ctr] == (i * 9 + j)) {
      empty_sqrs.erase(empty_sqrs.begin() + ctr);
      return;
    }
}

void sudoku::unset_inuse(int i, int j, int value) {
  game[i][j] = 0;
  int k = square_index(i, j);

  inuse[i][value] &= ~ROW_INUSE;
  inuse[j][value] &= ~COLUMN_INUSE;
  inuse[k][value] &= ~SQUARE_INUSE;

  for (int ctr = 0; ctr < empty_sqrs.size(); ++ctr)
    if (empty_sqrs[ctr] > (i * 9 + j)) {
      empty_sqrs.insert(empty_sqrs.begin() + ctr, (i * 9 + j));
      return;
    }
  empty_sqrs.push_back((i * 9 + j));
  return;
}

void sudoku::get_values(int i, int j, vector<int> &value_list) {
  // For each possible number, if it is not found in the row, column, or square,
  // add it to the list
  for (int c = 1; c < 10; ++c) {
    if (inuse[i][c] & ROW_INUSE || inuse[j][c] & COLUMN_INUSE ||
        inuse[square_index(i, j)][c] & SQUARE_INUSE) {
      continue;
    }
    value_list.push_back(c);
  }
}

void sudoku::test_error_check() { error_check(1); }

void sudoku::error_check(int mode) {
  vector<int> bad_values;
  vector<int> loc;
  for (int i = 0; i < 81; ++i) {
    int row = i / 9;
    int column = i % 9;
    int square = square_index(row, column);
    int spos = row - 3 * (row / 3);
    spos *= 3;
    spos += column - 3 * (column / 3);
    int val = game[row][column];
    if (val > 9 || val < mode)
      exit(1);
    if (val == 0)
      continue;
    for (int j = 0; j < 9; ++j) {
      if ((game[row][j] == val && j != column)) {
        // cout << pH[0] << pH[1] << pH[2] << '\n';
        loc.push_back(row);
        bad_values.push_back(val);
      }
      if (game[j][column] == val && j != row) {
        // cout << pH[0] << pH[1] << pH[2] << '\n';
        loc.push_back(column);
        bad_values.push_back(val + 10);
      }
      if (game[(j / 3) + 3 * (row / 3)][(j % 3) + 3 * (column / 3)] == val &&
          j != spos) {
        // cout << pH[0] << pH[1] << pH[2] << '\n';
        loc.push_back(square);
        bad_values.push_back(val + 20);
      }
    }
  }
  if (bad_values.size() == 0)
    return;
  int rep = 1;
  for (int rpt = 0; rpt < bad_values.size(); ++rpt) {
    if (bad_values[rpt] < 10)
      cout << "row[";
    else if (bad_values[rpt] < 20)
      cout << "column[";
    else
      cout << "square[";
    cout << loc[rpt] << "]: " << bad_values[rpt] % 10 << " seen ";
    for (int dbl = rpt + 1; dbl < bad_values.size(); ++dbl)
      if (loc[rpt] == loc[dbl] && bad_values[rpt] == bad_values[dbl]) {
        bad_values.erase(bad_values.begin() + dbl);
        loc.erase(loc.begin() + dbl);
        ++rep;
      }
    cout << rep << " times\n";
    rep = 1;
  }
  exit(1);

  // check rows, columns, squares
  // for uniqueness of data values
}

void sudoku::display() {
  cout << "| --------------------------- |\n";
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (j == 0)
        cout << "| " << game[i][j];
      else if (j % 3 == 0)
        cout << " | " << game[i][j];
      else
        cout << "  " << game[i][j];
    }
    cout << " |\n";
    if (i % 3 == 2)
      cout << "| --------------------------- |\n";
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  sudoku sudoku_game;
  sudoku_game.read(argv[1]);
  sudoku_game.solve();
  sudoku_game.write(argv[1], "solved");
}
