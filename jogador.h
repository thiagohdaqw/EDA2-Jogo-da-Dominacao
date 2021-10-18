#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED

#include <stdlib.h>
#include "coord.h"
#include "map.h"

typedef struct jogador{
  Coord coord;
  int esta_preso;
}Jogador;

typedef struct jogadores{
  Jogador *jogadores;
  int tamanho;
}Jogadores;

#define JOGADOR_NULL NULL
#define jogador_eh_null(J) ((J) == JOGADOR_NULL)

Jogador *jogadores_obter(Jogadores *jogadores, int indice){
  return &jogadores->jogadores[indice];
}

Jogador *jogadores_inserir(Jogadores *jogadores, Jogador j)
{
  jogadores->jogadores[jogadores->tamanho++] = j;
  return jogadores_obter(jogadores, jogadores->tamanho-1);
}

void jogadores_inicializa(Map *map, Jogadores *jogadores, Jogador jogador_inicial, int limite_turnos)
{
  MapCoord j = {0, 0, DOMINADO};
  jogadores->jogadores = (Jogador *)malloc((limite_turnos + 2) * sizeof(Jogador));
  jogadores->tamanho = 0;
  j.coord = jogador_inicial.coord;

  map_inserir(map, j);
  jogadores_inserir(jogadores, jogador_inicial);
}

Jogador jogador_criar(Coord coord){
  Jogador novo;
  novo.esta_preso = 0;
  novo.coord = coord;
  return novo;
}

void jogador_prender(Jogador *jogador){
  jogador->esta_preso = 1;
}

int jogador_esta_preso(Jogador *jogador){
  return jogador->esta_preso;
}

#endif