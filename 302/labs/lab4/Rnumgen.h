/*
  Drew Friend
  10/10/2022
  Stenography encoding
*/
#ifndef __RNUMGEN_H__
#define __RNUMGEN_H__

#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

class rnumgen {
public:
  rnumgen(std::vector<int> &, int = 0);
  int rand();

private:
  std::vector<float> F;
};

#endif
