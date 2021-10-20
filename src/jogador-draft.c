#include <stdio.h>
#include <stdlib.h>

/*
- Usar fila de prioridade com resizing array
  - dobrar a capacidade quando tamanho+1 == capacidade
  - reduzir a capacidade à metade quando tamanho/4 == capacidade

*/

typedef enum
{
  SONDADO,
  DOMINADO
} Estado;

typedef struct coord_t
{
  int x, y;
  int pontos;
  Estado estado;
} coord_t;

typedef int MaxPQ;

// Variáveis globais
coord_t *sondagens; // áreas que o juiz revelou
int tamanho_sondagens = 0;
coord_t *jogadores; // ao mesmo tempo são as áreas dominadas, pontos já ganhos
int tamanho_jogadores = 0, qtd_jogadores = 0;

MaxPQ<coord_t> sondados; // implementar com vetor não ordenado ou arvore binária
                         // guarda apenas coordenadas com pontos > 0
// HashMap<coord_t>
//

void imprimir_sondagens()
{
}

void fazer_sondagem(int qtd_jogadores)
{
  imprimir_sondagens();
}

void fazer_dominacao()
{
  if (!PQIsEmpty(sondados))
  {
    coord = escolher_ponto_pra_dominar();
    printf("dominar %d %d\n", coord.x, coord.y);
  }
}

coord_t escolher_ponto_pra_dominar()
{
  return PQDelMax(sondados);
}

void ler_resposta_do_juiz()
{
  static char str[15];
  // ler sondagens
  for (size_t i = 0; i < qtd_jogadores; i++)
  {
    scanf("%s %d %d %d", str, sondagens[i].x, sondagens[i].y, sondagens[i].pontos);
    sondagens[i].estado = SONDADO;
  }

  // ler info da dominação
  // dominado 30
  scanf("%*s %*d");
}

int main()
{
  int linha_inicial, coluna_inicial;
  int i, pontos, limite_de_turnos;
  coord_t coord;

  scanf("%d %d %d %d", &linha_inicial, &coluna_inicial,
        &pontos, &limite_de_turnos);

  tamanho_jogadores = limite_de_turnos + 2;

  jogadores = malloc(tamanho_jogadores * sizeof(coord_t));

  for (i = 0; i < limite_de_turnos; i++)
  {
    // sondar L' C' N vezes // N sendo a qtd atual de jogadores
    fazer_sondagem(qtd_jogadores); // imprime tbm
    // rodar algoritmo
    fazer_dominacao();

    printf("fimturno\n");

    ler_resposta_do_juiz(sondagens);
  }

  free(jogadores);

  return 0;
}