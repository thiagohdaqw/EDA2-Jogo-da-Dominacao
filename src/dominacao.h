#ifndef DOMINACAO_H_INCLUDED
#define DOMINACAO_H_INCLUDED

#include "debug.h"
#include "coord.h"
#include "map.h"
#include "sondados.h"
#include "jogador.h"

int sondar_coord(Map *map, MapCoord atual)
{
  long int indice = 0;
  MapCoord *pesquisado = map_buscar(map, atual, &indice);
  if (map_coord_eh_null(*pesquisado))
  {
    PRINT("sondar %ld %ld\n", atual.coord.x, atual.coord.y);
    pesquisado->coord = atual.coord;
    pesquisado->estado = SONDADO;
    return 1;
  }
  return 0;
}

int sondar_jogador(Map *map, Jogador *jogador, int *sondagem_extras, int *qtd_jogador_preso)
{
  if (jogador_esta_preso(jogador))
    return 0;
  MapCoord atual = {0, 0, SONDADO};
  int qtd_sondagem = 0;
  int sondagem_possiveis = 1 + *sondagem_extras;
  int x, y, dx, dy, t, contador;

  x = dx = 1;
  y = dy = 0;

  for (contador = 0; contador < 8 && sondagem_possiveis > 0; contador++)
  {
    atual.coord.x = jogador->coord.x + x;
    atual.coord.y = jogador->coord.y + y;
    if (sondar_coord(map, atual))
    {
      sondagem_possiveis--;
      qtd_sondagem++;
    }
    if ((x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1 - y)))
    {
      t = dx;
      dx = -dy;
      dy = t;
    }
    x += dx;
    y += dy;
  }

  if (contador == 8)
  {
    jogador_prender(jogador);
    *qtd_jogador_preso++;
  }

  *sondagem_extras = sondagem_possiveis;
  return qtd_sondagem;
}

int sondar(Map *map, Jogadores *jogadores)
{
  static int qtd_jogador_preso = 0;
  int sondagem = 0, sondagem_max = jogadores->tamanho;
  int sondagem_extras = qtd_jogador_preso;

  for (int i = jogadores->tamanho - 1; i >= 0 && sondagem < sondagem_max; i--)
    sondagem += sondar_jogador(map, jogadores_obter(jogadores, i), &sondagem_extras, &qtd_jogador_preso);

  return sondagem;
}

Jogador *dominar(Map *map, Jogadores *jogadores, Sondados *sondados)
{
  if (sondados_vazio(sondados))
    return JOGADOR_NULL;
  SondCoord sond = sondados_max(sondados);
  Jogador *dominado = jogadores_inserir(jogadores, jogador_criar(sond.coord));
  PRINT("dominar %ld %ld\n", dominado->coord.x, dominado->coord.y);

  if (DEBUG)
    PRINT("%ld\n", sond.pontos);

  return dominado;
}

static char str[100];

void ler_sondagem(Map *map, Sondados *sondados)
{
  SondCoord sondado = {0, 0, 0};
  SondCoord min_sondado;
  int indice = 0;

  scanf("%s %ld %ld %ld", str, &sondado.coord.x, &sondado.coord.y, &sondado.pontos);
  LOG(">> %s %ld %ld %ld\n", str, sondado.coord.x, sondado.coord.y, sondado.pontos);

  if (sondado.pontos > 0)
  {
    if (sondados_cheio(sondados))
    {
      min_sondado = sondados_min(sondados);
      if (!less(sondado, min_sondado))
      {
        LOG("pulou \n");
        return;
      }
      sondados_troca_min(sondados, sondado);
    }
    else
    {
      sondados_inserir(sondados, sondado);
    }
  }
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