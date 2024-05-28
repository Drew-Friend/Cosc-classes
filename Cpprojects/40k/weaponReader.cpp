#include "fstream"
#include "iostream"
#include "sstream"
#include <sstream>
#include <string>
#include <vector>

void printBin(int *ptr) {
  for (int b = 0; b < 8; ++b) {
    std::cout << ((*ptr >> b) & 1);
  }
}

std::vector<int> extract(std::string input) {
  std::vector<int> ret;
  for (int c = 0; c < 2; ++c) {
    printBin((int *)(&input[c]));
    // for (int b = 0; b < 8; ++b) {
    //   ret.push_back(input[c] >> b & 1);
    //   std::cout << (input[c] >> b & 1);
    // }
  }
  return ret;
}

int main() {
  std::string fileName;
  char in[2];
  std::cout << "Filename: ";
  std::cin >> fileName;

  std::fstream fin;
  fin.open(fileName, std::fstream::binary | std::fstream::in);

  fin.read(in, 2);
  fileName = in;
  std::cout << (fileName) << '\n';
  extract(fileName);

  fin.close();
}