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
static int colisao_max = 50;

void map_criar() {
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

int map_obter_indice_livre(coord_t item, int *indice)
{
  int h = hashone(item);
  int h2 = hashtwo(h);
  int colisao;
  for (colisao = 0; colisao < colisao_max; colisao++)
  {
    *indice = hash(h, h2, colisao);
    if (coord_eh_null(map_obter(*indice)))
      return 1;
    LOG_COLISAO();
  }
  // expand
  //return map_obter_indice_livre(item);
  return 0;
}

void map_mudar_capacidade_e_reinserir(int nova_capacidade);

int map_inserir(coord_t* map, coord_t item)
{
  if (map_size*1.0/map_capacidade >= 0.75) {
    map_mudar_capacidade_e_reinserir(map_capacidade*2+1);
  }

  int indice = 0;
  if (!map_obter_indice_livre(item, &indice))
    return NULL_COORD_INDICE;

  map[indice] = item;
  map_size++;
  return indice;
}

// mesma coisa que map_inserir, mas sem o if do resize
int map_reinserir(coord_t* map, coord_t item)
{
  int indice = 0;
  if (!map_obter_indice_livre(item, &indice))
    return NULL_COORD_INDICE;

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
  // expand
  *indice = -1;
  return &NULL_COORD;
}

void map_mudar_capacidade_e_reinserir(int nova_capacidade) {
  int i = 0;
  coord_t* tmp = (coord_t*) calloc(nova_capacidade, sizeof(coord_t));

  for (; i < map_capacidade; i++) {
    if (!coord_eh_null(&map[i]))
      map_reinserir(tmp, map[i]);
  }

  free(map);
  map = tmp;
  map_capacidade = nova_capacidade;
}


#endif // HASHTABLE_H_INCLUDED