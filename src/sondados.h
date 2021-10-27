#ifndef SONDADOS_H_INCLUDED
#define SONDADOS_H_INCLUDED

#include "coord.h"
#include "sondcoord.h"
#include "pq.h"

typedef struct pq_st Sondados;

void sondados_inicializa(Sondados *sondados, int max)
{
  PQinit(sondados, max + 1);
}

int sondados_vazio(Sondados *sondados)
{
  return PQempty(sondados);
}

int sondados_cheio(Sondados *sondados)
{
  return PQfull(sondados);
}

SondCoord sondados_min(Sondados *sondados)
{
  return PQmin(sondados);
}

SondCoord sondados_max(Sondados *sondados)
{
  return PQdelMax(sondados);
}

void sondados_troca_min(Sondados *sondados, SondCoord novo)
{
  sondados->pq[sondados->min] = novo;
  PQchange(sondados, sondados->min);
}

void sondados_expandir(Sondados *sondados){
  sondados->pq = (SondCoord*) realloc(sondados->pq, 2*sondados->capacity * sizeof(SondCoord));
  sondados->capacity = 2*sondados->capacity;
}

void sondados_inserir(Sondados *sondados, SondCoord novo)
{
  if(sondados->N+1 >= sondados->capacity)
    sondados_expandir(sondados);
  PQinsert(sondados, novo);
}

#endif