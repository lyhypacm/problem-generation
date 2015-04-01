#ifndef __CDOJ_VERIFIER_H__
#define __CDOJ_VERIFIER_H__

#include <cstdio>

#define ASSERT(x) { if (!(x)) return false; }

namespace verifier {

bool verify(FILE* input, FILE* output);

}

#endif // __CDOJ_VERIFIER_H__

