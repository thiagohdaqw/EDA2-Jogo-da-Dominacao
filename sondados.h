#ifndef SONDADOS_H_INCLUDED
#define SONDADOS_H_INCLUDED

#include "coord.h"

typedef struct SondCoord
{
  Coord coord;
  long int pontos;
} SondCoord;

#define Item SondCoord
#define pq_key(A) ((A).pontos)
#define less(A, B) (pq_key(A) < pq_key(B))

#include "pq.h"

typedef struct pq_st Sondados;

void sondados_inicializa(Sondados *sondados, int max)
{
  PQinit(sondados, max);
}

int sondados_vazio(Sondados *sondados)
{
  return PQempty(sondados);
}

int sondados_cheio(Sondados *sondados){
  return PQfull(sondados);
}

SondCoord sondados_min(Sondados *sondados)
{
  return PQmin(sondados);
}

SondCoord sondados_max(Sondados *sondados){
  return PQdelMax(sondados);
}

void sondados_inserir(Sondados *sondados, SondCoord novo){
  PQinsert(sondados, novo);
}

void sondados_troca_min(Sondados *sondados, SondCoord novo){
  sondados->pq[sondados->min] = novo;
  PQchange(sondados, sondados->min);
}

#endif