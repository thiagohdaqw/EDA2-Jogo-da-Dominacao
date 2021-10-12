#  Jogo da Dominação | EDA2 Trabalho 2

[Página do trabalho](https://www.brunoribas.com.br/eda2/2021-1/edazinho-enunciado/jogo.html)

[PDF com rascunhos do professor em aula](https://www.brunoribas.com.br/eda2/2021-1/edazinho-enunciado/jogo.html)

[Aula apresentando trabalho](https://www.youtube.com/watch?v=FxtlMbL-nFk)

# Como rodar

    chmod +x run.sh
    ./run.sh <RANDOM_SEED> <X_INICIAL> <Y_INICIAL> <QTD_TURNOS>

Por exemplo:

    ./run.sh 777 5 5 8


# Teste

    ./run.sh 777 5 5 8 2>&1 >/dev/null | grep "final: "

    cat tmp | grep "final: " | cut -d ' ' -f 4