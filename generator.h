#ifndef __CDOJ_GENERATION_H__
#define __CDOJ_GENERATION_H__

#include "util.h"

void doGen(int argc, char** argv);

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  doGen(argc, argv);
  return 0;
}

#endif // __CDOJ_GENERATION_H__

