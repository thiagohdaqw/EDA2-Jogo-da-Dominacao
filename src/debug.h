#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define PRINT(x, args...) \
  {                       \
    printf(x, ##args);    \
    fflush(stdout);       \
  }

long int qtd_colisao = 0;
long int qtd_redimensionamento = 0;

#ifndef DEBUG
#define DEBUG 0

#define LOG(x, args...)  {}
#define LOG_COLISAO() {}
#define LOG_REDIMENSIONAMENTO() {}

#else
#define LOG_COLISAO() (qtd_colisao++)
#define LOG_REDIMENSIONAMENTO() (qtd_redimensionamento++)
#define LOG(x, args...)         \
  {                             \
    fprintf(stderr, x, ##args); \
    fflush(stderr);             \
  }
#endif

void print_relatorio_final(){
  PRINT("%ld\n", qtd_colisao);
  PRINT("%ld\n", qtd_redimensionamento);
}

#endif // DEBUG_H_INCLUDED