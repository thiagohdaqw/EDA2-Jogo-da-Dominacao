#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define PRINT(x, args...) \
  {                       \
    printf(x, ##args);    \
    fflush(stdout);       \
  }

#ifndef DEBUG
int qtd_colisao = 0;
#define LOG(x, args...) \
  {                     \
  }
#define LOG_COLISAO() \
  {                   \
  }
#define DEBUG 0
#else
int qtd_colisao = 0;
#define LOG_COLISAO() (qtd_colisao++)
#define LOG(x, args...)         \
  {                             \
    fprintf(stderr, x, ##args); \
    fflush(stderr);             \
  }
#endif

void print_relatorio_final(int total_pontos, int pq_n, int pq_capacity){
  LOG("PQn=%d PQcapacity=%d\n", pq_n, pq_capacity);
  LOG("== Relatorio Final |")
  LOG("pontuação: %d |", total_pontos);
  LOG("Quantidade colisoes: %d |", qtd_colisao);
  LOG("\n");
}

#endif // DEBUG_H_INCLUDED