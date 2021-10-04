#include <stdio.h>

/*
- Usar fila de prioridade com resizing array
  - dobrar a capacidade quando tamanho+1 == capacidade
  - reduzir a capacidade à metade quando tamanho/4 == capacidade
*/

int main() {
  int linha_inicial, coluna_inicial;
  int i, pontos, limite_de_turnos;

  scanf("%d %d %d %d", &linha_inicial, &coluna_inicial,
    &pontos, &limite_de_turnos);
  
  for (i = 0; i < limite_de_turnos; i++) {
    // sondar L' C' N vezes // N sendo a qtd de Edazinhos
    // dominar L' C' // no máximo 1 vez apenas para áreas sondadas em turnos anteriores
    // fim turno

    // ler a resposta do Juiz
    //    ler N vezes (sondagem L' C' pontos) (1 linha por sondagem)
    //    ler (dominação P (pontos que ganhados na área dominada))
  }
  
  return 0;
}