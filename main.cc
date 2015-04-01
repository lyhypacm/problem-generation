#include "generator.h"
#include "verifier.h"
#include <cassert>

const int BUFF_SIZE = 1024;

char input_file_name[BUFF_SIZE], output_file_name[BUFF_SIZE];

// @args1 - seed
// @args2 - case number
// @args3 - data folder
int main(int argc, char** argv) {
  assert(argc == 4);
  size_t seed = (size_t) atoi(argv[1]);
  int case_id = atoi(argv[2]);
  assert(case_id >= 1 && case_id <= 9999);
  const char* data_folder = argv[3];

  sprintf(input_file_name, "%s/%04d.in", data_folder, case_id);
  FILE* input = fopen(input_file_name, "w");
  sprintf(output_file_name, "%s/%04d.out", data_folder, case_id);
  FILE* output = fopen(output_file_name, "w");

  generator::generate(seed, input, output);

  fclose(input);
  fclose(output);

  input = fopen(input_file_name, "r");
  output = fopen(output_file_name, "r");

  bool verifier_result = verifier::verify(input, output);

  fclose(input);
  fclose(output);

  if (verifier_result) {
    fprintf(stderr, "[\u001b[0;32mSUCCESS\u001b[m] generate test case #%d.\n", case_id);
  } else {
    fprintf(stderr, "[\u001b[1;31mFAILED\u001b[] generate test case #%d.\n", case_id);
  }

  return 0;
}

