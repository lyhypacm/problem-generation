#include "generator.h"
#include "verifier.h"
#include "solver.h"
#include <cassert>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

const int BUFF_SIZE = 1024;

char input_file_name[BUFF_SIZE], output_file_name[BUFF_SIZE];
bool isChild;

bool generate_verify_and_run_data(size_t seed, int case_id, const char* data_folder) {
  FILE *input, *output;

  sprintf(input_file_name, "%s/%04d.in", data_folder, case_id);
  sprintf(output_file_name, "%s/%04d.out", data_folder, case_id);

  // generate
  input = fopen(input_file_name, "w");
  generator::generate(case_id, seed, input);
  fclose(input);

  // verify input
  input = fopen(input_file_name, "r");
  bool verifier_result = verifier::verify_input(case_id, input);
  fclose(input);
  if (!verifier_result) {
    return false;
  }

  // run
  pid_t pid = fork();
  if (pid < -1) {
    return false;
  } else if (pid == 0) {
    isChild = true;
    freopen(input_file_name, "r", stdin);
    freopen(output_file_name, "w", stdout);
    solver::sol();
    fclose(stdin);
    fclose(stdout);
    return true;
  } else {
    int status;
    isChild = false;
    while (waitpid(pid, &status, 0) == -1) {
      // wait
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      return false;
    }
  }

  // verify output
  output = fopen(output_file_name, "r");
  verifier_result = verifier::verify_output(case_id, output);
  fclose (output);
  if (!verifier_result) {
    return false;
  }

  return true;
}

// @args1 - seed
// @args2 - case number
// @args3 - data folder
int main(int argc, char** argv) {
  assert(argc == 4);
  size_t seed = (size_t) atoi(argv[1]);
  int case_id = atoi(argv[2]);
  assert(case_id >= 1 && case_id <= 9999);
  const char* data_folder = argv[3];

  if (generate_verify_and_run_data(seed, case_id, data_folder)) {
    if (!isChild) {
      fprintf(stderr, "[\u001b[0;32mSUCCESS\u001b[m] generate test case #%d.\n", case_id);
    }
    return 0;
  } else {
    fprintf(stderr, "[\u001b[1;31mFAILED\u001b[m] generate test case #%d.\n", case_id);
    return 1;
  }
}

