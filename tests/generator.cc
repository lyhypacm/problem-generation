#include "generator.h"
#include <random>
#include <algorithm>
#include <functional>
#include <cstdio>

int generator::generate(int case_id, size_t seed, FILE* input) {
  init_engine(seed);
  auto next_int = new_distribution<int>(1, 10);
  int a = next_int(), b = next_int();
  fprintf(input, "%d %d\n", a, b);

  return 0;
}
