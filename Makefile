CPP = g++
CPP_FLAGS=-O2 -Wall -std=gnu++0x -DONLINE_JUDGE -I. -Itestlib
USER_LIBRARY_PATH ?= tests
TARGETS = generator.bin solver.bin verifier.bin checker.bin
DATA_BEGIN ?= 1
DATA_END ?= 10
DATA_FOLDER ?= ${USER_LIBRARY_PATH}/data
SRCS_FOLDER ?= ${USER_LIBRARY_PATH}/srcs
all: ${TARGETS}

test: ${TARGETS}
	./generate.sh "${USER_LIBRARY_PATH}" "${DATA_FOLDER}" "${DATA_BEGIN}" "${DATA_END}" "${SRCS_FOLDER}"

zip:
	cd ${DATA_FOLDER}; zip data.zip *.in *.out

%.cc.bin: ${SRCS_FOLDER}/%.cc
	${CPP} $< -o $@ ${CPP_FLAGS}

%.bin: ${USER_LIBRARY_PATH}/%.cc
	${CPP} $< -o $@ ${CPP_FLAGS}

clean:
	rm -f *.zip *.dll *.o *.so *.in *.out *.bin ${DATA_FOLDER}/*.ans ${DATA_FOLDER}/*.log \
		${USER_LIBRARY_PATH}/*.o ${USER_LIBRARY_PATH}/*.so ${USER_LIBRARY_PATH}/*.dll

clean_data:
	rm -f ${DATA_FOLDER}/*

