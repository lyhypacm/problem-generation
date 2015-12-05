#ifndef __CDOJ_VERIFIER_H__
#define __CDOJ_VERIFIER_H__

#include <bits/stdc++.h>

#define ASSERT_2(x, line) { \
  if (!(x)) { \
    fprintf(stderr, "Verification failed at %d\n", (int) (line)); \
    return false; \
  } \
}
#define ASSERT(x) ASSERT_2((x), __LINE__)

namespace verifier {

bool verify_input(int case_id, FILE* input);
bool verify_output(int case_id, FILE* output);

}

#endif // __CDOJ_VERIFIER_H__

