#include "generator.h"
#include "verifier.h"
#include "solver.h"
#include <random>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdio>

namespace solver {

int sol() {
  int a, b;
  scanf("%d%d", &a, &b);
  printf("%d\n", a + b);
  return 0;
}

}

namespace verifier {

bool verify(FILE* input) {
  int a, b;
  ASSERT(fscanf(input, "%d%d", &a, &b) == 2);
  ASSERT(fscanf(input, "%*d") == EOF);
  ASSERT(a >= 1 && a <= 10);
  ASSERT(b >= 1 && b <= 10);
  return true;
}

}

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

