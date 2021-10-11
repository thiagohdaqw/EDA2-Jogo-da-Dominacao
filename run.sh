ARB_ARGS="$*";
BIN_PATH="./bin";
MENSAGENS="$BIN_PATH/mensagens";

if [ ! -d $BIN_PATH ]; then
	mkdir $BIN_PATH;
fi

if [ ! -e "$MENSAGENS" ]; then
	mkfifo $MENSAGENS;
fi

gcc -o "$BIN_PATH/arbitro" arbitro.c -g
gcc -o "$BIN_PATH/domination" domination.c -DDEBUG=1 -g

$BIN_PATH/arbitro $ARB_ARGS < $MENSAGENS | $BIN_PATH/domination > $MENSAGENS
#$BIN_PATH/arbitro $ARB_ARGS < $MENSAGENS | valgrind $BIN_PATH/domination > $MENSAGENS