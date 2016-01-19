This is a simple problem generation framework for ACM/ICPC competitions.

### Introduction
What you need to do is write the files mentioned below and compile them into binary files using GNU
make toolchain.

### Files added
  - `generator.cc`: a implmentation of generator.h to generate input files.
  - `verifier.cc`: a implementation of verifier.h to verify input files are legal or not.
  - `solver.cc`: a standard solution, with input file as `stdin` and output file as `stdout`.
  - `checker.cc`: a implementation of checker.h to verify output files are legal or not.
  - `*.in` and `*.out`: predefined data(e.g. sample input/output) and will copy them
into data folder when generating data

### Usage
Run the command line below to build your own generator.
```
make test
```

Also, you can add some make variables before make.
```
USER_LIBRARY_PATH=tests make test
```

### Make targets
  - `all` will build the generator binary.
  - `test` will generate 10 test cases in `data` folder(the test case id and
data folder is defined in `Makefile`).
  - `zip` will zip the data into a zip package.

### Make variables
  - `CPP`: the compiler to build this library.
  - `CPP_FLAGS`: the compile flag to compile source code.
  - `USER_LIBRARY_PATH`: the path user library source codes located.
  - `DATA_BEGIN`: the begin test case id to be generated.
  - `DATA_END`: the end test case id(included) to be generated.
  - `DATA_FOLDER`: the location generated files located.
  - `SRCS_FOLDER`: the extra solutions location.

