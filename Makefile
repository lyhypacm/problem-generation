CPP ?= g++
CPP_FLAGS ?= -O3 -Wall -std=gnu++0x -DONLINE_JUDGE -I.
LD_FLAGS ?= -O3 -Wall -std=gnu++0x -DONLINE_JUDGE
USER_LIBRARY_PATH ?= tests
TARGETS = generator.bin
ifeq ($(OS), Windows_NT)
GENERATOR_DEPS = main.o ${USER_LIBRARY_PATH}/libgenerator.dll \
								 ${USER_LIBRARY_PATH}/libverifier.dll ${USER_LIBRARY_PATH}/libsolver.dll
else
GENERATOR_DEPS = main.o ${USER_LIBRARY_PATH}/libgenerator.so \
								 ${USER_LIBRARY_PATH}/libverifier.so ${USER_LIBRARY_PATH}/libsolver.so
endif
DATA_BEGIN ?= 1
DATA_END ?= 10
DATA_FOLDER ?= data
all: ${TARGETS}

test: generator.bin
	seed=$$RANDOM; \
	i=${DATA_BEGIN}; \
	for (( ; ; )); \
	do \
		if [[ $$i -gt ${DATA_END} ]]; then break; fi; \
		PATH=${USER_LIBRARY_PATH}:$${PATH} ./generator.bin $$seed $$i ${DATA_FOLDER}; \
		exit_code=$$? \
		seed=`expr $$seed + 1`; \
		if [[ $$exit_code -eq 0 ]]; then i=`expr $$i + 1`; fi; \
	done

lib%.so: %.o
	${CPP} $< -o $@ -shared -fPIC ${CPP_FLAGS}

lib%.dll: %.o
	${CPP} $< -o $@ -shared -fPIC ${CPP_FLAGS}

generator.bin: ${GENERATOR_DEPS}
	${CPP} main.o -o $@ ${LD_FLAGS} -L${USER_LIBRARY_PATH} -lgenerator -lverifier -lsolver

${USER_LIBRARY_PATH}/%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

clean:
	rm -f *.dll *.o *.so *.in *.out *.bin ${DATA_FOLDER}/* \
		${USER_LIBRARY_PATH}/*.so ${USER_LIBRARY_PATH}/*.dll

