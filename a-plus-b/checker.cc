#define problem_name "A + B problem"
#include "checker.h"

void doCheck(int argc, char** argv) {
  int expected = ans.readInt();
  int actual = ouf.readInt();
  if (expected != actual) quitf(_wa, "expected %d, found %d", expected, actual);
  quitf(_ok, "answer is %d, ok", expected);
}
