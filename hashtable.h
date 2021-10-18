#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "coord.h"

// Mapa - HashTable
#define HT_CAPACIDADE_INICIAL 997
static int map_capacity = HT_CAPACIDADE_INICIAL;
static int map_size = 0;
// static coord_t map[HT_CAPACIDADE_INICIAL] 
//   = {[0 ... HT_CAPACIDADE_INICIAL - 1] = {0, 0, 0, NAO_SONDADO}};
static coord_t* map;
static int colisao_max = 50;

typedef struct HT
{
  int size, capacidade;
  coord_t* arr;
} HT;


HT* HT_criar() {
  map = (coord_t*) calloc(HT_CAPACIDADE_INICIAL, sizeof(coord_t));
  HT* ht = (HT*) malloc(sizeof(HT));
  ht->capacidade = HT_CAPACIDADE_INICIAL;
  ht->size = 0;
  ht->arr = (coord_t*) calloc(HT_CAPACIDADE_INICIAL, sizeof(coord_t));
  return ht;
}

void HT_destruir(HT* ht) {
  free(ht->arr);
  free(ht);
  free(map);
}

int gen_hash(int *a, int b, int h, int valor)
{
  *a = *a * b % (map_capacity - 1);
  return (*a * h + valor) % map_capacity;
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
  return (16161 * (unsigned)h) % map_capacity;
}

int hash(int h1, int h2, int i)
{
  return (h1 + i * h2) % map_capacity;
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

int map_inserir(coord_t item)
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
  return &NULL_COORD;
}


#endif // HASHTABLE_H_INCLUDED