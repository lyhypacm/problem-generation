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
```bash
$ ./generator.py -p <problem folder name>
```

### Generator command line arguments
You can find the command line arguments description by
```bash
$ ./generator.py -h
```
