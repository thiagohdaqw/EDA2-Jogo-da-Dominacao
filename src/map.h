#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <stdlib.h>
#include "coord.h"
#include "debug.h"

typedef enum
{
  NAO_SONDADO,
  SONDADO,
  DOMINADO
} Estado;

typedef struct MapCoord
{
  Coord coord;
  Estado estado;
} MapCoord;

typedef struct map
{
  MapCoord *coords;
  long int capacity;
  long int size;
} Map;

#define MAP_INITIAL_CAPACITY 10000
#define COLISION_MAX 5000
#define MAP_COORD_NULL NAO_SONDADO
#define MAP_COORD_INDICE_NULL -1
#define map_coord_eh_null(A) ((A).estado == MAP_COORD_NULL)
#define map_coord_eh_igual(A, B) (coord_eh_igual((A).coord, (B).coord))
MapCoord coords[MAP_INITIAL_CAPACITY] = {[0 ... MAP_INITIAL_CAPACITY -1] = {0, 0, NAO_SONDADO}}; 
#define mapa_is_static(A) (A == coords)

void map_inicializa(Map *map)
{
  map->capacity = MAP_INITIAL_CAPACITY;
  map->size = 0;
  //map->coords = coords;
  map->coords = calloc(MAP_INITIAL_CAPACITY, sizeof(MapCoord));
}

void map_destruir(Map *map) {
  free(map->coords);
}

long int gen_hash(Map *map, long int *a, int b, long int h, long int valor)
{
  *a = *a * b % (map->capacity - 1);
  return (*a * (unsigned long)h + valor) % map->capacity;
}

long int hashone(Map *map, MapCoord item)
{
  long int a = 31415, b = 27183, h = 0;
  if(item.coord.x == item.coord.y)
    h = gen_hash(map, &a, b, h, item.coord.x & 1 ? 2 : 1);
  h = gen_hash(map, &a, b, h, item.coord.x < 0);
  h = gen_hash(map, &a, b, h, item.coord.y < 0);
  h = gen_hash(map, &a, b, h, item.coord.x);
  h = gen_hash(map, &a, b, h, item.coord.y);
  return h;
}

long int hashtwo(Map *map, long int h)
{
  return (16161 * h) % map->capacity;
}

long int hash(Map *map, long int h1, long int h2, int i)
{
  return (h1 + i * h2) % map->capacity;
}

MapCoord *map_obter(Map *map, long int indice)
{
  return &map->coords[indice];
}

void map_mudar_capacidade_e_reinserir(Map *map, long int nova_capacidade);

long int map_obter_indice_livre(Map *map, MapCoord item)
{
  long int indice = 0;
  long int h = hashone(map, item);
  long int h2 = hashtwo(map, h);
  long int colisao = 0;
  for (colisao = 0; colisao < COLISION_MAX; colisao++)
  {
    indice = hash(map, h, h2, colisao);
    if (map_coord_eh_null(*map_obter(map, indice)))
      return indice;
    LOG_COLISAO();
  }

  map_mudar_capacidade_e_reinserir(map, 2*map->capacity+1);
  return map_obter_indice_livre(map, item);
}

void map_inserir_indice(Map *map, MapCoord item, long int indice){
  map->coords[indice] = item;
  map->size++;

  if (map->size*1.0/map->capacity >= 0.75) {
    map_mudar_capacidade_e_reinserir(map, map->capacity*2+1);
  }
}

long int map_inserir(Map *map, MapCoord item)
{
  long int indice = map_obter_indice_livre(map, item);

  map_inserir_indice(map, item, indice);
  return indice;
}

MapCoord *map_buscar(Map *map, MapCoord item, long int *indice)
{
  long int h = hashone(map, item);
  long int h2 = hashtwo(map, h);

  for (int colisao = 0; colisao < COLISION_MAX; colisao++)
  {
    *indice = hash(map, h, h2, colisao);
    if (map_coord_eh_null(*map_obter(map, *indice)) || map_coord_eh_igual(*map_obter(map, *indice), item))
      return map_obter(map, *indice);
    LOG_COLISAO();
  }

  map_mudar_capacidade_e_reinserir(map, 2*map->capacity+1);
  return map_buscar(map, item, indice);
}

void map_mudar_capacidade_e_reinserir(Map *map, long int nova_capacidade) {
  int capacidade_antiga = map->capacity;
  MapCoord* map_antigo = map->coords;
  map->coords = (MapCoord*) calloc(nova_capacidade, sizeof(MapCoord));
  map->capacity = nova_capacidade;
  map->size = 0;
  for (int i = 0; i < capacidade_antiga; i++) {
    if (!map_coord_eh_null(map_antigo[i]))
      map_inserir(map, map_antigo[i]);
  }

  if(!mapa_is_static(map_antigo))
    free(map_antigo);
  LOG_RESIZE();
}

#endif // HASHTABLE_H_INCLUDED