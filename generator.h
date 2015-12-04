#ifndef __CDOJ_GENERATION_H__
#define __CDOJ_GENERATION_H__

#include <cstdio>
#include <sys/types.h>
#include <cassert>
#include <random>
#include <functional>

namespace generator {

std::default_random_engine engine;
bool is_engine_initialized = false;

void init_engine(size_t seed) {
  if (!is_engine_initialized) {
    is_engine_initialized = true;
    engine = std::default_random_engine(seed);
  }
}

// creates a new distribution with range [lower_bound, upper_bound]
template<class _IntType = int>
auto new_distribution(_IntType lower_bound, _IntType upper_bound) {
  assert(is_engine_initialized);
  return std::bind(std::uniform_int_distribution<_IntType>(lower_bound, upper_bound), engine);
}

int nextInt(int lower_bound, int upper_bound) {
  return new_distribution(lower_bound, upper_bound)(engine);
}

int generate(int case_id, size_t seed, FILE* input);

}

#endif // __CDOJ_GENERATION_H__

