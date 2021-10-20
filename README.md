#  Jogo da Dominação | EDA2 Trabalho 2

[Página de submissões](https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-EDA2-2021_1-trabalho2)

[Página do enunciado do trabalho](https://www.brunoribas.com.br/eda2/2021-1/edazinho-enunciado/jogo.html)

[PDF com rascunhos do professor em aula](https://www.brunoribas.com.br/eda2/2021-1/edazinho-enunciado/jogo.html)

[Aula apresentando trabalho](https://www.youtube.com/watch?v=FxtlMbL-nFk)

## Como rodar
A todos os arquivos `.sh` devem ser dadas permissão de execução:

    ls *.sh | xargs chmod +x 
    ./srun.sh <RANDOM_SEED> <X_INICIAL> <Y_INICIAL> <QTD_TURNOS>

Por exemplo:

    ./sbuild.sh
    ./srun.sh 777 5 5 8
