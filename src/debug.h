#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include<stdio.h>

#define PRINT(x, args...) \
  {                       \
    printf(x, ##args);    \
    fflush(stdout);       \
  }

long int qtd_colisao = 0;
long int qtd_resize = 0;

#ifndef DEBUG
#define DEBUG 0

#define LOG(x, args...)  {}
#define LOG_COLISAO() {}
#define LOG_RESIZE() {}

#else
#define LOG_COLISAO() (qtd_colisao++)
#define LOG_RESIZE() (qtd_resize++)
#define LOG(x, args...)         \
  {                             \
    fprintf(stderr, x, ##args); \
    fflush(stderr);             \
  }
#endif

void print_relatorio_final(){
  PRINT("%ld\n", qtd_colisao);
  PRINT("%ld\n", qtd_resize);
}

void print_relatorio_turno(int turno, int qtd_sondagem, int qtd_jogadores, int dominou)
{
  static long int qtd_colisao_antigo = 0;
  static long int qtd_resize_antigo = 0;
  PRINT("%d\n", turno);
  PRINT("%d\n", dominou);
  PRINT("%d\n", qtd_sondagem);
  PRINT("%d\n", qtd_jogadores);
  PRINT("%ld\n", qtd_colisao - qtd_colisao_antigo);
  PRINT("%ld\n", qtd_resize - qtd_resize_antigo);
  qtd_colisao_antigo = qtd_colisao;
  qtd_resize_antigo = qtd_resize;
}

#endif // DEBUG_H_INCLUDED