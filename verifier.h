#ifndef __CDOJ_VERIFIER_H__
#define __CDOJ_VERIFIER_H__

#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

#define ASSERT_2(x, line) { \
  if (!(x)) { \
    fprintf(stderr, "Verification failed at %d\n", (int) (line)); \
    return false; \
  } \
}
#define ASSERT(x) ASSERT_2((x), __LINE__)

namespace verifier {

bool verify(FILE* input);

}

#ifdef __cplusplus
}
#endif

#endif // __CDOJ_VERIFIER_H__

