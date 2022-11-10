/*
  Drew Friend
  10/10/2022
  Stenography encoding
*/

#ifndef __PPM_H__
#define __PPM_H__

#include <fstream>
#include <iostream>
#include <string>

struct RGB {
  RGB() {
    R = 0;
    G = 0;
    B = 0;
  }

  unsigned char R, G, B;
};

class PPM {
public:
  PPM() {
    size = 0;
    img = new RGB;
    header = new std::string[4];
  }
  ~PPM() {
    delete img;
    delete header;
  }

  void read(std::string);
  void write(std::string);

  RGB &operator[](int i) { return img[i]; }

  int get_Npixel() { return size; }

private:
  // data members
  int size;
  RGB *img;
  std::string *header;
};

#endif
