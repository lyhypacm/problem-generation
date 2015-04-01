CPP=g++
CPP_FLAGS=-O3 -w -static -Wall -std=gnu++0x
LD_FLAGS=-O3 -w -Wall -std=gnu++0x
TARGETS=generator.bin
GENERATOR_DEPS=main.o generator.o verifier.o
DATA_COUNT=100
DATA_FOLDER=data
all: ${TARGETS}

generate_all: generator.bin
	for i in `seq 1 ${DATA_COUNT}`; do ./generator.bin $$RANDOM $$i ${DATA_FOLDER} ; done

generator.bin: ${GENERATOR_DEPS}
	$(CPP) ${GENERATOR_DEPS} -o $@ ${LD_FLAGS}

%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

clean:
	rm -f *.o *.in *.out ${TARGETS} ${DATA_FOLDER}/*

