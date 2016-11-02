#include "generator.h"

void doGen(int argc, char** argv) {
  int a = rnd.next(1, 10);
  int b = rnd.next(1, 10);
  printf("%d %d\n", a, b);
}
