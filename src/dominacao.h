#ifndef DOMINACAO_H_INCLUDED
#define DOMINACAO_H_INCLUDED

#include <stdio.h>
#include "debug.h"
#include "coord.h"
#include "map.h"
#include "sondados.h"
#include "jogador.h"

int sondar_coord(Map *map, Coord atual)
{
  MapCoord sonda;
  long int indice = 0;

  sonda.coord = atual;
  sonda.estado = SONDADO;
  
  MapCoord *pesquisado = map_buscar(map, sonda, &indice);
  if (map_coord_eh_null(*pesquisado))
  {
    printf("sondar %ld %ld\n", atual.x, atual.y);
    map_inserir_indice(map, sonda, indice);
    return 1;
  }
  return 0;
}

typedef Coord Direcao;
#define LU {-1, -1}
#define MU {-1,  0}
#define RU {-1,  1}
#define ML { 0, -1}
#define MR { 0,  1}
#define UL { 1, -1}
#define UM { 1,  0}
#define UR { 1,  1}

int sondar_jogador(Map *map, Jogador *jogador, int *sondagem_extras, int *qtd_jogador_preso)
{
  if (jogador_esta_preso(jogador)){
    return 0;
  }
  Direcao direcoes[8] = {RU, LU, UL, UR, MR, MU, ML, UM};
  Coord atual = {0, 0};
  int qtd_sondagem = 0;
  int sondagem_possiveis = 1 + *sondagem_extras;
  int contador;

  for (contador = 0; contador < 8 && sondagem_possiveis > 0; contador++)
  {
    atual.x = jogador->coord.x + direcoes[contador].x;
    atual.y = jogador->coord.y + direcoes[contador].y;
    if (sondar_coord(map, atual))
    {
      sondagem_possiveis--;
      qtd_sondagem++;
    }
  }

  if (contador == 8)
  {
    jogador_prender(jogador);
    (*qtd_jogador_preso)++;
  }

  *sondagem_extras = sondagem_possiveis;
  return qtd_sondagem;
}

int sondar(Map *map, Jogadores *jogadores)
{
  static int qtd_jogador_preso = 0;
  int sondagem = 0, sondagem_max = jogadores->tamanho;
  int sondagem_extras = qtd_jogador_preso;

  // for (int i = jogadores->tamanho-1; i >= 0 && sondagem < sondagem_max; i--)
  for(int i = 0; i < jogadores->tamanho && sondagem < sondagem_max; i++)
    sondagem += sondar_jogador(map, jogadores_obter(jogadores, i), &sondagem_extras, &qtd_jogador_preso);

  return sondagem;
}

Jogador *dominar(Map *map, Jogadores *jogadores, Sondados *sondados)
{
  if (sondados_vazio(sondados))
    return JOGADOR_NULL;
  SondCoord sond = sondados_max(sondados);
  Jogador *dominado = jogadores_inserir(jogadores, jogador_criar(sond.coord));
  printf("dominar %ld %ld\n", dominado->coord.x, dominado->coord.y);

  if (DEBUG)
    printf("%ld\n", sond.pontos);

  return dominado;
}

static char str[100];

void ler_sondagem(Map *map, Sondados *sondados)
{
  SondCoord sondado = {0, 0, 0};
  int indice = 0;

  scanf("%s %ld %ld %ld", str, &sondado.coord.x, &sondado.coord.y, &sondado.pontos);
  LOG(">> %s %ld %ld %ld\n", str, sondado.coord.x, sondado.coord.y, sondado.pontos);
  sondados_inserir(sondados, sondado);
}

void ler_resposta_do_juiz(Map *map, Jogadores *jogadores, Sondados *sondados, int qtd_sondagem, Jogador *dominado)
{
  for (int j = 0; j < qtd_sondagem; j++)
    ler_sondagem(map, sondados);

  if (!jogador_eh_null(dominado))
  {
    long int pontos;
    scanf("%*s %ld", &pontos);
    LOG("> dominacao %ld %ld %ld\n", dominado->coord.x, dominado->coord.y, pontos);
  }
}

#endif // DOMINACAO_H_INCLUDED