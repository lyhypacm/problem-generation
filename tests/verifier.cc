#include "verifier.h"
#include <cstdio>

bool verifier::verify_input(int case_id, FILE* input) {
  int a, b;
  ASSERT(fscanf(input, "%d%d", &a, &b) == 2);
  ASSERT(fscanf(input, "%*d") == EOF);
  ASSERT(a >= 1 && a <= 10);
  ASSERT(b >= 1 && b <= 10);
  return true;
}

bool verifier::verify_output(int case_id, FILE* output) {
  return true;
}
