#include <stdio.h>
#include <stdlib.h>

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

void print_relatorio_turno(int turno, int qtd_sondagem, int dominou);

// Coordenadas
typedef enum
{
  NAO_SONDADO,
  SONDADO,
  DOMINADO
} Estado;

typedef struct coord_t
{
  int x, y;
  int pontos;
  Estado estado;
} coord_t;

static coord_t **jogadores;
static int qtd_jogadores = 0;
static coord_t NULL_COORD = {0, 0, 0, NAO_SONDADO};
#define NULL_COORD_INDICE -1

void jogadores_inserir(coord_t *jogador)
{
  jogadores[qtd_jogadores++] = jogador;
}

int coord_eh_igual(coord_t *a, coord_t *b)
{
  return a->x == b->x && a->y == b->y;
}

int coord_eh_null(coord_t *a)
{
  return a->estado == NULL_COORD.estado;
}

// Fim Coordenadas

// Mapa - HashTable
#define MAP_INITIAL_CAPACITY 997
static int map_capacity = MAP_INITIAL_CAPACITY;
static int map_size = 0;
static coord_t map[MAP_INITIAL_CAPACITY] = {[0 ... MAP_INITIAL_CAPACITY - 1] = {0, 0, 0, NAO_SONDADO}};
static int colisao_max = 50;

int gen_hash(int *a, int b, int h, int valor)
{
  *a = *a * b % (map_capacity - 1);
  return (*a * h + valor) % map_capacity;
}

int hashone(coord_t item)
{
  int a = 31415, b = 27183, h = 0;
  h = gen_hash(&a, b, h, item.x < 0);
  h = gen_hash(&a, b, h, item.y < 0);
  h = gen_hash(&a, b, h, item.x);
  h = gen_hash(&a, b, h, item.y);
  return h;
}

int hashtwo(int h)
{
  return (16161 * (unsigned)h) % map_capacity;
}

int hash(int h1, int h2, int i)
{
  return (h1 + i * h2) % map_capacity;
}

coord_t *map_obter(int indice)
{
  return &map[indice];
}

int map_obter_indice_livre(coord_t item, int *indice)
{
  int h = hashone(item);
  int h2 = hashtwo(h);
  int colisao;
  for (colisao = 0; colisao < colisao_max; colisao++)
  {
    *indice = hash(h, h2, colisao);
    if (coord_eh_null(map_obter(*indice)))
      return 1;
    LOG_COLISAO();
  }
  // expand
  //return map_obter_indice_livre(item);
  return 0;
}

int map_inserir(coord_t item)
{
  int indice = 0;
  if (!map_obter_indice_livre(item, &indice))
    return NULL_COORD_INDICE;

  map[indice] = item;
  map_size++;
  return indice;
}

coord_t *map_buscar(coord_t item)
{
  int h = hashone(item);
  int h2 = hashtwo(h);
  int colisao, indice;

  for (colisao = 0; colisao < colisao_max; colisao++)
  {
    indice = hash(h, h2, colisao);
    if (coord_eh_null(map_obter(indice)) || coord_eh_igual(map_obter(indice), &item))
      return map_obter(indice);
  }
  return &NULL_COORD;
}

// Fila de Prioridade baseada em indice

#define pq_key(A) (map[A].pontos)
#define less(A, B) (pq_key(A) < pq_key(B))

struct pq_ist
{
  int N;
  int capacity;
  int *pq;
  int *qp;
};

static struct pq_ist sondados;

void exch(struct pq_ist *PQ, int i, int j)
{
  int tmp = PQ->qp[i];
  PQ->qp[i] = PQ->qp[j];
  PQ->qp[j] = tmp;
  PQ->pq[PQ->qp[i]] = i;
  PQ->pq[PQ->qp[j]] = j;
}

void fixUp(struct pq_ist *PQ, int K)
{
  int *v = PQ->pq;

  while (K > 1 && less(v[K / 2], v[K]))
  {
    exch(PQ, v[K], v[K / 2]);
    K = K / 2;
  }
}

void fixDown(struct pq_ist *PQ, int K, int N)
{
  int *v = PQ->pq;
  int j;

  while (2 * K <= N)
  {
    j = 2 * K;
    if (j < N && less(v[j], v[j + 1]))
      j++;
    if (!less(v[K], v[j]))
      break;
    exch(PQ, v[K], v[j]);
    K = j;
  }
}

int PQempty(struct pq_ist *PQ)
{
  return !PQ->N;
}

void PQinit(struct pq_ist *PQ, int MAX)
{
  PQ->N = 0;
  PQ->capacity = MAX;
  PQ->pq = malloc(sizeof(int) * (MAX + 1));
  PQ->qp = malloc(sizeof(int) * (MAX + 1));
}

int PQdelMax(struct pq_ist *PQ)
{
  exch(PQ, PQ->pq[1], PQ->pq[PQ->N]);
  fixDown(PQ, 1, PQ->N - 1);
  return PQ->pq[PQ->N--];
}

void PQinsert(struct pq_ist *PQ, int K)
{
  PQ->qp[K] = ++PQ->N;
  PQ->pq[PQ->N] = K;
  fixUp(PQ, PQ->N);
}

void PQchange(struct pq_ist *PQ, int K)
{
  fixUp(PQ, PQ->qp[K]);
  fixDown(PQ, PQ->qp[K], PQ->N);
}

int PQmin(struct pq_ist *PQ)
{
  int *v = PQ->pq;
  if (less(v[PQ->N - 1], v[PQ->N]))
    return PQ->N - 1;
  return PQ->N;
}

int PQfull(struct pq_ist *PQ)
{
  return PQ->N >= PQ->capacity;
}

void PQprint(struct pq_ist *PQ)
{
  for (size_t i = 1; i < PQ->N; i++)
  {
    coord_t c = map[PQ->pq[i]];
    LOG("(%d, %d) -> %d, ", c.x, c.y, c.pontos);
  }
  LOG("\n");
}

// Logica do Jogo

int sondar()
{
  coord_t *jog;
  coord_t coord_atual;
  coord_t *coord_pesquisada;
  int qtd_sondagem = 0, achou = 0, sondagem_max = qtd_jogadores;

  for (int i = 0; i < qtd_jogadores && qtd_sondagem < sondagem_max; ++i)
  {
    jog = jogadores[i];
    achou = 0;

    for (coord_atual.x = jog->x - 1; coord_atual.x <= jog->x + 1 && !achou; coord_atual.x++)
    {
      for (coord_atual.y = jog->y - 1; coord_atual.y <= jog->y + 1 && !achou; coord_atual.y++)
        if (!(coord_atual.x == jog->x && coord_atual.y == jog->y))
        {
          coord_pesquisada = map_buscar(coord_atual);
          if (coord_eh_null(coord_pesquisada))
          {
            PRINT("sondagem %d %d", coord_atual.x, coord_atual.y);
            coord_pesquisada->estado = SONDADO;
            qtd_sondagem++;
            achou = 1;
          }
        }
    }
  }

  return qtd_sondagem;
}

coord_t *dominar()
{
  if (PQempty(&sondados))
    return &NULL_COORD;
  coord_t *dominado = map_obter(PQdelMax(&sondados));
  dominado->estado = DOMINADO;
  jogadores_inserir(dominado);
  PRINT("dominacao %d %d", dominado->x, dominado->y);
  return dominado;
}

static char str[100];

void ler_sondagem()
{
  coord_t sondado = {0, 0, 0, SONDADO};
  int min_indice = 0, indice = 0;

  scanf("%s %d %d %d", str, &sondado.x, &sondado.y, &sondado.pontos);
  LOG(">> %s %d %d %d\n", str, sondado.x, sondado.y, sondado.pontos);

  indice = map_inserir(sondado);
  if (sondado.pontos > 0)
  {
    min_indice = PQmin(&sondados);
    if (PQfull(&sondados) && less(indice, min_indice))
    {
      LOG("pulou \n");
      return;
    }
    PQinsert(&sondados, indice);
  }
}

void ler_resposta_do_juiz(int qtd_sondagem, coord_t *dominado)
{
  for (int j = 0; j < qtd_sondagem; j++)
    ler_sondagem();

  if (!coord_eh_null(dominado))
  {
    scanf("%*s %*d");
    LOG("> dominacao %d %d %d\n", dominado->x, dominado->y, dominado->pontos);
  }
}

void inicializa_jogadores(coord_t *jogador_inicial, int limite_turnos)
{
  jogadores = malloc((limite_turnos + 2) * sizeof(coord_t *));
  map_inserir(*jogador_inicial);
  jogadores_inserir(jogador_inicial);
}

void inicializa_sondados()
{
  PQinit(&sondados, 1000);
}

int calc_total_pontos()
{
  int total_pontos = 0;
  for (int i = 0; i < qtd_jogadores; ++i)
    total_pontos += jogadores[i]->pontos;
  return total_pontos;
}

int main()
{
  coord_t jogador_inicial = {0, 0, 0, DOMINADO};
  coord_t *dominado = &NULL_COORD;
  int limite_de_turnos, dominou = 0, qtd_sondagem;

  scanf("%d %d %d %d", &jogador_inicial.x, &jogador_inicial.y,
        &jogador_inicial.pontos, &limite_de_turnos);

  inicializa_jogadores(&jogador_inicial, limite_de_turnos);
  inicializa_sondados();

  for (int turno = 0; turno < limite_de_turnos; turno++)
  {
    qtd_sondagem = sondar();
    dominado = dominar();
    PRINT("fimturno\n");
    ler_resposta_do_juiz(qtd_sondagem, dominado);
    if (DEBUG)
      print_relatorio_turno(turno + 1, qtd_sondagem, !coord_eh_null(dominado));
  }

  LOG("== Relatorio Final |")
  LOG("pontuação: %d |", calc_total_pontos());
  LOG("Quantidade colisoes: %d |", qtd_colisao);
  LOG("\n");

  free(jogadores);
  free(sondados.pq);
  free(sondados.qp);
  return 0;
}

// Outros
void print_relatorio_turno(int turno, int qtd_sondagem, int dominou)
{
  static int qtd_colisao_passada = 0;
  int total_pontos = calc_total_pontos();
  LOG("-- turno %d\n", turno);
  LOG("-- qtd sondagem %d\n", qtd_sondagem);
  LOG("-- dominou %d\n", dominou);
  LOG("-- qtd jogadores: %d\n", qtd_jogadores);
  LOG("-- pontos até agora: %d\n", total_pontos);
  LOG("-- PQ: ");
  PQprint(&sondados);
  LOG("-- Quantidade de colisao: %d", qtd_colisao - qtd_colisao_passada);
  LOG("\n\n");
  qtd_colisao_passada = qtd_colisao;
}