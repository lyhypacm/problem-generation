CPP ?= g++
CPP_FLAGS=-O3 -Wall -std=gnu++0x -DONLINE_JUDGE
LD_FLAGS=-O3 -Wall -std=gnu++0x -DONLINE_JUDGE
TARGETS=generator.bin
ifeq ($(OS),Windows_NT)
GENERATOR_DEPS=main.o generator.dll verifier.dll solver.dll
TEST_GENERATOR_DEPS=main.o test.dll
else
GENERATOR_DEPS=main.o libgenerator.so libverifier.so libsolver.so
TEST_GENERATOR_DEPS=main.o libtest.so
endif
DATA_COUNT=100
DATA_FOLDER=data
all: ${TARGETS}

generate_all: generator.bin
	seed=$$RANDOM; \
	for i in `seq 1 ${DATA_COUNT}`; \
	do \
		./generator.bin $$seed $$i ${DATA_FOLDER} ; \
		seed=`expr $$seed + 1`; \
	done

test: test-generator.bin
	seed=$$RANDOM; \
	for i in `seq 1 ${DATA_COUNT}`; \
	do \
		./test-generator.bin $$seed $$i ${DATA_FOLDER} ; \
		seed=`expr $$seed + 1`; \
	done

lib%.so: %.o
	${CPP} $< -o $@ -shared -fPIC ${CPP_FLAGS}

%.dll: %.o
	${CPP} $< -o $@ -shared -fPIC ${CPP_FLAGS}

test-generator.bin: ${TEST_GENERATOR_DEPS}
	${CPP} main.o -o $@ ${LD_FLAGS} -L. -ltest

generator.bin: ${GENERATOR_DEPS}
	${CPP} main.o -o $@ ${LD_FLAGS} -L. -lgenerator -lverifier -lsolver

%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

clean:
	rm -f *.o *.so *.in *.out *.bin ${DATA_FOLDER}/*

