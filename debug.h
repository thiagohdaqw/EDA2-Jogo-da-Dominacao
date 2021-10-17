#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define PRINT(x, args...) \
  {                       \
    printf(x, ##args);    \
    fflush(stdout);       \
  }

#ifndef DEBUG
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



#endif // DEBUG_H_INCLUDED