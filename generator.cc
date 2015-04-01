#include "generator.h"
#include <random>
#include <algorithm>
#include <functional>

namespace generator {

int generate(size_t seed, FILE* input, FILE* output) {
  std::default_random_engine engine(seed);
  std::uniform_int_distribution<int> distribution(1, 10);

  auto next_int = std::bind(distribution, engine);
  int a = next_int(), b = next_int();
  fprintf(input, "%d %d\n", a, b);
  fprintf(output, "%d\n", a + b);
}

}

