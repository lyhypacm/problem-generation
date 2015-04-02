#include "generator.h"
#include <random>
#include <algorithm>
#include <functional>
#include <cstdio>

namespace generator {

int generate(int case_id, size_t seed, FILE* input) {
  std::default_random_engine engine(seed);
  std::uniform_int_distribution<int> distribution(1, 10);

  auto next_int = std::bind(distribution, engine);
  int a = next_int(), b = next_int();
  fprintf(input, "%d %d\n", a, b);

  return 0;
}

}

