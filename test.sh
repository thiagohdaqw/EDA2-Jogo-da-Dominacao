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
  result=$(time (./run.sh "$tc" 2>&1 >/dev/null | grep "final: ") 2>&1 )
  score=$(echo $result | cut -d ' ' -f 4)
  time_taken=$(echo $result | cut -d ' ' -f 5)
  echo "pontos: $score, tempo: ${time_taken}s" >> $logs_file
  echo
done <test_cases.txt
unset TIMEFORMAT


exit 0
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
  result=$(time (./run.sh "$tc" 2>&1 >/dev/null | grep "final: ") 2>&1 )
  score=$(echo $result | cut -d ' ' -f 4)
  time_taken=$(echo $result | cut -d ' ' -f 5)
  echo "pontos: $score, tempo: ${time_taken}s" >> $logs_file
  echo
done <test_cases.txt
unset TIMEFORMAT


exit 0