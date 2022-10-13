/*
  Drew Friend
  10/10/2022
  Stenography encoding
*/

#include "PPM.h"

using namespace std;
void PPM::read(string fname) {
  ifstream fin(fname);
  if (!fin.is_open()) {
    cerr << "ERROR: File did not open.";
    exit(1);
  }
  fin >> header[0] >> header[1] >> header[2] >> header[3];

  if (header[0] != "P6") {
    cerr << "ERROR: File in incorrect format.";
    exit(1);
  }
  if (header[3] != "255") {
    cerr << "ERROR: File has incorrect maximum value.";
    exit(1);
  }
  int count = stoi(header[1]) * stoi(header[2]);
  img = new RGB[count];
  fin.ignore();
  fin.read((char *)img, count * 3);
  // int seen = 0;
  // for (; seen < count; ++seen)
  //   fin >> img[seen].R >> img[seen].G >> img[seen].B;
  // if (seen != count) {
  //   cerr << "ERROR: File has too few values.";
  //   exit(1);
  // }
  char *t;
  fin.read(t, 1);

  if (fin.gcount() != 0) {
    cerr << "ERROR: File has too many values.";
    exit(1);
  }
  fin.close();
  size = count;
}

void PPM::write(string fname) {
  fname.insert(fname.find('.'), "_wmsg");
  ofstream newimage(fname);
  newimage << "P6\n" << header[1] << " " << header[2] << "\n255\n";
  for (int i = 0; i < size; ++i)
    newimage << img[i].R << img[i].G << img[i].B;
  // newimage << img[i].G << img[i].B << img[i].R;
  newimage.close();

  // r, g, b
  // g, b, r
}
