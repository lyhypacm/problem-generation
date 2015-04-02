This is a simple problem generation framework for ACM/ICPC competitions.

### Introduction
What you need to do is write the files mentioned below and compile them into .o file.

### Files added
  - `generator.cc`: a implmentation of generator.h to generate input files.
  - `verifier.cc`: a implementation of verifier.h to verify input/output files are legal or not.
  - `solver.cc`: a implementation of solver.h to generate output files.

### Usage
Run the command line below to build your own generator.
```
make generate_all
```

Also, you can add some make variables before make.
```
USER_LIBRARY_PATH=tests make generate_all
```

### Mkae targets
  - `all` will build the generator binary.
  - `generate` will generate 100 test cases in `data` folder(the data count and
data folder is defined in `Makefile`).
  - `test`: run integration test in current platform.

### Make variables
  - `CPP`: the compiler to build this library.
  - `CPP_FLAGS`: the compile flag to compile source code.
  - `LD_FLAGS`: the link flags to link user library and main library into runable file.
  - `USER_LIBRARY_PATH`: the path user library source codes located.
  - `DATA_BEGIN`: the begin test case id to be generated.
  - `DATA_END`: the end test case id(included) to be generated.
  - `DATA_FOLDER`: the location generated files located.

