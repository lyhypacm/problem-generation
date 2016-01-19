#ifndef __CDOJ_VERIFIER_H__
#define __CDOJ_VERIFIER_H__

#include "util.h"

void doVerification(int argc, char** argv);

int main(int argc, char** argv) {
  registerValidation();
  doVerification(argc, argv);
  return 0;
}

#endif // __CDOJ_VERIFIER_H__

