#include "doctest.h"

#include <iostream>

#ifndef TEST_HASHTABLE
#define TEST_HASHTABLE
extern "C" {
#endif
  #include "../hashtable.h"
#ifdef TEST_HASHTABLE
}
#endif

TEST_CASE("ht construtor") {
  map_criar();
  
  CHECK(map_size == 0);

  map_destruir();
}

TEST_CASE("ht inserir e buscar") {
  map_criar();

  int indice;
  coord_t c = {1, 1, 10, NAO_SONDADO};
  coord_t* ptr_c;

  map_inserir(map, c);
  CHECK(map_size == 1);
  ptr_c = map_buscar(c, &indice);
  CHECK(ptr_c->x == 1);
  CHECK(ptr_c->y == 1);
  CHECK(ptr_c->pontos == 10);

  c.x = 10;
  c.pontos = 20;
  map_inserir(map, c);
  CHECK(map_size == 2);
  ptr_c = map_buscar(c, &indice);
  CHECK(ptr_c->x == 10);
  CHECK(ptr_c->y == 1);
  CHECK(ptr_c->pontos == 20);

  map_destruir();
}

TEST_CASE("ht um resize apenas por tamanho") {
  map_criar();

  int indice, i;
  coord_t c = {1, 1, 10, SONDADO};
  coord_t* ptr_c;

  // +3 pra forçar resize
  int map_capacidade_tres_quartos = 0.75*map_capacidade + 2;
  for (i = 0; i < map_capacidade_tres_quartos; i++) {
    map_inserir(map, c);
    c.x++; c.y++;
  }

  REQUIRE(map_capacidade > 2*HT_CAPACIDADE_INICIAL);
  c.x = 1;
  c.y = 1;
  CHECK(!coord_eh_null(map_buscar(c, &indice)));  
  // for (i = 0; i < map_capacidade; i++) {
  // }

  map_destruir();
}

// TEST_CASE("ht dois resizes apenas por tamanho") {
//   map_criar();

//   int indice, i;
//   coord_t c = {1, 1, 10, NAO_SONDADO};
//   coord_t* ptr_c;

//   int map_capacidade_tres_quartos = 0.75*map_capacidade;
//   for (size_t i = 0; i < map_capacidade_tres_quartos-1; i++) {
//     c.x += i;
//     map_inserir(map, c);
//   }

//   REQUIRE(map_capacidade == HT_CAPACIDADE_INICIAL);
//   std::cout << "size " << map_size << std::endl;

//   map_destruir();
// }