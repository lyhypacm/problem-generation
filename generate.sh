#! /bin/bash
#

USER_LIBRARY_PATH=$1
DATA_FOLDER=$2
DATA_BEGIN=$3
DATA_END=$4
mkdir -p ${DATA_FOLDER}
cp ${USER_LIBRARY_PATH}/*.in ${USER_LIBRARY_PATH}/*.out ${DATA_FOLDER}/
seed=$RANDOM
i=${DATA_BEGIN}
for (( ; ; ))
do
  if [[ $i -gt ${DATA_END} ]]; then
    break
  fi
  LD_LIBRARY_PATH=${USER_LIBRARY_PATH} PATH=${USER_LIBRARY_PATH}:${PATH} \
      ./generator.bin $seed $i ${DATA_FOLDER}
  exit_code=$?
  seed=`expr $seed + 1`
  if [[ $exit_code -eq 0 ]]; then
    i=`expr $i + 1`
  fi
done

