// Drew Friend
// lab 7, makemaze: Create a random maze using MST
// 11/15

// Point of order: who in the world makes variable names like "Ncols"?
// It's like pascal case minus camel case no distinction between words.
// I'm not a snake case guy, but at least it shows where words start

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

// add constructor, operator overloads as needed
struct cell {
  int i, j;
  cell() {}
  cell(int a, int b) { i = a, j = b; }
};

int main(int argc, char *argv[]) {
  // process command line arguments
  // ./Findpath maze.txt path.txt

  if (argc != 3) {
    printf("Usage: ./Findpath maze.txt path.txt");
    return 1;
  }
  char *ifname = argv[1];
  char *ofname = argv[2];
  // obtain maze size from maze file header
  FILE *ifile;
  errno_t err = fopen_s(&ifile, ifname, "r");
  if (err)
    printf("not Open?");

  // Scan only works if I read them as strings, then assign to ints later
  char buf[100];
  char a[5];
  char b[5];
  char c[5];
  char d[5];
  fgets(buf, 100, ifile);
  sscanf_s(buf, "%s", b, 5);
  sscanf_s(buf, "MAZE %s %s", a, 5, b, 5);

  int Nrows = atoi(a);
  int Ncols = atoi(b);

  // create 3D adjacency table: allocate memory to access
  // this as shown below, initially mark all entries false
  //
  // adjtable[i][j][0]: cell(i,j) adjacent to cell(i-1,j)
  // adjtable[i][j][1]: cell(i,j) adjacent to cell(i+1,j)
  // adjtable[i][j][2]: cell(i,j) adjacent to cell(i,j-1)
  // adjtable[i][j][3]: cell(i,j) adjacent to cell(i,j+1)

  bool ***adjtable;
  adjtable = new bool **[Ncols];
  for (int c = 0; c < Ncols; ++c) {
    adjtable[c] = new bool *[Nrows];
    for (int r = 0; r < Nrows; ++r) {
      adjtable[c][r] = new bool;
      for (int dir = 0; dir < 4; ++dir)
        adjtable[c][r][dir] = false;
    }
  }

  while (fgets(buf, 100, ifile) != 0) {
    // Read in line
    sscanf_s(buf, "%s %s %s %s", a, 5, b, 5, c, 5, d, 5);
    int i1, j1, i2, j2;
    i1 = atoi(a), j1 = atoi(b), i2 = atoi(c), j2 = atoi(d);

    // Add to table
    if (i1 != i2) {
      adjtable[i1][j1][1] = true;
      adjtable[i2][j2][0] = true;
    } else {
      adjtable[i1][j1][3] = true;
      adjtable[i2][j2][2] = true;
    }
  }
  fclose(ifile);
  // find path using DFS source-to-sink traversal of graph
  // vcolor[i][j]: cell(i,j) WHITE, BLACK coloring
  // link[i][j]: cell(ip,jp) predecessor to cell(i,j)

  // cell source(0, 0);
  // cell sink(Nrows - 1, Ncols - 1);

  enum color_t { WHITE, BLACK };
  color_t **vcolor;
  vcolor = new color_t *[Ncols];
  for (int r = 0; r < Ncols; ++r) {
    vcolor[r] = new color_t[Nrows];
    for (int c = 0; c < Nrows; ++c) {
      vcolor[r][c] = WHITE;
    }
  }

  cell **link;
  link = new cell *[Ncols];
  for (int r = 0; r < Ncols; ++r) {
    link[r] = new cell[Nrows];
    for (int c = 0; c < Nrows; ++c) {
      link[r][c] = cell();
    }
  }

  // allocate memory for 2D vcolor and link arrays, mark
  // all cells WHITE, set all links to cells themselves

  // implement stack based DFS traversal that keeps track
  // of the order in which cells are visited while searching
  // for source-to-sink path -- resize stack along the way
  // as necessary to avoid stack overflow

  int NS = 0;      // stack size: initially 0
  int NSmax = 100; // stack capacity: initially 100
  cell *S;         // stack itself: allocate memory
  S = new cell[NSmax];
  int i, j;
  // add source to stack S
  S[NS++] = cell(0, 0);
  vcolor[0][0] = BLACK;

  while (NS != 0) {
    // printf("Stack: %i\n", NS);
    i = S[NS - 1].i;
    j = S[NS - 1].j;
    // Exit if finished
    if (i == Ncols - 1 && j == Nrows - 1)
      break;
    // Add Space to stack if full
    if (NS == NSmax) {
      NSmax *= 2;
      cell *temp;
      temp = new cell[NS];
      temp = S;
      S = new cell[NSmax];
      for (int i = 0; i < NS; ++i)
        S[i] = temp[i];
      delete[] temp;
    }
    // Attempt to progress if there is an unchecked branch from current cell
    // printf("(%i,%i)\n", i, j);

    // Set link of next cell to current, and color of next cell to black
    if (adjtable[i][j][0] && vcolor[i - 1][j] == WHITE) {
      link[i - 1][j] = cell(i, j);
      vcolor[i - 1][j] = BLACK;
      S[NS++] = cell(i - 1, j);
    } else if (adjtable[i][j][1] && vcolor[i + 1][j] == WHITE) {
      link[i + 1][j] = cell(i, j);
      vcolor[i + 1][j] = BLACK;
      S[NS++] = cell(i + 1, j);
    } else if (adjtable[i][j][2] && vcolor[i][j - 1] == WHITE) {
      link[i][j - 1] = cell(i, j);
      vcolor[i][j - 1] = BLACK;
      S[NS++] = cell(i, j - 1);
    } else if (adjtable[i][j][3] && vcolor[i][j + 1] == WHITE) {
      link[i][j + 1] = cell(i, j);
      vcolor[i][j + 1] = BLACK;
      S[NS++] = cell(i, j + 1);
    } else { // Backtrack
      // printf("%d, %d, %d, %d", adjtable[i][j][0], adjtable[i][j][1],
      //        adjtable[i][j][2], adjtable[i][j][3]);
      NS--;
    }
    // printf("check...");
  }
  // printf("Written.");
  // deallocate memory for 2D vcolor and link arrays
  // use stack to print source-to-sink path to file
  for (int r = 0; r < Ncols; ++r) {
    delete[] vcolor[r];
    delete[] link[r];
  }
  delete[] vcolor;
  delete[] link;

  // open file write header to file
  FILE *ofile;
  fopen_s(&ofile, ofname, "w+");
  fprintf(ofile, "PATH %i %i\n", Nrows, Ncols);
  fprintf(ofile, "SOURCE %i %i\n", 0, 0);
  fprintf(ofile, "SINK %i %i\n", Nrows - 1, Ncols - 1);
  for (int i = 0; i < NS; ++i)
    fprintf(ofile, "%3i %3i\n", S[i].i, S[i].j);
  fclose(ofile);
  // deallocate memory for stack and 3D adjtable
  delete[] S;
  for (int r = 0; r < Nrows; ++r) {
    for (int c = 0; c < Ncols; ++c) {
      delete[] adjtable[r][c];
    }
    delete[] adjtable[r];
  }
  delete[] adjtable;
}
