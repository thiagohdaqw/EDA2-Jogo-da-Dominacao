#include "doctest.h"

#ifndef TEST_HASHTABLE
#define TEST_HASHTABLE
extern "C" {
#endif
  #include "../hashtable.h"
#ifdef TEST_HASHTABLE
}
#endif

TEST_CASE("construtor") {
  HT* ht = HT_criar();

  CHECK(map_size == 0);

  HT_destruir(ht);
}

TEST_CASE("inserção funciona") {
  HT* ht = HT_criar();

  coord_t c = {0, 0, 10, NAO_SONDADO};
  map_inserir(c);
  CHECK(map_size == 1);

  HT_destruir(ht);
}