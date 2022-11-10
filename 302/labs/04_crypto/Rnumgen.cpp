/*
  Drew Friend
  10/10/2022
  Stenography encoding
*/
#include "Rnumgen.h"
#include <fstream>

rnumgen::rnumgen(std::vector<int> &v, int seedvalue) {
  srand(seedvalue);
  F.resize(v.size());
  std::partial_sum(v.begin(), v.end(), F.begin());
  std::transform(F.begin(), F.end(), F.begin(),
                 bind2nd(std::divides<float>(), F.back()));
}

int rnumgen::rand() {
  const double randmax = RAND_MAX + 1.0;
  const double p = (double)std::rand() / randmax;
  return std::upper_bound(F.begin(), F.end(), p) - F.begin();
}
