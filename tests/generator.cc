#include "generator.h"

int generator::generate(int case_id, size_t seed, FILE* input) {
  init_engine(seed);
  int a = next_int(1, 10), b = next_int(1, 10);
  fprintf(input, "%d %d\n", a, b);

  return 0;
}
