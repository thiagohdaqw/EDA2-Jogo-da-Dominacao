#!/bin/bash

logs_file=${1:-"logs.txt"}

./build.sh

build_succeed=$?
if [[ "$build_succeed" != "0" ]]; then
  exit 1
fi


TIMEFORMAT=%R # Para pegar apenas o tempo real do comando `time`
current_date=$(date '+%Y-%m-%d %H:%M:%S')
echo -e "\n[$current_date]" >> $logs_file
while read tc; do
  printf "test case $tc | " >> $logs_file
  result=$(time (./run.sh "$tc" 2>&1 >/dev/null | grep "==") 2>&1 )
  score=$(echo $result | cut -d '|' -f 2 | cut -d ' ' -f2);
  colision=$(echo $result | cut -d '|' -f 3 | cut -d ' ' -f3);
  time_taken=$(echo $result | cut -d '|' -f 4)
  echo "pontos: $score, tempo: ${time_taken}s, colisao: $colision" >> $logs_file
done <test_cases.txt
unset TIMEFORMAT


exit 0