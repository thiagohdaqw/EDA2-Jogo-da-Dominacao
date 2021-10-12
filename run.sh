#!/bin/bash

ARB_ARGS="$*";
BIN_PATH="./bin";
MENSAGENS="$BIN_PATH/mensagens";

$BIN_PATH/arbitro $ARB_ARGS < $MENSAGENS | $BIN_PATH/jogador > $MENSAGENS
#$BIN_PATH/arbitro $ARB_ARGS < $MENSAGENS | valgrind $BIN_PATH/jogador > $MENSAGENS

exit