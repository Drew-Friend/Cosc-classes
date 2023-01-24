// Drew Friend
// lab 7, makemaze: Create a random maze using MST
// 11/15

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

class dset {

  struct node {
    node() { rank = 0, parent = -1; }
    int rank;
    int parent;
  };
  int Nsets;
  node *S;

public:
  ~dset();
  dset(int Nsets);
  int size() { return Nsets; }
  int merge(int, int);
  int find(int);
};
dset::dset(int N) {
  S = new node[N];
  Nsets = N;
}
dset::~dset() { delete[] S; }
int dset::merge(int i, int j) {
  i = find(i);
  j = find(j);
  if (i != j) {
    node &Si = S[i];
    node &Sj = S[j];
    // merge (union) by rank
    if (Si.rank > Sj.rank)
      Sj.parent = i;
    else if (Si.rank < Sj.rank)
      Si.parent = j;
    else {
      Sj.parent = i;
      Si.rank += 1;
    }
    Nsets -= 1;
  }
  return find(i);
}

int dset::find(int i) {
  if (S[i].parent == -1)
    return i;
  // recursive path compression
  S[i].parent = find(S[i].parent);
  return S[i].parent;
}

// add constructors as needed
struct cell {
  int i, j;
  cell(int a, int b) { i = a, j = b; }
  cell() { i = -1, j = -1; }
  void print(int c) { printf("(%i, %i), %i\n", i, j, i + j * c); }
};

struct cell_pair {
  cell c1, c2;
  cell_pair(cell a, cell b) : c1(a.i, a.j), c2(b.i, b.j) {}
  cell_pair(int i1, int j1, int i2, int j2) : c1(i1, j1), c2(i2, j2) {}
  cell_pair() : c1(-1, -1), c2(-1, -1) {}
};

// optional function
// [void swap(...){...}]

int main(int argc, char *argv[]) {
  // process command line arguments
  if (argc != 4) {
    printf("Usage: ./Makemaze Nrows Ncols maze.txt");
    return 1;
  }
  char *fname = argv[3];
  int nRows = atoi(argv[1]);
  int nCols = atoi(argv[2]);
  int Ncells = nRows * nCols;
  srand(time(NULL));
  cell_pair *adjlist;
  adjlist = new cell_pair[2 * Ncells];

  // create list of cells (i,j) and their neighbors
  // below (i+1,j) and to the right (i,j+1) while
  // excluding neighbors outside grid

  // populate adjlist[] : (i, j)loop adding entries
  for (int x = 0; x < nCols; ++x)
    for (int y = 0; y < nRows; ++y) {
      if (x + 1 < nCols)
        adjlist[x + y * nCols] = cell_pair(x, y, x + 1, y);
      if (y + 1 < nRows)
        adjlist[(x + y * nCols) + Ncells] = cell_pair(x, y, x, y + 1);
    }

  // randomize content(optional: write swap function)
  cell_pair tmp;
  for (int i = 0; i < Ncells * 2; ++i) {
    int k = i;
    int j = (rand() % ((Ncells + 2) + 1));
    tmp = adjlist[k];
    adjlist[k] = adjlist[j];
    adjlist[j] = tmp;
  }

  // construct maze using kruskal's mst algorithm
  // place each cell in own set, then iteratively
  // merge neighboring cells if in different sets
  // otherwise, print cell pair (ie wall) to file

  // note: when all cells belong to same set, the
  // merging stops and you merely print cell pairs

  //  write MAZE header to file
  FILE *file;
  fopen_s(&file, fname, "w+");
  fprintf(file, "MAZE %i %i\n", nRows, nCols);

  // As with making them, a cell's 1d index is i+j*nCols
  dset DS(Ncells);
  int ctr = 0;
  cell c1;
  cell c2;
  int i1, i2;
  while (1 < DS.size()) {
    do {
      c1 = adjlist[ctr].c1;
      c2 = adjlist[ctr].c2;
      ++ctr;
      if (ctr > Ncells * 2)
        ctr %= (Ncells * 2);
    } while (c1.i == -1);

    i1 = (c1.j * nCols) + c1.i;
    i2 = (c2.j * nCols) + c2.i;
    if (DS.find(i1) != DS.find(i2)) {
      DS.merge(i1, i2);
      fprintf(file, "%3i %3i %3i %3i\n", c1.i, c1.j, c2.i, c2.j);
    }
  }
  fclose(file);
}
