#ifndef __CDOJ_GENERATION_H__
#define __CDOJ_GENERATION_H__

#include <bits/stdc++.h>

namespace generator {

bool is_engine_initialized = false;

void init_engine(size_t seed) {
  if (!is_engine_initialized) {
    is_engine_initialized = true;
    srand(seed);
  }
}

int nextInt(int lower_bound, int upper_bound) {
  assert(is_engine_initialized);
  return std::rand() % (upper_bound - lower_bound + 1) + lower_bound;
}

int generate(int case_id, size_t seed, FILE* input);

}

#endif // __CDOJ_GENERATION_H__

