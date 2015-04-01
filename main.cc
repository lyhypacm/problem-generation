#include "generator.h"
#include <cassert>

const int BUFF_SIZE = 1024;

char file_name[BUFF_SIZE];

// @args1 - seed
// @args2 - case number
// @args3 - data folder
int main(int argc, char** argv) {
  assert(argc == 4);
  size_t seed = (size_t) atoi(argv[1]);
  int case_id = atoi(argv[2]);
  assert(case_id >= 1 && case_id <= 9999);
  const char* data_folder = argv[3];

  sprintf(file_name, "%s/%04d.in", data_folder, case_id);
  FILE* input = fopen(file_name, "w");
  sprintf(file_name, "%s/%04d.out", data_folder, case_id);
  FILE* output = fopen(file_name, "w");

  generator::generate(seed, input, output);

  fclose(input);
  fclose(output);

  return 0;
}

