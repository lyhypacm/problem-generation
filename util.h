#ifndef __UTIL_H__
#define __UTIL_H__

#include <bits/stdc++.h>
#include "testlib.h"

/**
 * The test case is stored as command line parameter, --case=#, or -c #
 */
int getTestCase(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0) {
      return i + 1 < argc ? atoi(argv[i + 1]) : -1;
    } else if (strncmp(argv[i], "--case", 6) == 0) {
      return atoi(argv[i] + 6);
    }
  }
  return -1;
}

#endif // __UTIL_H__
