CPP=g++
CPP_FLAGS=-O3 -Wall -std=gnu++0x -DONLINE_JUDGE
LD_FLAGS=-O3 -Wall -std=gnu++0x -DONLINE_JUDGE
TARGETS=generator.bin
GENERATOR_DEPS=main.o libgenerator.so libverifier.so libsolver.so
TEST_GENERATOR_DEPS=main.o libtest.so
DATA_COUNT=100
DATA_FOLDER=data
all: ${TARGETS}

test: test-generator.bin
	for i in `seq 1 ${DATA_COUNT}`; do ./test-generator.bin $$RANDOM $$i ${DATA_FOLDER} ; done

lib%.so: %.o
	${CPP} $< -o $@ -shared -fPIC ${CPP_FLAGS}

test-generator.bin: ${TEST_GENERATOR_DEPS}
	${CPP} ${TEST_GENERATOR_DEPS} -o $@ ${LD_FLAGS} -L. -ltest

generator.bin: ${GENERATOR_DEPS}
	${CPP} ${GENERATOR_DEPS} -o $@ ${LD_FLAGS} -L. -lgenerator -lverifier -lsolver

%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

clean:
	rm -f *.o *.so *.in *.out ${TARGETS} ${DATA_FOLDER}/*

