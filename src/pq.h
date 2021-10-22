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
  int min;
};

int fixUp(struct pq_st *PQ, int K)
{
  Item *v = PQ->pq;
  int indice = K;

  while (K > 1 && less(v[K / 2], v[K]))
  {
    if(K/2 == PQ->min)
      PQ->min = K;
    exch(v[K], v[K / 2]);
    K = K / 2;
    indice = K;
  }
  return indice;
}

int fixDown(struct pq_st *PQ, int K, int N)
{
  Item *v = PQ->pq;
  int j, indice;
  while (2 * K <= N)
  {
    j = 2 * K;
    if (j < N && less(v[j], v[j + 1]))
      j++;
    if (!less(v[K], v[j]))
      break;
    if(j == PQ->min)
      PQ->min = j;
    exch(v[K], v[j]);
    K = j;
    indice = K;
  }
  return indice;
}

void PQinit(struct pq_st *PQ, int maxN)
{
  PQ->capacity = maxN;
  PQ->pq = (Item *)malloc(sizeof(Item) * (PQ->capacity + 1));
  PQ->N = 0;
  PQ->min = 0;
}

int PQempty(struct pq_st *PQ)
{
  return PQ->N == 0;
}

Item PQmin(struct pq_st *PQ)
{
  return PQ->pq[PQ->min];
}

void PQinsert(struct pq_st *PQ, Item novo)
{
  PQ->pq[++PQ->N] = novo;
  int indice = fixUp(PQ, PQ->N);
  
  if(PQ->N == 1)
    PQ->min = 1;
  else if (less(novo, PQmin(PQ)))
    PQ->min = indice;
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
  int indice = fixDown(PQ, K, PQ->N);
  if(less(PQ->pq[indice], PQmin(PQ)))
    PQ->min = indice;
}

void PQchangeMin(struct pq_st *PQ, Item novo){
  PQ->pq[PQ->min] = novo;
  PQchange(PQ, PQ->min);
}

int PQfull(struct pq_st *PQ)
{
  return PQ->N >= PQ->capacity;
}


#endif // PQ_H_INCLUDED