#include "doctest.h"

#include <iostream>

#ifndef TEST_SONDADOS
#define TEST_SONDADOS
extern "C" {
#endif
  #include "../src/coord.h"
  #include "../src/sondados.h"
#ifdef TEST_SONDADOS
}
#endif

#define sondado_eh_igual(A, B) ((A).pontos == (B).pontos && (A).coord.x == (B).coord.x && (A).coord.y == (B).coord.y )

TEST_CASE("sondados encher") {
  Sondados sondados;
  SondCoord sond = {0, 0, 1000};
  int max = 100;
  sondados_inicializa(&sondados, max);

  for(int i = 0; i < 2*max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  CHECK(sondados.N == sondados.capacity);
}

TEST_CASE("sondados minimo") {
  Sondados sondados;
  SondCoord sond = {0, 0, 1000};
  SondCoord sond_min = {-15, -15, 1};
  int max = 1000;
  sondados_inicializa(&sondados, max);
  sondados_inserir(&sondados, sond_min);

  for(int i = 0; i < max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}

TEST_CASE("sondados minimo apos delMax") {
  Sondados sondados;
  SondCoord sond = {0, 0, 1000};
  SondCoord sond_min = {-15, -15, 1};
  int max = 1000;
  sondados_inicializa(&sondados, max);
  sondados_inserir(&sondados, sond_min);

  for(int i = 0; i < max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  sondados_max(&sondados);
  sondados_max(&sondados);
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}

TEST_CASE("sondados minimo apos delMax e insercao") {
  Sondados sondados;
  SondCoord sond = {0, 0, 1000};
  SondCoord sond_min = {-15, -15, 1};
  int max = 1000;
  sondados_inicializa(&sondados, max);
  sondados_inserir(&sondados, sond_min);

  for(int i = 0; i < max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  sondados_max(&sondados);
  sondados_max(&sondados);
  sond.pontos -= 100;
  sondados_inserir(&sondados, sond);
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}

TEST_CASE("sondados insere min") {
  Sondados sondados;
  int max = 1000;
  SondCoord sond = {0, 0, 5*max};
  SondCoord sond_min = {-15, -15, 1};
  sondados_inicializa(&sondados, max);

  for(int i = 0; i < 2*max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  sond_min.pontos = sond.pontos - 100;
  sondados_inserir(&sondados, sond_min);
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}

TEST_CASE("sondados insere min") {
  Sondados sondados;
  int max = 1000;
  SondCoord sond = {0, 0, 5*max};
  SondCoord sond_min = {-15, -15, 1};
  sondados_inicializa(&sondados, max);

  for(int i = 0; i < 2*max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  sond_min.pontos = sond.pontos - 100;
  sondados_inserir(&sondados, sond_min);
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}