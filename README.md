This is a simple problem generation framework for ACM/ICPC competitions.

### Introduction
What you need to do is write the files mentioned below and compile them into .o file.

### Files added
  - `generator.cc`: a implmentation of generator.h to generate input files.
  - `verifier.cc`: a implementation of verifier.h to verify input files are legal or not.
  - `solver.cc`: a implementation of solver.h to generate output files.


### Targets
  - `all` will build the generator binary.
  - `generate_all` will generate 100 test cases in `data` folder(the 
data count and data folder is defined in `Makefile`).
  - `test`: run integration test in current platform.

