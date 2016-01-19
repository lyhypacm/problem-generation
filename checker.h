#ifndef __CDOJ_CHECKER_H__
#define __CDOJ_CHECKER_H__

#include "util.h"

#ifndef problem_name
#define problem_name "test"
#endif // problem_name

void doCheck(int argc, char** argv);

int main(int argc, char** argv) {
  setName("the data checker for problem: %s", problem_name);
  registerTestlibCmd(argc, argv);
  doCheck(argc, argv);
  return 0;
}

#endif // __CDOJ_CHECKER_H__
