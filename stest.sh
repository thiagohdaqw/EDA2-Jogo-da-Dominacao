#!/bin/bash

logs_file=${1:-"logs.txt"}

./sbuild.sh

build_succeed=$?
if [[ "$build_succeed" != "0" ]]; then
  exit 1
fi


TIMEFORMAT=%R # Para pegar apenas o tempo real do comando `time`
current_date=$(date '+%Y-%m-%d %H:%M:%S')
echo -e "\n[$current_date]" >> $logs_file
while read tc; do
  printf "test case $tc | " >> $logs_file
  result=$(time (./srun.sh "$tc" 2>&1 >/dev/null | grep "==") 2>&1 )
  player_result=$(echo $result | cut -d'\' -f2);
  time_taken=$(echo $result | cut -d'\' -f3)
  echo "tempo "$time_taken"s | $player_result" >> $logs_file
done <test_cases.txt
unset TIMEFORMAT


exit 0