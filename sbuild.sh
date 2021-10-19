#!/bin/bash

BIN_PATH="./bin";
MENSAGENS="$BIN_PATH/mensagens";

if [ ! -d $BIN_PATH ]; then
	mkdir $BIN_PATH;
fi

if [ ! -e "$MENSAGENS" ]; then
	mkfifo $MENSAGENS;
fi

gcc -o "$BIN_PATH/arbitro" src/arbitro.c -g -lm
success=$?

if [[ "$success" != "0" ]]; then
  exit 1
fi

./sextract_replace.sh

gcc -o "$BIN_PATH/jogador" src/main.submit.c -DDEBUG=1 -O2 -static -g
success=$?

if [[ "$success" != "0" ]]; then
  exit 1
fi

exit 0