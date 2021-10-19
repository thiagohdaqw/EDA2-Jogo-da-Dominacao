#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "coord.h"

// Mapa - HashTable
#define HT_CAPACIDADE_INICIAL 997
static int map_capacidade = HT_CAPACIDADE_INICIAL;
static int map_size = 0;
static coord_t* map;
static int colisao_max = 1995;

void map_criar() {
  map_size = 0;
  map_capacidade = HT_CAPACIDADE_INICIAL;
  colisao_max = 1995;
  map = (coord_t*) calloc(HT_CAPACIDADE_INICIAL, sizeof(coord_t));
}

void map_destruir() {
  free(map);
}

int gen_hash(int *a, int b, int h, int valor)
{
  *a = *a * b % (map_capacidade - 1);
  return (*a * h + valor) % map_capacidade;
}

int hashone(coord_t item)
{
  int a = 31415, b = 27183, h = 0;
  h = gen_hash(&a, b, h, item.x < 0);
  h = gen_hash(&a, b, h, item.y < 0);
  h = gen_hash(&a, b, h, item.x);
  h = gen_hash(&a, b, h, item.y);
  return h;
}

int hashtwo(int h)
{
  return (16161 * (unsigned)h) % map_capacidade;
}

int hash(int h1, int h2, int i)
{
  return (h1 + i * h2) % map_capacidade;
}

coord_t *map_obter(int indice)
{
  return &map[indice];
}

void map_mudar_capacidade_e_reinserir(int nova_capacidade);

int map_obter_indice_livre(coord_t item)
{
  int indice;
  int h = hashone(item);
  int h2 = hashtwo(h);
  int colisao = 0;
  for (colisao = 0; colisao < colisao_max; colisao++)
  {
    indice = hash(h, h2, colisao);
    if (coord_eh_null(map_obter(indice)))
      return indice;
    LOG_COLISAO();
  }

  map_mudar_capacidade_e_reinserir(2*map_capacidade+1);
  return map_obter_indice_livre(item);
}

int map_inserir(coord_t item)
{
  if (map_size*1.0/map_capacidade >= 0.75) {
    map_mudar_capacidade_e_reinserir(map_capacidade*2+1);
  }

  int indice = map_obter_indice_livre(item);

  map[indice] = item;
  map_size++;
  return indice;
}

coord_t *map_buscar(coord_t item, int *indice)
{
  int h = hashone(item);
  int h2 = hashtwo(h);
  int colisao;

  for (colisao = 0; colisao < colisao_max; colisao++)
  {
    *indice = hash(h, h2, colisao);
    if (coord_eh_null(map_obter(*indice)) || coord_eh_igual(map_obter(*indice), &item))
      return map_obter(*indice);
    LOG_COLISAO();
  }

  *indice = -1;
  return &NULL_COORD;
}

void map_mudar_capacidade_e_reinserir(int nova_capacidade) {
  int i = 0, capacidade_antiga = map_capacidade;

  coord_t* map_antigo = map;
  map = (coord_t*) calloc(nova_capacidade, sizeof(coord_t));

  map_capacidade = nova_capacidade;
  map_size = 0;
  for (; i < capacidade_antiga; i++) {
    if (!coord_eh_null(&map_antigo[i]))
      map_inserir(map_antigo[i]);
  }

  free(map_antigo);
}


#endif // HASHTABLE_H_INCLUDED