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

int sondados_contem(Sondados *sondados, SondCoord x){
  for(int i = 1; i < sondados->N; i++)
    if(sondado_eh_igual(sondados->pq[i], x))
      return 1;
  return 0;
}

long int random_number(unsigned int *seed){
  return (-1)^(rand_r(seed)%2) * rand_r(seed);
}

SondCoord sondado_random(unsigned int *seed){
  SondCoord sond;
  sond.coord.x = random_number(seed);
  sond.coord.y = random_number(seed);
  sond.pontos = random_number(seed);
  return sond;
}

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
  SondCoord sond = {0, 0, 2000};
  SondCoord sond_min = {-15, -15, 1};
  int max = 1000;
  sondados_inicializa(&sondados, max);
  sondados_inserir(&sondados, sond_min);

  for(int i = 0; i < max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
    CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
  }
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}

TEST_CASE("sondados minimo apos delMax") {
  int max = 1000;
  Sondados sondados;
  SondCoord sond = {0, 0, 2*max};
  SondCoord sond_min = {-15, -15, 1};
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
  int max = 1000;
  Sondados sondados;
  SondCoord sond = {0, 0, 2*max};
  SondCoord sond_min = {-15, -15, 1};
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
    CHECK(sondado_eh_igual(sondados_min(&sondados), sond));
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

TEST_CASE("sondados troca min") {
  int max = 1000;
  Sondados sondados;
  SondCoord sond = {0, 0, 5*max};
  SondCoord sond_min = {0, 0};
  sondados_inicializa(&sondados, max);

  for(int i = 0; i < 2*max; i++){
    sond.coord.x++;
    sond.coord.y++;
    sond.pontos--;
    sondados_inserir(&sondados, sond);
  }
  sond_min.pontos = sond.pontos - 1;
  sondados_troca_min(&sondados, sond_min);
  CHECK(!sondados_contem(&sondados, sond));
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
}

TEST_CASE("sondados insere aleatorio"){
  int max = 100000;
  Sondados sondados;
  SondCoord sond = {0, 0, 0};
  SondCoord sond_min = {0, 0, 0};
  sondados_inicializa(&sondados, max);
  unsigned int seed = 77777;

  sondados_inserir(&sondados, sond_min);
  for(int i = 0; i < 3*max; i++){
    sond = sondado_random(&seed);
    if(less(sond, sond_min))
      sond_min = sond;
    sondados_inserir(&sondados, sond);
    CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
  }
  printf("%d %d %ld\n", sondados.N, sondados.capacity, sondados_min(&sondados).pontos);
}

// TEST_CASE("sondados insere aleatorio e retira"){
//   int max = 100000;
//   Sondados sondados;
//   SondCoord sond = {0, 0, 0};
//   SondCoord sond_min = {0, 0, 0};
//   sondados_inicializa(&sondados, max);
//   unsigned int seed = 77777;

//   sondados_inserir(&sondados, sond_min);
//   for(int i = 0; i < 3*max; i++){
//     sond = sondado_random(&seed);
//     if(less(sond, sond_min))
//       sond_min = sond;
//     sondados_inserir(&sondados, sond);
//     CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
//     if(rand_r(&seed) % 2)
//       sondados_max(&sondados);
//   }
//   CHECK(sondado_eh_igual(sondados_min(&sondados), sond_min));
// }

TEST_CASE("sondados troca min para valor maior que segundo minimo e menor que o maximo"){
  int max = 100000;
  Sondados sondados;
  SondCoord sond = {0, 0, 0};
  sondados_inicializa(&sondados, max);

  sond.pontos = 100;
  sondados_inserir(&sondados, sond);
  sond.pontos = 10;
  sondados_inserir(&sondados, sond);
  sond.pontos = 200;
  sondados_inserir(&sondados, sond);
  sond.pontos = 10;
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond));
  sond.pontos = 150;
  sondados_troca_min(&sondados, sond);
  sond.pontos = 100;
  CHECK(sondado_eh_igual(sondados_min(&sondados), sond));
}

void print_sondados(Sondados *sondados){
  for(int i = 0; i < sondados->capacity; i++)
    printf("%ld ", sondados->pq[i].pontos);
  printf("\n");
}

void popula_sondados(Sondados *sondados, int n, long pontos_inical, long incremento){
  SondCoord sond;
  sond.pontos = pontos_inical;
  for(int i = 0; i < n; i++, sond.pontos += incremento){
    sondados_inserir(sondados, sond);
  }
}

TEST_CASE("sondados crescimento"){
  int max = 10;
  Sondados sondados;
  SondCoord sond = {0, 0, 0};
  sondados_inicializa(&sondados, max+5);

  popula_sondados(&sondados, max, 0, 1);
  print_sondados(&sondados);

  popula_sondados(&sondados, 10, 10, 1);
  print_sondados(&sondados);

  printf("%d %d\n", sondados.N, sondados.capacity);
  CHECK(1);
}

TEST_CASE("sondados resize"){
  int max = 10;
  Sondados sondados;
  SondCoord sond = {0, 0, 0};
  sondados_inicializa(&sondados, max);

  popula_sondados(&sondados, max+1, 0, 1);

  printf("%d %d\n", sondados.N, sondados.capacity);
  CHECK(sondados.capacity > sondados.N);
}
