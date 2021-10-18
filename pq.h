#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED

// Fila de Prioridade
#define exch(A, B) \
  {                \
    Item tmp = A;  \
    A = B;         \
    B = tmp;       \
  }

struct pq_st
{
  Item *pq;
  int N;
  int capacity;
};

void fixUp(struct pq_st *PQ, int K)
{
  Item *v = PQ->pq;

  while (K > 1 && less(v[K / 2], v[K]))
  {
    exch(v[K], v[K / 2]);
    K = K / 2;
  }
}

void fixDown(struct pq_st *PQ, int K, int N)
{
  Item *v = PQ->pq;
  int j;
  while (2 * K <= N)
  {
    j = 2 * K;
    if (j < N && less(v[j], v[j + 1]))
      j++;
    if (!less(v[K], v[j]))
      break;
    exch(v[K], v[j]);
    K = j;
  }
}

void PQinit(struct pq_st *PQ, int maxN)
{
  PQ->capacity = maxN;
  PQ->pq = malloc(sizeof(Item) * (PQ->capacity + 1));
  PQ->N = 0;
}

int PQempty(struct pq_st *PQ)
{
  return PQ->N == 0;
}

void PQinsert(struct pq_st *PQ, Item novo)
{
  PQ->pq[++PQ->N] = novo;
  fixUp(PQ, PQ->N);
}

Item PQdelMax(struct pq_st *PQ)
{
  exch(PQ->pq[1], PQ->pq[PQ->N]);
  fixDown(PQ, 1, --PQ->N);
  return PQ->pq[PQ->N + 1];
}

void PQchange(struct pq_st *PQ, int K)
{
  fixUp(PQ, K);
  fixDown(PQ, K, PQ->N);
}

Item PQmin(struct pq_st *PQ)
{
  Item *v = PQ->pq;
  if (less(v[PQ->N - 1], v[PQ->N]))
    return v[PQ->N - 1];
  return v[PQ->N];
}

int PQfull(struct pq_st *PQ)
{
  return PQ->N >= PQ->capacity;
}

void PQprint(struct pq_st *PQ)
{
  for (int i = 1; i < PQ->N; i++)
  {
    coord_t c = PQ->pq[i];
    LOG("(%d, %d) -> %d, ", c.x, c.y, c.pontos);
  }
  LOG("\n");
}


#endif // PQ_H_INCLUDED