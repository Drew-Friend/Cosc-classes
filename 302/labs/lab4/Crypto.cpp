/*
  Drew Friend
  10/10/2022
  Stenography encoding
*/

#include "PPM.h"
#include "Rnumgen.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const char EOT = 0x4; // ASCII: end-of-transmission

void set_pixel_list(PPM &pic, vector<int> &list, int first = 0) {
  int fib[] = {1, 1, 2, 3, 5, 8};
  list.push_back(first);
  for (int i = 0; list.back() < pic.get_Npixel(); ++i)
    list.push_back(list.back() + fib[i % 6]);
}

void perturb_pixel_list(PPM &pic, int seed, vector<int> &list) {
  vector<int> v(32768, 0);
  for (int p = 0; p < pic.get_Npixel(); ++p) {
    RGB pixel = pic[p];
    int pxl =
        ((pixel.R & 0x7c) << 9) | ((pixel.G & 0x7c) << 4) | (pixel.B & 0x7c);
    v[pxl] += 1;
  }
  rnumgen rng = rnumgen(v, seed);
  for (int i = (int)v.size() - 1; i > 0; --i) {
    swap(list[i], list[((rng.rand() << 15) | rng.rand()) % (i + 1)]);
  }
}

void decode(PPM &pic, vector<int> &list, string key = "") {
  string text = "";
  // Starting at -1 allows preincrementing in modulo check instead of
  // post-incrementing in each bitwise section
  int l = -1;
  // Until Reaching the EOT character, Read bits from the image in R,G,B pattern
  // to gather 7 of the 8 bits for each text character
  for (char t;;) {
    for (int bit = 6; bit >= 0; --bit) {
      if (++l % 3 == 0) {
        t |= (pic[list[l]].R & 0x1) << bit;
      } else if (l % 3 == 1)
        t |= (pic[list[l]].G & 0x1) << bit;
      else
        t |= (pic[list[l]].B & 0x1) << bit;
    }
    if (t == EOT)
      break;
    // Add character to complete text and reset
    text.push_back(t);
    t = 0x0;
  }

  // Undo XOR if given a key
  if (key != "")
    for (int i = 0; i < text.length(); ++i)
      text[i] ^= key[i % key.length()];
  cout << text;
}

void encode(PPM &pic, vector<int> &list, string key = "") {
  string text = "";
  int rem = 0;
  // I thought that using this vector was a cleaner way to add the EOT
  // character, I thought it wouldn't be too different
  vector<bool> bits;
  while (true) {
    text = cin.get();
    if (key != "")
      text[0] = text[0] ^ key[rem++ % key.length()];
    if (cin.eof())
      break;
    // For each character in the input message, break it down into a list of
    // bits
    for (auto letter : text)
      for (int bit = 6; bit >= 0; --bit)
        bits.push_back((letter >> bit) & 0x1);
  }
  // Add the list of bits for EOT
  for (int bit = 6; bit >= 0; --bit)
    bits.push_back((EOT >> bit) & 0x1);

  // Use XOR if given a key
  if (key != "") {
    for (int i = 0; i < text.length(); ++i) {
      text[i] ^= key[i % key.length()];
    }
  }
  // Alter the image to contain the message
  for (int i = 0; i < bits.size(); ++i) {
    if (i % 3 == 0)
      pic[list[i]].R = (pic[list[i]].R & 0xFE) | bits[i];
    else if (i % 3 == 1)
      pic[list[i]].G = (pic[list[i]].G & 0xFE) | bits[i];
    else
      pic[list[i]].B = (pic[list[i]].B & 0xFE) | bits[i];
  }
}

int main(int argc, char *argv[]) {
  // parse command line arguments
  // if something not right, print error message and exit
  string s, m, mode, key, fname;
  int seed = 0, med = 0;

  // I recognize that this could recognize unknown commands as correct
  // But it does always recognize valid parameters
  for (int i = 1; i < argc; ++i) {
    // Modifier / commands
    if (argv[i][0] == '-') {
      if (argv[i][1] == 's') {
        s = argv[i];
        seed = stoi(s.substr(6));
      } else if (argv[i][1] == 'm') {
        m = argv[i];
        med = stoi(m.substr(3));
      } else if (argv[i][1] == 'e') {
        mode = argv[i];
      } else if (argv[i][1] == 'd') {
        mode = argv[i];
      } else if (argv[i][1] == 'k') {
        key = argv[i];
        key = key.substr(5);
      }
    } else // Assume filename
      fname = argv[i];
  }

  if (fname != "" && mode != "") {
    PPM img;
    img.read(fname);
    vector<int> pixel_list;
    set_pixel_list(img, pixel_list, med);
    if (seed != 0)
      perturb_pixel_list(img, seed, pixel_list);

    if (mode == "-encode") {
      encode(img, pixel_list, key);
      img.write(fname);
    } else if (mode == "-decode")
      decode(img, pixel_list, key);
    else
      cerr << "ERROR: Invalid Mode.";
  } else
    cerr << "ERROR: Uasge: ./Crypto -encode|decode image.ppm [-option=value]";
}
