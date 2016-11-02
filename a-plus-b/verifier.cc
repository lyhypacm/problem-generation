#include "verifier.h"

void doVerification(int argc, char** argv) {
  inf.readInt(1, 10, "a");
  inf.readSpace();
  inf.readInt(1, 10, "b");
  inf.readEoln();
  inf.readEof();
}
