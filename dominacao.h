#ifndef DOMINACAO_H_INCLUDED
#define DOMINACAO_H_INCLUDED

#include "hashtable.h"
#include "pq.h"

static coord_t *jogadores;
static int qtd_jogadores = 0;
static struct pq_st sondados;

void jogadores_inserir(coord_t jogador)
{
  jogadores[qtd_jogadores++] = jogador;
}

int sondar_coord(coord_t coord)
{
  int indice = 0;
  coord_t *pesquisado = map_buscar(coord, &indice);
  if (coord_eh_null(pesquisado))
  {
    PRINT("sondagem %d %d", coord.x, coord.y);
    pesquisado->x = coord.x;
    pesquisado->y = coord.y;
    pesquisado->estado = SONDADO;
    return 1;
  }
  return 0;
}

int sondar_jogador(coord_t *jogador, int *sondagem_extras, int *qtd_jogador_preso)
{
  if (jogador->estado == PRESO)
    return 0;
  coord_t atual, *pesquisado;
  int qtd_sondagem = 0;
  int sondagem_possiveis = 1 + *sondagem_extras;
  int x, y, dx, dy, t, contador;

  x = dx = 1;
  y = dy = 0;

  for (contador = 0; contador < 8 && sondagem_possiveis > 0; contador++)
  {
    atual.x = jogador->x + x;
    atual.y = jogador->y + y;
    if (sondar_coord(atual))
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

  if(contador == 8){
    jogador->estado = PRESO;
    *qtd_jogador_preso++;
  }

  *sondagem_extras = sondagem_possiveis;
  return qtd_sondagem;
}

int sondar()
{
  static int qtd_jogador_preso = 0;
  int sondagem = 0, sondagem_max = qtd_jogadores;
  int sondagem_extras = qtd_jogador_preso;

  for (int i = qtd_jogadores - 1; i >= 0 && sondagem < sondagem_max; i--)
  {
    sondagem += sondar_jogador(&jogadores[i], &sondagem_extras, &qtd_jogador_preso);
  }

  return sondagem;
}

coord_t dominar()
{
  if (PQempty(&sondados))
    return NULL_COORD;
  coord_t dominado = PQdelMax(&sondados);
  dominado.estado = DOMINADO;
  jogadores_inserir(dominado);
  PRINT("dominacao %d %d\n", dominado.x, dominado.y);
  return dominado;
}

static char str[100];

void ler_sondagem()
{
  coord_t sondado = {0, 0, 0, SONDADO};
  coord_t min_sondado;
  int indice = 0;

  scanf("%s %d %d %d", str, &sondado.x, &sondado.y, &sondado.pontos);
  LOG(">> %s %d %d %d\n", str, sondado.x, sondado.y, sondado.pontos);

  map_buscar(sondado, &indice)->pontos = sondado.pontos;
  if (sondado.pontos > 0)
  {
    min_sondado = PQmin(&sondados);
    if (PQfull(&sondados) && less(sondado, min_sondado))
    {
      LOG("pulou \n");
      return;
    }
    PQinsert(&sondados, sondado);
  }
}

void ler_resposta_do_juiz(int qtd_sondagem, coord_t *dominado)
{
  for (int j = 0; j < qtd_sondagem; j++)
    ler_sondagem();

  if (!coord_eh_null(dominado))
  {
    scanf("%*s %*d");
    LOG("> dominacao %d %d %d\n", dominado->x, dominado->y, dominado->pontos);
  }
}

void inicializa_jogadores(coord_t *jogador_inicial, int limite_turnos)
{
  jogadores = malloc((limite_turnos + 2) * sizeof(coord_t));
  map_inserir(*jogador_inicial);
  jogadores_inserir(*jogador_inicial);
}

void inicializa_sondados(int max)
{
  PQinit(&sondados, max);
}

int calc_total_pontos()
{
  int total_pontos = 0;
  for (int i = 0; i < qtd_jogadores; ++i)
    total_pontos += jogadores[i].pontos;
  return total_pontos;
}


#endif // DOMINACAO_H_INCLUDED