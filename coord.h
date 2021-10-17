#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

// Coordenadas
typedef enum
{
  NAO_SONDADO,
  SONDADO,
  DOMINADO,
  PRESO
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


#endif // COORD_H_INCLUDED