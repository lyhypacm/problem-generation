#! /bin/bash
#

USER_LIBRARY_PATH=$1
DATA_FOLDER=$2
DATA_BEGIN=$3
DATA_END=$4
SRCS_FOLDER=$5
mkdir -p ${DATA_FOLDER}
cp ${USER_LIBRARY_PATH}/*.in ${USER_LIBRARY_PATH}/*.out ${DATA_FOLDER}/

for src in `ls ${SRCS_FOLDER}`; do
  make ${src}.bin || exit 0
done

i=${DATA_BEGIN}
for (( ; ; ))
do
  if [[ $i -gt ${DATA_END} ]]; then
    break
  fi
  ./generator.bin --case=$i > ${DATA_FOLDER}/`printf %04d.in $i`
  exit_code=$?
  if [[ $exit_code -eq 0 ]]; then
    ./verifier.bin < ${DATA_FOLDER}/`printf %04d.in $i`
    ./solver.bin < ${DATA_FOLDER}/`printf %04d.in $i` > ${DATA_FOLDER}/`printf %04d.out $i`
    for src in `ls ${SRCS_FOLDER}`; do
      ./${src}.bin < ${DATA_FOLDER}/`printf %04d.in $i` > ${DATA_FOLDER}/`printf %04d.ans $i`
      ./checker.bin ${DATA_FOLDER}/`printf %04d.in $i` ${DATA_FOLDER}/`printf %04d.out $i` \
          ${DATA_FOLDER}/`printf %04d.ans $i` ${DATA_FOLDER}/`printf %04d.log $i` || exit 0
    done
    echo -e "[\u001b[0;32mSUCCESS\u001b[m] generate test case $i."
    i=`expr $i + 1`
  fi
done

