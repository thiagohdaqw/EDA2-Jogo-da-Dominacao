#ifndef SONDCOORD_H_INCLUDED
#define SONDCOORD_H_INCLUDED

#include "coord.h"


typedef struct SondCoord
{
  Coord coord;
  long int pontos;
} SondCoord;

#define Item SondCoord
#define pq_key(A) ((A).pontos)
#define less(A, B) (pq_key(A) < pq_key(B))
#define equal(A, B) (pq_key(A) < pq_key(B))


#endif // SONDCOORD_H_INCLUDED