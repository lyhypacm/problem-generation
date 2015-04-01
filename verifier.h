#ifndef __CDOJ_VERIFIER_H__
#define __CDOJ_VERIFIER_H__

#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

#define ASSERT(x) { if (!(x)) return false; }

namespace verifier {

bool verify(FILE* input, FILE* output);

}

#ifdef __cplusplus
}
#endif

#endif // __CDOJ_VERIFIER_H__

