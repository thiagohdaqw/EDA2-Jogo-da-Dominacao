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

  map_inserir(c);
  CHECK(map_size == 1);
  ptr_c = map_buscar(c, &indice);
  CHECK(ptr_c->x == 1);
  CHECK(ptr_c->y == 1);
  CHECK(ptr_c->pontos == 10);

  c.x = 10;
  c.pontos = 20;
  map_inserir(c);
  CHECK(map_size == 2);
  ptr_c = map_buscar(c, &indice);
  CHECK(ptr_c->x == 10);
  CHECK(ptr_c->y == 1);
  CHECK(ptr_c->pontos == 20);

  map_destruir();
}

TEST_CASE("ht muito inserir e buscar sem resize") {
  map_criar();

  int indice, i;
  coord_t c = {1, 1, 10, SONDADO};
  coord_t* ptr_c;

  // +2 pra forçar resize
  int map_capacidade_tres_quartos = 0.75*map_capacidade-2;
  for (i = 0; i < map_capacidade_tres_quartos; i++) {
    map_inserir(c);
    c.x++; c.y++;
  }

  // certificar que não ocorreu resize
  REQUIRE(map_capacidade == HT_CAPACIDADE_INICIAL);

  c.x = c.y = 1;
  for (i = 0; i < map_capacidade_tres_quartos; i++) {
    CHECK(!coord_eh_null(map_buscar(c, &indice)));  
    c.x++; c.y++;
  }

  map_destruir();
}

TEST_CASE("ht um resize apenas pelo tamanho") {
  map_criar();

  int indice, i;
  coord_t c = {1, 1, 10, SONDADO};
  coord_t* ptr_c;

  // +2 pra forçar resize
  int capacidade_inicial = map_capacidade;
  for (i = 0; i < capacidade_inicial; i++) {
    map_inserir(c);
    c.x++; c.y++;
  }

  REQUIRE(map_capacidade > 2*HT_CAPACIDADE_INICIAL);
  c.x = c.y = 1;
  for (i = 0; i < capacidade_inicial; i++) {
    map_buscar(c, &indice);  
    CHECK(coord_eh_igual(&c, &map[indice]));
    c.x++; c.y++;
  }

  map_destruir();
}

TEST_CASE("ht pelo menos dois resizes apenas por tamanho") {
  map_criar();

  int indice, i;
  int x_inicial = 0, y_inicial = 0;
  coord_t c = {x_inicial, y_inicial, 10, SONDADO};
  coord_t* ptr_c;

  int x2_capacidade_inicial = 2*map_capacidade + 2;
  for (size_t i = 0; i < x2_capacidade_inicial; i++) {
    c.x++; c.y++;
    map_inserir(c);
  }

  // std::cout << "map size " << map_size << std::endl;
  // std::cout << "map cap " << map_capacidade << std::endl;
  REQUIRE(map_capacidade > HT_CAPACIDADE_INICIAL);

  c.x = x_inicial; c.y = y_inicial;
  for (i = 0; i < x2_capacidade_inicial; i++) {
    map_buscar(c, &indice);  
    CHECK(coord_eh_igual(&c, &map[indice]));
    c.x++; c.y++;
  }

  map_destruir();
}