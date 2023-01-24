// Drew Friend
// lab 7, makeppm: Turn path and maze into PPM image
// 11/17

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

const int CELL_WIDTH = 10;

struct RGB {
  RGB() {
    R = 0;
    G = 0;
    B = 0;
  }
  RGB(unsigned char r, unsigned char g, unsigned char b) {
    R = r;
    G = g;
    B = b;
  }

  unsigned char R, G, B;
};

class PPM {
public:
  PPM(int r, int c) {
    nRow = r;
    nCol = c;
    size = r * c;
    img = new RGB[size];
    header = new char;
  }
  ~PPM() {
    delete img;
    delete header;
  }

  void read(char *);
  void write(char *);

  RGB &operator[](int i) { return img[i]; }

  int get_Npixel() { return size; }

private:
  // data members
  int size;
  int nRow, nCol;
  RGB *img;
  char *header;
};
void PPM::write(char *fname) {
  char *oName = fname;
  for (int c = 0; true; ++c) {
    if (fname[c] == '.') {
      oName[c + 1] = 'p';
      oName[c + 2] = 'p';
      oName[c + 3] = 'm';
      break;
    }
  }
  printf("Renamed to :%s  ", oName);
  FILE *oFile;
  fopen_s(&oFile, oName, "w+");
  fprintf(oFile, "P6\n%i %i\n255\n", nCol, nRow);
  printf("%ix%i\n", nCol, nRow);
  for (int i = 0; i < size; ++i) {
    if ((i % (nCol)) == 0)
      printf("\n\n");
    printf("%3i", img[i].R);
    unsigned char buf[3];
    buf[0] = img[i].R;
    buf[1] = img[i].G;
    buf[2] = img[i].B;
    fwrite(buf, 1, 3, oFile);
  }
  fclose(oFile);
  printf("Completed\n");
}

int main(int argc, char *argv[]) {
  char *mazeF = argv[1];
  FILE *iFile;
  char buf[100];
  char a[5];
  char b[5];
  char c[5];
  char d[5];
  int nRows, nCols;

  fopen_s(&iFile, mazeF, "r");
  fscanf_s(iFile, "MAZE %s %s", a, 5, b, 5);
  nRows = atoi(a);
  nCols = atoi(b);
  PPM img = PPM((nRows * CELL_WIDTH + 1), (nCols * CELL_WIDTH + 1));
  for (int i = 0; i < img.get_Npixel(); ++i) {
    img[i] = ((i % (nRows * CELL_WIDTH))) ? RGB(0, 0, 0) : RGB(255, 255, 255);
    printf("%i\n", i);
  }

  while (fgets(buf, 100, iFile) != 0) {
    // Read in line
    sscanf_s(buf, "%s %s %s %s", a, 5, b, 5, c, 5, d, 5);
    int i1, j1, i2, j2;
    i1 = atoi(a), j1 = atoi(b), i2 = atoi(c), j2 = atoi(d);

    for (int a = 0; a < CELL_WIDTH; ++a) {
    }
    // for (int i = i1 * CELL_WIDTH; i <= i2 * CELL_WIDTH; ++i) {
    //   img[i + j1 * nCols * CELL_WIDTH] = RGB(0, 0, 0);
    //   printf("(%2i,%2i):  %i  ", i, j1 * CELL_WIDTH,
    //          i + j1 * nCols * CELL_WIDTH);
    // }
    // for (int j = j1 * CELL_WIDTH; j < j2 * CELL_WIDTH; ++j) {
    //   img[i1 * CELL_WIDTH + j * nCols] = RGB(0, 0, 0);
    //   printf("(%2i,%2i):  %i  ", i1 * CELL_WIDTH, j,
    //          i1 * CELL_WIDTH + j * nCols);
    // }
    printf("\n");

    // printf("%i, %i\n", i1, j1);
  }
  fclose(iFile);
  img.write(mazeF);
}