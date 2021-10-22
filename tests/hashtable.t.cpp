#include "doctest.h"

#include <iostream>

#ifndef TEST_HASHTABLE
#define TEST_HASHTABLE
extern "C" {
#endif
  #include "../src/coord.h"
  #include "../src/map.h"
#ifdef TEST_HASHTABLE
}
#endif

TEST_CASE("ht construtor") {
  Map map;
  map_inicializa(&map);
  
  CHECK(map.size == 0);

  map_destruir(&map);
}

TEST_CASE("ht inserir e buscar") {
  Map map;
  map_inicializa(&map);

  long int indice;
  MapCoord c = {1, 1, NAO_SONDADO};
  MapCoord* ptr_c;

  map_inserir(&map, c);
  CHECK(map.size == 1);
  ptr_c = map_buscar(&map, c, &indice);
  CHECK(ptr_c->coord.x == 1);
  CHECK(ptr_c->coord.y == 1);

  c.coord.x = 10;
  map_inserir(&map, c);
  CHECK(map.size == 2);
  ptr_c = map_buscar(&map, c, &indice);
  CHECK(ptr_c->coord.x == 10);
  CHECK(ptr_c->coord.y == 1);

  map_destruir(&map);
}

TEST_CASE("ht muito inserir e buscar sem resize") {
  Map map;
  map_inicializa(&map);

  long int indice, i;
  MapCoord c = {1, 1, SONDADO};
  MapCoord* ptr_c;

  // +2 pra forçar resize
  long int map_capacidade_tres_quartos = 0.75*map.capacity-2;
  for (i = 0; i < map_capacidade_tres_quartos; i++) {
    map_inserir(&map, c);
    c.coord.x++; c.coord.y++;
  }

  // certificar que não ocorreu resize
  REQUIRE(map.capacity == MAP_INITIAL_CAPACITY);

  c.coord.x = c.coord.y = 1;
  for (i = 0; i < map_capacidade_tres_quartos; i++) {
    CHECK(!map_coord_eh_null(*map_buscar(&map, c, &indice)));  
    c.coord.x++; c.coord.y++;
  }

  map_destruir(&map);
}

TEST_CASE("ht um resize apenas pelo tamanho") {
  Map map;
  map_inicializa(&map);

  long int indice, i;
  MapCoord c = {1, 1, SONDADO};
  MapCoord* ptr_c;

  // +2 pra forçar resize
  long int capacidade_inicial = map.capacity;
  for (i = 0; i < capacidade_inicial; i++) {
    map_inserir(&map, c);
    c.coord.x++; c.coord.y++;
  }

  REQUIRE(map.capacity > 2*MAP_INITIAL_CAPACITY);
  c.coord.x = c.coord.y = 1;
  for (i = 0; i < capacidade_inicial; i++) {
    map_buscar(&map, c, &indice);  
    CHECK(map_coord_eh_igual(c, *map_obter(&map, indice)));
    c.coord.x++; c.coord.y++;
  }

  map_destruir(&map);
}

TEST_CASE("ht pelo menos dois resizes apenas por tamanho") {
  Map map;
  map_inicializa(&map);

  long int indice, i;
  long int x_inicial = 0, y_inicial = 0;
  MapCoord c = {x_inicial, y_inicial, SONDADO};
  MapCoord* ptr_c;

  long int x2_capacidade_inicial = 2*map.capacity + 2;
  for (size_t i = 0; i < x2_capacidade_inicial; i++) {
    c.coord.x++; c.coord.y++;
    map_inserir(&map, c);
  }

  // std::cout << "map size " << map.size << std::endl;
  // std::cout << "map cap " << map.capacity << std::endl;
  REQUIRE(map.capacity > MAP_INITIAL_CAPACITY);

  c.coord.x = x_inicial; c.coord.y = y_inicial;
  for (i = 0; i < x2_capacidade_inicial; i++) {
    map_buscar(&map, c, &indice);  
    CHECK(map_coord_eh_igual(c, *map_obter(&map, indice)));
    c.coord.x++; c.coord.y++;
  }

  map_destruir(&map);
}