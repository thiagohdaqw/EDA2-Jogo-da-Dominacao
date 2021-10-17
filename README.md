#  Jogo da Dominação | EDA2 Trabalho 2

[Página do trabalho](https://www.brunoribas.com.br/eda2/2021-1/edazinho-enunciado/jogo.html)

[PDF com rascunhos do professor em aula](https://www.brunoribas.com.br/eda2/2021-1/edazinho-enunciado/jogo.html)

[Aula apresentando trabalho](https://www.youtube.com/watch?v=FxtlMbL-nFk)

## Como rodar
A todos os arquivos `.sh` devem ser dadas permissão de execução:

    ls *.sh | xargs chmod +x 
    ./run.sh <RANDOM_SEED> <X_INICIAL> <Y_INICIAL> <QTD_TURNOS>

Por exemplo:

    ./run.sh 777 5 5 8

## Sobre o script `extract-replace.sh`
Ele funciona copiando o conteúdo dos arquivos `*.h` declarados em `jogador.c` 
para um arquivo resultante `jogador.submit.c`, que é o arquivo que pode ser
submetido no MOJ. Tanto o programa resultante de `jogador.c` quanto o de 
`jogador.submit.c` podem ser compilados e executados localmente com o script
`build.sh`.

`extract-replace.sh` assume que:
- arquivos `*.h` e `jogador.c` estão no mesmo diretório que o script.
- todo arquivo `.h` define o cabeçalho com `<NOME_ARQUIVO_MAIUSCULO>_H_INCLUDED`
e termina com `#endif // <NOME_ARQUIVO_MAIUSCULO>_H_INCLUDED` (é possível criar 
um snippet no vscode para facilitar a definição do cabeçalho). Tudo o que está 
entre essas duas strings é copiado para o arquivo resultante.

