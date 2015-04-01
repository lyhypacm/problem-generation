This is a simple problem generation framework for ACM/ICPC competitions.

What you need to do is write the `generator.cc` file and `verifier.cc` file then
compile it into .o file.

- `make all` will build the generator with your generator and verifier.
- `make generate_all` will generate 100 test cases in `data` folder(the 
data count and data folder is defined in `Makefile`).
