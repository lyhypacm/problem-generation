CPP ?= g++
CPP_FLAGS ?= -O2 -Wall -std=gnu++0x -DONLINE_JUDGE -fPIC -I.
LD_FLAGS ?= -O2 -Wall -std=gnu++0x -DONLINE_JUDGE -fPIC
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
DATA_FOLDER ?= ${USER_LIBRARY_PATH}/data
all: ${TARGETS}

test: generator.bin
	./generate.sh "${USER_LIBRARY_PATH}" "${DATA_FOLDER}" "${DATA_BEGIN}" "${DATA_END}"

zip:
	cd ${DATA_FOLDER}; zip data.zip *.in *.out

lib%.so: %.o
	${CPP} $< -o $@ -shared ${CPP_FLAGS}

lib%.dll: %.o
	${CPP} $< -o $@ -shared ${CPP_FLAGS}

generator.bin: ${GENERATOR_DEPS}
	${CPP} main.o -o $@ ${LD_FLAGS} -L${USER_LIBRARY_PATH} -lgenerator -lverifier -lsolver

${USER_LIBRARY_PATH}/%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

%.o: %.cc
	${CPP} $< -c -o $@ ${CPP_FLAGS}

clean:
	rm -f *.zip *.dll *.o *.so *.in *.out *.bin ${DATA_FOLDER}/* \
		${USER_LIBRARY_PATH}/*.so ${USER_LIBRARY_PATH}/*.dll

