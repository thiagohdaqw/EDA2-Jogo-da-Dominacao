#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED

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


#endif // PQ_H_INCLUDED