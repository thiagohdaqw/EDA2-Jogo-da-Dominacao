#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include<stdio.h>

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
  printf("%ld\n", qtd_colisao);
  printf("%ld\n", qtd_resize);
}

void print_relatorio_turno(int turno, int qtd_sondagem, int qtd_jogadores, int dominou)
{
  static long int qtd_colisao_antigo = 0;
  static long int qtd_resize_antigo = 0;
  printf("%d\n", turno);
  printf("%d\n", dominou);
  printf("%d\n", qtd_sondagem);
  printf("%d\n", qtd_jogadores);
  printf("%ld\n", qtd_colisao - qtd_colisao_antigo);
  printf("%ld\n", qtd_resize - qtd_resize_antigo);
  qtd_colisao_antigo = qtd_colisao;
  qtd_resize_antigo = qtd_resize;
}

#endif // DEBUG_H_INCLUDED